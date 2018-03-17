





#include "MainContextInput.h"
#include "Events.h"


using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::context::impl;
using namespace strange::extensions::mediation::api;
using namespace strange::extensions::mediation::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace UnityEngine::EventSystems;
using namespace UnityEngine::SceneManagement;

MainContextInput::MainContextInput(MonoBehaviour *contextView) : MainContextRoot(contextView)
{
}

IContext *MainContextInput::Start()
{
	IContext *c = MainContextRoot::Start();
	return c;
}

void MainContextInput::Update()
{
	if (dispatcher != nullptr)
	{
		UpdateInput();
		dispatcher::Dispatch(EventGlobal::E_AppUpdate, Time->deltaTime);
	}
	else
	{
		Log->Error(L"Update ERROR!!! dispatcher == null");
	}
}

void MainContextInput::FixedUpdate()
{
	if (dispatcher != nullptr)
	{
		dispatcher::Dispatch(EventGlobal::E_AppFixedUpdate, Time->deltaTime);
	}
	else
	{
		Log->Error(L"FixedUpdate ERROR!!! dispatcher == null");
	}
}

void MainContextInput::LateUpdate()
{
	if (dispatcher != nullptr)
	{
		dispatcher::Dispatch(EventGlobal::E_AppLateUpdate, Time->deltaTime);
	}
	else
	{
		Log->Error(L"LateUpdate ERROR!!! dispatcher == null");
	}
}

void MainContextInput::OnGUI()
{

}

void MainContextInput::UpdateInput()
{
	// Android beack button
	if (Input->GetKeyDown(KeyCode::Escape))
	{
		Log->Write(L"Escape Key EVENT");
		dispatcher::Dispatch(EventGlobal::E_AppBackButton);
	}
	//
}
