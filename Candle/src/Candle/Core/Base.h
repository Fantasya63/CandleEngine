#pragma once

#include "PlatformDetection.h"

#include <memory>

//#ifdef CD_PLATFORM_WINDOWS
//	// Removed DLL Import export
//#else
//	#error Candle Only Supports Windows
//#endif // CD_PLATFORM_WINDOWS

#ifdef CD_DEBUG
	#if defined(CD_PLATFORM_WINDOWS)
		#define CD_DEBUGBREAK() __debugbreak()
	#elif defined(CD_PLATFORM_LINUX)
		#include <signal.h>
		#define CD_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define CD_ENABLE_ASSERTS
#else
	#define CD_DEBUGBREAK()
#endif

#define CD_EXPAND_MACRO(x) x
#define CD_STRINGIFY_MACRO(x) #x


#ifdef  CD_ENABLE_ASSERTS
#define CD_ASSERT(x, ...) { if(!(x)) { CD_ERROR("{0}|| Assertion {1} Failed: {2}", __LINE__, #x, __VA_ARGS__); CD_DEBUGBREAK(); } }
#define CD_CORE_ASSERT(x, ...)  { if(!(x)) { CD_CORE_ERROR("{0}|| Assertion {1} Failed: {2}", __LINE__, #x, __VA_ARGS__); CD_DEBUGBREAK(); } }
#else
	#define CD_ASSERT(x, ...)
	#define CD_CORE_ASSERT(x, ...)
#endif //  CD_ENABLE_ASSERTS

// Idk how this works tbh
#define CD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define BIT(x) (1 << x)

namespace Candle
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
