#include <Components/RigidBodyComp.h>

void Components::RigidBodyComp::Serialize(XMLElement* p_compSegment,
    XMLDocument& p_xmlDoc) const noexcept
{
    XMLElement* newVariable{};
    if (m_isKinematic)
    {
        newVariable = p_xmlDoc.NewElement("isKinematic");
        newVariable->SetText(m_isKinematic);
        p_compSegment->InsertEndChild(newVariable);
    }
}

void Components::RigidBodyComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
    XMLElement* compVariable = p_compSegment->FirstChildElement("isKinematic");
    if (compVariable != nullptr)
    {
        bool isDirectional;
        compVariable->QueryBoolText(&isDirectional);
        m_gameObject.GetComponent<RigidBodyComp>()->SetKinematic(isDirectional);
    }
}
