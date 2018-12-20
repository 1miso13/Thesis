#pragma once
#include <string>
std::string RemoveWhitespaceChars(std::string &s) {
	// remove first empty char
		size_t i = 0;
	for (; i < s.size(); i++)
	{

		if (!isspace(s[i])) {
			break;
		}
	}
	//remove last empty char
	int j = s.size() - 1;
	for (; j > 0; j--)
	{

		if (!isspace(s[j])) {
			break;
		}
	}
	return s.substr(i, j - i + 1);

}