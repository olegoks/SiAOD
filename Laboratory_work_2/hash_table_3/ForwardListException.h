#pragma once
#ifndef _FORWARDLISTEXCEPTION_H_
#define _FORWARDLISTEXCEPTION_H_
#include "base_list.h"



	static const std::string DEFAULT_ERROR_NAME = "Forward list exception.";

	class ForwardListException :public ListException {
	private:
	protected:
	public:
		explicit ForwardListException()noexcept :
			ListException(DEFAULT_ERROR_NAME) {

		}
		explicit ForwardListException(const string& error)noexcept :
			ListException(error){
		}

	};


#endif

