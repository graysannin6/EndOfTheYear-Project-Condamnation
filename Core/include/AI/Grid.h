#pragma once

#include <array>

#include <AI/Dots.h>

namespace Core::AI
{
    class Grid
    {
    public:
        Grid(int p_sizeX, int p_sizeY);
        ~Grid();

        Dots* GetNode(int x, int y) const;

        const int& GetSizeX() const;
        const int& GetSizeY() const;

        std::array<std::array<int, 2>, 4> LURDMoves{};
    private:
        Dots** m_grid;

        int m_sizeX;
        int m_sizeY;
    };
}
