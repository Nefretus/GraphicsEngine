#pragma once
#include<iostream>
#include<glad/glad.h>
#include<utility>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__));


namespace Engine {
    void GLClearError();

    template <typename Arg, typename... Args>
    bool GLCheckError(Arg&& arg, Args&&... args) {
        GLenum error;
        while (error = glGetError()) {
            std::cout << std::forward<Arg>(arg);
            using expander = int[];
            (void)expander {
                0, (void(std::cout << std::hex << error << std::endl << std::forward<Args>(args)), 0)...
            };
            return false;
        }
        return true; // true means error didnt occur
    }
}
