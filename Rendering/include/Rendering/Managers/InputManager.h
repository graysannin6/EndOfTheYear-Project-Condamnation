#pragma once

#include <memory>
#include <list>

#include <Rendering/Context/IWindow.h>
#include <Rendering/Export.h>

namespace Rendering::Managers
{
    class API_RENDERING InputManager
    {
    public:
        using KeyCode = Utils::Event<int>::KeyCode;
        using KeyState = Utils::Event<int>::KeyState;

        InputManager(const std::shared_ptr<Context::IWindow>& p_window) noexcept;
        ~InputManager() noexcept;

		static void Init(const std::shared_ptr<Context::IWindow>& p_window);
        static const std::unique_ptr<InputManager>& GetInstance() noexcept { return m_instance; }
        
        bool GetKeyDown(const KeyCode& p_keyCode);
        bool GetKeyUp(const KeyCode& p_keyCode);
        bool GetKey(const KeyCode& p_keyCode);

        void UpdateCursorPos();

		const std::tuple<double, double>& GetMouseCursorPos() const noexcept { return m_mouseCursorPos; }

    private:
        void OnKeyPressed(int p_key);
        void OnKeyReleased(int p_key);
        void OnMouseButtonPressed(int p_button);
        void OnMouseButtonReleased(int p_button);


		std::shared_ptr<Context::IWindow> m_window{};

        std::list<int> m_keyInputList{};
        glm::vec2 m_MouseInputList{0,0};

        uint8_t m_idKeyPressedListener {0};
        uint8_t m_idKeyReleasedListener {0};
        uint8_t m_idMouseButtonPressedListener {0};
        uint8_t m_idMouseButtonReleasedListener {0};

        std::unordered_map<int, int> m_inputBuffer{};
        std::tuple<double, double> m_mouseCursorPos{};

		static std::unique_ptr<InputManager> m_instance;

    };
}
