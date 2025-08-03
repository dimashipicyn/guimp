#include "filler.h"

#include "game/canvas.h"
#include <queue>
#include <utility>

namespace guimp
{
void Filler::Use(const Point& position, Canvas& canvas)
{
    if (std::exchange(m_used, true))
        return;

    Color pixel = canvas.GetPixel(position);
    if (pixel == m_color)
        return;

    Filling(position, canvas);
}

void Filler::End()
{
    m_used = false;
}

void Filler::Filling(const Point& position, Canvas& canvas)
{
    const Size canvas_size = canvas.GetSize();
    if (position.x < 0 || position.x >= canvas_size.x)
        return;
    if (position.y < 0 || position.y >= canvas_size.y)
        return;

    std::queue<Point> q;
    q.push(position);

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();

        Color pixel = canvas.GetPixel(p);
        if (pixel != m_replace_color)
            continue;

        canvas.SetPixel(p, m_color);

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++)
        {
            const Point next{p.x + dx[i], p.y + dy[i]};
            if (next.x < 0 || next.x >= canvas_size.x)
                continue;
            if (next.y < 0 || next.y >= canvas_size.y)
                continue;
            q.push(next);
        }
    }
}

} // namespace guimp