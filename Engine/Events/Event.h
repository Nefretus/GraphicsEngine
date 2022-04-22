#pragma once
#include"CompiledHeader.h"
#include"Core/DllMacro.h"

namespace Engine {

	enum class eventType {
		NONE = 0,
		MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED,
		KEY_PRESSED, KEY_RELEASED,
		WINDOW_CLOSED, WINDOW_RESIZED
	};

#define EVENT_TYPE(type) static const char* GetStaticEventName() { return #type; }\
						 virtual const char* GetEventName() const override { return GetStaticEventName(); }

	class BaseEvent {
	public:
		virtual ~BaseEvent() = default;
		virtual eventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
	private:
		bool handled = false; // potrzebne?
	};

	class EventDispatcher {
	public:
		using EventCallbackFunction = std::function<void(BaseEvent&)>;

		template<typename T>
		void subscribe(const EventCallbackFunction& callbackFunction) {
			callbacks[T::GetStaticEventName()].push_back(callbackFunction);
		}

		template<typename T>
		void dispatch(BaseEvent& event) {
			const std::string eventName = event.GetEventName();
			if (callbacks.find(eventName) == callbacks.end()) {
				std::cout << "Callback function is not set!\n";
				return;
			}
			else {
				// Call callback functions
				for (const auto& callback : callbacks.at(eventName))
					callback(event);
			}
		}

	private:
		std::unordered_map<std::string, std::vector<EventCallbackFunction>> callbacks;
	};
}



