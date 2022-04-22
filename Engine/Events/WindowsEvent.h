#pragma once
#include "Event.h"
namespace Engine {
	class WindowResizedEvent : public BaseEvent {
	public:
		WindowResizedEvent(int width, int height)
			: width(width), height(height) {}

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }

		static eventType GetStaticType() { return eventType::WINDOW_CLOSED; }
		eventType GetEventType() const override { return GetStaticType(); }
		EVENT_TYPE(WindowResized);

	private:
		int width, height;
	};

	class WindowClosedEvent : public BaseEvent {
	public:
		WindowClosedEvent() {}

		static eventType GetStaticType() { return eventType::WINDOW_RESIZED; }
		eventType GetEventType() const override { return GetStaticType(); }
		EVENT_TYPE(WindowClosed);
	};
}
