#pragma once
#include "Utility/DebugOutput/DebugOutput.h"
#include <string>
#include <chrono>
#include <ctime>
#include <winerror.h>
#include <comdef.h>

class Debug
{

private:
	static DebugOutput* output;
	static int logSize;
	static void initOutput()
	{
		output = new DebugOutput();
	}

	// Helper function for getting the current system time into a std::string.
	static std::string getCurrentTimeString()
	{
		// Get the current time
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		char buffer[8];
		time(&now);

		strftime(buffer, sizeof(buffer), "%H:%M", &newtime);
		std::string timeString(buffer);

		return "[" + timeString + "] ";
	}

	static void CheckLogSize()
	{
		if (output->getItems().size() > logSize)
			output->ClearLog();
	}

public:

	//Disabled Warning for C4840, which is because the compiler doesnt like the fact im passing an varadic args to a varadic args.
	#pragma warning(push)
	#pragma warning( disable : 4840 )

	template<typename ... Args>
	// Logs a message to console. Supports arguments like printf.
	static void Log(const char* fmt, Args ... args)IM_FMTARGS(2)
	{
		if (output == nullptr)
			initOutput();

		CheckLogSize();

		std::string stringInput = std::string(fmt);
		
		stringInput = getCurrentTimeString() + stringInput;

		output->AddLog(stringInput.c_str(), args ...);
	};

	template<typename ... Args>
	static void LogError(const char* fmt, Args ... args)IM_FMTARGS(2)
	{
		if (output == nullptr)
			initOutput();

		CheckLogSize();

		std::string stringInput = std::string(fmt);

		stringInput = "[error] " + getCurrentTimeString() + stringInput;

		output->AddLog(stringInput.c_str(), args ...);
	};

	template<typename ... Args>
	static void LogHResult(HRESULT hr, const char* fmt,Args ... args)IM_FMTARGS(2)
	{
		if (output == nullptr)
			initOutput();

		CheckLogSize();

		std::string stringInput = "";

		char* convOutput = nullptr;

		if(FAILED(hr))
		{
			// Get the Error message out of the HResult.
			_com_error err(hr);
			LPCTSTR errMsg = err.ErrorMessage();
			convOutput = new char[256];
			size_t numConverted = 0;
			size_t size = 256;

			wcstombs_s(&numConverted, convOutput, size, errMsg, size-1);

			std::string errorString = std::string(convOutput);

			stringInput = "[HRESULT][error] " + getCurrentTimeString() + fmt + " " + errorString;
		}else
		{
			stringInput = "[HRESULT]" + getCurrentTimeString() + fmt + " Completed Sucessfully.";
		}
		output->AddLog(stringInput.c_str(), args ...);

		if (FAILED(hr))
			delete[] convOutput;
	}

	#pragma warning(pop)

	static DebugOutput* getOutput() 
	{
		if (!output)
			initOutput();

		return output;
	}


};