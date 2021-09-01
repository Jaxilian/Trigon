#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

enum class DebugColor
{
	Green,
	White,
	Yellow,
	Red
};

enum class DebugType
{
	None,
	Pick,
	Create,
	Destroy,
	Release,
	Bind,
	Delete,
	Remove,
	Compile,
	Init,
	Load
};

enum class DebugResult
{
	None,
	Success,
	Failed,
	Warning,
};

class Debug
{
public:
	static void Log(const char* format, ...)
	{
#ifdef _DEBUG
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stderr, format, argptr);
		va_end(argptr);
		printf("\n");
#endif
	}

	static void LogError(const char* format, ...)
	{
#ifdef _DEBUG
		printf("\033[0;31m");
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stderr, format, argptr);
		va_end(argptr);
		printf("\033[0m\n");
#endif
	}

	//Prints out the context followed by result in specific color
	static void LogStatus(DebugType type, DebugResult result, DebugColor color, const char* name, ...)
	{
#ifdef _DEBUG
		int length = 0;

		switch (type)
		{
		case DebugType::None:											break;
		case DebugType::Create:		printf("Create  "); length += 8;	break;
		case DebugType::Delete:		printf("Delete  "); length += 8;	break;
		case DebugType::Remove:		printf("Remove  "); length += 8;	break;
		case DebugType::Init:		printf("Init    "); length += 8;	break;
		case DebugType::Compile:	printf("Compile "); length += 8;	break;
		case DebugType::Load:		printf("Load    "); length += 8;	break;
		case DebugType::Release:	printf("Release "); length += 8;	break;
		case DebugType::Bind:		printf("Bind    "); length += 8;	break;
		case DebugType::Destroy:	printf("Destroy "); length += 8;	break;
		case DebugType::Pick:		printf("Pick    "); length += 8;	break;
		default:break;
		}


		va_list argptr;
		va_start(argptr, name);
		vfprintf(stderr, name, argptr);
		va_end(argptr);

		if (argptr != nullptr && strlen(argptr) > 0) length += (int)strlen(argptr);

		length += (int)strlen(name);

		//text += "...";

		std::string emptySpace = "";

		if (length < 40)
		{
			for (int i = 0; i < 30 - length; i++)
			{
				emptySpace += ' ';
			}

			printf("%s", emptySpace.c_str());

			switch (color)
			{
			case DebugColor::Green:
				printf("\033[0;32m");
				break;
			case DebugColor::White:
				printf("\33[0m");
				break;
			case DebugColor::Yellow:
				printf("\033[0;33m");
				break;
			case DebugColor::Red:
				printf("\033[0;31m");
				break;
			default:
				LogError("DebugColor not valid");
				break;
			}

			switch (result)
			{
			case DebugResult::Success:	printf("Success..."); break;
			case DebugResult::Failed:	printf("Failed..."); break;
			case DebugResult::None:		printf(""); break;
			case DebugResult::Warning:	printf("Waning..."); break;
			}
			printf("\33[0m");
		}
		else
		{
			Debug::LogWarning("Output LogStatus reached maximum length, perhaps adjust it? Skipping output");
		}

		printf("\n");
#endif
	};

	static void LogWarning(const char* format, ...)
	{
#ifdef _DEBUG
		printf("\n\033[0;33m");
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stderr, format, argptr);
		va_end(argptr);
		printf("\033[0m");
#endif
	}

	static void LogSuccess(const char* format, ...)
	{
#ifdef _DEBUG
		printf("\n\033[0;32m");
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stderr, format, argptr);
		va_end(argptr);
		printf("\033[0m");
#endif
	}
};


#endif // !OctaSystem_H

