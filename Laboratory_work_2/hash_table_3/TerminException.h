#pragma once
#ifndef _TEMRIN_EXCEPTION_H_
#define _TERMIN_EXCEPTION_H_
#include <string>
using std::string;
static const string DEFAULT_TERMIN_EXCEPTION = "TerminException.";

class TerminException
{
private:

	string error_name;

protected:
public:

	explicit TerminException()noexcept :
		error_name(DEFAULT_TERMIN_EXCEPTION) {}
	explicit TerminException(const string& _error_name)noexcept :
		error_name(_error_name) {}

	inline const string& What()const noexcept { return error_name; }

};




#endif

