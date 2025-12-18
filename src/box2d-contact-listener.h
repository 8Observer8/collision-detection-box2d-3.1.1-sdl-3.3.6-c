#ifndef BOX2D_CONTACT_LISTENER_H
#define BOX2D_CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char text[128];
    bool dirty;
} ContactListenerData;

// Call this every frame after stepping the world
void ProcessContactEvents(b2WorldId worldId, ContactListenerData *listener)
{
    b2ContactEvents events = b2World_GetContactEvents(worldId);

    // --- Begin contacts ---
    for (int i = 0; i < events.beginCount; i++)
    {
        b2ContactBeginTouchEvent event = events.beginEvents[i];

        const char *nameA = (const char *)b2Shape_GetUserData(event.shapeIdA);
        const char *nameB = (const char *)b2Shape_GetUserData(event.shapeIdB);

        if (!nameA) nameA = "unknown";
        if (!nameB) nameB = "unknown";

        const char *wallName = strcmp(nameA, "player") == 0 ? nameB : nameA;

        snprintf(listener->text, sizeof(listener->text),
                 "Begin contact with %s", wallName);

        listener->dirty = true;
    }

    // --- End contacts ---
    for (int i = 0; i < events.endCount; i++)
    {
        b2ContactEndTouchEvent event = events.endEvents[i];

        const char *nameA = (const char *)b2Shape_GetUserData(event.shapeIdA);
        const char *nameB = (const char *)b2Shape_GetUserData(event.shapeIdB);

        if (!nameA) nameA = "unknown";
        if (!nameB) nameB = "unknown";

        const char *wallName = strcmp(nameA, "player") == 0 ? nameB : nameA;

        snprintf(listener->text, sizeof(listener->text),
                 "End contact with %s", wallName);
        listener->dirty = true;
    }
}

#endif // BOX2D_CONTACT_LISTENER_H
