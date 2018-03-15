#pragma once







#include <vector>
#include <typeinfo>

using namespace strange::extensions::reflector::api;

namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{
class ReflectedClass : public IReflectedClass
{
private:
	ConstructorInfo* privateConstructor;
	std::vector<std::type_info> privateConstructorParameters;
	std::vector<MethodInfo*> privatePostConstructors;
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> privateSetters;
	std::vector<void*> privateSetterNames;
	bool privatePreGenerated = false;

public:
	ConstructorInfo* getConstructor() const;
	void setConstructor( ConstructorInfo* value );
	std::vector<std::type_info> getConstructorParameters() const;
	void setConstructorParameters( std::vector<std::type_info>& value );
	std::vector<MethodInfo*> getPostConstructors() const;
	void setPostConstructors( std::vector<MethodInfo*>& value );
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> getSetters() const;
	void setSetters( std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value );
	std::vector<void*> getSetterNames() const;
	void setSetterNames( std::vector<void*>& value );
	bool getPreGenerated() const;
	void setPreGenerated( const bool& value );

	/// [Obsolete"Strange migration to conform to C# guidelines. Removing camelCased publics"]
	ConstructorInfo* getconstructor() const;
	void setconstructor( ConstructorInfo* value );
	std::vector<std::type_info> getconstructorParameters() const;
	void setconstructorParameters( std::vector<std::type_info>& value );
	std::vector<MethodInfo*> getpostConstructors() const;
	void setpostConstructors( std::vector<MethodInfo*>& value );
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> getsetters() const;
	void setsetters( std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value );
	std::vector<void*> getsetterNames() const;
	void setsetterNames( std::vector<void*>& value );
	bool getpreGenerated() const;
	void setpreGenerated( const bool& value );
};
}
}
}
}

