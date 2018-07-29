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
	size_t sourceByteCount = source.length(), totalSpaceOfDestinationBuffer = sourceByteCount * 2, availableSpaceOfDestinationBuffer = totalSpaceOfDestinationBuffer;
	char *destinationBuffer = new char[totalSpaceOfDestinationBuffer], *destinationPtr = destinationBuffer;
	std::string converted;
	size_t convertedCharCount;
	while (sourceByteCount > 0)
	{
		size_t ret = iconv(conversionDescriptor, &sourcePtr, &sourceByteCount, &destinationPtr, &availableSpaceOfDestinationBuffer);
		if (static_cast<size_t>(-1) == ret)
		{
			++sourcePtr;
			--sourceByteCount;
		}
		convertedCharCount = totalSpaceOfDestinationBuffer - availableSpaceOfDestinationBuffer;
	}
	converted.append(destinationBuffer, convertedCharCount);
	delete[] destinationBuffer;
	return converted;
}