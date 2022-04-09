#include <iostream>

#include <AI/Grid.h>

Core::AI::Grid::Grid(int p_sizeX, int p_sizeY) : m_sizeX(p_sizeX), m_sizeY(p_sizeY)
{
    LURDMoves[0] = {-1, 0};
    LURDMoves[1] = {0, -1};
    LURDMoves[2] = {1, 0};
    LURDMoves[3] = {0, 1};

    m_grid     = new Dots*[m_sizeX];
    for (int i = 0; i < m_sizeX; ++i)
    {
        m_grid[i] = new Dots[m_sizeY];
    }

    for (int i = 0; i < m_sizeX; ++i)
    {
        for (int j = 0; j < m_sizeY; ++j)
        {
            m_grid[i][j].SetPosition(glm::vec3(i, j, 0));
            m_grid[i][j].SetIndexXY(i, j);
            m_grid[i][j].ShowIndex();
            // std::cout << "x:" << m_grid[i][j].x << " y:" << m_grid[i][j].y << " | ";
        }
        std::cout << '\n';
    }
}

Core::AI::Grid::~Grid()
{
    for (int i = 0; i < m_sizeX; ++i)
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

Core::AI::Dots* Core::AI::Grid::GetNode(int p_x, int p_y) const
{
    if (p_x < 0 || p_x >= m_sizeX ||
        p_y < 0 || p_y >= m_sizeY)
    {
        return nullptr;
    }
    return &m_grid[p_x][p_y];
}

const int& Core::AI::Grid::GetSizeX() const
{
    return m_sizeX;
}

const int& Core::AI::Grid::GetSizeY() const
{
    return m_sizeY;
}
