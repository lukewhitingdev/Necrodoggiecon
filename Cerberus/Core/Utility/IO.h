/*****************************************************************//**
 * \file   IO.h
 * \brief  A Utility class to make IO easier to use.
 * 
 * \author Everyone
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <string>

class IO
{
public:

	/**
	 * Returns the extension of a file as a string.
	 * 
	 * \param path to a file.
	 * \return extension of file in path specified.
	 */
	static std::string FindExtension(const std::string& path)
	{
		//store the position of last '.' in the file name
		size_t position = path.find_last_of(".");
		//store the characters after the '.' from the file_name string
		if (position != -1)
			return path.substr(position + 1);
		else
			return "";
	}
};
