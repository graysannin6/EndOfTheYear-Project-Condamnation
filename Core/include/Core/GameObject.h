#pragma once

#include <iostream>
#include <string>

#include <Rendering/Resources/Model.h>
#include <Rendering/LowRenderer/Camera.h>

#include <Components/Component.h>

namespace Core
{
    class GameObject
    {
    public:
        GameObject();
        GameObject(const char* p_name);
        GameObject(const std::shared_ptr<Rendering::Resources::Mesh>& p_mesh, const std::shared_ptr<Rendering::Shaders::Shader>& p_shader, const char* p_name);
        ~GameObject() = default;

        void SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh>& p_mesh);
        void SetModelShader(std::shared_ptr<Rendering::Shaders::Shader>& p_shader);
		void SetTag(const std::string& p_tag) { m_tag = p_tag; }

		const std::string& GetName() const noexcept { return m_name; }
		std::shared_ptr<GameObject> GetParent() const noexcept { return m_parent; }
		std::shared_ptr<GameObject> GetChild() const noexcept { return m_child; }
		const std::string& GetTag() const noexcept { return m_tag; }

        void Update(Rendering::LowRenderer::Camera& cam, std::vector<GameObject>& p_lights);
        void ReloadShader();
        bool CollidesWith(const std::shared_ptr<GameObject>& p_gameObjects);

        template<class ComponentType, typename ... args>
        ComponentType* AddComponent(args ... p_args)
        {
            std::shared_ptr<ComponentType> comp = std::make_shared<ComponentType>(*this, p_args ...);
            m_components.emplace_back(comp);
            return comp.get();
        }

        template<class ComponentType>
        ComponentType* GetComponent() const noexcept
        {
            const bool isComponent = std::is_base_of<Components::Component, ComponentType>::value;
            assert(isComponent);
		    
		    std::shared_ptr<ComponentType> result;

            if (m_components.empty())
                return nullptr;

            for (auto& component : m_components)
            {
                assert(component != nullptr);
                if (result = std::dynamic_pointer_cast<ComponentType>(component))
                {
                    break;
                }
            }
            if (result == nullptr)
            {
                return nullptr;
            }

            return result.get();
        }

        const unsigned int GetComponentCount() const noexcept
		{
			return static_cast<unsigned int>(m_components.size());
		}

		std::vector<std::shared_ptr<Components::Component>>& GetComponents() noexcept
		{
			return m_components;
		}

    private:
        float degree{0.0f};
        std::string m_name{};
		std::string m_tag{};
		std::shared_ptr<GameObject> m_parent = nullptr;
		std::shared_ptr<GameObject> m_child = nullptr;
        std::vector<std::shared_ptr<Components::Component>> m_components{};
    };

	bool operator==(GameObject& p_1, GameObject& p_2);
}
