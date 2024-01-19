#pragma once
#include "Candle/Core/Platform.h"

namespace Candle
{
	class PlatformWindows : public Platform
	{
	protected:
		virtual float GetTimeImpl() override;
	};

}

