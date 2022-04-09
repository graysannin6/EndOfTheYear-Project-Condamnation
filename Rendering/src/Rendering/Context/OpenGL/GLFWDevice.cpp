#include "stdafx.h"

#include <Rendering/Context/OpenGL/GLFWDevice.h>

using namespace Rendering::Context::OpenGL;

GLFWDevice::GLFWDevice() noexcept
{
    Init();
}

GLFWDevice::~GLFWDevice() noexcept
{
    glfwTerminate();
}

void GLFWDevice::Init() noexcept
{
    glfwInit();

    m_window = std::make_shared<GLFWWindow>();

    //Debug
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    //OpenGL Context Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glfwMakeContextCurrent(std::any_cast<GLFWwindow*>(m_window->Data()));

    m_lastTime = static_cast<float>(glfwGetTime());
    m_maxFPS   = 60;
}

bool GLFWDevice::ShouldClose() const noexcept
{
    return m_window->ShouldClose();
}

void GLFWDevice::Render() const noexcept
{
    glfwSwapBuffers(std::any_cast<GLFWwindow*>(m_window->Data()));
}

void GLFWDevice::RefreshEvents() const noexcept
{
    glfwPollEvents();
}

void GLFWDevice::CalculateDeltaTime() noexcept
{
    m_currentTime = static_cast<float>(glfwGetTime());
    m_deltaTime   = m_currentTime - m_lastTime;
    m_deltaTime *= m_maxFPS;
    m_lastTime = m_currentTime;
}

void GLFWDevice::Close() const noexcept
{
    glfwSetWindowShouldClose(std::any_cast<GLFWwindow*>(m_window->Data()), true);
}
