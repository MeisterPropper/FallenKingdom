#pragma once
#include <Windows.h>
#include <string>

class DebugUtilities {
public:
	static inline void printLn(char * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[BUILD][FallenKingdomDebug] : ");
			OutputDebugStringA(string);
			OutputDebugStringA("\n");
#endif
	}
	static inline void printLn(wchar_t * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[BUILD][FallenKingdomDebug] : ");
			OutputDebugStringW(string);
			OutputDebugStringA("\n");
#endif
	}
	static inline void printLn(std::string & string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[BUILD][FallenKingdomDebug] : ");
			OutputDebugStringA(string.c_str());
			OutputDebugStringA("\n");
#endif
	}
		static inline void printInfo(char * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[INFO][FallenKingdomDebug] : ");
			OutputDebugStringA(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printInfo(wchar_t * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[INFO][FallenKingdomDebug] : ");
			OutputDebugStringW(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printInfo(std::string & string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[INFO][FallenKingdomDebug] : ");
			OutputDebugStringA(string.c_str());
			OutputDebugStringA("\n");
#endif
		}
		static inline void printErr(char * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[ERROR][FallenKingdomDebug] : ");
			OutputDebugStringA(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printErr(wchar_t * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[ERROR][FallenKingdomDebug] : ");
			OutputDebugStringW(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printErr(std::string & string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[ERROR][FallenKingdomDebug] : ");
			OutputDebugStringA(string.c_str());
			OutputDebugStringA("\n");
#endif
		}
		static inline void printWarn(char * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[WARN][FallenKingdomDebug] : ");
			OutputDebugStringA(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printWarn(wchar_t * string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[WARN][FallenKingdomDebug] : ");
			OutputDebugStringW(string);
			OutputDebugStringA("\n");
#endif
		}
		static inline void printWarn(std::string & string) {
#if defined(_MSC_VER) && defined(_DEBUG)
			OutputDebugStringA("[WARN][FallenKingdomDebug] : ");
			OutputDebugStringA(string.c_str());
			OutputDebugStringA("\n");
#endif
		}
	
private:
};
