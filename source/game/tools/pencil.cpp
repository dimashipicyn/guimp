#include "pencil.h"
#include "game/canvas.h"

namespace guimp
{
void Pencil::Use(const Point& position, Canvas& canvas)
{
    if (!m_prev_position)
        canvas.SetPixel(position, m_color);
    else
        canvas.SetLine(*m_prev_position, position, m_color);
    m_prev_position =  position;
}

void Pencil::End()
{
    m_prev_position.reset();
}
} // namespace guimp