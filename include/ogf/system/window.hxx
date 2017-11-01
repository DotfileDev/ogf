#pragma once

#include <string>
#include <tuple>

namespace ogf {

    class Event;

    class Window {
    public:
        Window();
        ~Window();

        // Open a new window. If window is opened when this function is called, the existing one is closed first and the
        // new one is created.
        Window& create(const std::string_view title, unsigned short width, unsigned short height);
        void close();
        bool is_open() const noexcept;

        Window& make_current_context();

        bool poll_event(Event& event) const noexcept;
        bool wait_event(Event& event) const noexcept;

        void clear();
        void swap_buffers();

        Window& set_title(const std::string_view title) noexcept;
        std::string_view title();

        Window& set_size(const unsigned int width, const unsigned int height);
        std::tuple<unsigned short, unsigned short> size() const;

        Window& set_position(const int x, const int y);
        std::tuple<int, int> position() const;

    private:
        bool translate_sdl_event_to_ogf_event(Event& event) const;

        static unsigned int s_window_count;

        struct Impl;
        Impl* m_impl;
    };

}
