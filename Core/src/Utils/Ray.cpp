#include <Utils/Ray.h>
#include <Components/TransformComp.h>
#include <Components/BoxColliderComp.h>
#include "Components/ModelComp.h"

std::shared_ptr<Core::GameObject> Utils::RayCast(std::shared_ptr<Core::GameObject> p_origin, const glm::vec3& p_direction, Core::GameObjectManager& p_gameManager, int p_maxDistance = 100)
{
	glm::vec3 currPos = p_origin->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
	glm::vec3 direction = glm::normalize(p_direction);
	direction.x /= 10.0f;
	direction.y /= 10.0f;
	direction.z /= 10.0f;

	for (int i = 0; i < p_maxDistance; ++i)
	{
		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (gameObject == p_origin ||
				gameObject->GetComponent<Components::TransformComp>() == nullptr ||
				gameObject->GetComponent<Components::ModelComp>() == nullptr ||
				gameObject->GetComponent<Components::BoxColliderComp>() == nullptr ||
				gameObject->GetTag() == "NonDestructable")
				continue;

			currPos = currPos + direction;
			glm::vec4 minVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMinVec();
			glm::vec4 maxVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMaxVec();

			if (maxVec.x > currPos.x && minVec.x < currPos.x &&
				maxVec.y > currPos.y && minVec.y < currPos.y &&
				maxVec.z > currPos.z && minVec.z < currPos.z)
			{
				return gameObject;
			}

		}
	}
	return nullptr;
}

std::shared_ptr<Core::GameObject> Utils::RayCast(Core::GameObject& p_origin, const glm::vec3 & p_direction, Core::GameObjectManager & p_gameManager, int p_maxDistance = 100)
{
	glm::vec3 currPos = p_origin.GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
	glm::vec3 direction = glm::normalize(p_direction);
	direction.x /= 10.0f;
	direction.y /= 10.0f;
	direction.z /= 10.0f;

	for (int i = 0; i < p_maxDistance; ++i)
	{
		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (*gameObject == p_origin
				|| glm::distance(gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition(),
					p_origin.GetComponent<Components::TransformComp>()->GetTransform()->GetPosition()) > p_maxDistance ||
				gameObject->GetComponent<Components::TransformComp>() == nullptr ||
				gameObject->GetComponent<Components::ModelComp>() == nullptr ||
				gameObject->GetComponent<Components::BoxColliderComp>() == nullptr ||
				gameObject->GetTag() == "NonDestructable")
				continue;

			currPos = currPos + direction;
			glm::vec4 minVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMinVec();
			glm::vec4 maxVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMaxVec();

			if (maxVec.x > currPos.x && minVec.x < currPos.x &&
				maxVec.y > currPos.y && minVec.y < currPos.y &&
				maxVec.z > currPos.z && minVec.z < currPos.z)
			{
				return gameObject;
			}

		}
	}
	return nullptr;
}
