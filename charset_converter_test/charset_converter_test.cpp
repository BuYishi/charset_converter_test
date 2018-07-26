#include <iostream>
#include <fstream>
#include "CharsetConverter.h"
int main()
{
	std::string filename("text_utf-8.txt");
	std::ifstream ifs(filename, std::ifstream::in);
	if (ifs)
	{
		std::string line, utf8Text;
		while (std::getline(ifs, line))
			utf8Text.append(line + "\n");
		try
		{
			const std::string &converted = CharsetConverter("GBK", "UTF-8").convert(utf8Text);
			std::cout << converted << std::endl;
			filename = "text_gbk.txt";
			std::ofstream ofs(filename, std::ofstream::out);
			if (ofs)
			{
				ofs.write(converted.c_str(), converted.length());
			}
			else
				std::cerr << "Cannot open file: " << filename << std::endl;
		}
		catch (const std::string &ex)
		{
			std::cerr << ex << std::endl;
		}
	}
	else
		std::cerr << "Cannot open file: " << filename << std::endl;
	std::system("pause");
	return 0;
}