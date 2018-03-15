





#include "SequencerException.h"

using namespace strange::extensions::sequencer::api;
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{

SequencerExceptionType SequencerException::gettype() const
{
	return privatetype;
}

void SequencerException::settype(const SequencerExceptionType& value)
{
	privatetype = value;
}

SequencerException::SequencerException() : Exception()
{
}

SequencerException::SequencerException(const std::wstring& message, SequencerExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
