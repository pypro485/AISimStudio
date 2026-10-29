#include "../include/AISimStudio/shader.h"

#include <glad/glad.h>


namespace Engine::Render {


    Shader::~Shader() {
        glDeleteProgram(shaderProgram);
    }

        Shader::Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) {
            std::string vertexCode = extractShader(vertexShaderPath);
            std::string fragmentCode = extractShader(fragmentShaderPath);
            const char* vertexSource = vertexCode.c_str();
            const char* fragmentSource = fragmentCode.c_str();
            shaderProgram = glCreateProgram();
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(vertexShader, 1, &vertexSource, nullptr);
            glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
            glCompileShader(vertexShader);
            glCompileShader(fragmentShader);

            int success{};
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
                throw std::runtime_error(std::format("Failed to compile vertex shader!: {}", infoLog));
            }

            CORE_DEBUG(std::format("Compiled vertex shader {}", vertexShaderPath.string()));

            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
                throw std::runtime_error(std::format("Failed to compile fragment shader!: {}", infoLog));
            }
            CORE_DEBUG(std::format("Compiled fragment shader {}", fragmentShaderPath.string()));

            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                throw std::runtime_error(std::format("Failed to link shaders! {}", infoLog));
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            CORE_INFO("Linked Shaders to program");
        }

        void Shader::bindShader() {
            glUseProgram(shaderProgram);
            CORE_TRACE("Bound Shaders");
        }

        std::string Shader::extractShader(const std::filesystem::path& shaderPath) {
            std::ifstream file(shaderPath);

            if (!file.is_open()) {
                throw std::runtime_error(std::format("Failed to open shader file {}", shaderPath.string()));
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }


    } // Render
