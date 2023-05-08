#pragma once

#include <iostream>

#ifdef DXR_DEBUG
#include <Windows.h>
#include <comdef.h>
#define DXR_ASSERT(x) {if(FAILED(x)){_com_error err(x);LPCTSTR errMsg = err.ErrorMessage();	__debugbreak();}}
#else
#define DXR_ASSERT(x)
#endif

#define BIT(x) (1 << x)

#define DXR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include <memory>

template<typename ...Args>
void DXR_INFO(Args && ...args)
{
	(std::cout << ... << args);
	std::cout << std::endl;
}

namespace DXR
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