#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <format>
#include "AISimStudio/logger.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;


class App {
public:
    // Remove the ability to copy 'App' Class in order to prevent double free errors
    App() = default;

    App(const App &other) = delete;

    App &operator =(const App &other) = delete;

    ~App() {
        CORE_INFO("Cleaning up Application!");
        cleanup();
    }

    void run() {
        initWindow();
        initGL();
        mainLoop();
    }

private:
    GLFWwindow *window = nullptr;

    void initWindow() {
        glfwSetErrorCallback(Engine::Log::glfw_error_callback);
        if (glfwInit() == GLFW_FALSE) {
            throw std::runtime_error("Failed to Init GLFW!");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 9);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 9);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "AI Playground!", nullptr, nullptr);
        if (window == nullptr) {
            throw std::runtime_error("Failed to create window");
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetWindowUserPointer(window, this);
    }

    static void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        CORE_TRACE(std::format("Framebuffer resized to, {}x{}", width, height));
    }

    void initGL() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw std::runtime_error("Failed to init OPENGL");
        }

        CORE_INFO(std::format("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION))));
        int framebufferWidth{}, framebufferHeight{};
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void cleanup() {
        if (!(window == nullptr)) {
            glfwDestroyWindow(window);
            window = nullptr;
        }


        glfwTerminate();
    }

    void processInput(GLFWwindow *content) {
        if (glfwGetKey(content, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(content, true);
            CORE_DEBUG("Escape Key Pressed!");
        }
    }
};


int main() {
    Engine::Log::Logger::init();
    App app;
    try {
        app.run();
    } catch (const std::exception &e) {
        CORE_CRITICAL(e.what());
        return 1;
    }

    return 0;
}
