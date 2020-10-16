#pragma once
#ifndef _SUBJECTINDEXEXCEPTION_H_
#define _SUBJECTINDEXEXCEPTION_H_

#include "TerminsListException.h"


	static const std::string DEFAULT_SUBJECT_INDEX_EXCEPTION = "Subject index exception.";

	using std::string;

	class SubjectIndexException{
	private:

		string error_name_;

	protected:
	public:

		explicit SubjectIndexException(const string& error_name)noexcept: 
			error_name_(error_name) {

		}
		explicit SubjectIndexException()noexcept :
			error_name_(DEFAULT_SUBJECT_INDEX_EXCEPTION) {

		}

	};

#endif

