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
	public:													//����֮ǰ����FIFO()�����ĺ��� �� FIFO ����Controller�����		
		friend class FileView;								//��view����Ԫ������Ϊ view��Ҫ�����������������ʾ controller������Ҫ�޸����������
		friend class FileController;
		FileModel();
		void Notify();
		void Attach(ViewBase *_view);
		void Detach(){}
	private:												//private�����ŵ�Ӧ�����߼����
		ViewBase* view;
		std::string userName;
		vector<sf::Text> textVec;							//�����text�����¼�ľ��������string	����getstring�õ�
		vector<sf::Text> editorText;
		Directory* currentNode;
		Directory* root;
		int depth;											//indicate the depth of the tree
		int FAT[BLOCK_NUMBER];								//FATλ�� -1��ʾ��λΪ�� -2ΪEOF
		int BITVector[BLOCK_NUMBER];						//λͼ
		PhysicalBlock disk[BLOCK_NUMBER];
};