#pragma once

#include <Components/Component.h>
#include <Core/GameObject.h>

namespace Components
{
    class EnemyComp : public Component
    {
    public:
        EnemyComp(Core::GameObject& p_gameObject, float p_speed = 0,
                    Core::GameObject* p_target = nullptr) 
        : m_gameObject{ p_gameObject }
        , m_speed{p_speed}, m_target{p_target} {}

        ~EnemyComp() = default;

        void  SetSpeed(float p_speed) { m_speed = p_speed; }
        float GetSpeed() const { return m_speed; }

        void SetTarget(Core::GameObject* p_target) { m_target = p_target; }
        void RemoveTarget() { m_target = nullptr; }

        void Update() override;

        void MoveToTarget() const;

        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override {}
        void Deserialize(XMLElement* p_compSegment) const noexcept override {}

    private:
        float m_speed;

        Core::GameObject& m_gameObject;
        Core::GameObject* m_target;
    };
}
