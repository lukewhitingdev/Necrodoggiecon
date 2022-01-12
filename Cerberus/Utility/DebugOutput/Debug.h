#pragma once
#include "UI/Debug/DebugOutput.h"
#include <string>
#include <chrono>
#include <ctime>

class Debug
{

private:
	static DebugOutput* output;
	static void initOutput()
	{
		output = new DebugOutput();
	}

	static std::string getCurrentTimeString()
	{
		// Get the current time
		time_t Time;
		char buffer[8];
		time(&Time);

		strftime(buffer, sizeof(buffer), "%H:%M", localtime(&Time));
		std::string timeString(buffer);

		return "[" + timeString + "] ";
	}

public:
	template<typename ... Args>
	// Logs a message to console. Supports arguments like printf.
	static void Log(const char* fmt, Args ... args)IM_FMTARGS(2)
	{
		if (output == nullptr)
			initOutput();

		std::string stringInput = std::string(fmt);
		
		stringInput = getCurrentTimeString() + stringInput;

		output->AddLog(stringInput.c_str(), args ...);
	};

	template<typename ... Args>
	static void LogError(const char* fmt, Args ... args)IM_FMTARGS(2)
	{
		if (output == nullptr)
			initOutput();

		std::string stringInput = std::string(fmt);

		stringInput = "[error] " + getCurrentTimeString() + stringInput;

		output->AddLog(stringInput.c_str(), args ...);
	};

	static DebugOutput* getOutput() 
	{
		if (!output)
			initOutput();

		return output;
	}


};