#pragma once

#include "Candle/Core.h"
#include <Candle/Events/Event.h>

//TODO At macros to remove debug names
//TODO ADD eneble disable layers
namespace Candle
{
	class CANDLE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

