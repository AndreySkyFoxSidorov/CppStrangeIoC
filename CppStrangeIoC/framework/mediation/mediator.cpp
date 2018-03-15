





#include "Mediator.h"

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

GameObject* Mediator::getcontextView() const
{
	return privatecontextView;
}

void Mediator::setcontextView(GameObject* value)
{
	privatecontextView = value;
}

Mediator::Mediator()
{
}

void Mediator::PreRegister()
{
}

void Mediator::OnRegister()
{
}

void Mediator::OnRemove()
{
}
}
}
}
}
