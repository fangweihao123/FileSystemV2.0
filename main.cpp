#include "Controller/FileController.h"
#include "Model/FileModel.h"
#include "View/FileView.h"
#include "View\MyComponent.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

int main(void)
{
	int flag = 1;
	std::string CMDLine="Po:>";
	std::string text;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Po's CLI", sf::Style::Titlebar);			//None is no decoration at all    titlebar only contain title  
	sf::RenderWindow textwindow(sf::VideoMode(800, 600), "Editor");
	sf::View standard = window.getView();
	textwindow.setPosition(sf::Vector2i(1000,240));
	textwindow.setVisible(false);
	window.setVerticalSyncEnabled(true);				//if your application run too fast that the app's refresh rate is not synchronized with vertical frequency of monitor
	window.setMouseCursorVisible(false);				//set the mousecursor invisible within the window
	window.setKeyRepeatEnabled(false);
	MyFont::loadFromFile("Resource/CENTURY.TTF");
	FileModel filemodel;
	FileView fileview(&filemodel,&window,&textwindow);
	FileController filecontroller(&filemodel);
	filecontroller.Register(&filemodel, &fileview);
	filecontroller.init();
	filecontroller.loadInit("Configuration.txt","Table.txt");
	while (window.isOpen())
	{
		std::cout << window.getSize().y << std::endl;
		std::cout << standard.getCenter().y << std::endl;
		sf::Event event, editorEvent;
		if (window.pollEvent(event)) {}					//because you have to listen the event happen in the main window
		if (textwindow.pollEvent(editorEvent))
		{
			if (editorEvent.type == sf::Event::Closed)
			{
				flag = 1;
				filecontroller.Save();
				text.clear();
			}
		}
		if (flag)
		{
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					if((standard.getCenter().y - window.getSize().y / 2)>0)
						standard.move(0, -20);
				}
				else
				{
					standard.move(0, 20);
				}
			}
			textwindow.setVisible(false);
			filecontroller.KeyboardListener(event, CMDLine, window, flag);
		}
		else
		{
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					standard.move(0, -20);
				}
				else
				{
					standard.move(0, 20);
				}
			}
			textwindow.setVisible(true);
			filecontroller.TextKeyboardListener(editorEvent, text, flag);
			fileview.textViewUpdate();
			textwindow.setView(standard);
			textwindow.display();
		}
		fileview.Update();
		window.setView(standard);
		window.display();							//显示出窗口上的物品
		window.clear(sf::Color(199, 223, 244));
		textwindow.clear(sf::Color::White);
		Sleep(70);
	}
	system("pause");
	return 0;
}

/*using namespace rapidxml;
int main()
{
	std::ifstream infile;
	//infile.open("Configuration.ini");
	file<>  fdoc("Configuration.txt");	
	//infile.close();
	char text[100] = {"<a href=\"xxx\">"            //both form is the same
		"<b>bbbbbb</b>"
		"<c>cccccccc</c>"
		"<d>ddddddddd</d>"
		"</a>"
	};
//	char text[100] = { "<a href=\"xxx\"><b>bbbbbb</b><c>cccccc</c><d>ddddddddd</d></a>"	};				//对中文不乱码 已经支持了
	xml_document<> doc;							//character type default to char
	doc.parse<0>(fdoc.data());							//0 means default parse flag
	for (xml_node<> *node = doc.first_node()->first_node(); node; node = node->next_sibling())
	{
		std::cout << node->value() << std::endl;
	}
	system("pause");
}*/


/*#include <string>							//to eliminate console window you there are three steps you need to do
#include <sstream>							//open the property option of your projects and within the property configuration you need to find pre-processor in the C/C++ and daa _WINDOWS
using namespace std;						//and in the linker option you need to find advance to add mainCRTStartup to the entrance last one is that you need to choose “Windows（/SUBSYSTEM:WINDOWS）”instead of (/SUBSYSTEM:CONSOLE) in the subsystem of system

int main()
{
	string line;
	while (getline(cin, line))
	{
		int sum = 0, x;
		stringstream ss(line);
		while (ss >> x) sum += x;
		cout << sum << endl;
	}
	return 0;
}*/