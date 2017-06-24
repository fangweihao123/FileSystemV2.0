#pragma once
class ModelBase;
class ViewBase;
class ControllerBase
{
	public:
		ControllerBase(){}
		ControllerBase(ModelBase *_model);						//Controller ��ʵֻcontrol model���� Ȼ��model�ı���֮����notify view
		virtual ~ControllerBase(){}
		virtual void Register(ModelBase *_model, ViewBase *_view)=0;
};