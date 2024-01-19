#pragma once

namespace Candle
{
	class Platform
	{
	public:
		inline static float GetTime() { return s_Instance->GetTimeImpl(); }

	protected:
		virtual float GetTimeImpl() = 0;


	private:
		static Platform* s_Instance;
	};
}