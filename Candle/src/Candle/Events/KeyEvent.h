#pragma once

#include "Event.h"

namespace Candle {

	class CANDLE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard || EventCategoryInput)

	protected:
		KeyEvent(int _keyCode)
			: m_KeyCode(_keyCode) {}

		int m_KeyCode;
	};


	class CANDLE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int _keyCode, int _repeatCount)
		: KeyEvent(_keyCode), m_RepeatCount(_repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		//Should only used for debug purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};


	class CANDLE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int _keyCode)
			: KeyEvent(_keyCode) {}

		//Should only used for debug purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}