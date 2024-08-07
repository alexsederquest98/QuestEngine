#ifndef QUEST_SMART_POINTER_H_INCLUDED
#define QUEST_SMART_POINTER_H_INCLUDED

#include <memory>

namespace QE
{
	// Smart pointer wrappers
	template <typename T>
	using RefPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr RefPtr<T> CreateRefPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using ScopedPtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ScopedPtr<T> CreateScopedPtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using WeakRefPtr = std::weak_ptr<T>;
}

#endif // QUEST_SMART_POINTER_H_INCLUDED
