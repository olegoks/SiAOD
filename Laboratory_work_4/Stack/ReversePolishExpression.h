#pragma once
#ifndef PEVERSEPOLISHEXPRESSION
#define REVERSEPOLISHEXPRESSION

#include <string>
#include "Stack.h"
#include <regex>
using Priority = int;

bool SymbolIsOperator(const char symbol);
Priority ReturnPriorityStack(const char symbol);
Priority ReturnPriorityRel(const char symbol);
std::string ConvertToRevPolExpr(const std::string& expression);
int CountRang(const std::string& expression);

#endif //REVERSEPOLISHEXPRESSION