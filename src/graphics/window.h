#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace sengine { namespace graphics {
        class Window 
        {
        private:
            const char *m_Title;
            int m_Width, m_Height;
            GLFWwindow *m_Window;
            bool m_Closed;
        public:
            Window(int width, int height, const char *title);
            ~Window();
            void update();
            void clear() const;
            bool closed() const;

            inline int getWidth() const { return m_Width; }
            inline int getHeight() const { return m_Height; }
        private:
            bool init();
        };
}}