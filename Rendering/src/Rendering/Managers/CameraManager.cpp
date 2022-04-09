#include "stdafx.h"

#include <Rendering/Managers/CameraManager.h>
#include <Rendering/Managers/InputManager.h>

Rendering::Managers::CameraManager::CameraManager(const glm::vec3& p_position,
    const glm::vec3& p_up, const float& p_yaw, const float& p_pitch, bool p_freeFloat)
{
    Init(p_position, p_up, p_yaw, p_pitch);
	m_freeFloat = p_freeFloat;
}

Rendering::Managers::CameraManager::CameraManager(const float& p_posX, const float& p_posY,
    const float& p_posZ, const float& p_upX, const float& p_upY, const float& p_upZ, const float& p_yaw, const float& p_pitch)
{
    Init(glm::vec3(p_posX, p_posY, p_posZ),
        glm::vec3(p_upX, p_upY, p_upZ),
        p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::Init(const glm::vec3& p_position, const glm::vec3& p_up,
    const float& p_yaw, const float& p_pitch)
{
    m_camera = std::make_shared<LowRenderer::Camera>(p_position, p_up, p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::ProcessKeyInput(const float& p_deltaTime)
{
	glm::vec3 FPS = m_camera->GetFront();
	glm::vec3 freeFloat = FPS;
	FPS.y = 0.0f;

	InputManager* inputManager = &*InputManager::GetInstance();

    if (inputManager->GetKey(InputManager::KeyCode::W)) //move forward
    {
		if (m_freeFloat)
			MoveCamera(freeFloat * static_cast<float>(p_deltaTime));
		else
			MoveCamera(FPS * static_cast<float>(p_deltaTime));
    }
    if (inputManager->GetKey(InputManager::KeyCode::S)) //move backward
    {
		if (m_freeFloat)
			MoveCamera(-freeFloat * static_cast<float>(p_deltaTime));
		else
			MoveCamera(-FPS * static_cast<float>(p_deltaTime));
    }
    if (inputManager->GetKey(InputManager::KeyCode::A)) //move left
    {
        MoveCamera(-m_camera->GetRight() * p_deltaTime);
    }
    if (inputManager->GetKey(InputManager::KeyCode::D)) //move right
    {
        MoveCamera(m_camera->GetRight() * p_deltaTime);
    }
    if (inputManager->GetKey(InputManager::KeyCode::LeftShift)) //move up
    {
        MoveCamera(m_camera->GetWorldUp() * p_deltaTime);
    }
    if (inputManager->GetKey(InputManager::KeyCode::LeftControl)) //move down
    {
        MoveCamera(-m_camera->GetWorldUp() * p_deltaTime);
    }
}

void Rendering::Managers::CameraManager::ProcessMouseInput()
{
	std::tuple mouseCursor = InputManager::GetInstance()->GetMouseCursorPos();
    const float mouseX = static_cast<float>(std::get<0>(mouseCursor));
    const float mouseY = static_cast<float>(std::get<1>(mouseCursor));
    float xOffset = mouseX - m_lastX;
    float yOffset = m_lastY - mouseY;

    m_lastX = mouseX;
    m_lastY = mouseY;

    const float mouseSens = m_camera->GetMouseSensitivity();
    xOffset *= mouseSens;
    yOffset *= mouseSens;

    const float yaw = m_camera->GetYaw();
    const float pitch = m_camera->GetPitch();

    if (pitch + yOffset > 75.0f)
        m_camera->SetPitch(74.0f);
    else if (pitch + yOffset < -75.0f)
        m_camera->SetPitch(-74.0f);
    else
    {
        m_camera->SetPitch(pitch + yOffset);
    }
        m_camera->SetYaw(yaw + xOffset);
    // Update Front, Right and Up Vectors using the updated Euler angles
    m_camera->UpdateCameraVectors();
}

void Rendering::Managers::CameraManager::MoveCamera(const glm::vec3& p_direction) const
{
    m_camera->SetPosition(m_camera->GetPosition() + p_direction * m_camera->GetMovementSpeed());
}
