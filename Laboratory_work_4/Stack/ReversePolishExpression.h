#pragma once
#ifndef PEVERSEPOLISHEXPRESSION
#define REVERSEPOLISHEXPRESSION

#include <string>
#include "Stack.h"

using Priority = size_t;

bool SymbolIsOperator(const char symbol);
Priority ReturnOperatorPriority(const char symbol);
std::string ConvertToRevPolExpr(const std::string& expression);

#endif //REVERSEPOLISHEXPRESSION