#include "stdafx.h"

#include <Physics/RigidBody.h>


Physics::RigidBody::RigidBody(glm::vec3& p_pos) : m_position{ p_pos } {}

glm::vec3& Physics::RigidBody::GetPosition()
{
    return m_position;
}

void Physics::RigidBody::SetPosition(const glm::vec3& p_pos)
{
	m_position = p_pos;
}
