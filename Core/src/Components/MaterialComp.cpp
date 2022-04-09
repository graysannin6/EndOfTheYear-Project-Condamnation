#include <string>

#include <Components/MaterialComp.h>


void Components::MaterialComp::Serialize(XMLElement*  p_compSegment,
                                         XMLDocument& p_xmlDoc) const noexcept
{
    XMLElement* newVariable;

    if (m_material->GetColor() != glm::vec3(1))
    {
        newVariable = p_xmlDoc.NewElement("color");
        newVariable->SetAttribute("r", m_material->GetColorR());
        newVariable->SetAttribute("g", m_material->GetColorG());
        newVariable->SetAttribute("b", m_material->GetColorB());
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_material->GetShininess() != 0.0f)
    {
        newVariable = p_xmlDoc.NewElement("shininess");
        newVariable->SetText(m_material->GetShininess());
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_material->GetOpacity() != 1.0f)
    {
        newVariable = p_xmlDoc.NewElement("opacity");
        newVariable->SetText(m_material->GetOpacity());
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_material->GetTexture().GetName() != nullptr)
    {
        newVariable = p_xmlDoc.NewElement("texture");
        newVariable->SetText(m_material->GetTexture().GetName());
        p_compSegment->InsertEndChild(newVariable);
    }
}

void Components::MaterialComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
    XMLElement* compVariable = p_compSegment->FirstChildElement("color");
    if (compVariable != nullptr)
    {
        float r{1}, g{1}, b{1};
        compVariable->QueryFloatAttribute("r", &r);
        compVariable->QueryFloatAttribute("g", &g);
        compVariable->QueryFloatAttribute("b", &b);
        m_material->SetColor(r, g, b);
    }

    compVariable = p_compSegment->FirstChildElement("shininess");
    if (compVariable != nullptr)
    {
        float shininess;
        compVariable->QueryFloatText(&shininess);
        m_material->SetShininess(shininess);
    }

    compVariable = p_compSegment->FirstChildElement("opacity");
    if (compVariable != nullptr)
    {
        float opacity;
        compVariable->QueryFloatText(&opacity);
        m_material->SetOpacity(opacity);
    }

    compVariable = p_compSegment->FirstChildElement("texture");
    if (compVariable != nullptr)
    {
        std::string textureName = compVariable->GetText();
        m_material->LoadTexture(textureName.c_str());
    }
}

