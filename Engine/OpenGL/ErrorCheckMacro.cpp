#include"CompiledHeader.h"
#include"ErrorCheckMacro.h"

namespace Engine {
    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }
}
