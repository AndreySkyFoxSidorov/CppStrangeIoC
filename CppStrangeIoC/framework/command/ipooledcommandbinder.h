#pragma once





using namespace strange::extensions::pool::impl;
using namespace strange::extensions::command::impl;

namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
class IPooledCommandBinder
{
	/// Retrieve the Pool of the specified type
public:
	template<typename T>
	Pool<T>* GetPool() = 0;

	/// Switch to disable pooling for those that don't want to use it.
	virtual bool getusePooling() const = 0;
	virtual void setusePooling( const bool& value ) = 0;
};
}
}
}
}

