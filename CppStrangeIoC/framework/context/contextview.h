#pragma once








using namespace strange::extensions::context::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class ContextView : public MonoBehaviour, public IContextView
{
private:
	IContext* privatecontext;
	bool privaterequiresContext = false;
	bool privateregisteredWithContext = false;
	bool privateautoRegisterWithContext = false;

public:
	IContext* getcontext() const;
	void setcontext( IContext* value );

	ContextView();

	/// <summary>
	/// When a ContextView is Destroyed, automatically removes the associated Context.
	/// </summary>
protected:
	virtual void OnDestroy();

	//	#region IView implementation

public:
	bool getrequiresContext() const;
	void setrequiresContext( const bool& value );

	bool getregisteredWithContext() const;
	void setregisteredWithContext( const bool& value );

	bool getautoRegisterWithContext() const;
	void setautoRegisterWithContext( const bool& value );

	//	#endregion
};
}
}
}
}

