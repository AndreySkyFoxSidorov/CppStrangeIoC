#include "SemiBinding.h"

using namespace strange::framework::api;
namespace strange
{
	namespace framework
	{
		namespace impl
		{

			Enum* SemiBinding::getconstraint() const
			{
				return privateconstraint;
			}

			void SemiBinding::setconstraint(Enum* value)
			{
				privateconstraint = value;
			}

			bool SemiBinding::getuniqueValues() const
			{
				return privateuniqueValues;
			}

			void SemiBinding::setuniqueValues(const bool& value)
			{
				privateuniqueValues = value;
			}

			SemiBinding::SemiBinding()
			{
				setconstraint(BindingConstraintType::ONE);
				setuniqueValues(true);
			}

			IManagedList* SemiBinding::Add(void* o)
			{
				if (objectValue.empty() || static_cast<BindingConstraintType*>(getconstraint()) == BindingConstraintType::ONE)
				{
					objectValue = std::vector<void*>(1);
				}
				else
				{
					if (getuniqueValues())
					{
						int aa = objectValue.size();
						for (int a = 0; a < aa; a++)
						{
							auto val = objectValue[a];
							if (val->Equals(o))
							{
								return this;
							}
						}
					}
					std::vector<void*> tempList = objectValue;
					int len = tempList.size();
					objectValue = std::vector<void*>(len + 1);
					tempList.CopyTo(objectValue, 0);
				}
				objectValue[objectValue.size() - 1] = o;
				return this;
			}

			IManagedList* SemiBinding::Add(std::vector<void*>& list)
			{
				for (auto item : list)
				{
					Add(item);
				}
				return this;
			}

			IManagedList* SemiBinding::Remove(void* o)
			{
				if (o->Equals(objectValue) || objectValue.empty())
				{
					objectValue.clear();
					return this;
				}
				int aa = objectValue.size();
				for (int a = 0; a < aa; a++)
				{
					auto currVal = objectValue[a];
					if (o->Equals(currVal))
					{
						spliceValueAt(a);
						return this;
					}
				}
				return this;
			}

			IManagedList* SemiBinding::Remove(std::vector<void*>& list)
			{
				for (auto item : list)
				{
					Remove(item);
				}
				return this;
			}

			void* SemiBinding::getvalue() const
			{
				if (getconstraint()->Equals(BindingConstraintType::ONE))
				{
					return (objectValue.empty()) ? nullptr : objectValue[0];
				}
				return objectValue;
			}

			void SemiBinding::spliceValueAt(int splicePos)
			{
				std::vector<void*> newList(objectValue.size() - 1);
				int mod = 0;
				int aa = objectValue.size();
				for (int a = 0; a < aa; a++)
				{
					if (a == splicePos)
					{
						mod = -1;
						continue;
					}
					newList[a + mod] = objectValue[a];
				}
				objectValue = (newList.empty()) ? nullptr : newList;
			}
		}
	}
}
