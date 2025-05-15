#pragma once

#include "Event.h"

namespace GameEngine {

	class GE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		inline int GetScanCode() const { return m_ScanCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode, int scancode)
			: m_KeyCode(keycode), m_ScanCode(scancode) {}

		int m_KeyCode;
		int m_ScanCode;
	};

	class GE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int scancode, int repeatCount)
			: KeyEvent(keycode, scancode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent, keycode: " << m_KeyCode <<
				", scancode: " << m_ScanCode <<
				" (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class GE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int scancode)
			: KeyEvent(keycode, scancode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent, keycode: " << m_KeyCode << ", scancode: " << m_ScanCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class GE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode, 0) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent, codepoint: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	private:
	};
}