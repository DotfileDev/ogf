#pragma once

union SDL_Event;

namespace ogf {

    enum class EventType {
        CLOSED
    };

    class Event {
    public:
        Event();
        ~Event();

        EventType type;

    private:
        friend class Window;

        SDL_Event* m_sdl_event{nullptr};
    };

}
