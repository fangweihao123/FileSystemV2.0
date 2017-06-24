#include "FileView.h"

void FileView::Update()
{
	for(int i=0;i<filemodel->textVec.size();i++)
		window->draw(filemodel->textVec[i]);
}

void FileView::textViewUpdate()
{
	for (int j = 0; j < filemodel->editorText.size(); j++)
		textWindow->draw(filemodel->editorText[j]);
}