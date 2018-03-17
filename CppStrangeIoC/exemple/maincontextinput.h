#pragma once







#include "MainContextRoot.h"


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

class MainContextInput : public MainContextRoot
{
public:
	MainContextInput(MonoBehaviour *contextView);

	IContext *Start() override;

	void Update();

	void FixedUpdate();

	void LateUpdate();

	void OnGUI();

	void UpdateInput();
};
