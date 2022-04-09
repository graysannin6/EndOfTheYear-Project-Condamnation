#include <Rendering/Managers/Renderer.h>

#include <Core/RenderEngine.h>
#include <Components/ModelComp.h>

void Core::RenderEngine::DrawElements(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObject, std::vector<GameObject>& p_lights,
    Rendering::LowRenderer::Camera& p_camera, Rendering::Managers::Renderer& p_renderer)
{
    for (auto& pGameObject : p_gameObject)
    {
        pGameObject->Update(p_camera, p_lights);

        if (pGameObject->GetComponent<Components::ModelComp>() != nullptr)
            p_renderer.Draw(*pGameObject->GetComponent<Components::ModelComp>()->GetModel()->GetMesh());
    }
}
