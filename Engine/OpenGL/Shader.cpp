#include"CompiledHeader.h"
#include "Shader.h"
#include"ErrorCheckMacro.h"

namespace Engine {

    struct ShaderSource {
        std::string VertexShader;
        std::string FragmentShader;
    };

    Shader::Shader(const std::string& filePath) : fileName(filePath) {
        ShaderSource shader = loadShaders();
        createShaderProgram(shader.FragmentShader, shader.VertexShader);
    }

    Shader::~Shader() {
        glDeleteProgram(program);
    }

    std::string Shader::getShadersDirectory() {
        return std::string(_SOLUTIONDIR + std::string(R"(Resources\shaders\Shader.shader)"));
    }

    ShaderSource Shader::loadShaders() const {
        std::ifstream stream;
        stream.open(fileName, std::ifstream::in);
        if (stream.is_open()) {
            std::cout << "File opened\n";
            enum class ShaderType {
                VERTEX = 0,
                FRAGMENT = 1
            };
            ShaderType type;
            std::string line;
            std::ostringstream ss[2];
            while (getline(stream, line)) {
                if (line.find("#vertex shader") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("#fragment shader") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
                else {
                    ss[static_cast<int>(type)] << line << '\n';
                }
            }
            return { ss[0].str(), ss[1].str() };
        }
        else {
            std::cout << "File could not be open\n";
            __debugbreak();
            exit(1); // error
        }
    }

    void Shader::createShaderProgram(const std::string& fragmentShaderSource, const std::string& vertexShaderSource) {
        program = glCreateProgram();
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    GLuint Shader::compileShader(GLuint type, const std::string& source) const {
        GLuint id = glCreateShader(type);
        const char* scr = source.c_str();
        glShaderSource(id, 1, &scr, NULL);
        glCompileShader(id);
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << message << std::endl;
            glDeleteShader(id);
            delete[] message;
            return 0;
        }
        return id;
    }

    void Shader::bind() const {
        glUseProgram(program);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    GLint Shader::getUniformLocation(const std::string& name) const {
        if (locationCache.find(name) != locationCache.end()) {
            return locationCache[name];
        }
        GLint location;
        location = glGetUniformLocation(program, name.c_str());
        if (location == -1) {
            std::cout << "Uniform not found\n";
        }
        locationCache[name] = location;
        return location;
    }

    void Shader::setUniformInt(const std::string& name, int v0) {
        GLCall(glUniform1i(getUniformLocation(name), v0));
    }

    void Shader::setUniformIntArray(const std::string& name, GLuint count, GLint* values) {
        GLCall(glUniform1iv(getUniformLocation(name), count, values));
    }

    void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }
}