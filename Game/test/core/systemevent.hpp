/*
 * Class which represents an operating system event.
 * Licença: LGPL. Sem copyright.
 */
#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include <SDL2/SDL.h>

class SystemEvent
{
public:
    typedef enum { UNKNOWN, QUIT } Type;

    SystemEvent(Type type);

    Type type() const;

    static SystemEvent from_SDL(const SDL_Event& event);

private:
    Type m_type;
};

#endif
