#ifndef BOX2D_DEBUG_DRAWER_H
#define BOX2D_DEBUG_DRAWER_H

#include <SDL3/SDL.h>

extern SDL_Renderer *renderer;
extern const SDL_PixelFormatDetails *format;
extern float ppm;

static void drawSolidPolygon(b2Transform transform,
    const b2Vec2 *vertices, int vertexCount,
    float radius, b2HexColor color, void *context)
{
    (void)radius;
    (void)context;

    // Extract RGB
    Uint8 r, g, b;
    SDL_GetRGB(color, format, NULL, &r, &g, &b);
    // Draw a collider rectangle with lines
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < vertexCount; ++i)
    {
        int next_index = (i + 1 == vertexCount) ? 0 : i + 1;
        b2Vec2 p0 = b2TransformPoint(transform, vertices[i]);
        b2Vec2 p1 = b2TransformPoint(transform, vertices[next_index]);
        float x0 = p0.x * ppm;
        float y0 = p0.y * ppm;
        float x1 = p1.x * ppm;
        float y1 = p1.y * ppm;
        SDL_RenderLine(renderer, x0, y0, x1, y1);
    }

    // --- Tip: Draw orientation line ---
    // Compute polygon center
    float cx = 0.f, cy = 0.f;
    for (int i = 0; i < vertexCount; ++i) {
        b2Vec2 p = b2TransformPoint(transform, vertices[i]);
        cx += p.x;
        cy += p.y;
    }
    cx = (cx / vertexCount) * ppm;
    cy = (cy / vertexCount) * ppm;

    // Midpoint of second edge (vertex[1] → vertex[2])
    b2Vec2 p1 = b2TransformPoint(transform, vertices[1]);
    b2Vec2 p2 = b2TransformPoint(transform, vertices[2]);
    float mx = (p1.x + p2.x) * 0.5f * ppm;
    float my = (p1.y + p2.y) * 0.5f * ppm;

    // Draw center → edge midpoint line (acts like "direction tip")
    SDL_RenderLine(renderer, cx, cy, mx, my);
}

static void drawSolidCircle(b2Transform transform, float radius,
    b2HexColor color, void *context)
{
    (void)radius;
    (void)context;

    float angle = 0.f;
    const int numberOfSegments = 20;
    const float angleStep = 360.f / numberOfSegments;

    // Extract RGB
    Uint8 r, g, b;
    SDL_GetRGB(color, format, NULL, &r, &g, &b);
    // Draw a collider rectangle with lines
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    float x = radius * cos(angle * SDL_PI_F / 180.f);
    float y = radius * sin(angle * SDL_PI_F / 180.f);
    b2Vec2 p0 = b2TransformPoint(transform, (b2Vec2){ x, y });
    float x0 = p0.x * ppm;
    float y0 = p0.y * ppm;
    angle += angleStep;

    for (int i = 0; i < numberOfSegments; ++i)
    {
        float x = radius * cos(angle * SDL_PI_F / 180.f);
        float y = radius * sin(angle * SDL_PI_F / 180.f);
        b2Vec2 p1 = b2TransformPoint(transform, (b2Vec2){ x, y });
        float x1 = p1.x * ppm;
        float y1 = p1.y * ppm;
        SDL_RenderLine(renderer, x0, y0, x1, y1);
        x0 = x1;
        y0 = y1;
        angle += angleStep;
        if (angle >= 360.f)
        {
            angle = 0.f;
        }
    }

    // --- Tip: Draw orientation line ---
    // Circle center
    b2Vec2 c = b2TransformPoint(transform, (b2Vec2){ 0.f, 0.f });
    float cx = c.x * ppm;
    float cy = c.y * ppm;

    // Direction = transform applied to (radius, 0)
    b2Vec2 orient = b2TransformPoint(transform, (b2Vec2){ radius, 0.f });
    float ox = orient.x * ppm;
    float oy = orient.y * ppm;

    // Draw center → orientation marker
    SDL_RenderLine(renderer, cx, cy, ox, oy);
}

#endif // BOX2D_DEBUG_DRAWER_H
