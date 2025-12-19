#define SDL_MAIN_USE_CALLBACKS 1 // Use the callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <box2d/box2d.h>
#include <stdio.h>

#include "box2d-contact-listener.h"
#include "box2d-debug-drawer.h"

#define DEG2RAD(x) ((x) * 0.017453292519943295f)
#define TIME_STEP (1.0f / 60.0f)
#define MAX_FRAME_TIME 0.25f

// We will use this renderer to draw into this window every frame
static SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
static SDL_Texture *textTexture = NULL;
const SDL_PixelFormatDetails *format = NULL;
static TTF_Font *font = NULL;
static SDL_FRect textRect;

static b2WorldId worldId;
float ppm = 30.f; // Pixels per meter
float friction = 0.1f;
static b2DebugDraw debugDrawer;
static ContactListenerData contactData;

static b2BodyId playerBodyId;
static float playerSpeed = 5.f;

static float accumulator = 0.0f;
static Uint64 last_ticks = 0;

typedef struct
{
    bool up;
    bool down;
    bool left;
    bool right;
} Keys;

static Keys keys = { 0 };

// This function runs once at startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Initialize the TTF library
    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    const char *title = "Collision Detection (SDL3 / C)";
    if (!SDL_CreateWindowAndRenderer(title, 430, 430, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, 1);

    // --- Print SDL versions ---
    printf("Compiled SDL3 version: %d.%d.%d\n",
        SDL_MAJOR_VERSION,
        SDL_MINOR_VERSION,
        SDL_MICRO_VERSION);
    // Get the version of the SDL library linked at runtime
    int v = SDL_GetVersion();
    printf("Linked SDL3 version:   %d.%d.%d\n", SDL_VERSIONNUM_MAJOR(v),
        SDL_VERSIONNUM_MINOR(v), SDL_VERSIONNUM_MICRO(v));

    // --- SDL3_ttf version ---
    v = TTF_Version();
    int major = SDL_VERSIONNUM_MAJOR(v);
    int minor = SDL_VERSIONNUM_MINOR(v);
    int micro = SDL_VERSIONNUM_MICRO(v);
    printf("SDL3_ttf version:      %d.%d.%d\n", major, minor, micro);

    // --- Print Box2D v3 version ---
    b2Version version = b2GetVersion();
    printf("Box2D version:         %d.%d.%d\n", version.major, version.minor, version.revision);

    // Get the pixel format
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    format = SDL_GetPixelFormatDetails(surface->format);

    font = TTF_OpenFont("./assets/fonts/LiberationSans-Regular.ttf", 28);
    if (!font)
    {
        SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Initialize contact listener data
    strcpy(contactData.text, "Make a contact with a wall");
    contactData.dirty = true;

    b2Vec2 gravity = { 0.f, 0.f };
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;
    worldId = b2CreateWorld(&worldDef);

    debugDrawer = b2DefaultDebugDraw();
    debugDrawer.drawShapes = true;
    debugDrawer.DrawSolidPolygonFcn = drawSolidPolygon;
    debugDrawer.DrawSolidCircleFcn = drawSolidCircle;

    // --- Top wall ---
    {
        b2BodyDef topWallBodyDef = b2DefaultBodyDef();
        topWallBodyDef.type = b2_staticBody;
        topWallBodyDef.position = (b2Vec2) { 200.f / ppm, 150.f / ppm };
        topWallBodyDef.rotation = b2MakeRot(DEG2RAD(20.0f));

        b2BodyId topWallBodyId = b2CreateBody(worldId, &topWallBodyDef);

        b2Polygon topWallShape =
            b2MakeBox((200.f / 2.f) / ppm, (20.f / 2.f) / ppm);

        b2ShapeDef topWallShapeDef = b2DefaultShapeDef();
        topWallShapeDef.material.friction = friction;
        topWallShapeDef.enableContactEvents = true;

        b2ShapeId topWallShapeId =
            b2CreatePolygonShape(topWallBodyId, &topWallShapeDef, &topWallShape);

        // User data
        b2Shape_SetUserData(topWallShapeId, "top wall");
    }

    // --- Left wall ---
    {
        b2BodyDef leftWallBodyDef = b2DefaultBodyDef();
        leftWallBodyDef.type = b2_staticBody;
        leftWallBodyDef.position = (b2Vec2) { 120.f / ppm, 230.f / ppm };
        leftWallBodyDef.rotation = b2MakeRot(DEG2RAD(90.0f));

        b2BodyId leftWallBodyId = b2CreateBody(worldId, &leftWallBodyDef);

        b2Polygon leftWallShape =
            b2MakeBox((200.f / 2.f) / ppm, (20.f / 2.f) / ppm);

        b2ShapeDef leftWallShapeDef = b2DefaultShapeDef();
        leftWallShapeDef.material.friction = friction;
        leftWallShapeDef.enableContactEvents = true;

        b2ShapeId leftWallShapeId =
            b2CreatePolygonShape(leftWallBodyId, &leftWallShapeDef, &leftWallShape);

        b2Shape_SetUserData(leftWallShapeId, "left wall");
    }

    // --- Right wall ---
    {
        b2BodyDef rightWallBodyDef = b2DefaultBodyDef();
        rightWallBodyDef.type = b2_staticBody;
        rightWallBodyDef.position = (b2Vec2) { 280.f / ppm, 285.f / ppm };
        rightWallBodyDef.rotation = b2MakeRot(DEG2RAD(90.0f));

        b2BodyId rightWallBodyId = b2CreateBody(worldId, &rightWallBodyDef);

        b2Polygon rightWallShape =
            b2MakeBox((200.f / 2.f) / ppm, (20.f / 2.f) / ppm);

        b2ShapeDef rightWallShapeDef = b2DefaultShapeDef();
        rightWallShapeDef.material.friction = friction;
        rightWallShapeDef.enableContactEvents = true;

        b2ShapeId rightWallShapeId =
            b2CreatePolygonShape(rightWallBodyId, &rightWallShapeDef, &rightWallShape);

        b2Shape_SetUserData(rightWallShapeId, "right wall");
    }

    // --- Player ---
    {
        b2BodyDef playerBodyDef = b2DefaultBodyDef();
        playerBodyDef.type = b2_dynamicBody;
        playerBodyDef.position = (b2Vec2) { 200.f / ppm, 250.f / ppm };
        playerBodyDef.fixedRotation = true;
        playerBodyDef.enableSleep = false;

        playerBodyId = b2CreateBody(worldId, &playerBodyDef);

        b2Circle playerCircle = {
            .center = { 0.0f, 0.0f },
            .radius = 20.f / ppm
        };

        b2ShapeDef playerShapeDef = b2DefaultShapeDef();
        playerShapeDef.density = 1.0f;
        playerShapeDef.material.friction = friction;
        playerShapeDef.enableContactEvents = true;

        b2ShapeId playerShapeId =
            b2CreateCircleShape(playerBodyId, &playerShapeDef, &playerCircle);

        b2Shape_SetUserData(playerShapeId, "player");
    }

    last_ticks = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

// This function runs when a new event (mouse input, keypresses, etc) occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
        {
            SDL_Scancode sc = event->key.scancode;

            if (sc == SDL_SCANCODE_W || sc == SDL_SCANCODE_UP)
                keys.up = true;
            if (sc == SDL_SCANCODE_S || sc == SDL_SCANCODE_DOWN)
                keys.down = true;
            if (sc == SDL_SCANCODE_A || sc == SDL_SCANCODE_LEFT)
                keys.left = true;
            if (sc == SDL_SCANCODE_D || sc == SDL_SCANCODE_RIGHT)
                keys.right = true;
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            SDL_Scancode sc = event->key.scancode;

            if (sc == SDL_SCANCODE_W || sc == SDL_SCANCODE_UP)
                keys.up = false;
            if (sc == SDL_SCANCODE_S || sc == SDL_SCANCODE_DOWN)
                keys.down = false;
            if (sc == SDL_SCANCODE_A || sc == SDL_SCANCODE_LEFT)
                keys.left = false;
            if (sc == SDL_SCANCODE_D || sc == SDL_SCANCODE_RIGHT)
                keys.right = false;
            break;
        }

        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

void keyboard(void)
{
    b2Vec2 velocity = { 0.0f, 0.0f };

    if (keys.up)
    {
        velocity.y = -playerSpeed;
    }
    else if (keys.down)
    {
        velocity.y = playerSpeed;
    }
    else if (keys.left)
    {
        velocity.x = -playerSpeed;
    }
    else if (keys.right)
    {
        velocity.x = playerSpeed;
    }

    b2Body_SetLinearVelocity(playerBodyId, velocity);
}

// This function runs once per frame, and is the heart of the program
SDL_AppResult SDL_AppIterate(void *appstate)
{
    Uint64 current_ticks = SDL_GetTicks();

    float frameTime = (float)(current_ticks - last_ticks) / 1000.0f;
    last_ticks = current_ticks;

    if (frameTime > MAX_FRAME_TIME)
    {
        frameTime = MAX_FRAME_TIME;
    }

    accumulator += frameTime;

    while (accumulator >= TIME_STEP)
    {
        // Step physics
        b2World_Step(worldId, TIME_STEP, 3);

        // Read contact events immediately
        ProcessContactEvents(worldId, &contactData);

        accumulator -= TIME_STEP;
    }

    // Process keyboard input
    keyboard();

    // --- Update text only when dirty ---
    if (contactData.dirty)
    {
        // Destroy old texture
        if (textTexture)
        {
            SDL_DestroyTexture(textTexture);
            textTexture = NULL;
        }

        SDL_Color textColor = { 255, 255, 255 };

        // Render text to surface
        SDL_Surface *surface = TTF_RenderText_Blended(font, contactData.text,
            strlen(contactData.text), textColor);

        if (surface)
        {
            // Create texture from surface
            textTexture = SDL_CreateTextureFromSurface(renderer, surface);

            // Get texture size
            float w, h;
            SDL_GetTextureSize(textTexture, &w, &h);

            // Set text rectangle
            textRect.x = 50.0f;
            textRect.y = 50.0f;
            textRect.w = (float)w;
            textRect.h = (float)h;

            SDL_DestroySurface(surface);
        }

        contactData.dirty = false;
    }

    SDL_SetRenderDrawColor(renderer, 55, 55, 55, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // --- Render text every frame ---
    if (textTexture)
    {
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
    }

    b2World_Draw(worldId, &debugDrawer);

    // Update the screen
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

// This function runs once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (textTexture)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }

    if (font)
    {
        TTF_CloseFont(font);
        font = NULL;
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    TTF_Quit();
    SDL_Quit();
}
