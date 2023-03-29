#pragma once

#ifdef CD_PLATFORM_WINDOWS
	#ifdef CD_BUILD_DLL
		#define CANDLE_API __declspec(dllexport)
	#else
		#define CANDLE_API __declspec(dllimport)
	#endif // CD_BUILD_DLL
#else
	#error Candle Only Supports Windows
#endif // CD_PLATFORM_WINDOWS

#ifdef  CD_ENABLE_ASSERTS
	#define CD_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("{0}|| Assertion Failed: {1}", __LINE__, __VA_ARGS__); __debugbreak(); } }
	#define CD_CORE_ASSERT(x, ...)  { if(!(x)) { HZ_CORE_ERROR("{0}|| Assertion Failed: {1}", __LINE__, __VA_ARGS__); __debugbreak(); } }
#else
	#define CD_ASSERT(x, ...)
	#define CD_CORE_ASSERT(x, ...)
#endif //  CD_ENABLE_ASSERTS

#define CD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)