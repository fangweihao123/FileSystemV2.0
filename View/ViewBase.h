#pragma once
#include <iostream>
using namespace std;

class ModelBase;
class ViewBase
{
	public:
		ViewBase(){}
		ViewBase(ModelBase *_model);
		virtual ~ViewBase(){}
		virtual void Update()=0;
};