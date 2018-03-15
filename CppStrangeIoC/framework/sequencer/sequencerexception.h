#pragma once

#include <string>
#include <stdexcept>


using namespace strange::extensions::sequencer::api;

namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{
class SequencerException : public std::exception
{
private:
	SequencerExceptionType privatetype = static_cast<SequencerExceptionType>( 0 );

public:
	SequencerExceptionType gettype() const;
	void settype( const SequencerExceptionType& value );

	SequencerException();

	/// Constructs a SequencerException with a message and SequencerExceptionType
	SequencerException( const std::wstring& message, SequencerExceptionType exceptionType );
};
}
}
}
}

