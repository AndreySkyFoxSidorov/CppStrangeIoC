#pragma once







namespace strange
{
namespace framework
{
namespace api
{
enum class BindingConstraintType
{
	/// Constrains a SemiBinding to carry no more than one item in its Value
	ONE,
	/// Constrains a SemiBinding to carry a list of items in its Value
	MANY,
	/// Instructs the Binding to apply a Pool instead of a SemiBinding
	POOL,
};
}
}
}

