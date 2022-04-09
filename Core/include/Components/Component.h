#pragma once

#include <Core/Interface/ISerializable.h>

namespace Components
{
    class Component : public Core::Interface::ISerializable
    {
    public:
        Component() = default;
        ~Component() = default;

		virtual void Update() = 0;

        size_t m_type = 0;

        bool IsEqual(const size_t& p_type) 
        {
            return p_type == m_type;
        }
    };
}

