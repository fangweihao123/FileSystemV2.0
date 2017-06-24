#include "FileController.h"

void convertCharToStr(char* name, std::string &str)
{
	for (int i = 0; i < strlen(name); i++)
	{
		str.push_back(name[i]);
	}
}

void convertCharToInt(char *value, int &result)
{
	result = 0;
	for (int i = strlen(value); i >0; i--)
	{
		result += (value[i - 1] - '0')*pow(10, i - 1);
	}
}

void convertStrToChar(std::string &str,char *name)
{
	for (int i = 0; i < str.size(); i++)
	{
		name[i] = str[i];
	}
}

void convertIntToChar(int start, char *value)
{
	int startTemp = start;
	int remainder = 0;
	int length = 0;
	if (start == 0)
		value[0] = '0';
	for (; startTemp != 0;)
	{
		length++;
		startTemp = startTemp / 10;
	}
	for (int i = length-1; i >=0 ; i--)
	{
		remainder = start % 10;
		value[i] = remainder+'0';
		start=start / 10;
	}
}


bool SpilitSlash(std::string path, std::string &front, std::string &back)			//true means it contains the '/'
{
	int i = 0;
	int count = 0;
	for (; i < path.size(); i++)
	{
		if (path[i] == '/')
		{
			count++;
			break;
		}
	}
	if (!count)
		return false;
	front.append(path, 0, i);
	back.append(path, i + 1, path.size() - i - 1);
	return true;
}


void Spilit(std::string &line, std::string &command, std::string &name)
{
	int flag = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			flag = 1;
			continue;
		}

		if (!flag)
		{
			command.push_back(line[i]);
		}
		else
		{
			name.push_back(line[i]);
		}
	}
}

void FileController::Register(ModelBase *_model, ViewBase *_view)
{
	_model->Attach(_view);
}

void FileController::init()
{
	std::string str = "Welcome to the file management system !" + filemodel->userName;
	text.setString(str);
	text.setFont(MyFont::font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color(0, 0, 0));
	text.setPosition(0,0);
	filemodel->textVec.push_back(text);
	text.setString("");
	text.setPosition(0, 20);
	filemodel->textVec.push_back(text);
	pushText("You can enter GET to get detailed instructions!");
	text.setString("");
	text.setPosition(0, 0);
	filemodel->editorText.push_back(text);
}

void FileController::KeyboardListener(sf::Event &event,std::string &str,sf::RenderWindow &window,int &flag)
{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == 13)						
			{
				text.setString("Po:>");
				text.setPosition(0, 20 * filemodel->textVec.size());
				filemodel->textVec.push_back(text);
				wordAnalyze(str, window,flag);
				str.clear();
				str = "Po:>";
				return;
			}
			if (event.text.unicode == 8)
			{
				if (str.length() > 4)
				{
					str.pop_back();
					filemodel->textVec[filemodel->textVec.size() - 1].setString(str);
				}
				return;
			}
			if (event.text.unicode < 128)
			{
				str.push_back((char)event.text.unicode);
				filemodel->textVec[filemodel->textVec.size()-1].setString(str);
			}
		}
}

void FileController::TextKeyboardListener(sf::Event &event, std::string &str,int &flag)			//这个STR被clear了
{
	str = filemodel->editorText[filemodel->editorText.size() - 1].getString();
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == 13)							//这是回车键
		{
			text.setString("");
			text.setPosition(0, 20*filemodel->editorText.size());
			filemodel->editorText.push_back(text);
			str.clear();
			return;
		}
		if (event.text.unicode == 8)							//这是delete键
		{
			if(str.size()>0)
			{
				str.pop_back();
				filemodel->editorText[filemodel->editorText.size() - 1].setString(str);
				return;
			}
		}
		if (event.text.unicode < 128)
		{
			str.push_back((char)event.text.unicode);
			filemodel->editorText[filemodel->editorText.size() - 1].setString(str);
			//filemodel->
		}
	}

}

void FileController::wordAnalyze(std::string &str, sf::RenderWindow &window,int &flag)						//you only need to analyze the latest instruction so there is no need for parameter
{
	std::string command, name,firstName,listInfo;
	Spilit(str, command, name);
	commandName = name;
	std::cout << name.size() << std::endl;
	std::cout << command << std::endl << name << std::endl;
	switch (commandNumber(command))
	{
		case -1:
			pushText("The command you require doesn't exist,or you write it in wrong format!");
			break;
		case 0:															//get gelp
			pushText("1.format----format your disk   2.mkdir----make sub directory  3.rmdir----remove sub direc");
			pushText("4.ls----list all the files and sub directory   5.cd----enter the specific path directory");
			pushText("6.touch----create a new file   7.open----open the files   8.cat----show the content of file");
			pushText("9.rm----remove specific file   10.quit----quit the file system");
			break;
		case 1:															//format  focus on FAT 

			break;
		case 2:															//mkdir
			if (name != "")
			{
				filemodel->currentNode->addChild(new Directory(name, filemodel->depth), filemodel->depth);					//成功塞入
				pushText("You have created a directory named " + name);
			}
			else
				pushText("The command you require doesn't exist,or you write it in wrong format!");
			break;
		case 3:															//rmdir
			if (Rmdir(name)!=NULL)
			{
				pushText("Done!");
			}
			else
			{
				pushText("The " + name + " you require to delete doesn't exist!");
			}
			break;
		case 4:															//ls
			filemodel->currentNode->Ls(listInfo);
			pushText(listInfo);
			break;
		case 5:															//cd
			if (name=="root")
			{
				filemodel->currentNode = filemodel->root;
				pushText("Trace back to the root");
				break;
			}
			firstName.append(name, 0, 5);
			if (firstName == "root/")
			{
				filemodel->currentNode = filemodel->root;
				name.erase(0, 5);
			}
			if (searchPath(name))								//如果return true 就是存在的 return false  就是不存在的
			{
				pushText("exist");
			}
			else
			{
				pushText("not exist");
			}
			break;
		case 6:															//touch
			if (name != "")
			{
				filemodel->currentNode->createFile(name, filemodel->FAT, filemodel->BITVector);
				pushText("You have created a new file named " + name);
			}
			else
				pushText("The command you require doesn't exist,or you write it in wrong format!");
			break;
		case 7:															//open  文件的扩张和重新读取
			if (filemodel->currentNode->searchFile(name))
			{
				loadFile(name);
				flag = 0;
				pushText("You've open file " + name);
			}
			else
			{
				pushText("Can't find the target file!");
			}
			break;
		case 8:															//close	what i am thinking about is that you call close() function in the text view
																		//and it the same the as save function i think this function is useless
			break;
		case 9:															//cat read from file
			if (filemodel->currentNode->searchFile(name))
			{
				std::string content="aaaaa";
				pushText("");
				fileContent(name);
			
			}
			else
			{
				pushText("Can't find the target file!");
			}
			break;
		case 10:														//rm  remove file 
			if (filemodel->currentNode->searchFile(name))
			{
				deleteFile(name,filemodel->currentNode);									//可以delete掉name
				pushText(name + " has been eliminated");
			}
			else
			{
				pushText("The file you want to delete doesn't exist");
			}
			break;
		case 11:														//quit	you should write everything into log including instruction history and directory structure
			window.close();												//我需要自己定义一个结构来存储这个结构
			SaveDisk();
			break;
		case 12:														//就输出一个空的
			pushText("");
			break;
	}
}

int FileController::commandNumber(std::string &str)
{
	for (int i = 0; i < 37 ; i++)
	{
		if (str==strArray[i])
		{
			return i / 3;
		}
	}
	return -1;
}

void FileController::pushText(std::string str)
{
	filemodel->textVec[filemodel->textVec.size() - 1].setString(str);
	text.setString("Po:>");
	text.setPosition(0, 20 * filemodel->textVec.size());
	filemodel->textVec.push_back(text);
}


void FileController::Save()					//这个save 贼烦  首先 如果内容是增加的话 需要从物理块里面拿出来 如果内容是减少的话 需要释放物理块 也就是位图  反正每次save的时候要重新扫描一次
{					
	int count = 0;
	int blockNumber;
	FCB* temp = filemodel->currentNode->FCBhead;											//在currentNode下面寻找file的名字
	for (; temp != NULL; temp = temp->next)
	{
		if (temp->filename == commandName)
			break;
	}
	blockNumber = temp->startAddress;
	for (int i = 0; i < filemodel->editorText.size(); i++)
	{
		for (int j = 0; j < filemodel->editorText[i].getString().getSize(); j++)
		{
			if (count == 2&& filemodel->FAT[blockNumber]==-2)
			{
				int z = 0;
				count = 0;
				for (; z < BLOCK_NUMBER; z++)
				{
					if (filemodel->BITVector[z] == 0)
						break;
				}
				filemodel->FAT[z] = -2;							//FAT也要修改
				filemodel->FAT[blockNumber] = z;
				filemodel->BITVector[z] = 1;
				blockNumber = z;
			}
			else if (count == 2 && filemodel->FAT[blockNumber] != -2)
			{
				count = 0;
				blockNumber = filemodel->FAT[blockNumber];
			}
			if ((filemodel->disk[blockNumber].content[count] == (filemodel->editorText[i].getString().toAnsiString(std::locale()))[j]) || filemodel->disk[blockNumber].content[count] == '-')
			{
				count++;
				continue;
			}
			else
			{
				count++;
				filemodel->disk[blockNumber].content.push_back((filemodel->editorText[i].getString().toAnsiString(std::locale()))[j]);
			}
		}
		if (count == 2)
			{
				int z = 0;
				count = 0;
				for (; z < BLOCK_NUMBER; z++)
				{
					if (filemodel->BITVector[z] == 0)
						break;
				}
				filemodel->FAT[z] = -2;							//FAT也要修改
				filemodel->FAT[blockNumber] = z;
				filemodel->BITVector[z] = 1;
				blockNumber = z;
			}
		if (i < filemodel->editorText.size()-1&&filemodel->FAT[blockNumber]==-2)
		{
			filemodel->disk[blockNumber].content.push_back('-');
			count++;
		}

	}
	filemodel->editorText.clear();
	text.setString("");
	text.setPosition(0, 0);
	filemodel->editorText.push_back(text);									//在这里重新init了一遍
}

bool FileController::Rmdir(std::string &name)					//需要判断这个文件夹是否存在		先判断是否存在 存在的话 就一个个删除子目录 删除子目录的时候 释放资源
{
	Directory* temp,*pre;
	pre = filemodel->currentNode->Child;
	temp=filemodel->currentNode->findDir(name);
	if (temp == NULL)
		return false;
	else
	{
		if(temp==filemodel->currentNode->Child)
			deleteDirectory(&filemodel->currentNode->Child);
		else
		{
			while (pre->Sibling != temp)
				pre = pre->Sibling;
			pre->Sibling = temp->Sibling;
			temp->Sibling = NULL;
			deleteDirectory(&temp);
		}
		return true;
	}

}

bool FileController::searchPath(std::string &path)
{
	std::string front, back;
	Directory* temp;
	if (SpilitSlash(path, front, back))
	{
		if ((temp = filemodel->currentNode->searchName(front)) == NULL)
			return false;
		else
		{
			filemodel->currentNode = temp;
			return searchPath(back);
		}
	}
	else
	{
		if ((temp = filemodel->currentNode->searchName(path)) == NULL)				//现在path里面没有斜杠
			return false;
		else
		{
			filemodel->currentNode = temp;
			return true;
		}
	}
}

void FileController::fileContent(const std::string& name)
{
	int address;
	std::string str;
	FCB* temp = filemodel->currentNode->FCBhead;
	for ( ; temp != NULL; temp = temp->next)
	{
		if (temp->filename == name)
		{
			break;
		}
	}
	address = temp->startAddress;
	while(filemodel->FAT[address]!=-2)							//-2 means the end of file
	{	
		catFile(str, address);
		//str.append(filemodel->disk[address].content);
		address = filemodel->FAT[address];
	}
	catFile(str, address);
}

void FileController::deleteFile(std::string &name,Directory *current)
{
	int address;
	FCB* pre;
	FCB* temp = current->FCBhead;
	pre = temp;
	if (temp->next == NULL)
	{
		address = temp->startAddress;
		delete(temp);
		current->FCBhead = NULL;
	}
	else
	{
		for (; temp != NULL; temp = temp->next)
		{
			if (temp->filename == name)
				break;
			pre = temp;
		}				//还需要释放掉资源
		address = temp->startAddress;
		pre->next = temp->next;
		delete(temp);
	}
	freeResource(address);
}

void FileController::deleteAllFile(Directory* current)
{
	std::string name;
	FCB* temp = current->FCBhead;
	if (temp == NULL)
		return;
	else
	{
		while (current->FCBhead != NULL)
		{
			temp = current->FCBhead;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			name = temp->filename;
			deleteFile(name,current);
		}
	}
}

void FileController::loadFile(std::string &name)			//load fromfile实在open的时候使用的  因为之前save的时候已经把editortext清空了 所以要重新载入 但是save的时候 在最后一行又push了一个text
{
	std::string str;
	FCB* temp = filemodel->currentNode->FCBhead;
	for (; temp != NULL; temp = temp->next)
	{
		if (temp->filename == name)
			break;
	}
	int address = temp->startAddress;
	while (filemodel->FAT[address] != -2)
	{
		loadDisk(str, address);
		address = filemodel->FAT[address];
	}
	//-2 包含的内容也要打印出来
	loadDisk(str, address);
}

void FileController::loadDisk(std::string &str,int &address)
{
	for (int i = 0; i < filemodel->disk[address].content.size(); i++)
	{
		if (filemodel->disk[address].content[i] == '-')
		{
			str.clear();
			text.setString(str);
			text.setPosition(0, 20 * filemodel->editorText.size());
			filemodel->editorText.push_back(text);
		}
		else
		{
			str.push_back(filemodel->disk[address].content[i]);
			filemodel->editorText[filemodel->editorText.size() - 1].setString(str);
		}
	}
}

void FileController::catFile(std::string &str, int &address)
{
	for (int i = 0; i < filemodel->disk[address].content.size();i++)
	{
		if (filemodel->disk[address].content[i]=='-')
		{
			pushText("");
			str.clear();
		}
		else
		{
			str.push_back(filemodel->disk[address].content[i]);
			filemodel->textVec[filemodel->textVec.size() - 2].setString(str);					//为什么要减2呢 因为最后一行是我pushtext的时候新添加的命令行
		}
	}
}

void FileController::freeResource(int &startAddress)				//位图释放 FAT释放 disk释放
{
	int address = startAddress;
	int temp;
	while (filemodel->FAT[address] != -2)
	{
		filemodel->BITVector[address] = 0;
		filemodel->disk[address].content.clear();
		temp = filemodel->FAT[address];
		filemodel->FAT[address] = -1;
		address = temp;
	}
	filemodel->BITVector[address] = 0;
	filemodel->disk[address].content.clear();
	filemodel->FAT[address] = -1;
}

void FileController::SaveDisk()
{
	int i;
	std::ofstream out;
	out.open("Table.txt");
	for (i= 0; i < BLOCK_NUMBER; i++)
	{
		out << filemodel->FAT[i] << " ";
	}
	out << std::endl;
	for (i = 0; i < BLOCK_NUMBER; i++)
	{
		if (filemodel->disk[i].content.size() >=1)
		{
			out << filemodel->disk[i].content << " ";
		}
		else if (filemodel->disk[i].content.empty())
		{
			out << "__ ";
		}
	}
	out << std::endl;
	for (i = 0; i < BLOCK_NUMBER; i++)
	{
		out << filemodel->BITVector[i]<<" ";
	}

	out.close();

	//xml_document<> doc;
	xml_node<> *node;														//node type  name  value
	node = doc.allocate_node(node_element, "A");
	filemodel->currentNode = filemodel->root;
	saveDire(&node, filemodel->currentNode);
	doc.append_node(node);
	//doc.append_node(node);
	//filemodel->currentNode = filemodel->root;
	out.open("Configuration.txt");
	out << doc;
	out.close();
}

void FileController::loadInit(const char *config,const std::string &table)
{
	int i;
	std::string temp;
	std::string line;
	std::ifstream infile1, infile2;
	infile1.open(table);
	infile1.seekg(0, infile1.end);
	fstream::off_type Len = infile1.tellg();
	if (Len == 0)
		return;
	infile1.seekg(0, infile1.beg);
	getline(infile1, line);
	std::stringstream ss(line);
	for (i = 0; i < BLOCK_NUMBER; i++)
	{
		ss >> filemodel->FAT[i];
	}
	getline(infile1, line);
	ss.str(line);
	for (i = 0; i < BLOCK_NUMBER; i++)
	{
		ss >> temp;
		if (temp == "__")
			continue;
		else
			filemodel->disk[i].content = temp;
	}
	getline(infile1, line);
	ss.str(line);
	for (i = 0; i < BLOCK_NUMBER; i++)
	{
		ss >> filemodel->BITVector[i];
	}
	infile1.close();
	
	//infile2.open("Configuration.txt"); 
	file<> fdoc(config);
	xml_document <> doc;
	doc.parse<0>(fdoc.data());
	xml_node<> *node = doc.first_node();				//root 因为root已经存在了
	inOrderConstruct(node,&(filemodel->root),1);
}

void FileController::deleteDirectory(Directory** dir)					//还要删掉自己
{
	if ((*dir)->Child == NULL)
	{
		Directory* temp = *dir;			//如果delete掉了 那就找不到temp了
		deleteAllFile(temp);
		if ((*dir)->Sibling != NULL)
			(*dir) = (*dir)->Sibling;
		else
			(*dir) = NULL;
		delete(temp);												//只是去除了指针

	}
	else
	{
		Directory* temp = (*dir)->Child;
		for (; temp != NULL; )
		{
			deleteDirectory(&temp);
		}
		(*dir)->Child = NULL;
		deleteAllFile((*dir));
		delete((*dir));
		(*dir) = NULL;
	}
}

void FileController::inOrderConstruct(xml_node<> *node, Directory** point, int i)
{
	int count = 0;
	int countdown = 0;
	std::string name;
	int startAddress;
	xml_attribute<> *attr = node->first_attribute();
	while (attr != NULL)
	{
		count++;
		if (count==1)
		{
			convertCharToStr(attr->value(), name);
			*point = new Directory(name, i);
		}
		else
		{
			if (count % 2)									//file length
			{
				convertCharToInt(attr->value(), startAddress);
				countdown++;
			} 
			else											//file name
			{
				name.clear();
				convertCharToStr(attr->value(), name);
				countdown++;
			}
			if (countdown == 2)
			{
				(*point)->createFile(name, startAddress);
				countdown = 0;
			}
		}
		attr = attr->next_attribute();
	}
	i++;
	if (node->first_node()->first_node() != NULL)
		inOrderConstruct(node->first_node(), &((*point)->Child), i);
	if (node->next_sibling() != NULL)
		inOrderConstruct(node->next_sibling(), &((*point)->Sibling), i);


}

void FileController::saveDire(xml_node<> **node,Directory* temp)				//this node is   
{
	//xml_document<> doc;
	//xml_node<> *nodeChild = (*node)->first_node();
	//xml_node<> *nodeSibling = (*node)->next_sibling();
	char name[10] = { '\0' };			//存在内存释放问题
	//(*node) = doc.allocate_node(node_element,"A","1");											//name and value


	convertStrToChar(temp->name, name);
	char *port = doc.allocate_string(name, 10);
	(*node)->append_attribute(doc.allocate_attribute("Directory", port));
	addFileToAttr(node,temp);
	if (temp->Child != NULL)
	{
		(*node)->append_node(doc.allocate_node(node_element, "A","1"));
		xml_node<> *nodeChild = (*node)->first_node();
		saveDire(&nodeChild,temp->Child);
	}
	if (temp->Sibling != NULL)
	{
		(*node)->parent()->append_node(doc.allocate_node(node_element, "A","1"));
		xml_node<> *nodeSibling = (*node)->next_sibling();
		saveDire(&nodeSibling,temp->Sibling);
	}
}

void FileController::addFileToAttr(xml_node<> **node, Directory* temp)
{
	char *temp1, *temp2;
	char name[10] = { '\0' };
	char value[10] = { '\0' };
	if (temp->FCBhead == NULL)
	{
		return;
	}
	else
	{
		FCB* current = temp->FCBhead;
		while (current != NULL)
		{
			convertIntToChar(current->startAddress, value);
			convertStrToChar(current->filename, name);
			temp1 = doc.allocate_string(name, 10);
			temp2 = doc.allocate_string(value, 10);
			(*node)->append_attribute(doc.allocate_attribute("file",temp1));
			(*node)->append_attribute(doc.allocate_attribute("length", temp2));
			current = current->next;
			for (int i = 0; i < strlen(name); i++)
				name[i] = '\0';
			for (int i = 0; i < strlen(value); i++)
				value[i] = '\0';
		}
		//(*node)->append_attribute(doc.allocate_attribute("a", "a.c"));
	}
}