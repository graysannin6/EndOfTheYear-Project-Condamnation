#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace Core::AI
{
    class Dots
    {
    public:
        Dots();

        bool operator==(const Dots& p_right) const;

        void SetPosition(const glm::vec3& p_position);
        void SetIndexXY(int p_x, int p_y);

        const int& GetX() const { return x; }
        const int& GetY() const { return y; }

        const bool& GetIfWall() const { return isWall; }

        const float& GetF() const { return f; }
        const float& GetG() const { return g; }
        const float& GetH() const { return h; }

        void SetF(float p_f) { f = p_f; }
        void SetG(float p_g) { g = p_g; }
        void SetH(float p_h) { h = p_h; }

        void SetPrevious(Dots* p_prevDot);

        std::vector<Dots>& GetNeighbors() { return m_neighbors; }
        std::vector<Dots>& GetNeighboringWalls() { return m_neighboringWalls; }

        void ShowIndex() const;
    private:
        int x;
        int y;

        float f;
        float g;
        float h;

        glm::vec3 m_position;
        std::vector<Dots> m_neighbors;
        std::vector<Dots> m_neighboringWalls;

        Dots* previous;

        bool isWall = false;

    };
}
