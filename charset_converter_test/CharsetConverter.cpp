#include "CharsetConverter.h"
CharsetConverter::CharsetConverter(const char *toCode, const char *fromCode)
{
	conversionDescriptor = iconv_open(toCode, fromCode);
	if (reinterpret_cast<iconv_t>(-1) == conversionDescriptor)
	{
		if (errno == EINVAL)
			throw std::string("Not supported from " + std::string(fromCode) + " to " + toCode);
		else
			throw std::string("Unknown error");
	}
}
CharsetConverter::~CharsetConverter()
{
	iconv_close(conversionDescriptor);
}
std::string CharsetConverter::convert(const std::string &source) const
{
	const char *sourcePtr = source.c_str();
	size_t byteCount = source.length(), totalSpaceOfDestinationBuffer = byteCount * 2, availableSpaceOfDestinationBuffer = totalSpaceOfDestinationBuffer;
	char *destinationBuffer = new char[totalSpaceOfDestinationBuffer], *destinationPtr = destinationBuffer;
	std::string converted;
	while (byteCount > 0)
	{
		size_t ret = iconv(conversionDescriptor, &sourcePtr, &byteCount, &destinationPtr, &availableSpaceOfDestinationBuffer);
		if (static_cast<size_t>(-1) == ret)
		{
			++sourcePtr;
			--byteCount;
		}
		size_t charCount = totalSpaceOfDestinationBuffer - availableSpaceOfDestinationBuffer;
		converted.append(destinationBuffer, charCount);
	}
	delete[] destinationBuffer;
	return converted;
}