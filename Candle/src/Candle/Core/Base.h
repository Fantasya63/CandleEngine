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
#define CD_ASSERT(x, ...) { if(!(x)) { CD_ERROR("{0}|| Assertion {1} Failed: {2}", __LINE__, #x, __VA_ARGS__); __debugbreak(); } }
#define CD_CORE_ASSERT(x, ...)  { if(!(x)) { CD_CORE_ERROR("{0}|| Assertion {1} Failed: {2}", __LINE__, #x, __VA_ARGS__); __debugbreak(); } }
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