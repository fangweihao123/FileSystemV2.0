#pragma once
class ModelBase;
class ViewBase;
class ControllerBase
{
	public:
		ControllerBase(){}
		ControllerBase(ModelBase *_model);						//Controller 其实只control model罢了 然后model改变了之后再notify view
		virtual ~ControllerBase(){}
		virtual void Register(ModelBase *_model, ViewBase *_view)=0;
};