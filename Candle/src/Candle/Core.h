#pragma once

#include <memory>

//#ifdef CD_PLATFORM_WINDOWS
//	// Removed DLL Import export
//#else
//	#error Candle Only Supports Windows
//#endif // CD_PLATFORM_WINDOWS


#ifdef CD_DEBUG
	#define CD_ENABLE_ASSERTS
#endif


#ifdef  CD_ENABLE_ASSERTS
	#define CD_ASSERT(x, ...) { if(!(x)) { CD_ERROR("{0}|| Assertion Failed: {1}", __LINE__, __VA_ARGS__); __debugbreak(); } }
	#define CD_CORE_ASSERT(x, ...)  { if(!(x)) { CD_CORE_ERROR("{0}|| Assertion Failed: {1}", __LINE__, __VA_ARGS__); __debugbreak(); } }
#else
	#define CD_ASSERT(x, ...)
	#define CD_CORE_ASSERT(x, ...)
#endif //  CD_ENABLE_ASSERTS

#define CD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)

namespace Candle
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}