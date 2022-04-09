#pragma once
#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>

namespace Components
{
	class PlayerComp : public Component
	{
	public:
		PlayerComp(Core::GameObject& p_gameObject, std::shared_ptr<Rendering::LowRenderer::Camera> p_camera, int p_health) :
			m_gameObject{ p_gameObject }, m_camera{ p_camera }, m_health { p_health } {}
		~PlayerComp() = default;

		void ProcessKeyInput(Core::GameObjectManager& p_gameManager, const double & p_deltaTime);
		void Update() override;
		std::shared_ptr<Core::GameObject> RayCast(Core::GameObjectManager& p_gameManager, int p_maxDistance) const;
		void MovePlayer(const glm::vec3 & p_direction) const;

        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;

	private:
		Core::GameObject& m_gameObject;
		std::shared_ptr<Rendering::LowRenderer::Camera> m_camera;
		int m_health{ 0 };

	};
}
