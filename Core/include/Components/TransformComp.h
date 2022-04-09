#pragma once

#include <memory>

#include <Rendering/LowRenderer/Transform.h>

#include <Components/Component.h>
#include <Components/LightComp.h>
#include <Core/GameObject.h>

namespace Components
{
	class TransformComp : public Component
	{
	public:
		TransformComp(Core::GameObject& p_gameObject) : m_transform{ std::make_shared<Rendering::LowRenderer::Transform>() }, m_gameObject{ p_gameObject },
			m_localTransform{ std::make_shared<Rendering::LowRenderer::Transform>() } {}
		~TransformComp() = default;

		void SetLocalTransformPos(const glm::vec3& p_pos) const { m_localTransform->SetPosition(p_pos); }
		void SetChild()
		{
			m_child->SetParent();
		    m_child = nullptr;
		}
		void SetChild(std::shared_ptr<TransformComp> p_child)
		{
		    m_child = p_child;
			p_child->m_parent = std::make_shared<TransformComp>(*this);
		}
		void SetChild(Core::GameObject& p_child)
		{
		    m_child = std::shared_ptr<TransformComp>(p_child.GetComponent<TransformComp>());
			p_child.GetComponent<TransformComp>()->m_parent = std::make_shared<TransformComp>(*this);
		}
		void SetChild(std::shared_ptr<Core::GameObject> p_child)
		{
		    m_child = std::shared_ptr<TransformComp>(p_child->GetComponent<TransformComp>());
			p_child->GetComponent<TransformComp>()->m_parent = std::make_shared<TransformComp>(*this);
		}
		void SetParent()
		{
			m_parent->m_child = nullptr;
		    m_parent = nullptr;
		}
		void SetParent(std::shared_ptr<TransformComp> p_parent)
		{
		    m_parent = p_parent;
			p_parent->m_child = std::make_shared<TransformComp>(*this);
		}
		void SetParent(Core::GameObject& p_parent)
		{
		    m_parent = std::shared_ptr<TransformComp>(p_parent.GetComponent<TransformComp>());
			p_parent.GetComponent<TransformComp>()->m_child = std::make_shared<TransformComp>(*this);
		}
		void SetParent(std::shared_ptr<Core::GameObject> p_parent)
		{
		    m_parent = std::shared_ptr<TransformComp>(p_parent->GetComponent<TransformComp>());
			p_parent->GetComponent<TransformComp>()->m_child = std::make_shared<TransformComp>(*this);
		}
        void SetChildMatrix(const glm::mat4& p_mat) const
		{
		    m_transform->SetTransMat(p_mat * m_localTransform->GetTransMat());
		}

		std::shared_ptr<TransformComp> GetChild() const { return m_child; }
		std::shared_ptr<TransformComp> GetParent() const { return m_parent; }
		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Transform> GetTransform() const noexcept { return m_transform; }
		[[nodiscard]] Core::GameObject& GetGameObject() const { return m_gameObject; }

		void Update() override;

        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;

    private:
		Core::GameObject& m_gameObject;

		std::shared_ptr<TransformComp> m_parent = nullptr;
		std::shared_ptr<TransformComp> m_child = nullptr;
        
	    std::shared_ptr<Rendering::LowRenderer::Transform> m_transform;
        std::shared_ptr<Rendering::LowRenderer::Transform> m_localTransform;
    };
}

