#pragma once
#include <string>
#include "../Controller/FileController.h"

class PhysicalBlock
{
	public:
		friend class FileController;
		PhysicalBlock(){}
	private:
		//int index;
		std::string content;								//assume that every physicalblock can only contain one char
};