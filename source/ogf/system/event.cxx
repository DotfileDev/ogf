#include <ogf/system/event.hxx>

#include <SDL2/SDL_events.h>

namespace ogf {

    Event::Event() {
        m_sdl_event = new SDL_Event;
    }

    Event::~Event() {
        delete m_sdl_event;
    }

}
