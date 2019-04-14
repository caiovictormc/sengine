#include "window.h"

namespace sengine { namespace graphics {
        void windowResize(GLFWwindow *window, int width, int height);

        Window::Window(int width, int height, const char *title) {
            m_Title = title;
            m_Height = height;
            m_Width = width;
            if (!init())
                glfwTerminate();
            glfwSetWindowSizeCallback(m_Window, windowResize);
        }

        Window::~Window() {
            glfwTerminate();
        }

        bool Window::init() {
            if (!glfwInit()) {
                std::cout << "Failed to initialize GLFW" << std::endl;
                return false;
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window) {
                glfwTerminate();
                std::cout << "Failed to created the GLFW window" << std::endl;
                return false;
            }
            glfwMakeContextCurrent(m_Window);

            if (glewInit() != GLEW_OK) {
                std::cout << "Failed to initialze GLEW" << std::endl;
                return false;
            }
            std::cout << glGetString(GL_VERSION) << std::endl;

            return true;
        }

        void Window::clear() const {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        bool Window::closed() const {
            return glfwWindowShouldClose(m_Window) == 1;
        }

        void Window::update() {
            glfwPollEvents();
            glfwSwapBuffers(m_Window);

            #ifdef __APPLE__
                        static bool macMoved = false;

                        if(!macMoved) {
                            int x, y;
                            glfwGetWindowPos(m_Window, &x, &y);
                            glfwSetWindowPos(m_Window, ++x, y);
                            macMoved = true;
                        }
            #endif
        }

        void windowResize(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }
}}
