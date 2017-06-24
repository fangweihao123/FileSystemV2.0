#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ModelBase.h"
#include "../View/ViewBase.h"
#include "../Logic/PhysicalBlock.h"
#include "../Logic/Directory.h"
#include "../Controller/FileController.h"
#include "../View/FileView.h"
#define BLOCK_NUMBER 100

class FileModel :public ModelBase
{
	public:													//比如之前就有FIFO()这样的函数 呸 FIFO 是在Controller里面的		
		friend class FileView;								//是view的友元类是因为 view需要里面的数据来进行显示 controller则是需要修改里面的数据
		friend class FileController;
		FileModel();
		void Notify();
		void Attach(ViewBase *_view);
		void Detach(){}
	private:												//private里面存放的应该是逻辑组件
		ViewBase* view;
		std::string userName;
		vector<sf::Text> textVec;							//输出的text里面记录的就是命令的string	可以getstring得到
		vector<sf::Text> editorText;
		Directory* currentNode;
		Directory* root;
		int depth;											//indicate the depth of the tree
		int FAT[BLOCK_NUMBER];								//FAT位表 -1表示该位为空 -2为EOF
		int BITVector[BLOCK_NUMBER];						//位图
		PhysicalBlock disk[BLOCK_NUMBER];
};