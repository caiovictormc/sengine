#include "window.h"

namespace sengine { namespace graphics {
        bool Window::m_Keys[MAX_KEYS];
        bool Window::m_MouseButton[MAX_BUTTONS];
        double Window::my;
        double Window::mx;
        void window_resize(GLFWwindow *window, int width, int height);
        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        // void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods); 

        Window::Window(int width, int height, const char *title) {
            m_Title = title;
            m_Height = height;
            m_Width = width;
            if (!init())
                glfwTerminate();
            glfwSetWindowSizeCallback(m_Window, window_resize);

            for (int i=0; i < MAX_KEYS; i++) {
                m_Keys[i] = false;
            }
            for (int i=0; i < MAX_BUTTONS; i++) {
                m_MouseButton [i] = false;
            }
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
            glfwSetWindowUserPointer(m_Window, this);
            glfwSetKeyCallback(m_Window, key_callback);
            glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
            glfwSetCursorPosCallback(m_Window, cursor_position_callback);

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

        bool Window::isKeyPressed(unsigned int keycode) {
            if (keycode >= MAX_KEYS)
                return false;
            return m_Keys[keycode];
        }

        bool Window::isButtonMousePressed(unsigned int button) {
            if (button >= MAX_BUTTONS)
                return false;
            return m_MouseButton[button];
        }

        void Window::getMousePosition(double &x, double &y) {
            x = mx;
            y = mx;
        }

        void window_resize(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_Keys[key] = (action != GLFW_RELEASE);
        }

        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_MouseButton[button] = (action != GLFW_RELEASE);
        }

        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos; 
        }
}}
