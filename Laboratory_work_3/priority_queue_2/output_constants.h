#pragma once
#ifndef OUTPUT_CONSTANTS_H
#define OUTPUT_CONSTANTS_H


static const char* const GenerateSeparatorLine(size_t number, const char separator) {

	number++;
	char* const separator_line = (char* const) new char[number];

	for (size_t i = 0; i < number - 1; i++)
		separator_line[i] = separator;

	separator_line[number] = '\0';

	return separator_line;
}

constexpr char kVerticalSeparator = '|';
constexpr char kHorizontalSeparator = '-';
constexpr char kSpace = ' ';
constexpr size_t kCellWidth = 5;
constexpr size_t kKpdPrecision = 2;
constexpr size_t kTableWidth = 11;
const char* const kSeparatorLine = GenerateSeparatorLine((kTableWidth) * (kCellWidth + 2), kHorizontalSeparator);

#endif