#include "Context.h"

using namespace strange::extensions::context::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{

void* Context::getcontextView() const
{
	return privatecontextView;
}

void Context::setcontextView(void* value)
{
	privatecontextView = value;
}

IContext* Context::firstContext;

Context::Context()
{
}

Context::Context(void* view, ContextStartupFlags flags)
{
	//If firstContext was unloaded, the contextView will be null. Assign the new context as firstContext.
	if(firstContext == nullptr || firstContext->GetContextView() == nullptr)
	{
		firstContext = this;
	}
	else
	{
		firstContext->AddContext(this);
	}
	SetContextView(view);
	addCoreComponents();
	this->autoStartup = (flags & ContextStartupFlags::MANUAL_LAUNCH) != ContextStartupFlags::MANUAL_LAUNCH;
	if((flags & ContextStartupFlags::MANUAL_MAPPING) != ContextStartupFlags::MANUAL_MAPPING)
	{
		Start();
	}
}

Context::Context(void* view) : Context(view, ContextStartupFlags::AUTOMATIC)
{
}

Context::Context(void* view, bool autoMapping) : Context(view, (autoMapping) ? ContextStartupFlags::MANUAL_MAPPING : ContextStartupFlags::MANUAL_LAUNCH | ContextStartupFlags::MANUAL_MAPPING)
{
}

void Context::addCoreComponents()
{
}

void Context::instantiateCoreComponents()
{
}

IContext* Context::SetContextView(void* view)
{
	setcontextView(view);
	return this;
}

void* Context::GetContextView()
{
	return getcontextView();
}

IContext* Context::Start()
{
	instantiateCoreComponents();
	mapBindings();
	postBindings();
	if(autoStartup)
	{
		Launch();
	}
	return this;
}

void Context::Launch()
{
}

void Context::mapBindings()
{
}

void Context::postBindings()
{
}

IContext* Context::AddContext(IContext* context)
{
	return this;
}

IContext* Context::RemoveContext(IContext* context)
{
	//If we're removing firstContext, set firstContext to null
	if(context == firstContext)
	{
		firstContext = nullptr;
	}
	else
	{
		context->OnRemove();
	}
	return this;
}

template<typename T>
void* Context::GetComponent()
{
	return nullptr;
}

template<typename T>
void* Context::GetComponent(void* name)
{
	return nullptr;
}

void Context::AddView(void* view)
{
	//Override in subclasses
}

void Context::RemoveView(void* view)
{
	//Override in subclasses
}
}
}
}
}
