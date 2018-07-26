#pragma once
#include <iconv/iconv.h>
#include <string>
class CharsetConverter
{
public:
	CharsetConverter(const char *toCode, const char *fromCode);
	~CharsetConverter();
	std::string convert(const std::string &source) const;
private:
	iconv_t conversionDescriptor;
};