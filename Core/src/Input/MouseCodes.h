#pragma once
#include <ostream>

namespace DXR
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : uint16_t
		{
			ButtonLeft = 0x0001,
			ButtonRight = 0x0002,
			ButtonMiddle = 0x0010,
		};
	}
}