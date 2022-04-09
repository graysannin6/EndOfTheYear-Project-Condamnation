#pragma once

#include <memory>

#include <Rendering/Context/IDevice.h>
#include <Rendering/Export.h>
#include <Rendering/Context/OpenGL/GLFWWindow.h>

namespace Rendering::Context::OpenGL
{
    class API_RENDERING GLFWDevice : public IDevice
    {
    public:
        GLFWDevice() noexcept;
        ~GLFWDevice() noexcept;

        void Init() noexcept override;
        bool ShouldClose() const noexcept override;

        void CalculateDeltaTime() noexcept;

        void RefreshEvents() const noexcept override;
        void Render() const noexcept override;

        std::shared_ptr<GLFWWindow> GetWindow() const noexcept { return m_window; }
        const float&                GetDeltaTime() const noexcept { return m_deltaTime; }

        void Close() const noexcept;

    private:
        std::shared_ptr<GLFWWindow> m_window{};

        float m_lastTime{0};
        float m_currentTime{0};
        float m_deltaTime{0};
        int   m_maxFPS{0};
    };
}
