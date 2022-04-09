#include <iostream>

#include <AI/Dots.h>

Core::AI::Dots::Dots()
{
}

bool Core::AI::Dots::operator==(const Dots& p_right) const
{
    return (this == &p_right);
}

void Core::AI::Dots::SetPosition(const glm::vec3& p_position)
{
    m_position = p_position;
}

void Core::AI::Dots::SetIndexXY(int p_x, int p_y)
{
    x = p_x;
    y = p_y;
}

void Core::AI::Dots::SetPrevious(Dots* p_prevDot)
{
    previous = p_prevDot;
}

void Core::AI::Dots::ShowIndex() const
{
    std::cout << "x:" << x << " y:" << y << " | ";
}
