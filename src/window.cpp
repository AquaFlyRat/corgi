#include "window.hpp"

Window::Window() {}

Window::Window(std::string name, glm::ivec2 size)
{
    bool sdl_ok = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0;
    if (!sdl_ok)
        throw std::runtime_error("Unable to initialize SDL: {}"_format(SDL_GetError()));
    FINALLY_ON_THROW( SDL_Quit(); )

    data.m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, 0);
    if (!data.m_window)
        throw std::runtime_error("Unable to open window: {}"_format(SDL_GetError()));
    FINALLY_ON_THROW( SDL_DestroyWindow(data.m_window); )

    data.m_renderer = SDL_CreateRenderer(data.m_window, -1, 0);
    if (!data.m_renderer)
        throw std::runtime_error("Unable to create renderer: {}"_format(SDL_GetError()));
    FINALLY_ON_THROW( SDL_DestroyRenderer(data.m_renderer); )

    data.m_size = size;
}

Window::Window(Window &&other) noexcept : data(std::exchange(other.data, {})) {}

Window &Window::operator=(Window other) noexcept
{
    std::swap(data, other.data);
    return *this;
}

Window::~Window()
{
    if (*this)
    {
        SDL_DestroyRenderer(data.m_renderer);
        SDL_DestroyWindow(data.m_window);
        SDL_Quit();
    }
}

Window::operator bool() const
{
    return bool(data.m_window);
}

void Window::ProcessEvents()
{
    assert(*this);

    data.m_ticks++;

    data.m_exit_requested = false;
    data.m_resized = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
          case SDL_QUIT:
            data.m_exit_requested = true;
            break;
          case SDL_WINDOWEVENT:
            switch (event.window.type)
            {
              case SDL_WINDOWEVENT_RESIZED:
                data.m_resized = true;
                break;
            }
            break;
        }
    }
}

void Window::SwapBuffers()
{
    assert(*this);
    SDL_RenderPresent(data.m_renderer);
}

glm::ivec2 Window::Size() const
{
    assert(*this);
    return data.m_size;
}

bool Window::ExitRequested() const
{
    assert(*this);
    return data.m_exit_requested;
}

bool Window::Resized() const
{
    assert(*this);
    return data.m_resized;
}
