#pragma once

#include <Rendering/Export.h>

namespace Rendering::Context
{
    class API_RENDERING IDevice
    {
    public:
        virtual ~IDevice() = default;

        virtual void Init() noexcept = 0;
        virtual bool ShouldClose() const noexcept = 0;
        virtual void Render() const noexcept = 0;
        virtual void RefreshEvents() const noexcept = 0;
    };
}