#include"CompiledHeader.h"
#include"Window.h"
#include"Events/KeyEvent.h"
#include"Events/MouseEvent.h"
#include"Events/WindowsEvent.h"
#include"Events/Event.h"

namespace Engine {
	static bool GLFWinitialized = false;

	Window::Window(const WindowProperties& _properties) {
		properties.height = _properties.height;
		properties.width = _properties.width;
		properties.title = _properties.title;
		if (!GLFWinitialized)
			if (!glfwInit())
				throw WindowInitError();
		//setHints();
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			throw WindowInitError();
		} 
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) __debugbreak();
		glfwSwapInterval(1);
		glfwSetWindowUserPointer(window, &properties);
		GLFWinitialized = true;
		setGLFWCallbacks();
		TurnOnBlending();
	}

	void Window::setGLFWCallbacks() {
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowProperties& data = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent e(key);
				data.eventCallbackFuntion(e);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				data.eventCallbackFuntion(e);
				break;
			}
			default:
				std::cout << "Repeat event ?\n;";
				return;
			}
			// tutaj maly problem, dlaczego nie mozna przekazac do lambdy po prostu [this] (...) {...}  i zrobic - properties.eventCallbackFuntion(e);
			// odpowiedz : https://stackoverflow.com/questions/7852101/c-lambda-with-captures-as-a-function-pointer 
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowProperties& data = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent e(xpos, ypos);
			data.eventCallbackFuntion(e);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowProperties& data = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			switch (action) {
			case GLFW_PRESS: {
				MousePressedEvent e(button);
				data.eventCallbackFuntion(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseReleasedEvent e(button);
				data.eventCallbackFuntion(e);
				break;
			}
			default:
				std::cout << "Repeat event ?\n;";
				return;
			}
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowProperties& data = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			WindowClosedEvent e;
			data.eventCallbackFuntion(e);
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowProperties& data = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;
			WindowResizedEvent e(width, height);
			data.eventCallbackFuntion(e);
			});
	}

	void Window::TurnOnBlending() {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void Window::setHints() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	std::unique_ptr<Window> Window::create(const WindowProperties& _properties) {
		return std::make_unique<Window>(_properties);
	}

	void Window::onUpdate() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Window::~Window() {
		if (GLFWinitialized)
			glfwTerminate();
		glfwDestroyWindow(window);
	}
}