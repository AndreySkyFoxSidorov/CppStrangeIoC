#pragma once








using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::context::impl;
using namespace strange::extensions::mediation::api;
using namespace strange::extensions::mediation::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;

class MainContextRoot : public MVCSContext
{
public:
	MainContextRoot(MonoBehaviour *contextView);

protected:
	void addCoreComponents() override;

	// Commands and Bindings
	void mapBindings() override;
};
