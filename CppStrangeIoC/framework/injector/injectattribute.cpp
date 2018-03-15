





#include "InjectAttribute.h"


Inject::Inject()
{
}

Inject::Inject(void* n)
{
	setname(n);
}

void* Inject::getname() const
{
	return privatename;
}

void Inject::setname(void* value)
{
	privatename = value;
}

Construct::Construct()
{
}

PostConstruct::PostConstruct()
{
}

PostConstruct::PostConstruct(int p)
{
	setpriority(p);
}

int PostConstruct::getpriority() const
{
	return privatepriority;
}

void PostConstruct::setpriority(const int& value)
{
	privatepriority = value;
}

Deconstruct::Deconstruct()
{
}
