#pragma once







namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IMediator
{
	/// Get/set the GameObject that represents the top-most item in this Context
public:
	virtual GameObject* getcontextView() const = 0;
	virtual void setcontextView( GameObject* value ) = 0;

	/// This method fires immediately after instantiation, but before injection.
	/// Override to handle anything that needs to happen prior to injection.
	virtual void PreRegister() = 0;

	/// This method fires immediately after injection.
	/// Override to perform the actions you might normally perform in a constructor.
	virtual void OnRegister() = 0;

	/// This method fires just before a GameObject will be destroyed.
	/// Override to clean up any listeners, or anything else that might keep the View/Mediator pair from being garbage collected.
	virtual void OnRemove() = 0;
};
}
}
}
}

