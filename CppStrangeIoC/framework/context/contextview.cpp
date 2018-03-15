#include "ContextView.h"
#include "Context.h"


using namespace strange::extensions::context::api;
namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{

IContext* ContextView::getcontext() const
{
	return privatecontext;
}

void ContextView::setcontext(IContext* value)
{
	privatecontext = value;
}

ContextView::ContextView()
{
}

void ContextView::OnDestroy()
{
	if(getcontext() != nullptr)
	{
		Context::firstContext->RemoveContext(getcontext());
	}
}

bool ContextView::getrequiresContext() const
{
	return privaterequiresContext;
}

void ContextView::setrequiresContext(const bool& value)
{
	privaterequiresContext = value;
}

bool ContextView::getregisteredWithContext() const
{
	return privateregisteredWithContext;
}

void ContextView::setregisteredWithContext(const bool& value)
{
	privateregisteredWithContext = value;
}

bool ContextView::getautoRegisterWithContext() const
{
	return privateautoRegisterWithContext;
}

void ContextView::setautoRegisterWithContext(const bool& value)
{
	privateautoRegisterWithContext = value;
}
}
}
}
}
