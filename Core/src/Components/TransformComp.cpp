#include <Components/TransformComp.h>

void Components::TransformComp::Update()
{
	if (m_gameObject.GetComponent<LightComp>() != nullptr)
	{
		m_gameObject.GetComponent<LightComp>()->GetLight()->SetPos(m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	}

	if (m_parent != nullptr)
	{
		SetChildMatrix(m_parent->m_transform->GetTransMat());
	}
}

void Components::TransformComp::Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept
{
    XMLElement* newVariable;
    if (m_transform->GetTransMat() != glm::mat4{ 0 })
    {
        newVariable = p_xmlDoc.NewElement("transMat");
        newVariable->SetAttribute("m0-0", m_transform->GetTransMat()[0][0]);
        newVariable->SetAttribute("m0-1", m_transform->GetTransMat()[0][1]);
        newVariable->SetAttribute("m0-2", m_transform->GetTransMat()[0][2]);
        newVariable->SetAttribute("m0-3", m_transform->GetTransMat()[0][3]);

        newVariable->SetAttribute("m1-0", m_transform->GetTransMat()[1][0]);
        newVariable->SetAttribute("m1-1", m_transform->GetTransMat()[1][1]);
        newVariable->SetAttribute("m1-2", m_transform->GetTransMat()[1][2]);
        newVariable->SetAttribute("m1-3", m_transform->GetTransMat()[1][3]);

        newVariable->SetAttribute("m2-0", m_transform->GetTransMat()[2][0]);
        newVariable->SetAttribute("m2-1", m_transform->GetTransMat()[2][1]);
        newVariable->SetAttribute("m2-2", m_transform->GetTransMat()[2][2]);
        newVariable->SetAttribute("m2-3", m_transform->GetTransMat()[2][3]);

        newVariable->SetAttribute("m3-0", m_transform->GetTransMat()[3][0]);
        newVariable->SetAttribute("m3-1", m_transform->GetTransMat()[3][1]);
        newVariable->SetAttribute("m3-2", m_transform->GetTransMat()[3][2]);
        newVariable->SetAttribute("m3-3", m_transform->GetTransMat()[3][3]);

        p_compSegment->InsertEndChild(newVariable);
    }

    else if (m_transform->GetPosition() != glm::vec3(0))
    {
        newVariable = p_xmlDoc.NewElement("position");
        newVariable->SetAttribute("x", m_transform->GetRawPosition().x);
        newVariable->SetAttribute("y", m_transform->GetRawPosition().y);
        newVariable->SetAttribute("z", m_transform->GetRawPosition().z);
        p_compSegment->InsertEndChild(newVariable);
    }
    
    else if (m_transform->GetRotation() != glm::vec3(0))
    {
        newVariable = p_xmlDoc.NewElement("rotation");
        newVariable->SetAttribute("x", m_transform->GetRotation().x);
        newVariable->SetAttribute("y", m_transform->GetRotation().y);
        newVariable->SetAttribute("z", m_transform->GetRotation().z);
        p_compSegment->InsertEndChild(newVariable);
    }

    else if (m_transform->GetScale() != glm::vec3(1))
    {
        newVariable = p_xmlDoc.NewElement("scale");
        newVariable->SetAttribute("x", m_transform->GetScale().x);
        newVariable->SetAttribute("y", m_transform->GetScale().y);
        newVariable->SetAttribute("z", m_transform->GetScale().z);
        p_compSegment->InsertEndChild(newVariable);
    }
}

void Components::TransformComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
    XMLElement* compVariable{};

    compVariable = p_compSegment->FirstChildElement("transMat");
    if (compVariable != nullptr)
    {
        glm::mat4 transMat;
        compVariable->QueryFloatAttribute("m0-0", &transMat[0][0]);
        compVariable->QueryFloatAttribute("m0-1", &transMat[0][1]);
        compVariable->QueryFloatAttribute("m0-2", &transMat[0][2]);
        compVariable->QueryFloatAttribute("m0-3", &transMat[0][3]);

        compVariable->QueryFloatAttribute("m1-0", &transMat[1][0]);
        compVariable->QueryFloatAttribute("m1-1", &transMat[1][1]);
        compVariable->QueryFloatAttribute("m1-2", &transMat[1][2]);
        compVariable->QueryFloatAttribute("m1-3", &transMat[1][3]);

        compVariable->QueryFloatAttribute("m2-0", &transMat[2][0]);
        compVariable->QueryFloatAttribute("m2-1", &transMat[2][1]);
        compVariable->QueryFloatAttribute("m2-2", &transMat[2][2]);
        compVariable->QueryFloatAttribute("m2-3", &transMat[2][3]);

        compVariable->QueryFloatAttribute("m3-0", &transMat[3][0]);
        compVariable->QueryFloatAttribute("m3-1", &transMat[3][1]);
        compVariable->QueryFloatAttribute("m3-2", &transMat[3][2]);
        compVariable->QueryFloatAttribute("m3-3", &transMat[3][3]);
        m_transform->SetTransMat(transMat);
    }

    compVariable = p_compSegment->FirstChildElement("position");
    if (compVariable != nullptr)
    {
        glm::vec3 pos;
        compVariable->QueryFloatAttribute("x", &pos.x);
        compVariable->QueryFloatAttribute("y", &pos.y);
        compVariable->QueryFloatAttribute("z", &pos.z);
        m_transform->Translate(pos);
    }

    compVariable = p_compSegment->FirstChildElement("rotation");
    if (compVariable != nullptr)
    {
        glm::vec3 rot;
        compVariable->QueryFloatAttribute("x", &rot.x);
        compVariable->QueryFloatAttribute("y", &rot.y);
        compVariable->QueryFloatAttribute("z", &rot.z);
        m_transform->Rotate(rot);
    }

    compVariable = p_compSegment->FirstChildElement("scale");
    if (compVariable != nullptr)
    {
        glm::vec3 scale;
        compVariable->QueryFloatAttribute("x", &scale.x);
        compVariable->QueryFloatAttribute("y", &scale.y);
        compVariable->QueryFloatAttribute("z", &scale.z);
        m_transform->Scale(scale);
    }
}
