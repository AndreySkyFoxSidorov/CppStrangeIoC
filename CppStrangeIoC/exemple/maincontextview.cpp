#include "MainContextView.h"
#include "MainContextInput.h"

using namespace strange::extensions::context::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;

bool MainContextView::isPauseDisable = false;
MainContextView *MainContextView::instance = nullptr;
IEventDispatcher *MainContextView::strangeDispatcher = nullptr;

void MainContextView::Start()
{
	GameObject::DontDestroyOnLoad(this);
	instance = this;
	isRunContext = false;
}

void MainContextView::DispatchStrangeEvent(void *eventType)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->Dispatch(eventType);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

void MainContextView::DispatchStrangeEvent(void *eventType, void *data)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->Dispatch(eventType, data);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

void MainContextView::AddListenerStrangeEvent(void *evt, EventCallback *callback)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->AddListener(evt, callback);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

void MainContextView::AddListenerStrangeEvent(void *evt, EmptyCallback *callback)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->AddListener(evt, callback);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

void MainContextView::RemoveListenerStrangeEvent(void *evt, EmptyCallback *callback)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->RemoveListener(evt, callback);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

void MainContextView::RemoveListenerStrangeEvent(void *evt, EventCallback *callback)
{
	if (strangeDispatcher != nullptr)
	{
		strangeDispatcher->RemoveListener(evt, callback);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
}

bool MainContextView::HasListenerStrangeEvent(void *evt, EventCallback *callback)
{
	if (strangeDispatcher != nullptr)
	{
		return strangeDispatcher->HasListener(evt, callback);
	}
	else
	{
		Log->Error(L"strangeDispatcher Not Redy");
	}
	return false;
}

void MainContextView::OnGUI()
{
	if (context != nullptr)
	{
		(dynamic_cast<MainContextInput*>(context))->OnGUI();
	}
}

void MainContextView::Update()
{
	if (!isRunContext)
	{
		isRunContext = true;
		MonoBehaviour *view = this;
		if (view != nullptr)
		{
			context = new MainContextInput(view);
			context::Start();
		}
		else
		{
			Log->Error(L"MonoBehaviour == NULL & MainContextInput == NULL! ERROR context Not Started");
		}
	}
	else
	{
		if (context != nullptr)
		{
			(dynamic_cast<MainContextInput*>(context))->Update();
			if (strangeDispatcher == nullptr)
			{
				if ((dynamic_cast<MainContextInput*>(context))->dispatcher != nullptr)
				{
					strangeDispatcher = (dynamic_cast<MainContextInput*>(context))->dispatcher;
				}
			}
		}
	}
}

void MainContextView::FixedUpdate()
{
	if (context != nullptr)
	{
		(dynamic_cast<MainContextInput*>(context))->FixedUpdate();
	}
}

void MainContextView::LateUpdate()
{
	if (context != nullptr)
	{
		(dynamic_cast<MainContextInput*>(context))->LateUpdate();
	}
}

void MainContextView::OnApplicationPause(bool pauseStatus)
{
}
