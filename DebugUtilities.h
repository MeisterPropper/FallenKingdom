#pragma once
#include <Windows.h>
#include <string>

class DebugUtilities {
public:
	static inline void printLn(char * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
		OutputDebugStringA(string);
		OutputDebugStringA("\n");
#endif
	}
	static inline void printLn(wchar_t * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
		OutputDebugStringW(string);
		OutputDebugStringA("\n");
#endif
	}
	static inline void printLn(std::string & string) {
#if defined(_MSC_VER) && defined(_DEBUG)
		OutputDebugStringA(string.c_str());
		OutputDebugStringA("\n");
#endif
	}

private:
};
