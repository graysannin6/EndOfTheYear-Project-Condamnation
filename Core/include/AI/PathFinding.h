#pragma once

#include <memory>

#include <AI/Grid.h>

namespace Core::AI
{
    class PathFinding
    {
    public:
        PathFinding(int p_sizeX, int p_sizeY);
        ~PathFinding() = default;

        void FindNeighbors(Grid& p_grid, Dots& p_dot) const;

        std::unique_ptr<Grid> m_grid;
    };
}
