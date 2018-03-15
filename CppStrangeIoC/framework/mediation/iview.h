#pragma once






namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IView
{
	/// Indicates whether the View can work absent a context
	///
	/// Leave this value true most of the time. If for some reason you want
	/// a view to exist outside a context you can set it to false. The only
	/// difference is whether an error gets generated.
public:
	virtual bool getrequiresContext() const = 0;
	virtual void setrequiresContext( const bool& value ) = 0;

	/// Indicates whether this View  has been registered with a Context
	virtual bool getregisteredWithContext() const = 0;
	virtual void setregisteredWithContext( const bool& value ) = 0;

	/// Exposure to code of the registerWithContext (Inspector) boolean. If false, the View won't try to register.
	virtual bool getautoRegisterWithContext() const = 0;
};
}
}
}
}

