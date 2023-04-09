#pragma once

#include "Event.h"

namespace Candle {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_x(x), m_y(y) {}

		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseEvent: " << m_x << ", " << m_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_x, m_y;
	};

	class MouseScrolledEvent : public Candle::Event
	{
	public:
		MouseScrolledEvent(float _xOffset, float _yOffset)
			: m_XOffset(_xOffset), m_YOffset(_yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int _button)
			: m_Button(_button) {}

		int m_Button;
	};

	class MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int button)
			: MouseButtonEvent(button) {}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}