#pragma once

#include "GameEngine/Core.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace GameEngine {

	// Events are currently blocking, when an event occurs it gets dispatched and dealt immediately

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,					          // 00000
		EventCategoryApplication	= BIT(0), // 00001
		EventCategoryInput			= BIT(1), // 00010
		EventCategoryKeyboard		= BIT(2), // 00100
		EventCategoryMouse			= BIT(3), // 01000
		EventCategoryMouseButton	= BIT(4)  // 10000
	};

	// preprocessor directives, the ## concatenates two arguments:
	// #define CREATE_VAR(name) int my_##name;
	// CREATE_VAR(int) // results in: int my_int;

	// the # replace the content with a string:
	// #define str(x) #x
	// std::cout << str(Marco); // results in: std::cout << "Marco";
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class GE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			// EXAMPLE:
			// 01010 EventCategoryInput OR (|) EventCategoryMouse
			// 10000 EventCategoryMouseButton
			// 00000 final result equals to 0, same as false

			// 01010 EventCategoryInput OR (|) EventCategoryMouse
			// 01000 EventCategoryMouse
			// 01000 final result it's 8(DEC), different from 0, same as true

			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	// This code is implemented but not used yet
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; // Returns bool and receives any type of event
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Get the pointer of m_Event, cast it into a T pointer, and then dereference it, getting an m_Event cast into a T type
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// Not working yet, spdlog has broken ostream support
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}