#pragma once
using namespace strange::extensions::context::api;
using namespace strange::extensions::mediation::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class Mediator : public MonoBehaviour, public IMediator
{
private:
	GameObject* privatecontextView;


public:
	GameObject* getcontextView() const;
	void setcontextView( GameObject* value );

	Mediator();

	/**
	 * Fires directly after creation and before injection
	 */
	virtual void PreRegister();

	/**
	 * Fires after all injections satisifed.
	 *
	 * Override and place your initialization code here.
	 */
	virtual void OnRegister();

	/**
	 * Fires on removal of view.
	 *
	 * Override and place your cleanup code here
	 */
	virtual void OnRemove();
};
}
}
}
}

