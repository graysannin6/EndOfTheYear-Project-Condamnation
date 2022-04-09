#include <Components/EnemyComp.h>
#include "Components/TransformComp.h"

void Components::EnemyComp::Update()
{
    if (m_target != nullptr)
    {
        MoveToTarget();
    }
}

void Components::EnemyComp::MoveToTarget() const
{
    glm::vec3 newPos = m_target->GetComponent<TransformComp>()->GetTransform()->
                                 GetPosition();
    normalize(newPos);
    newPos *= m_speed;

    m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->Translate(newPos);
}
