#pragma once

#include <Rendering/Export.h>
#include <Rendering/Context/IDriver.h>

namespace Rendering::Context::OpenGL
{
    class API_RENDERING GLEWDriver : public IDriver
    {
    public:
        GLEWDriver() noexcept;

        void Clear() const noexcept override;
        void PolygonMode(std::any p_face, std::any p_mode) const noexcept override;
        void EnableDebug() const noexcept override;
    };
}
