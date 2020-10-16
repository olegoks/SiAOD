#pragma once
#ifndef _MAPEXCEPTION_H_
#define _MAPEXCEPTION_H_

#include "ForwardListException.h"

namespace mp {



	static const std::string DEFAULT_ERROR_NAME = "Map exception.";

	class MapException:public ForwardListException{
	private:
	protected:
	public:

		explicit MapException()noexcept:
			ForwardListException(DEFAULT_ERROR_NAME) {

		}
		explicit MapException(const std::string& error)noexcept:
			ForwardListException(error) {

		}

	};

}
#endif

