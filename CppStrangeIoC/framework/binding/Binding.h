#pragma once
#define Enum void

#include "Binder.h"
#include "BinderException.h"
#include "BinderExceptionType.h"
#include "BindingConst.h"
#include "BindingConstraintType.h"
#include "IBinder.h"
#include "IBinding.h"
#include "IInstanceProvider.h"
#include "IManagedList.h"
#include "ISemiBinding.h"
#include "SemiBinding.h"
using namespace strange::framework::api;

namespace strange
{
	namespace framework
	{
		namespace impl
		{
			class Binding : public IBinding
			{
			public:
				std::function<void(IBinding* binding)> resolver;

			protected:
				ISemiBinding * _key;
				ISemiBinding* _value;
				ISemiBinding* _name;

			public:
				virtual ~Binding()
				{
					delete _key;
					delete _value;
					delete _name;
				}

				Binding(std::function<void(IBinding* binding)> resolver);

				Binding();

				//	#region IBinding implementation
				void* getkey() const;

				void* getvalue() const;

				void* getname() const;

				Enum* getkeyConstraint() const;
				void setkeyConstraint(Enum* value);

				Enum* getvalueConstraint() const;
				void setvalueConstraint(Enum* value);

				Enum* getnameConstraint() const;
				void setnameConstraint(Enum* value);

			protected:
				bool _isWeak = false;
			public:
				bool getisWeak() const;

				template<typename T>
				IBinding* Bind();

				virtual IBinding* Bind(void* o);

				template<typename T>
				IBinding* To();

				virtual IBinding* To(void* o);

				template<typename T>
				IBinding* ToName();

				virtual IBinding* ToName(void* o);

				template<typename T>
				IBinding* Named();

				virtual IBinding* Named(void* o);

				virtual void RemoveKey(void* o);

				virtual void RemoveValue(void* o);

				virtual void RemoveName(void* o);

				virtual IBinding* Weak();
				//	#endregion
			};
		}
	}
}
