#pragma once

/**
 * @class Inject
 *
 * The `[Inject]` attribute marks a setter Injection point.
 *
 * Example:

		[Inject]
		public IMyInterface myInstance{get;set;}

 *
 * Inject tags can also specify a name:
 *

 		[Inject(SomeEnum.VALUE)]
 		public IMyInterface myInstance{get;set;}


 * @class Construct
 *
 * The `[Construct]` attribute marks a preferred Constructor. If omitted,
 * the Reflector will mark as Constructor the shortest available
 * Constructor. Obviously, if there only one constructor, this tag
 * is not requried.
 *
 * @class PostConstruct
 *
 * The `[PostConstruct]` attribute marks one or more methods as PostConstructors.
 * A PostConstructor is triggered immediately after injection. This allows
 * you to use use a PostConstructor in much the same way as a Constructor,
 * safe in the knowledge that there will be no null pointers on injected
 * dependencies. PostConstructors do not accept arguments.
 *
 * You may optionally include a priority int on your PostConstructor. This allows for multiple
 * PostConstruction methods which will fire in a predictable order.
 *
 * @class Deconstruct
 *
 * Unsupported.
 */


// FixiME The following .NET attribute has no direct equivalent in native C++:
// [AttributeUsage(AttributeTargets.Property, AllowMultiple = false, Inherited = true)] public class Inject: Attribute
class Inject : public Attribute
{
private:
	void* privatename;

public:
	Inject();

	Inject( void* n );

	void* getname() const;
	void setname( void* value );
};

//Tag [PostConstruct] to perform post-injection construction actions
// FixiME The following .NET attribute has no direct equivalent in native C++:
// [AttributeUsage(AttributeTargets.Constructor, AllowMultiple = false, Inherited = true)] public class Construct: Attribute
class Construct : public Attribute
{
public:
	Construct();
};

//Tag [PostConstruct] to perform post-injection construction actions
// FixiME The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [AttributeUsage(AttributeTargets.Method, AllowMultiple = false, Inherited = true)] public class PostConstruct: Attribute
class PostConstruct : public Attribute
{
private:
	int privatepriority = 0;

public:
	PostConstruct();

	PostConstruct( int p );

	int getpriority() const;
	void setpriority( const int& value );
};

// FixiME The following .NET attribute has no direct equivalent in native C++:
// [AttributeUsage(AttributeTargets.Method, AllowMultiple = false, Inherited = true)] public class Deconstruct: Attribute
class Deconstruct : public Attribute
{
public:
	Deconstruct();
};
