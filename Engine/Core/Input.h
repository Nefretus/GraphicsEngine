#pragma once
#include"DllMacro.h"
#include<memory>

// THIS CLASS IS SINGLETON
namespace Engine {
	class Input {
	public:
		static bool IsKeyPressed(int keycode) { return GetInstance()->IsKeyPressedImpl(keycode); }
		static bool IsMousePressed(int button) { return GetInstance()->IsKeyPressedImpl(button); }
		static float GetMousePosX() { return GetInstance()->GetMousePosXImpl(); }
		static float GetMousePosY() { return GetInstance()->GetMousePosYImpl(); }

		Input(Input&) = delete;
		void operator=(const Input&) = delete;
	private:
		static float GetMousePosXImpl();
		static float GetMousePosYImpl();
		static bool IsKeyPressedImpl(int keycode);
		static bool IsMousePressedImpl(int button);
		Input() : posX(0), posY(0) {}
		static Input* GetInstance();
		static Input* instance;
		float posX, posY;
	};
};
