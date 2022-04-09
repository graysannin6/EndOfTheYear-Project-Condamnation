#pragma once

#include <unordered_map>
#include <functional>

namespace Rendering::Utils
{
    template<typename ... Types>
    class Event
    {
    public:
        using callback = std::function<void(Types ...)>;
        using callback_id = uint8_t;

        void Invoke(Types ...p_args)
        {
            for (const auto& [id, callback] : m_callbacks)
                callback(p_args...);
        }

        callback_id AddListener(callback p_callback) noexcept
        {
            callback_id id = m_availableListener++;
            m_callbacks.emplace(id, p_callback);
            return id;
        }

        bool RemoveListener(callback_id p_id) noexcept
        {
            return m_callbacks.erase(p_id) != 0;
        }

        void RemoveAllListener() noexcept
        {
            m_callbacks.clear();
        }

		enum KeyState
		{
			Null = -1,
			KeyDown = 1,
			KeyUp = 2,
			Key = 3,
			Completed = 4
        };
        enum KeyCode
        {
            None = -1, //not assigned to our keyboard (shouldn't be sent as return of a key)
            Backspace = 259,
            Delete = 261,
            Tab = 258,
            Return = 257,
            Escape = 256,
            Space = 32,
            KeyPad0 = 320,
            KeyPad1 = 321,
            KeyPad2 = 322,
            KeyPad3 = 323,
            KeyPad4 = 324,
            KeyPad5 = 325,
            KeyPad6 = 326,
            KeyPad7 = 327,
            KeyPad8 = 328,
            KeyPad9 = 329,
            KeyPadPeriod = 330,
            KeyPadDivide = 331,
            KeyPadMultiply = 332,
            KeyPadMinus = 333,
            KeyPadPlus = 334,
            KeyPadEnter = 335,
            UpArrow = 265,
            DownArrow = 264,
            RightArrow = 262,
            LeftArrow = 263,
            Insert = 260,
            Home = 268,
            End = 269,
            PageUp = 266,
            PageDown = 267,
            F1 = 290,
            F2 = 291,
            F3 = 292,
            F4 = 293,
            F5 = 294,
            F6 = 295,
            F7 = 296,
            F8 = 297,
            F9 = 298,
            F10 = 299,
            F11 = 301,
            F12 = 302,
            F13 = 303,
            F14 = 304,
            F15 = 305,
            Alpha0 = 48,
            Alpha1 = 49,
            Alpha2 = 50,
            Alpha3 = 51,
            Alpha4 = 52,
            Alpha5 = 53,
            Alpha6 = 54,
            Alpha7 = 55,
            Alpha8 = 56,
            Alpha9 = 57,
            Backslash = 92,
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,
            Tilde = 96,
            Numlock = 282,
            CapsLock = 280,
            ScrollLock = 281,
            RightShift = 344,
            LeftShift = 340,
            RightControl = 345,
            LeftControl = 341,
            RightAlt = 346,
            LeftAlt = 342,
            LeftWindows = 343,
            RightWindows = 347,
            Print = 342,
            Mouse0 = 0,
            Mouse1 = 1,
            Mouse2 = 2,
        };

    private:
        callback_id                                    m_availableListener{0u};
        std::unordered_map<callback_id, callback> m_callbacks;
    };
}
