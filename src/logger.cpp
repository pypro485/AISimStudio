#include "AISimStudio/logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

#include "GLFW/glfw3.h"


    namespace Engine::Log {
        std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

        void Logger::init() {
            spdlog::set_pattern("[%T] [thread %t] %^[%l]%$ [ENGINE] %v");
            s_CoreLogger = spdlog::stdout_color_mt("CORE");
#ifndef NDEBUG
            s_CoreLogger->set_level(spdlog::level::debug);
#else
            s_CoreLogger->set_level(spdlog::level::info);
#endif
        }

        void glfw_error_callback(int error_code, const char *description) {
            switch (error_code) {
                case GLFW_NOT_INITIALIZED:
                case GLFW_API_UNAVAILABLE:
                case GLFW_VERSION_UNAVAILABLE:
                case GLFW_PLATFORM_UNAVAILABLE:
                case GLFW_OUT_OF_MEMORY:
                case GLFW_PLATFORM_ERROR:
                    CORE_CRITICAL(std::format("{}: {}", error_code, description));
                    break;
                case GLFW_NO_CURRENT_CONTEXT:
                case GLFW_NO_WINDOW_CONTEXT:
                case GLFW_INVALID_ENUM:
                case GLFW_INVALID_VALUE:
                    CORE_ERROR(std::format("{}: {}", error_code, description));
                    break;
                case GLFW_FORMAT_UNAVAILABLE:
                case GLFW_CURSOR_UNAVAILABLE:
                case GLFW_FEATURE_UNAVAILABLE:
                case GLFW_FEATURE_UNIMPLEMENTED:
                    CORE_WARN(std::format("{}: {}", error_code, description));
                    break;
                default:
                    CORE_ERROR(std::format("{}: {}", error_code, description));
            }
        }
    }

