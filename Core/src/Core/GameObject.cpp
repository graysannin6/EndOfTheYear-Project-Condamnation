#include "stdafx.h"
#include <string>

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

#include <Core/GameObject.h>
#include <Components/ModelComp.h>
#include <Components/TransformComp.h>
#include <Components/LightComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>
#include <Components/RigidBodyComp.h>


Core::GameObject::GameObject()
{
    AddComponent<Components::TransformComp>();
}

Core::GameObject::GameObject(const char * p_name)
{
    AddComponent<Components::TransformComp>();
    m_name = p_name;
}

Core::GameObject::GameObject(const std::shared_ptr<Rendering::Resources::Mesh>& p_mesh, const std::shared_ptr<Rendering::Shaders::Shader>& p_shader, const char* p_name)
{
	m_name = p_name;
	AddComponent<Components::TransformComp>();

	AddComponent<Components::ModelComp>()->GetModel()->SetMesh(p_mesh);
	GetComponent<Components::ModelComp>()->GetModel()->SetShader(p_shader);

	AddComponent<Components::MaterialComp>();
}

void Core::GameObject::SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh>& p_mesh)
{
    if(GetComponent<Components::ModelComp>() != nullptr)
        GetComponent<Components::ModelComp>()->GetModel()->SetMesh(p_mesh);
}

void Core::GameObject::SetModelShader(std::shared_ptr<Rendering::Shaders::Shader>& p_shader)
{
    if (GetComponent<Components::ModelComp>() != nullptr)
        GetComponent<Components::ModelComp>()->GetModel()->SetShader(p_shader);
}

void Core::GameObject::Update(Rendering::LowRenderer::Camera & p_cam, std::vector<GameObject>& p_lights)
{

    std::vector<Rendering::LowRenderer::Light> m_lights;
    for (auto& light : p_lights)
    {
        m_lights.emplace_back(*light.GetComponent<Components::LightComp>()->GetLight());
    }
    degree += 0.01f;

    if (GetComponent<Components::ModelComp>() != nullptr)
    {
        GetComponent<Components::MaterialComp>()->GetMaterial()->SetTextureActive();
        GetComponent<Components::ModelComp>()->GetModel()->GetShader()->ApplyShader();
        GetComponent<Components::ModelComp>()->GetModel()->GetShader()->Update(
        p_cam, 
        *GetComponent<Components::TransformComp>()->GetTransform(),
        *GetComponent<Components::MaterialComp>()->GetMaterial(), 
        m_lights.data(), m_lights.size());
    }

	for (auto& component : m_components)
	{
		component->Update();
	}
}

void Core::GameObject::ReloadShader()
{
    if (GetComponent<Components::ModelComp>() != nullptr)
    {
        const char* vertexPath = GetComponent<Components::ModelComp>()->GetModel()->GetShader()->m_vertPath;
        const char* fragPath = GetComponent<Components::ModelComp>()->GetModel()->GetShader()->m_fragPath;

        GetComponent<Components::ModelComp>()->GetModel()->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(vertexPath, fragPath));
    }
}

bool Core::GameObject::CollidesWith(const std::shared_ptr<Core::GameObject>& p_gameObject)
{
    if (GetComponent<Components::BoxColliderComp>() == nullptr || p_gameObject->GetComponent<Components::BoxColliderComp>() == nullptr)
    {
        return false;
    }

    GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();
    p_gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();

    Physics::Collider& colliderOne = *GetComponent<Components::BoxColliderComp>()->GetCollider();
    Physics::Collider& colliderTwo = *p_gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider();

    bool isOverlapping = true;
    if (colliderOne.GetMaxVec().x < colliderTwo.GetMinVec().x)
    {
        isOverlapping = false;
    }

    if (colliderOne.GetMinVec().x > colliderTwo.GetMaxVec().x)
    {
        isOverlapping = false;
    }

    if (colliderOne.GetMaxVec().y < colliderTwo.GetMinVec().y) 
    {
        isOverlapping = false;
    }

    if (colliderOne.GetMinVec().y > colliderTwo.GetMaxVec().y)
    {
        isOverlapping = false;
    }

    if (colliderOne.GetMaxVec().z < colliderTwo.GetMinVec().z)
    {
        isOverlapping = false;
    }

    if (colliderOne.GetMinVec().z > colliderTwo.GetMaxVec().z)
    {
        isOverlapping = false;
    }

    if(isOverlapping)
    {
        std::cout << m_name <<  " Collided with " << p_gameObject->m_name << "\n";
        return true;
    }
    else
    {
        return false;
    }
}

bool Core::operator==(GameObject& p_1, GameObject& p_2)
{
	if (p_1.GetName() == p_2.GetName())
		return true;

	return false;
}
