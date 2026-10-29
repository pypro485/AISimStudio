#pragma once
#include <spdlog/spdlog.h>
#include <memory>


    namespace Engine::Log {

        class Logger {
        public:
            static void init();
            static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
        };


        void glfw_error_callback(int error_code, const char* description);
    } // namespace Engine::Log


// Short Core Engine Macros remain here
#define CORE_TRACE(...)    ::Engine::Log::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     ::Engine::Log::Logger::getCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Engine::Log::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Engine::Log::Logger::getCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Engine::Log::Logger::getCoreLogger()->critical(__VA_ARGS__)
#define CORE_DEBUG(...) ::Engine::Log::Logger::getCoreLogger()->debug(__VA_ARGS__)

