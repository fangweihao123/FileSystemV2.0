#pragma once
#include<string>
//#include "../Controller/FileController.h"
//#include "Directory.h"

class FCB
{
public:
	friend class Directory;
	friend class FileController;
	FCB() {}
	FCB(std::string _filename, int _startAddress) :filename(_filename), startAddress(_startAddress), length(1), next(NULL) {}
private:
	std::string filename;
	int startAddress;
	int length;
	FCB* next;
};

class Directory
{
	public:
		friend class FileController;
		Directory(){}
		Directory(std::string dirName,int depth) {
			Child = NULL;
			Sibling = NULL;
			FCBhead = NULL;
			name = dirName;
			offset = depth * 10;
		}
		bool createFile(std::string name,int* FAT,int* BITVector);
		void createFile(std::string name, int start);
		Directory* searchName(std::string& str);
		bool searchFile(std::string& name);
		Directory* findDir(std::string &str);
		void Ls(std::string &listInfo);
		void addChild(Directory* child,int &depth);
		void addSibling(Directory* sibling);
	private:
		std::string name;
		Directory* Child;
		Directory* Sibling;
		FCB* FCBhead;
		FCB* current;
		int offset;
};