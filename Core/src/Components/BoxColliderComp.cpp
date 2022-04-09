#include <Components/BoxColliderComp.h>
#include <Components/ModelComp.h>

void Components::BoxColliderComp::Serialize(XMLElement* p_compSegment,
    XMLDocument& p_xmlDoc) const noexcept
{

}

void Components::BoxColliderComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
    m_gameObject.GetComponent<BoxColliderComp>()->SetCollider(m_gameObject.GetComponent<ModelComp>()->GetModel()->GetMesh()->m_positions);
}
