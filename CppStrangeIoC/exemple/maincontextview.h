#pragma once








using namespace strange::extensions::context::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;

class MainContextView : public strange::extensions::context::impl::ContextView
{
private:
	bool isRunContext = false;
public:
	static bool isPauseDisable;

	static MainContextView *instance;
	static IEventDispatcher *strangeDispatcher;


private:
	void Start();

public:
	static void DispatchStrangeEvent(void *eventType);

	static void DispatchStrangeEvent(void *eventType, void *data);

	static void AddListenerStrangeEvent(void *evt, EventCallback *callback);

	static void AddListenerStrangeEvent(void *evt, EmptyCallback *callback);

	static void RemoveListenerStrangeEvent(void *evt, EmptyCallback *callback);


	static void RemoveListenerStrangeEvent(void *evt, EventCallback *callback);

	static bool HasListenerStrangeEvent(void *evt, EventCallback *callback);


private:
	void OnGUI();

	void Update();

	void FixedUpdate();

	void LateUpdate();

	void OnApplicationPause(bool pauseStatus);

};
