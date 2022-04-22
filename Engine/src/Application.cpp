#include"CompiledHeader.h"
#include"Application.h"
#include<iostream>

namespace Engine {
    void Application::Run() {
        GLFWwindow* window;
        /* Initialize the library */
        if (!glfwInit())
            __debugbreak();
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            __debugbreak();
            glfwTerminate();
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) __debugbreak();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }
}

