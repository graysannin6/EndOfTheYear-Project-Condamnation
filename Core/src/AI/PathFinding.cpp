#include <AI/PathFinding.h>

Core::AI::PathFinding::PathFinding(int p_sizeX, int p_sizeY)
{
    m_grid = std::make_unique<Grid>(p_sizeX, p_sizeY);
}

void Core::AI::PathFinding::FindNeighbors(Grid& p_grid, Dots& p_dot) const
{
    // Add Left/Up/Right/Down Moves
    for (int k = 0; k < 4; ++k)
    {
        Dots* node = p_grid.GetNode(p_dot.GetX() + p_grid.LURDMoves[k][0],
            p_dot.GetY() + p_grid.LURDMoves[k][1]);

        if (node != nullptr)
        {
            if (!node->GetIfWall())
            {
                p_dot.GetNeighbors().push_back(*node);
            }
            else
            {
                p_dot.GetNeighboringWalls().push_back(*node);
            }
        }
    }
}
