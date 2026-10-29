#pragma once
#include <filesystem>
#include <AISimStudio/logger.h>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

    namespace Engine::Render {
        class Shader {
        public:
            Shader() = default;

            Shader(const Shader &other) = delete;

            Shader &operator = (const Shader &other) = delete;
            ~Shader();


            // Constructor declaration
            Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShader);

            void bindShader();

        private:
            unsigned int shaderProgram;
            unsigned int vertexShader;
            unsigned int fragmentShader;
            std::filesystem::path vertexShaderPath;   // Member variables matching the parameter names
            std::filesystem::path fragmentShaderPath;
            static std::string extractShader(const std::filesystem::path& shaderPath);
        };
    } // Render

