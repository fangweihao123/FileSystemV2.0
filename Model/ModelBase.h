#pragma once
class ViewBase;
class ModelBase
{
	public:
		friend class FileController;
		ModelBase() {}
		ModelBase(ViewBase *_view);
		virtual ~ModelBase(){}
		virtual void Notify()=0;
		virtual void Attach(ViewBase* _view)=0;
		virtual void Detach() = 0;

};