#pragma once

#include <algorithm> // For std::min and std::max.

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

namespace MathUtils
{
	// Clamp a value between a min and max range.
	template<typename T>
	constexpr const T& clamp(const T& val, const T& min, const T& max)
	{
		return val < min ? min : val > max ? max : val;
	}
}