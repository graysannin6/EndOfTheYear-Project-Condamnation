#pragma once

#include <any>

#include <Rendering/Export.h>

namespace Rendering::Context
{
    class API_RENDERING IDriver
    {
    public:
        virtual ~IDriver() = default;

        virtual void Clear() const noexcept = 0;
        virtual void PolygonMode(std::any p_face, std::any p_mode) const noexcept = 0;
        virtual void EnableDebug() const noexcept = 0;
    };
}