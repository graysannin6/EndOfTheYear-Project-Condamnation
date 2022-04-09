#include <tinyxml2.h>

#include <Core/GameObjectManager.h>
#include <Components/LightComp.h>
#include <Components/TransformComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>
#include <Components/RigidBodyComp.h>
#include <Components/ModelComp.h>
#include <Rendering/Managers/InputManager.h>

#include <unordered_map>
#include "Components/PlayerComp.h"

static int phase = 0;

Core::GameObjectManager::GameObjectManager(MeshManager& p_modelManager, Rendering::Managers::CameraManager& p_camera)
{
    LoadScene(p_modelManager, "DOOM");

    Find("Player")->AddComponent<Components::PlayerComp>(p_camera.GetCamera(), 100);

}

void Core::GameObjectManager::Update(const float& p_deltaTime, Rendering::Managers::CameraManager& p_camera)
{
    phase += 1;
    float frequency = 0.02f;
    if (Rendering::Managers::InputManager::GetInstance()->GetKeyDown(Rendering::Managers::InputManager::KeyCode::Mouse1))
    {
        if(Find("Link") != nullptr )
        Find("Link")->GetComponent<Components::RigidBodyComp>()->AddForce({ p_camera.GetCamera()->GetFront().x * 100, p_camera.GetCamera()->GetFront().y * 100 , p_camera.GetCamera()->GetFront().z * 100 });
        if(Find("Link2") != nullptr)
        Find("Link2")->GetComponent<Components::RigidBodyComp>()->AddForce({ p_camera.GetCamera()->GetFront().x * 100, p_camera.GetCamera()->GetFront().y * 100 , p_camera.GetCamera()->GetFront().z * 100 });
    }

    Find("Torch1")->GetComponent<Components::LightComp>()->GetLight()->SetColor(sin(frequency * phase), sin(frequency * phase + 2), sin(frequency * phase + 4));
    Find("Torch2")->GetComponent<Components::LightComp>()->GetLight()->SetColor(sin(frequency * phase + 2), sin(frequency * phase + 4), sin(frequency * phase + 6));
    Find("Torch3")->GetComponent<Components::LightComp>()->GetLight()->SetColor(sin(frequency * phase + 4), sin(frequency * phase + 6), sin(frequency * phase + 8));
    Find("Torch4")->GetComponent<Components::LightComp>()->GetLight()->SetColor(sin(frequency * phase + 6), sin(frequency * phase + 8), sin(frequency * phase + 10));
    
    if (Find("Player") != nullptr)
        Find("Player")->GetComponent<Components::PlayerComp>()->ProcessKeyInput(*this, p_deltaTime);

    m_angle += 0.005f * p_deltaTime;

    if (Find("BlueLight") != nullptr)
    {
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 1, 0) * p_deltaTime);
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0.1, 0, 0) * p_deltaTime);     
        Find("BlueLight")->GetComponent<Components::TransformComp>()->Update();
    }

    if (Find("OrangeLight") != nullptr)
        Find("OrangeLight")->GetComponent<Components::TransformComp>()->Update();

    for (auto& gameObject : m_gameObjects)
    {
        if (gameObject->GetComponent<Components::BoxColliderComp>() != nullptr)
        {
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetPosVec() = gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMat() = gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetTransMat();
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();
        }
    }
}

int Core::GameObjectManager::SaveScene(const MeshManager& p_modelManager, const std::string& p_sceneName)
{
    using namespace tinyxml2;

    std::unordered_map<std::string, int> compTypes
    {
        {"BoxColliderComp", 0},
        {"LightComp", 1},
        {"MaterialComp", 2},
        {"ModelComp", 3},
        {"TransformComp", 4},
        {"RigidBodyComp", 5}
    };

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { std::cerr << "Error while parsing XML [LOADER] Error Type: " << a_eResult << '\n'; return a_eResult; }
#endif

    XMLDocument xmlDoc;
    XMLNode* root = xmlDoc.NewElement("scene");
    xmlDoc.InsertFirstChild(root);

    XMLElement* GOList = xmlDoc.NewElement("GameObjectList");
    GOList->SetAttribute("count", static_cast<unsigned int>(m_gameObjects.size()));
    root->InsertFirstChild(GOList);

    for (auto gameObject : m_gameObjects)
    {
        XMLElement* GOelement = xmlDoc.NewElement("GameObject");
        GOelement->SetAttribute("name", gameObject->GetName().c_str());

        if (gameObject->GetComponent<Components::ModelComp>() != nullptr)
        {
            GOelement->SetAttribute("mesh", FindInstanceIteratorInVector(gameObject->GetComponent<Components::ModelComp>()->GetModel()->GetMesh(), p_modelManager.GetMeshes()));
            GOelement->SetAttribute("shader", FindInstanceIteratorInVector(gameObject->GetComponent<Components::ModelComp>()->GetModel()->GetShader(), p_modelManager.GetShaders()));
        }

        GOelement->SetAttribute("tag", gameObject->GetTag().c_str());

        XMLElement* ComponentList = xmlDoc.NewElement("ComponentList");
	    ComponentList->SetAttribute("count", gameObject->GetComponentCount());


        for (const auto& component : gameObject->GetComponents())
        {
            XMLElement* CompElement = xmlDoc.NewElement("Component");
            std::string rawClassName = typeid(*component).name();
            size_t offset = rawClassName.find_last_of(':');
            std::string realName = rawClassName.substr(offset + 1);

            CompElement->SetAttribute("type", realName.c_str());

			component->Serialize(CompElement, xmlDoc);
            ComponentList->InsertEndChild(CompElement);
        }
		GOelement->InsertFirstChild(ComponentList);
        GOList->InsertEndChild(GOelement);
    }

	XMLError eResult = xmlDoc.SaveFile((p_sceneName + ".xml").c_str());
	XMLCheckResult(eResult);
	return eResult;
}

int Core::GameObjectManager::LoadScene(const MeshManager& p_modelManager, const std::string& p_sceneName)
{
    using namespace tinyxml2;

    std::unordered_map<std::string, int> compTypes
	{
		{"BoxColliderComp", 0},
		{"LightComp", 1},
		{"MaterialComp", 2},
		{"ModelComp", 3},
		{"TransformComp", 4},
		{"RigidBodyComp", 5}
	};

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { std::cerr << "Error while parsing XML [LOADER] Error Type: " << a_eResult << '\n'; return a_eResult; }
#endif

    XMLDocument xmlDoc;
    XMLError    eResult = xmlDoc.LoadFile((p_sceneName + ".xml").c_str());
    XMLCheckResult(eResult);

    XMLNode* root = xmlDoc.FirstChild();
    if (root == nullptr)
        return XML_ERROR_FILE_READ_ERROR;

    XMLElement* GOList = root->FirstChildElement("GameObjectList");
    if (GOList == nullptr)
        return XML_ERROR_PARSING_ELEMENT;

    XMLElement* GOelement = GOList->FirstChildElement("GameObject");
    while (GOelement != nullptr)
    {
        const char* newGoName = nullptr;
        const char* tag = nullptr;
        int meshId{0}, shaderId{0};
        bool empty{ true };

        newGoName = GOelement->Attribute("name");
        if (newGoName == nullptr)
            return XML_ERROR_PARSING_ATTRIBUTE;

        eResult = GOelement->QueryIntAttribute("mesh", &meshId);
        if (eResult == XML_SUCCESS)
            empty = false;
        
        eResult = GOelement->QueryIntAttribute("shader", &shaderId);
        if (eResult == XML_SUCCESS)
            empty = false;

        tag = GOelement->Attribute("tag");

        std::shared_ptr<GameObject> newGo{};

        if (!empty)
            newGo = std::make_shared<GameObject>(p_modelManager.GetMesh(meshId), p_modelManager.GetShader(shaderId), newGoName);
        else if (empty)
            newGo = std::make_shared<GameObject>(newGoName);

        newGo->SetTag(tag);
                
        XMLElement* ComponentList = GOelement->FirstChildElement("ComponentList");
        if (GOelement == nullptr)
            return XML_ERROR_PARSING_ELEMENT;

        XMLElement* CompElement = ComponentList->FirstChildElement("Component");
        while (CompElement != nullptr)
        {
            const char* attribText = nullptr;

            attribText = CompElement->Attribute("type");
            if (attribText == nullptr)
                return XML_ERROR_PARSING_ATTRIBUTE;
            std::string newCompType{attribText};

            std::unordered_map<std::string, int>::const_iterator got = compTypes.find(newCompType);


            // this line will be triggered by the playerComp, we are not handling it
            // for the moment, and we shouldn't pay much attention to it. It is not an error.
            if (got == compTypes.end())
                std::cout << "component not found\n";
            else
            {
                switch (got->second)
                {
                case 0: //boxColliderComp
                    if (newGo->GetComponent<Components::BoxColliderComp>() == nullptr)
                        newGo->AddComponent<Components::BoxColliderComp>();

                    newGo->GetComponent<Components::BoxColliderComp>()->Deserialize(CompElement);
                    break;
                case 1: //LightComp
                    if (newGo->GetComponent<Components::LightComp>() == nullptr)
                        newGo->AddComponent<Components::LightComp>();

                    newGo->GetComponent<Components::LightComp>()->Deserialize(CompElement);
                    break;
                case 2: //materialComp
                    if (newGo->GetComponent<Components::MaterialComp>() == nullptr)
                        newGo->AddComponent<Components::MaterialComp>();

                    newGo->GetComponent<Components::MaterialComp>()->Deserialize(CompElement);
                    break;
                case 3: //modelComp
                    if (newGo->GetComponent<Components::ModelComp>() == nullptr)
                        newGo->AddComponent<Components::ModelComp>();
                    break;
                case 4: //TransformComp
                    if (newGo->GetComponent<Components::TransformComp>() == nullptr)
                        newGo->AddComponent<Components::TransformComp>();

                    newGo->GetComponent<Components::TransformComp>()->Deserialize(CompElement);
                    break;
                case 5: //TransformComp
                    if (newGo->GetComponent<Components::RigidBodyComp>() == nullptr)
                        newGo->AddComponent<Components::RigidBodyComp>(this);

                    newGo->GetComponent<Components::RigidBodyComp>()->Deserialize(CompElement);
                    break;
                default:
                    std::cerr <<
                            "ERROR : something went wrong when trying to load components on the XML loader\n Your component type is non-existent.";
                    break;
                }
            }
            CompElement = CompElement->NextSiblingElement("Component");
        }
        GOelement = GOelement->NextSiblingElement("GameObject");
        m_gameObjects.push_back(newGo);
    }

    return EXIT_SUCCESS;
}

std::shared_ptr<Core::GameObject> Core::GameObjectManager::Find(const std::string& p_name)
{
    for (auto& m_gameObject : m_gameObjects)
    {
        if (m_gameObject->GetName() == p_name)
            return m_gameObject;
    }

	std::cout << "Could not find object " << p_name << "in Game Manager\n";
    return {};
}

std::vector<std::shared_ptr<Core::GameObject>>& Core::GameObjectManager::GetGameObjects() noexcept
{
	return m_gameObjects;
}

void Core::GameObjectManager::RemoveGameObject(std::shared_ptr<GameObject> p_gameObject)
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (*m_gameObjects[i] == *p_gameObject)
		{
			if (m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild() != nullptr)
			{
				Core::GameObject& tmp = m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild()->GetGameObject();
				m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild()->SetParent();
				RemoveGameObject(std::make_shared<GameObject>(tmp));
				return;
			}
			
			m_gameObjects.erase(m_gameObjects.begin() + i);
			return;
		}
	}
}
