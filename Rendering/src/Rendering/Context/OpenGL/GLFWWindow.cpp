#include "stdafx.h"

#include <Rendering/Context/OpenGL/GLFWWindow.h>

using namespace Rendering::Context::OpenGL;

GLFWWindow* GLFWWindow::m_instance;

GLFWWindow::GLFWWindow()
{
    m_glfwWindow = glfwCreateWindow(1920, 1080, "Hello World", glfwGetPrimaryMonitor(), nullptr);

    assert(m_instance == nullptr);
    m_instance = this;

    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    BindKeyCallback();
    BindMouseCallback();
    BindMouseMovementCallback();
}

GLFWWindow::~GLFWWindow()
{
    if (m_glfwWindow != nullptr)
        glfwDestroyWindow(m_glfwWindow);
}

bool GLFWWindow::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(m_glfwWindow);
    
}

const std::any GLFWWindow::Data() const noexcept
{
    return m_glfwWindow;
}

GLFWWindow* GLFWWindow::GetInstance() noexcept
{
    return m_instance;
}

void GLFWWindow::BindKeyCallback() const noexcept
{
    const auto keyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
    {
        IWindow* instanceWindow = GetInstance();

        if (instanceWindow != nullptr)
        {
            if (p_action == GLFW_PRESS)
                instanceWindow->m_keyPressedEvent.Invoke(p_key);

            if (p_action == GLFW_RELEASE)
                instanceWindow->m_keyReleasedEvent.Invoke(p_key);
        }
    };

    glfwSetKeyCallback(m_glfwWindow, keyCallback);
}

void GLFWWindow::BindMouseCallback() const noexcept
{
    const auto mouseCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
    {
        IWindow* instanceWindow = GetInstance();

        if (instanceWindow != nullptr)
        {
            if (p_action == GLFW_PRESS)
                instanceWindow->m_mouseButtonPressedEvent.Invoke(p_button);

            if (p_action == GLFW_RELEASE)
                instanceWindow->m_mouseButtonReleasedEvent.Invoke(p_button);
        }
    };

     glfwSetMouseButtonCallback(m_glfwWindow, mouseCallback);
}

void GLFWWindow::BindMouseMovementCallback() const noexcept
{
    const auto mouseMovementCallback = [](GLFWwindow* p_window, double p_xPos, double p_yPos)
    {
        IWindow* instanceWindow = GetInstance();

        if (instanceWindow != nullptr)
        {
            instanceWindow->m_mouseMoved.Invoke(p_xPos, p_yPos);
        }
    };

    glfwSetCursorPosCallback(m_glfwWindow, mouseMovementCallback);
}
