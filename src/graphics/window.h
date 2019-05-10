#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32


namespace sengine { namespace graphics {
        class Window 
        {
        private:
            const char *m_Title;
            int m_Width, m_Height;
            GLFWwindow *m_Window;
            bool m_Closed;
            static bool m_Keys[MAX_KEYS];
            static bool m_MouseButton[MAX_BUTTONS];
            static double mx, my;
        public:
            Window(int width, int height, const char *title);
            ~Window();
            void update();
            void clear() const;
            bool closed() const;

            inline int getWidth() const { return m_Width; }
            inline int getHeight() const { return m_Height; }

            static bool isKeyPressed(unsigned int keycode);
            static bool isButtonMousePressed(unsigned int button);
            static void getMousePosition(double &x, double &y);
        private:
            bool init();
            friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
            friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
            friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
            // static void callback(GLFWwindow *window, int key, int scancode, int action, int mods); 
        };
}}