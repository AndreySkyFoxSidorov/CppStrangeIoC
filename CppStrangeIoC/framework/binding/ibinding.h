#pragma once
#define Enum void

namespace strange
{
	namespace framework
	{
		namespace api
		{
			class IBinding
			{
				/**
				 * Tie this binding to a Type key
				 */
			public:
				template<typename T>
				IBinding* Bind() = 0;
				/**
				 * Tie this binding to a value key, such as a string or class instance
				 */
				virtual IBinding* Bind(void* key) = 0;

				/**
				 * Set the Binding's value to a Type
				 **/
				template<typename T>
				IBinding* To() = 0;
				/**
				 * Set the Binding's value to a value, such as a string or class instance
				 */
				virtual IBinding* To(void* o) = 0;

				/**
				 * Qualify a binding using a marker type
				 */
				template<typename T>
				IBinding* ToName() = 0;

				/**
				 * Qualify a binding using a value, such as a string or class instance
				 */
				virtual IBinding* ToName(void* o) = 0;

				/**
				 * Retrieve a binding if the supplied name matches, by Type
				 */
				template<typename T>
				IBinding* Named() = 0;

				/**
				 * Retrieve a binding if the supplied name matches, by value
				 */
				virtual IBinding* Named(void* o) = 0;

				/**
				 * Remove a specific key from the binding.
				 */
				virtual void RemoveKey(void* o) = 0;

				/**
				 * Remove a specific value from the binding
				 */
				virtual void RemoveValue(void* o) = 0;

				/**
				 * Remove a name from the binding
				 */
				virtual void RemoveName(void* o) = 0;

				/// Get the binding''s key
				virtual void* getkey() const = 0;

				/// Get the binding's name
				virtual void* getname() const = 0;

				/// Get the binding's value
				virtual void* getvalue() const = 0;

				/// Get or set a MANY or ONE constraint on the Key
				virtual Enum* getkeyConstraint() const = 0;
				virtual void setkeyConstraint(Enum* value) = 0;

				/// Get or set a MANY or ONE constraint on the Value
				virtual Enum* getvalueConstraint() const = 0;
				virtual void setvalueConstraint(Enum* value) = 0;

				//Mark a binding as weak, so that any new binding will override it
				virtual IBinding* Weak() = 0;

				//Get whether or not the binding is weak, default false
				virtual bool getisWeak() const = 0;

			};
		}
	}
}

