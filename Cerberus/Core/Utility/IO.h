#pragma once
#include <string>

class IO
{
public:
	static std::string FindExtension(const std::string& path)
	{
		//store the position of last '.' in the file name
		int position = path.find_last_of(".");
		//store the characters after the '.' from the file_name string
		if (position != -1)
			return path.substr(position + 1);
		else
			return "";
	}
};
