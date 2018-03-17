#include "Binder.h"
#include "BinderException.h"
#include "Binding.h"
#include "IBinding.h"

using namespace strange::framework::api;
namespace strange
{
	namespace framework
	{
		namespace impl
		{

			Binder::Binder()
			{
				bindings = std::unordered_map <void*, std::unordered_map<void*, IBinding*>>();
				conflicts = std::unordered_map <void*, std::unordered_map<IBinding*, void*>>();
			}

			template<typename T>
			IBinding* Binder::Bind()
			{
				return Bind(T::typeid);
			}

			IBinding* Binder::Bind(void* key)
			{
				IBinding* binding;
				binding = GetRawBinding();
				binding->Bind(key);
				return binding;
			}

			template<typename T>
			IBinding* Binder::GetBinding()
			{
				return GetBinding(T::typeid, nullptr);
			}

			IBinding* Binder::GetBinding(void* key)
			{
				return GetBinding(key, nullptr);
			}

			template<typename T>
			IBinding* Binder::GetBinding(void* name)
			{
				return GetBinding(T::typeid, name);
			}

			IBinding* Binder::GetBinding(void* key, void* name)
			{
				if (conflicts.size() > 0)
				{
					std::wstring conflictSummary = L"";
					/*std::unordered_map<void*, std::unordered_map<IBinding*, void*>>::KeyCollection keys = conflicts.Keys;
					for (auto k : keys)
					{
						if (conflictSummary.length() > 0)
						{
							conflictSummary += L", ";
						}
						//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
						// conflictSummary += k.ToString();
					}*/
					throw BinderException(L"Binder cannot fetch Bindings when the binder is in a conflicted state.\nConflicts: " + conflictSummary, BinderExceptionType::CONFLICT_IN_BINDER);
				}
				if (bindings.find(key) != bindings.end())
				{
					std::unordered_map<void*, IBinding*> dict = bindings[key];
					name = (name == nullptr) ? NULL : name;
					if (dict.find(name) != dict.end())
					{
						return dict[name];
					}
				}
				return nullptr;
			}

			template<typename T>
			void Binder::Unbind()
			{
				Unbind(T::typeid, nullptr);
			}

			void Binder::Unbind(void* key)
			{
				Unbind(key, nullptr);
			}

			template<typename T>
			void Binder::Unbind(void* name)
			{
				Unbind(T::typeid, name);
			}

			void Binder::Unbind(void* key, void* name)
			{
				if (bindings.find(key) != bindings.end())
				{
					std::unordered_map<void*, IBinding*> dict = bindings[key];
					auto bindingName = (name == nullptr) ? NULL : name;
					if (dict.find(bindingName) != dict.end())
					{
						dict.erase(bindingName);
					}
				}
			}

			void Binder::Unbind(IBinding* binding)
			{
				if (binding == nullptr)
				{
					return;
				}
				Unbind(&binding->getkey, binding->getname);
			}

			void Binder::RemoveValue(IBinding* binding, void* value)
			{
				if (binding == nullptr || value == nullptr)
				{
					return;
				}
				auto key = binding->getkey;
				std::unordered_map<void*, IBinding*> dict;
				if ((bindings.find(key) != bindings.end()))
				{
					dict = bindings[key];
					if (dict.find(binding->getname) != dict.end())
					{
						IBinding* useBinding = dict[binding->getname];
						useBinding->RemoveValue(value);
						//If result is empty, clean it out
						std::vector<void*> values = dynamic_cast<std::vector<void*>>(useBinding->getvalue);
						if (values.empty() || values.empty())
						{
							dict.erase(useBinding->getname);
						}
					}
				}
			}

			void Binder::RemoveKey(IBinding* binding, void* key)
			{
				if (binding == nullptr || key == nullptr || bindings.find(key) != bindings.end() == false)
				{
					return;
				}
				std::unordered_map<void*, IBinding*> dict = bindings[key];
				if (dict.find(binding->getname) != dict.end())
				{
					IBinding* useBinding = dict[binding->getname];
					useBinding->RemoveKey(key);
					std::vector<void*> keys = dynamic_cast<std::vector<void*>>(useBinding->getkey);
					if (keys.size() > 0 && keys.empty())
					{
						dict.erase(binding->getname);
					}
				}
			}

			void Binder::RemoveName(IBinding* binding, void* name)
			{
				if (binding == nullptr || name == nullptr)
				{
					return;
				}
				void* key;
				if (binding->getkeyConstraint->Equals(BindingConstraintType::ONE))
				{
					key = binding->getkey;
				}
				else
				{
					std::vector<void*> keys = dynamic_cast<std::vector<void*>>(binding->getkey);
					key = keys[0];
				}
				std::unordered_map<void*, IBinding*> dict = bindings[key];
				if (dict.find(name) != dict.end())
				{
					IBinding* useBinding = dict[name];
					useBinding->RemoveName(name);
				}
			}

			IBinding* Binder::GetRawBinding()
			{				
				return new Binding([&](IBinding binding)
				{
					resolver(binding);
				});
			}

			void Binder::resolver(IBinding* binding)
			{
				auto key = binding->getkey;
				if (binding->getkeyConstraint->Equals(BindingConstraintType::ONE))
				{
					ResolveBinding(binding, key);
				}
				else
				{
					std::vector<void*> keys = dynamic_cast<std::vector<void*>>(key);
					int aa = keys.size();
					for (int a = 0; a < aa; a++)
					{
						ResolveBinding(binding, keys[a]);
					}
				}
			}

			void Binder::ResolveBinding(IBinding* binding, void* key)
			{
				//Check for existing conflicts
				if (conflicts.find(key) != conflicts.end())  //does the current key have any conflicts?
				{
					std::unordered_map<IBinding*, void*> inConflict = conflicts[key];
					if (inConflict.find(binding) != inConflict.end())  //Am I on the conflict list?
					{
						auto conflictName = inConflict[binding];
						if (isConflictCleared(inConflict, binding))  //Am I now out of conflict?
						{
							clearConflict(key, conflictName, inConflict); //remove all from conflict list.
						}
						else
						{
							return; //still in conflict
						}
					}
				}
				//Check for and assign new conflicts
				auto bindingName = (binding->getname == nullptr) ? BindingConst::NULLOID : binding->getname;
				std::unordered_map<void*, IBinding*> dict;
				if ((bindings.find(key) != bindings.end()))
				{
					dict = bindings[key];
					//Will my registration create a new conflict?
					if (dict.find(bindingName) != dict.end())
					{
						//If the existing binding is not this binding, and the existing binding is not weak
						//If it IS weak, we will proceed normally and overwrite the binding in the dictionary
						IBinding* existingBinding = dict[bindingName];
						//if (existingBinding != binding && !existingBinding.isWeak)
						//SDM2014-01-20: as part of cross-context implicit bindings fix, attempts by a weak binding to replace a non-weak binding are ignored instead of being
						if (existingBinding != binding && !existingBinding->getisWeak && !binding->getisWeak)
						{
							//register both conflictees
							registerNameConflict(key, binding, dict[bindingName]);
							return;
						}
						if (existingBinding->getisWeak)
						{
							//SDM2014-01-20: (in relation to the cross-context implicit bindings fix)
							// 1) if the previous binding is weak and the new binding is not weak, then the new binding replaces the previous;
							// 2) but if the new binding is also weak, then it only replaces the previous weak binding if the previous binding
							// has not already been instantiated:
							if (existingBinding != binding && existingBinding->getisWeak && (!binding->getisWeak || existingBinding->getvalue == nullptr || dynamic_cast<std::type_info>(existingBinding->getvalue) != nullptr))
							{
								//Remove the previous binding.
								dict.erase(bindingName);
							}
						}
					}
				}
				else
				{
					dict = std::unordered_map<void*, IBinding*>();
					bindings[key] = dict;
				}
				//Remove nulloid bindings
				if (dict.find(BindingConst::NULLOID) != dict.end() && dict[BindingConst::NULLOID] == binding)
				{
					dict.erase(BindingConst::NULLOID);
				}
				//Add (or override) our new binding!
				if (dict.find(bindingName) == dict.end())
				{
					dict.emplace(bindingName, binding);
				}
			}

			void Binder::registerNameConflict(void* key, IBinding* newBinding, IBinding* existingBinding)
			{
				std::unordered_map<IBinding*, void*> dict;
				if (conflicts.find(key) != conflicts.end() == false)
				{
					dict = std::unordered_map<IBinding*, void*>();
					conflicts[key] = dict;
				}
				else
				{
					dict = conflicts[key];
				}
				dict[newBinding] = newBinding->getname;
				dict[existingBinding] = newBinding->getname;
			}

			bool Binder::isConflictCleared(std::unordered_map<IBinding*, void*>& dict, IBinding* binding)
			{
				for (auto kv : dict)
				{
					if (kv.first != binding && kv.first->getname == binding->getname)
					{
						return false;
					}
				}
				return true;
			}

			void Binder::clearConflict(void* key, void* name, std::unordered_map<IBinding*, void*>& dict)
			{
				std::vector<IBinding*> removalList;
				for (auto kv : dict)
				{
					auto v = kv.second;
					if (v->Equals(name))
					{
						removalList.push_back(kv.first);
					}
				}
				int aa = removalList.size();
				for (int a = 0; a < aa; a++)
				{
					dict.erase(removalList[a]);
				}
				if (dict.empty())
				{
					conflicts.erase(key);
				}
			}

			template<typename T>
			std::vector<T> Binder::spliceValueAt(int splicePos, std::vector<void*>& objectValue)
			{
				std::vector<T> newList(objectValue.size() - 1);
				int mod = 0;
				int aa = objectValue.size();
				for (int a = 0; a < aa; a++)
				{
					if (a == splicePos)
					{
						mod = -1;
						continue;
					}
					newList[a + mod] = static_cast<T>(objectValue[a]);
				}
				return newList;
			}

			std::vector<void*> Binder::spliceValueAt(int splicePos, std::vector<void*>& objectValue)
			{
				return spliceValueAt<void*>(splicePos, objectValue);
			}

			void Binder::OnRemove()
			{
			}
		}
	}
}
