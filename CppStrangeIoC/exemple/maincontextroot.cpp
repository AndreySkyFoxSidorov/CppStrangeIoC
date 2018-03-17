





#include "MainContextRoot.h"
#include "Events.h"


using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::context::impl;
using namespace strange::extensions::mediation::api;
using namespace strange::extensions::mediation::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;

MainContextRoot::MainContextRoot(MonoBehaviour *contextView) : MVCSContext(contextView,ContextStartupFlags::MANUAL_MAPPING)
{
}

void MainContextRoot::addCoreComponents()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// CoreComponents
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	MVCSContext::addCoreComponents();
	injectionBinder::Bind<ISFXManager*>().To<SFXManager*>().ToSingleton();
	injectionBinder::Bind<ILocalizationManager*>().To<LocalizationManager*>().ToSingleton();
	injectionBinder::Bind<ICoroutineExecutor*>().To<CoroutineExecutor*>().ToSingleton();
}

void MainContextRoot::mapBindings()
{
	MVCSContext::mapBindings();

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Mediator Init
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	Camera::main::gameObject::AddComponent<CameraView*>();
	mediationBinder::BindView<CameraView*>().ToMediator<CameraMediator*>();
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// System Commands
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	commandBinder::Bind(ContextEvent::START).To<AppLoadCommand*>().Pooled().InSequence().Once();
	//

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// UI
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	commandBinder::Bind(EventGlobal::E_UIPopUpShow).To<UIPopUpShowCommand*>().Pooled();
	commandBinder::Bind(EventGlobal::E_UIPopUpHide).To<UIPopUpHideCommand*>().Pooled();
	mediationBinder::BindView<UIPopUpView*>().ToMediator<UIPopUpMediator*>();

	commandBinder::Bind(EventGlobal::E_ShowWarning).To<UIWarningShowCommand*>().Pooled();


	commandBinder::Bind(EventGlobal::E_UISelectLevelShow).To<UISelectLevelShowCommand*>().Pooled();
	commandBinder::Bind(EventGlobal::E_UISelectLevelHide).To<UISelectLevelHideCommand*>().Pooled();
	mediationBinder::BindView<UISelectLevelView*>().ToMediator<UISelectLevelMediator*>();

	commandBinder::Bind(EventGlobal::E_UIStartShow).To<UIStartShowCommand*>().Pooled();
	commandBinder::Bind(EventGlobal::E_UIStartHide).To<UIStartHideCommand*>().Pooled();
	mediationBinder::BindView<UIStartView*>().ToMediator<UIStartMediator*>();
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	commandBinder::Bind(EventGlobal::E_LoadLevel).To<LoadLevelCommand*>().Pooled();
	commandBinder::Bind(EventGlobal::E_UnLoadLevel).To<UnLoadLevelCommand*>().Pooled();


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Facebook
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	commandBinder::Bind(EventGlobal::E_FBInvateFriends).To<FacebookLogInCommand*>().To<FacebookInvateFriends*>().InSequence().Pooled();
	//commandBinder.Bind(EventGlobal.E_FBInvateCancelled).To<>().InSequence().Pooled();
	//commandBinder.Bind(EventGlobal.E_FBInvateSuccess).To<>().InSequence().Pooled();
	commandBinder::Bind(EventGlobal::E_FBLogin).To<FacebookLogInCommand*>().InSequence().Pooled();
	commandBinder::Bind(EventGlobal::E_FBLogout).To<FacebookLogOutCommand*>().InSequence().Pooled();
	commandBinder::Bind(EventGlobal::E_FBSharing).To<FacebookLogInCommand*>().To<FacebookSharingCommand*>().InSequence().Pooled();
	//commandBinder.Bind(EventGlobal.E_FBSharingSuccess).To<>().InSequence().Pooled();
	//commandBinder.Bind(EventGlobal.E_FBSharingCancelled).To<>().InSequence().Pooled();
	///////////////////////////////////////////////////////////////////////////////////////////////////////

}
