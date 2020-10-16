#pragma once
#ifndef _TERMINSLISTEXCEPTION_H_
#define _TERMINSLISTEXCEPTION_H_
#include "TerminException.h"



	static const string TERMINS_LIST_EXCEPTION = "TerminsListException.";

	class TerminsListException:public TerminException
	{
	private:
	protected:
	public:
		explicit TerminsListException(const string& _error_name)noexcept :
			TerminException(TERMINS_LIST_EXCEPTION) {}

	};

#endif

