#include <Components/PlayerComp.h>
#include <Core/GameObjectManager.h>
#include <Components/ModelComp.h>
#include <Components/BoxColliderComp.h>
#include <Components/TransformComp.h>
#include <Utils/Ray.h>
#include <Components/RigidBodyComp.h>

void Components::PlayerComp::ProcessKeyInput(Core::GameObjectManager& p_gameManager, const double & p_deltaTime)
{
    Rendering::Managers::InputManager* inputManager = &*Rendering::Managers::InputManager::GetInstance();

	if (inputManager->GetKey(Rendering::Managers::InputManager::KeyCode::W)) //move forward
	{
		MovePlayer(m_camera->GetFront() * static_cast<float>(p_deltaTime));
	}
	if (inputManager->GetKey(Rendering::Managers::InputManager::KeyCode::S)) //move backward
	{
		MovePlayer(-m_camera->GetFront() * static_cast<float>(p_deltaTime));
	}
	if (inputManager->GetKey(Rendering::Managers::InputManager::KeyCode::A)) //move left
	{
		MovePlayer(-m_camera->GetRight() * static_cast<float>(p_deltaTime));
	}
	if (inputManager->GetKey(Rendering::Managers::InputManager::KeyCode::D)) //move right
	{
		MovePlayer(m_camera->GetRight() * static_cast<float>(p_deltaTime));
	}
	if (Rendering::Managers::InputManager::GetInstance()->GetKeyDown(Rendering::Managers::InputManager::KeyCode::Mouse0))
	{
        if (m_gameObject.GetComponent<RigidBodyComp>() != nullptr)
        {
			m_gameObject.GetComponent<RigidBodyComp>()->AddForce({ 0, 15, 0 });
        }
		std::shared_ptr<Core::GameObject> collision = Utils::RayCast(m_gameObject, m_camera->GetFront(), p_gameManager, 1000);
		if (collision != nullptr)
		{
			p_gameManager.RemoveGameObject(collision);
		}
	}
}

void Components::PlayerComp::Update()
{
	m_camera->SetPosition(m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition());
}

std::shared_ptr<Core::GameObject> Components::PlayerComp::RayCast(Core::GameObjectManager& p_gameManager, int p_maxDistance = 100) const
{
	glm::vec3 currPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition() + m_camera->GetFront();
	glm::vec3 cameraFront = glm::normalize(m_camera->GetFront());
	cameraFront.x /= 10.0f;
	cameraFront.y /= 10.0f;
	cameraFront.z /= 10.0f;

	for (int i = 0; i < p_maxDistance; ++i)
	{
		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (&*gameObject == &m_gameObject ||
				 glm::distance(gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition(), 
					 m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition()) > p_maxDistance ||
				gameObject->GetComponent<TransformComp>() == nullptr ||
				gameObject->GetComponent<ModelComp>() == nullptr ||
				gameObject->GetComponent<BoxColliderComp>() == nullptr ||
				gameObject->GetTag() == "NonDestructable")
				continue;

			currPos = currPos + cameraFront;
			glm::vec4 minVec = gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMinVec();
			glm::vec4 maxVec = gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMaxVec();

			if (maxVec.x > currPos.x && minVec.x < currPos.x &&
				maxVec.y > currPos.y && minVec.y < currPos.y &&
				maxVec.z > currPos.z && minVec.z < currPos.z)
			{
				std::cout << m_gameObject.GetName() << " raycast collision with " << gameObject->GetName() << '\n';
				return gameObject;
			}
			
		}
	}
		return {};
}

void Components::PlayerComp::MovePlayer(const glm::vec3& p_direction) const
{
    if (m_gameObject.GetComponent<Components::RigidBodyComp>() != nullptr)
	    m_gameObject.GetComponent<Components::RigidBodyComp>()->GetRigidBody()->SetPosition(m_camera->GetPosition() + p_direction * m_camera->GetMovementSpeed());

	else
		m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_camera->GetPosition() + p_direction * m_camera->GetMovementSpeed());
}

void Components::PlayerComp::Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept
{
	std::cout << "[PLAYER_COMP] Function not implemented\n";
}

void Components::PlayerComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[PLAYER_COMP] Function not implemented\n";
}
