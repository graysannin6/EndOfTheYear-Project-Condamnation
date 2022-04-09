#pragma once

#include <Physics/BoxCollider.h>

#include <Components/Component.h>
#include <Core/GameObject.h>

namespace Components
{
	class BoxColliderComp : public Component
	{
	public:
		BoxColliderComp(Core::GameObject& p_gameObject) : m_gameObject{ p_gameObject } {}
		~BoxColliderComp() = default;

		[[nodiscard]] std::shared_ptr<Physics::Collider> GetCollider() const noexcept { return m_collider; }

		void SetCollider(std::vector<glm::vec3>& p_vec) 
        { 
            m_collider = std::make_shared<Physics::Collider>(p_vec); 
            m_collider->SetBoundingBox();
        }

		void Update() override {}

        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;
    private:
        std::shared_ptr<Physics::Collider> m_collider{};
        Core::GameObject& m_gameObject;
    };
}
