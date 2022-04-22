#pragma once
#include"Event.h"

namespace Engine {
	class KeyEvent : public BaseEvent {
	public:
		int getKeyCode() { return key; }
	protected:
		KeyEvent(int _key) : key(_key) {}
		int key;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key) :
			KeyEvent(key) {}

		static eventType GetStaticType() { return eventType::KEY_PRESSED; }
		eventType GetEventType() const override { return GetStaticType(); }

		EVENT_TYPE(KeyPressed);
	private:
		// repeat count eventually 
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key) :
			KeyEvent(key) {}

		static eventType GetStaticType() { return eventType::KEY_RELEASED; }
		eventType GetEventType() const override { return GetStaticType(); }
		EVENT_TYPE(KeyReleased);
	};
}
