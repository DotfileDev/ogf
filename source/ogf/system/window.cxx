#include <ogf/system/window.hxx>

#include <glad/glad.h>

#include <SDL2/SDL.h>

#include <ogf/graphics/drawable.hxx>
#include <ogf/system/event.hxx>

namespace ogf {

    struct Window::Impl {
        SDL_Window*   window{nullptr};
        SDL_GLContext gl_context{nullptr};
    };

    unsigned int Window::s_window_count{0};

    Window::Window() {
        m_impl = new Impl;
        ++s_window_count;
        if(s_window_count > 0) {
            SDL_Init(SDL_INIT_VIDEO);
        }
    }

    Window::~Window() {
        close();
        delete m_impl;
        --s_window_count;
        if(s_window_count == 0) {
            SDL_Quit();
        }
    }

    Window& Window::create(const std::string_view title, unsigned short width, unsigned short height) {
        // TODO: Move it somewhere else and let user set these.
        m_impl->window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_OPENGL);
        if(m_impl->window == nullptr) {
            throw std::runtime_error{"Failed to create the window. Reason: " + std::string{SDL_GetError()}};
        }
        make_current_context();
        if(!gladLoadGL()) {
            throw std::runtime_error{"Failed to initialize glad."};
        }
        glEnable(GL_DEPTH_TEST);
        return *this;
    }

    void Window::close() {
        if(m_impl->window == nullptr) {
            return;
        }
        SDL_GL_DeleteContext(m_impl->gl_context);
        SDL_DestroyWindow(m_impl->window);
        m_impl->window = nullptr;
    }

    Window& Window::make_current_context() {
        if(m_impl->gl_context == nullptr) {
            m_impl->gl_context = SDL_GL_CreateContext(m_impl->window);
        } else {
            if(!SDL_GL_MakeCurrent(m_impl->window, m_impl->gl_context)) {
                throw std::runtime_error{"Failed to set the window as current context."};
            }
        }
        return *this;
    }

    bool Window::poll_event(Event& event) const noexcept {
        if(!SDL_PollEvent(event.m_sdl_event)) {
            return false;
        }
        const auto is_known_event = translate_sdl_event_to_ogf_event(event);
        if(!is_known_event) {
            return false;
        }
        return true;
    }

    bool Window::wait_event(Event& event) const noexcept {
        if(!SDL_WaitEvent(event.m_sdl_event)) {
            return false;
        }
        const auto is_known_event = translate_sdl_event_to_ogf_event(event);
        if(!is_known_event) {
            return false;
        }
        return true;
    }

    void Window::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::swap_buffers() {
        SDL_GL_SwapWindow(m_impl->window);
    }

    void Window::draw(const Drawable& drawable, Shader& shader) const {
        drawable.draw(*this, shader);
    }

    bool Window::is_open() const noexcept {
        return m_impl->window != nullptr;
    }

    Window& Window::set_title(const std::string_view title) noexcept {
        SDL_SetWindowTitle(m_impl->window, title.data());
        return *this;
    }

    std::string_view Window::title() {
        return SDL_GetWindowTitle(m_impl->window);
    }

    Window& Window::set_size(const unsigned int width, const unsigned int height) {
        SDL_SetWindowSize(m_impl->window, width, height);
        return *this;
    }

    std::tuple<unsigned short, unsigned short> Window::size() const {
        int w{}, h{};
        SDL_GetWindowSize(m_impl->window, &w, &h);
        return std::make_tuple(static_cast<unsigned short>(w), static_cast<unsigned short>(h));
    }

    Window& Window::set_position(const int x, const int y) {
        SDL_SetWindowPosition(m_impl->window, x, y);
        return *this;
    }

    std::tuple<int, int> Window::position() const {
        int x{}, y{};
        SDL_GetWindowSize(m_impl->window, &x, &y);
        return std::make_tuple(x, y);
    }

    bool Window::translate_sdl_event_to_ogf_event(Event& event) const {
        switch(event.m_sdl_event->type) {
            case SDL_QUIT: {
                event.type = EventType::CLOSED;
                return true;
            }
            default: {
                return false;
            }
        }
        return false;
    }

}
