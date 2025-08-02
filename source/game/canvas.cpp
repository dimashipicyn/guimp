#include "canvas.h"

#include "core/app.h"
#include "core/color.h"
#include "core/provider.h"
#include "core/renderer.h"

namespace guimp
{
Canvas::Canvas(const Size& size)
{
    Renderer* r = Provider::Self().Renderer();
    m_texture = r->CreateTexture(size);

    r->SetRenderTarget(m_texture);
    r->DrawFillRect({GetAbsPos().x, GetAbsPos().y, size.x, size.y}, Colors::WHITE);
    r->SetRenderTarget({});
}

void Canvas::SetPixel(const Point& position, const Color& color)
{
    Renderer* r = Provider::Self().Renderer();
    r->SetRenderTarget(m_texture);
    r->DrawPoint(position, color);
    r->SetRenderTarget({});
}

void Canvas::SetLine(const Point& start, const Point& end, const Color& color)
{
    Renderer* r = Provider::Self().Renderer();
    r->SetRenderTarget(m_texture);
    r->DrawLine(start, end, color);
    r->SetRenderTarget({});
}

void Canvas::Draw(App& app)
{
    app.Renderer->DrawTexture(m_texture);
}

} // namespace guimp