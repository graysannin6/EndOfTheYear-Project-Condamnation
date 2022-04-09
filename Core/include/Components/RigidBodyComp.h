#pragma once

#include <Physics/RigidBody.h>

#include <Components/Component.h>
#include <Components/TransformComp.h>
#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>

namespace Components
{
    class RigidBodyComp : public Component
    {
    public:
		RigidBodyComp(Core::GameObject& p_gameObject, Core::GameObjectManager* p_gameObjectManager) : m_gameObject{ p_gameObject },
			m_gameObjectManager{ p_gameObjectManager }, m_rigidbody{ std::make_unique<Physics::RigidBody>() } 
        {
            m_rigidbody->SetPosition(m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition());
        }

		~RigidBodyComp() = default;

        void Update() override
        {
            if (!m_isKinematic)
            {
                AddForce({0, -10.0f, 0});
                m_velocity += m_force;

                if (m_rigidbody->GetPosition().x < m_rigidbody->GetMinX())
                {
                    m_velocity.x = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetMinX(),  m_rigidbody->GetPosition().y, m_rigidbody->GetPosition().z });
                }
                if (m_rigidbody->GetPosition().x > m_rigidbody->GetMaxX())
                {
                    m_velocity.x = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetMaxX(),  m_rigidbody->GetPosition().y, m_rigidbody->GetPosition().z });
                }

                if (m_rigidbody->GetPosition().y < m_rigidbody->GetMinY())
                {
                    m_velocity.y = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetPosition().x, m_rigidbody->GetMinY(), m_rigidbody->GetPosition().z });
                }
                if (m_rigidbody->GetPosition().y > m_rigidbody->GetMaxY())
                {
                    m_velocity.y = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetPosition().x, m_rigidbody->GetMaxY(), m_rigidbody->GetPosition().z });
                }

                if (m_rigidbody->GetPosition().z < m_rigidbody->GetMinZ())
                {
                    m_velocity.z = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetPosition().x, m_rigidbody->GetPosition().y, m_rigidbody->GetMinZ() });
                }
                if (m_rigidbody->GetPosition().z > m_rigidbody->GetMaxZ())
                {
                    m_velocity.z = 0;
                    m_rigidbody->SetPosition({ m_rigidbody->GetPosition().x, m_rigidbody->GetPosition().y, m_rigidbody->GetMaxZ() });
                }

                m_rigidbody->SetPosition(m_rigidbody->GetPosition() + m_velocity);
            }
            m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_rigidbody->GetPosition());
            m_force = { 0, 0, 0 };
        }


        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;
        
        const glm::vec3& GetVelocity() { return m_velocity; }
        const glm::vec3& GetForce() { return m_force; }
       
        void SetVelocity(const glm::vec3& p_velocity) { m_velocity = p_velocity; }
        void SetForce(const glm::vec3& p_force) { m_force = p_force; }
		void SetKinematic(bool p_kin) { m_isKinematic = p_kin; }

        void AddForce(const glm::vec3& p_force) { m_force += p_force * 0.001f; };
        void ResetVelocity() { m_velocity = glm::vec3(0, 0, 0); }

        std::unique_ptr<Physics::RigidBody>& GetRigidBody() { return m_rigidbody; }
    private:
        bool m_isKinematic{ false };
        bool m_isColliding{ false };

        glm::vec3 m_velocity{};
		glm::vec3 m_force{};

        Core::GameObject& m_gameObject;
        Core::GameObjectManager* m_gameObjectManager;
        std::unique_ptr<Physics::RigidBody> m_rigidbody;
    };
}

