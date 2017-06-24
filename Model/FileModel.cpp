#include "FileModel.h"

FileModel::FileModel()
{
	currentNode = new Directory("root",0);
	root = currentNode;
	depth = 0;
	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		FAT[i] = -1;
		BITVector[i] = 0;				//0 means this physicalblock is empty
	}
	//physicalList = new PhysicalBlock[BLOCK_NUMBER];

}

void FileModel::Notify()
{
	view->Update();
}

void FileModel::Attach(ViewBase *_view)
{
	view = _view;
}

