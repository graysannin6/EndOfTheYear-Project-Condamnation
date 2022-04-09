#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

#include <Core/MeshManager.h>
#include <Core/GameObject.h>

void Core::MeshManager::AddMesh(const char* p_filePath)
{
    m_meshes.push_back(Rendering::Resources::Model::LoadMesh(p_filePath));
}

void Core::MeshManager::AddShader(const char* p_vertPath, const char* p_fragPath)
{
	std::shared_ptr<Rendering::Shaders::Shader> newShader = Rendering::Resources::Loaders::ShaderLoader::LoadShader(p_vertPath, p_fragPath);
    m_shaders.push_back(newShader);
}

void Core::MeshManager::ReloadShader(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects)
{
    for (unsigned int i = 0; i < m_shaders.size(); ++i)
    {
        const char* pathA = m_shaders[i]->m_vertPath;
        const char* pathB = m_shaders[i]->m_fragPath;

        m_shaders[i] = std::make_shared<Rendering::Shaders::Shader>(*Rendering::Resources::Loaders::ShaderLoader::LoadShader(pathA, pathB));
    }

    for (auto& gameObject : p_gameObjects)
        gameObject->ReloadShader();
}

void Core::MeshManager::LoadMeshes()
{
    AddMesh(R"(..\Resources\Meshes\YoungLink.obj)");
    AddMesh(R"(..\Resources\Meshes\sphere.fbx)");
    AddMesh(R"(..\Resources\Meshes\pistol.obj)");
    AddMesh(R"(..\Resources\Meshes\newCube.obj)");
}

void Core::MeshManager::LoadShaders()
{
    AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/fragShader2.frag");
    AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/lightShader.frag");
    AddShader("../Resources/Shaders/textUI.vert", "../Resources/Shaders/textUI.frag");
}