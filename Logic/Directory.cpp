#include "Directory.h"

void Directory::addChild(Directory* child,int &depth)			//depth的层数表明其实的位置
{
	if (Child == NULL)
	{
		depth++;
		Child = child;
	}
	else
	{
		Child->addSibling(child);
	}
}

void Directory::addSibling(Directory* sibling)
{
	if (Sibling != NULL)
	{
		Sibling->addSibling(sibling);
	}
	else
	{
		Sibling = sibling;
	}
	return;
}

bool Directory::createFile(std::string name,int* FAT,int *BITVector)
{
	int i = offset-1;
	for ( ; ; i++)
	{
		if (BITVector[i] == 0)
			break;
	}
	if (FCBhead == NULL)
	{
		FCBhead = new FCB(name, i);
		current = FCBhead;
	}
	else
	{
		current->next = new FCB(name, i);
		current = current->next;
	}
	BITVector[i] = 1;
	FAT[i] = -2;												//-2表示的是文件的结束
	return true;												//文件创建成功 返回true值
}

void Directory::createFile(std::string name, int start)
{
	if (FCBhead == NULL)
	{
		FCBhead = new FCB(name, start);
		current = FCBhead;
	}
	else
	{
		current->next = new FCB(name, start);
		current = current->next;
	}
}

Directory* Directory::searchName(std::string &str)
{
	if (Child == NULL)
		return false;
	Directory* temp = Child;
	do
	{
		if (temp->name == str)
			return temp;
		temp = temp->Sibling;
	} while (temp != NULL);

	return NULL;
}

Directory* Directory::findDir(std::string &str)
{
	Directory* pre=NULL;
	if (Child == NULL)
		return NULL;
	Directory* temp = Child;
	do
	{
		if (temp->name == str)
		{
			return temp;
		}
		temp = temp->Sibling;
	} while (temp != NULL);
	return NULL;
}

void Directory::Ls(std::string &listInfo)
{
	if (Child == NULL&& FCBhead == NULL)
	{
		listInfo = "This directory doesn't contain any other dire.";
		return;
	}
	else
	{
		if (Child != NULL)
		{
			Directory* temp = Child;
			listInfo.append("Sub Directory--- ");
			do
			{
				listInfo.append(temp->name + " ");
				temp = temp->Sibling;
			} while (temp!= NULL);
		 }

		if (FCBhead != NULL)
		{
			FCB* tempFCB = FCBhead;
			listInfo.append(" Sub file--- ");
			do
			{
				listInfo.append(tempFCB->filename + " ");						//because FCB is the friend class of Directory
				tempFCB = tempFCB->next;
			} while (tempFCB!=NULL);
		}

	}
}

bool Directory::searchFile(std::string& name)
{
	for (FCB* temp = FCBhead; temp != NULL; temp = temp->next)
	{
		if (temp->filename == name)
			return true;
	}
	return false;
}