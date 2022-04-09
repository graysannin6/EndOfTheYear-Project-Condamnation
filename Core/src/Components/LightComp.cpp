#include <Components/LightComp.h>

void Components::LightComp::Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept
{
    XMLElement* newVariable;
    if (m_light->GetPos() != glm::vec3(0))
    {
        newVariable = p_xmlDoc.NewElement("position");
        newVariable->SetAttribute("x", m_light->GetPos().x);
        newVariable->SetAttribute("y", m_light->GetPos().y);
        newVariable->SetAttribute("z", m_light->GetPos().z);
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_light->GetColor() != glm::vec3(1))
    {
        newVariable = p_xmlDoc.NewElement("color");
        newVariable->SetAttribute("r", m_light->GetColor().x);
        newVariable->SetAttribute("g", m_light->GetColor().y);
        newVariable->SetAttribute("b", m_light->GetColor().z);
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_light->GetIsDirectional())
    {
        newVariable = p_xmlDoc.NewElement("isDirectional");
        newVariable->SetText(m_light->GetIsDirectional());
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_light->GetIntensity() != 0.0f)
    {
        newVariable = p_xmlDoc.NewElement("intensity");
        newVariable->SetText(m_light->GetIntensity());
        p_compSegment->InsertEndChild(newVariable);
    }
}

void Components::LightComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	XMLElement* compVariable = p_compSegment->FirstChildElement("position");
	if (compVariable != nullptr)
	{
		float x, y, z;
		compVariable->QueryFloatAttribute("x", &x);
		compVariable->QueryFloatAttribute("y", &y);
		compVariable->QueryFloatAttribute("z", &z);
		m_light->SetPos(x, y, z);
	}

	compVariable = p_compSegment->FirstChildElement("color");
	if (compVariable != nullptr)
	{
		float r, g, b;
		compVariable->QueryFloatAttribute("r", &r);
		compVariable->QueryFloatAttribute("g", &g);
		compVariable->QueryFloatAttribute("b", &b);
		m_light->SetColor(r, g, b);
	}

	compVariable = p_compSegment->FirstChildElement("intensity");
	if (compVariable != nullptr)
	{
		float intensity;
		compVariable->QueryFloatText(&intensity);
		m_light->SetIntensity(intensity);
	}

	compVariable = p_compSegment->FirstChildElement("isDirectional");
	if (compVariable != nullptr)
	{
		bool isDirectional;
		compVariable->QueryBoolText(&isDirectional);
		m_light->SetDirectional(isDirectional);
	}
}
