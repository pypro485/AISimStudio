#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <format>
#include "AISimStudio/logger.h"
#include "AISimStudio/shader.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

class App {
public:
    // Remove the ability to copy 'App' Class in order to prevent double free errors
    App() = default;

    App(const App &other) = delete;

    App &operator = (const App &other) = delete;

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
    unsigned int VBO{};
    unsigned int VAO{};
    std::unique_ptr<Engine::Render::Shader> shader;
    GLFWwindow *window = nullptr;

    void initWindow() {
        glfwSetErrorCallback(Engine::Log::glfw_error_callback);
        if (glfwInit() == GLFW_FALSE) {
            throw std::runtime_error("Failed to Init GLFW!");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error("Failed to init OPENGL");
        }

        CORE_INFO(std::format("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION))));
        int framebufferWidth{}, framebufferHeight{};
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        CORE_INFO(std::format("Generated VBO with ID: {}", VBO));
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        CORE_INFO("Sent vertex data to VBO");
        shader = std::make_unique<Engine::Render::Shader>(R"(C:\dev\AISimStudio\shaders\vertex.glsl)",R"(C:\dev\AISimStudio\shaders\fragment.glsl)");


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);



    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            shader->bindShader();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        shader.reset();
        if (window != nullptr) {
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
    try {
        App app;
        app.run();
    } catch (const std::exception &e) {
        CORE_CRITICAL(e.what());
        return 1;
    }

    return 0;
}
