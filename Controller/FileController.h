#pragma once
#include "ControllerBase.h"
#include "../View/ViewBase.h"
#include "../Model/FileModel.h"
#include "../View/MyComponent.h"
#include "../View/FileView.h"
#include "../Logic/Directory.h"
#include "../rapidxml\rapidxml.hpp"
#include "../rapidxml\rapidxml_print.hpp"
#include "../rapidxml\rapidxml_utils.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace rapidxml;

class FileController :public ControllerBase
{
	public:
		//friend class ModelBase;
		FileController() {}
		FileController(FileModel *_filemodel) :filemodel(_filemodel){
			strArray = new std::string[37]{"Po:>get","Po:>Get","Po:>GET","Po:>format","Po:>Format","Po:>FORMAT","Po:>mkdir","Po:>Mkdir","Po:>MKDIR","Po:>rmdir","Po:>Rmdir","Po:>RMDIR",
				"Po:>ls","Po:>Ls","Po:>LS","Po:>cd","Po:>Cd","Po:>CD","Po:>touch","Po:>Touch","Po:>TOUCH",
				"Po:>open","Po:>Open","Po:>OPEN","Po:>close","Po:>Close","Po:>CLOSE","Po:>cat","Po:>Cat","Po:>CAT","Po:>rm","Po:>Rm","Po:>RM","Po:>quit","Po:>Quit","Po:>QUIT","Po:>"	
			};
		}
		void Register(ModelBase *_model,ViewBase *_view);
		void KeyboardListener(sf::Event &event,std::string &str,sf::RenderWindow &window,int &flag);
		void TextKeyboardListener(sf::Event &event, std::string &str,int &flag);												//close window inside function
		void wordAnalyze(std::string &str,sf::RenderWindow &window,int &flag);
		int commandNumber(std::string &str);
		void pushText(std::string str);
		void fileContent(const std::string &name);
		void deleteFile(std::string &name,Directory* current);
		void deleteAllFile(Directory* current);											//delete all the file within a direc
		void deleteDirectory(Directory** dir);												//delete the direc and sub-direc
		void loadFile(std::string &name);
		void loadInit(const char * config,const std::string &table);							//this function can load the initialization configuration of previous file system
		void SaveDisk();																//when you quit you need to store the structure of your file system
		void loadDisk(std::string &str,int &address);
		void catFile(std::string &str, int &address);
		bool Rmdir(std::string &name);
		bool searchPath(std::string &path);
		void freeResource(int &startAddress);					//free resource when you delete files
		void inOrderConstruct(xml_node<> *node,Directory** point,int i);
		void saveDire(xml_node<> **node,Directory* temp);
		void addFileToAttr(xml_node<> **node,Directory* temp);
		void Save();						//when editor is closed you need to save the content to the disk
		void init();
	private:
		FileModel *filemodel;
		sf::Text text;
		sf::Text viewtext;
		std::string *strArray;
		std::string commandName;
		xml_document<> doc;
};