#pragma once
#include <SFML/Graphics.hpp>
#include "../Controller/FileController.h"
#include "ViewBase.h"

class FileModel;
class FileView :public ViewBase				//������private����Ļ���ָ��ָ��������ָ�룬ʵ�ֶ�̬��
{
	public:
		FileView(FileModel *_filemodel,sf::RenderWindow *renderwindow, sf::RenderWindow *textwindow):filemodel(_filemodel),window(renderwindow),textWindow(textwindow){}			//the pointer is point to the main scene
		static void initUpdate();
		void Update();
		void textViewUpdate();
	private:
		FileModel *filemodel;
		sf::RenderWindow *window;
		sf::RenderWindow *textWindow;
};