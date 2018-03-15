#pragma once







#include <vector>
#include <typeinfo>


namespace strange
{
namespace extensions
{
namespace reflector
{
namespace api
{
class IReflectedClass
{
	/// Get/set the preferred constructor
public:
	virtual ConstructorInfo* getConstructor() const = 0;
	virtual void setConstructor( ConstructorInfo* value ) = 0;

	/// Get/set the preferred constructor's list of parameters
	virtual std::vector<std::type_info> getConstructorParameters() const = 0;
	virtual void setConstructorParameters( const std::vector<std::type_info>& value ) = 0;

	/// Get/set any PostConstructors. This includes inherited PostConstructors.
	virtual std::vector<MethodInfo*> getPostConstructors() const = 0;
	virtual void setPostConstructors( const std::vector<MethodInfo*>& value ) = 0;

	/// Get/set the list of setter injections. This includes inherited setters.
	virtual std::vector<KeyValuePair<std::type_info, PropertyInfo*>> getSetters() const = 0;
	virtual void setSetters( const std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value ) = 0;
	virtual std::vector<void*> getSetterNames() const = 0;
	virtual void setSetterNames( const std::vector<void*>& value ) = 0;

	/// For testing. Allows a unit test to assert whether the binding was
	/// generated on the current call, or on a prior one.
	virtual bool getPreGenerated() const = 0;
	virtual void setPreGenerated( const bool& value ) = 0;

	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual ConstructorInfo* getconstructor() const = 0;
	virtual void setconstructor( ConstructorInfo* value ) = 0;
	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual std::vector<std::type_info> getconstructorParameters() const = 0;
	virtual void setconstructorParameters( const std::vector<std::type_info>& value ) = 0;
	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual std::vector<MethodInfo*> getpostConstructors() const = 0;
	virtual void setpostConstructors( const std::vector<MethodInfo*>& value ) = 0;
	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual std::vector<KeyValuePair<std::type_info, PropertyInfo*>> getsetters() const = 0;
	virtual void setsetters( const std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value ) = 0;
	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual std::vector<void*> getsetterNames() const = 0;
	virtual void setsetterNames( const std::vector<void*>& value ) = 0;
	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	virtual bool getpreGenerated() const = 0;
	virtual void setpreGenerated( const bool& value ) = 0;
};
}
}
}
}

