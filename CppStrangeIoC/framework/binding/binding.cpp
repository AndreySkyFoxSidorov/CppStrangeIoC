#include "Binding.h"

using namespace strange::framework::api;
namespace strange
{
namespace framework
{
namespace impl
{

Binding::Binding(Binder::BindingResolver resolver)
{
	this->resolver = resolver;
	_key = new SemiBinding();
	_value = new SemiBinding();
	_name = new SemiBinding();
	setkeyConstraint(BindingConstraintType::ONE);
	setnameConstraint(BindingConstraintType::ONE);
	setvalueConstraint(BindingConstraintType::MANY);
}

Binding::Binding() : Binding(nullptr)
{
}

void* Binding::getkey() const
{
	return _key->value;
}

void* Binding::getvalue() const
{
	return _value->value;
}

void* Binding::getname() const
{
	return (_name->value == nullptr) ? BindingConst::NULLOID : _name->value;
}

Enum* Binding::getkeyConstraint() const
{
	return _key->constraint;
}

void Binding::setkeyConstraint(Enum* value)
{
	_key->constraint = value;
}

Enum* Binding::getvalueConstraint() const
{
	return _value->constraint;
}

void Binding::setvalueConstraint(Enum* value)
{
	_value->constraint = value;
}

Enum* Binding::getnameConstraint() const
{
	return _name->constraint;
}

void Binding::setnameConstraint(Enum* value)
{
	_name->constraint = value;
}

bool Binding::getisWeak() const
{
	return _isWeak;
}

template<typename T>
IBinding* Binding::Bind()
{
	return Bind(T::typeid);
}

IBinding* Binding::Bind(void* o)
{
	_key->Add(o);
	return this;
}

template<typename T>
IBinding* Binding::To()
{
	return To(T::typeid);
}

IBinding* Binding::To(void* o)
{
	_value->Add(o);
	if(resolver != nullptr)
	{
		resolver(this);
	}
	return this;
}

template<typename T>
IBinding* Binding::ToName()
{
	return ToName(T::typeid);
}

IBinding* Binding::ToName(void* o)
{
	auto toName = (o == nullptr) ? BindingConst::NULLOID : o;
	_name->Add(toName);
	if(resolver != nullptr)
	{
		resolver(this);
	}
	return this;
}

template<typename T>
IBinding* Binding::Named()
{
	return Named(T::typeid);
}

IBinding* Binding::Named(void* o)
{
	return _name->value == o ? this : nullptr;
}

void Binding::RemoveKey(void* o)
{
	_key->Remove(o);
}

void Binding::RemoveValue(void* o)
{
	_value->Remove(o);
}

void Binding::RemoveName(void* o)
{
	_name->Remove(o);
}

IBinding* Binding::Weak()
{
	_isWeak = true;
	return this;
}
}
}
}
