#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <typeinfo>
#include <functional>

#include "BinderException.h"
#include "BinderExceptionType.h"
#include "Binding.h"
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
			class Binder : public IBinder
			{
				/// Dictionary of all bindings
				/// Two-layer keys. First key to individual Binding keys,
				/// then to Binding names. (This wouldn't be required if
				/// Unity supported Tuple or HashSet.)
			protected:
				std::unordered_map<void*, std::unordered_map<void*, IBinding*>> bindings;

				std::unordered_map<void*, std::unordered_map<IBinding*, void*>> conflicts;

				/// A handler for resolving the nature of a binding during chained commands
				using BindingResolver = std::function<void(IBinding* binding)>;

			public:
				Binder();

				template<typename T>
				IBinding* Bind();

				virtual IBinding* Bind(void* key);

				template<typename T>
				IBinding* GetBinding();

				virtual IBinding* GetBinding(void* key);

				template<typename T>
				IBinding* GetBinding(void* name);

				virtual IBinding* GetBinding(void* key, void* name);

				template<typename T>
				void Unbind();

				virtual void Unbind(void* key);

				template<typename T>
				void Unbind(void* name);

				virtual void Unbind(void* key, void* name);

				virtual void Unbind(IBinding* binding);

				virtual void RemoveValue(IBinding* binding, void* value);

				virtual void RemoveKey(IBinding* binding, void* key);

				virtual void RemoveName(IBinding* binding, void* name);

				virtual IBinding* GetRawBinding();

				/// The default handler for resolving bindings during chained commands
			protected:
				virtual void resolver(IBinding* binding);

				/**
				 * This method places individual Bindings into the bindings Dictionary
				 * as part of the resolving process. Note that while some Bindings
				 * may store multiple keys, each key takes a unique position in the
				 * bindings Dictionary.
				 *
				 * Conflicts in the course of fluent binding are expected, but GetBinding
				 * will throw an error if there are any unresolved conflicts.
				 */
			public:
				virtual void ResolveBinding(IBinding* binding, void* key);

				/// Take note of bindings that are in conflict.
				/// This occurs routinely during fluent binding, but will spark an error if
				/// GetBinding is called while this Binder still has conflicts.
			protected:
				void registerNameConflict(void* key, IBinding* newBinding, IBinding* existingBinding);

				/// Returns true if the provided binding and the binding in the dict are no longer conflicting
				bool isConflictCleared(std::unordered_map<IBinding*, void*>& dict, IBinding* binding);

				void clearConflict(void* key, void* name, std::unordered_map<IBinding*, void*>& dict);

				template<typename T>
				std::vector<T> spliceValueAt(int splicePos, std::vector<void*>& objectValue);

				/// Remove the item at splicePos from the list objectValue
				std::vector<void*> spliceValueAt(int splicePos, std::vector<void*>& objectValue);

			public:
				virtual void OnRemove();
			};
		}
	}
}

