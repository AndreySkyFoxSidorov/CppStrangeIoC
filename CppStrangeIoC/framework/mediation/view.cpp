





#include "View.h"


using namespace strange::extensions::context::api;
using namespace strange::extensions::context::impl;
using namespace strange::extensions::mediation::api;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

bool View::getrequiresContext() const
{
	return _requiresContext;
}

void View::setrequiresContext(const bool& value)
{
	_requiresContext = value;
}

bool View::getautoRegisterWithContext() const
{
	return registerWithContext;
}

void View::setautoRegisterWithContext(const bool& value)
{
	registerWithContext = value;
}

bool View::getregisteredWithContext() const
{
	return privateregisteredWithContext;
}

void View::setregisteredWithContext(const bool& value)
{
	privateregisteredWithContext = value;
}

void View::Awake()
{
	if(getautoRegisterWithContext() && !getregisteredWithContext())
	{
		bubbleToContext(this, true, false);
	}
}

void View::Start()
{
	if(getautoRegisterWithContext() && !getregisteredWithContext())
	{
		bubbleToContext(this, true, true);
	}
}

void View::OnDestroy()
{
	bubbleToContext(this, false, false);
}

void View::bubbleToContext(MonoBehaviour* view, bool toAdd, bool finalTry)
{
	constexpr int LOOP_MAX = 100;
	int loopLimiter = 0;
	Transform* trans = view->gameObject.transform;
	while(trans->parent != nullptr && loopLimiter < LOOP_MAX)
	{
		loopLimiter++;
		trans = trans->parent;
		if(trans->gameObject.GetComponent<ContextView*>() != nullptr)
		{
			ContextView* contextView = dynamic_cast<ContextView*>(trans->gameObject.GetComponent<ContextView*>());
			if(contextView->context != nullptr)
			{
				IContext* context = contextView->context;
				if(toAdd)
				{
					context->AddView(view);
					setregisteredWithContext(true);
					return;
				}
				else
				{
					context->RemoveView(view);
					return;
				}
			}
		}
	}
	if(getrequiresContext() && finalTry)
	{
		//last ditch. If there's a Context anywhere, we'll use it!
		if(Context::firstContext != nullptr)
		{
			Context::firstContext::AddView(view);
			setregisteredWithContext(true);
			return;
		}
	}
	if(getrequiresContext() && !finalTry && !toAdd)
	{
		//last ditch. If there's a Context anywhere, we'll use it!
		if(Context::firstContext != nullptr)
		{
			Context::firstContext::RemoveView(view);
			return;
		}
	}
}
}
}
}
}
