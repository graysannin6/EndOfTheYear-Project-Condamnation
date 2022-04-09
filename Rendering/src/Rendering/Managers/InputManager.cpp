#include "stdafx.h"

#include <Rendering/Managers/InputManager.h>

std::unique_ptr<Rendering::Managers::InputManager> Rendering::Managers::InputManager::m_instance;

Rendering::Managers::InputManager::InputManager(
    const std::shared_ptr<Context::IWindow>& p_window) noexcept
    : m_window{p_window}
{
    m_idKeyPressedListener = p_window->m_keyPressedEvent.AddListener(
        std::bind(&InputManager::OnKeyPressed, this, std::placeholders::_1));

    m_idKeyReleasedListener = p_window->m_keyReleasedEvent.AddListener(
        std::bind(&InputManager::OnKeyReleased, this, std::placeholders::_1));

    m_idMouseButtonPressedListener = p_window->m_mouseButtonPressedEvent.AddListener(
        std::bind(&InputManager::OnMouseButtonPressed, this, std::placeholders::_1));

    m_idMouseButtonReleasedListener = p_window->m_mouseButtonReleasedEvent.AddListener(
        std::bind(&InputManager::OnMouseButtonReleased, this, std::placeholders::_1));
    m_mouseCursorPos = std::make_tuple(0.0, 0.0);
}

Rendering::Managers::InputManager::~InputManager() noexcept
{
    assert(m_window->m_keyPressedEvent.RemoveListener(m_idKeyPressedListener));
    assert(m_window->m_keyReleasedEvent.RemoveListener(m_idKeyReleasedListener));
    assert(m_window->m_mouseButtonPressedEvent.RemoveListener(m_idMouseButtonPressedListener));
    assert(m_window->m_mouseButtonReleasedEvent.RemoveListener(m_idMouseButtonReleasedListener));
}

void Rendering::Managers::InputManager::Init(const std::shared_ptr<Context::IWindow>& p_window)
{
	m_instance = std::make_unique<InputManager>(p_window);
}

bool Rendering::Managers::InputManager::GetKeyDown(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == KeyState::KeyDown)
        {
            m_inputBuffer.at(p_keyCode) = KeyState::Completed;
            return true;
        }
    return false;

}

bool Rendering::Managers::InputManager::GetKeyUp(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == KeyState::KeyUp)
        {
            m_inputBuffer.at(p_keyCode) = KeyState::Completed;
            return true;
        }
    return false;
}

bool Rendering::Managers::InputManager::GetKey(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == KeyState::KeyDown)
            return true;
    return false;
}

void Rendering::Managers::InputManager::OnKeyPressed(int p_key)
{
    m_inputBuffer.insert_or_assign(p_key, KeyState::KeyDown);
}

void Rendering::Managers::InputManager::OnKeyReleased(int p_key)
{
    m_inputBuffer.insert_or_assign(p_key, KeyState::KeyUp);
}

void Rendering::Managers::InputManager::OnMouseButtonPressed(int p_button)
{
    m_inputBuffer.insert_or_assign(p_button, KeyState::KeyDown);
}

void Rendering::Managers::InputManager::OnMouseButtonReleased(int p_button)
{
    m_inputBuffer.insert_or_assign(p_button, KeyState::KeyUp);
}

void Rendering::Managers::InputManager::UpdateCursorPos()
{
    glfwGetCursorPos(std::any_cast<GLFWwindow*>(m_window->Data()), &std::get<0>(m_mouseCursorPos), &std::get<1>(m_mouseCursorPos));
}
