#pragma once

#include <stdexcept>
#include <string>

#include <glm/glm.hpp>
#include <SDL.h>

#include "finally.hpp"
#include "libfmt.hpp"

class Window
{
    struct Data
    {
        // Either both or none of those pointers are null.
        SDL_Window *m_window = 0;
        SDL_Renderer *m_renderer = 0;
        glm::ivec2 m_size = glm::ivec2(0);

        std::uint64_t m_ticks = 1;

        bool m_exit_requested = false;
        bool m_resized = false;
    };
    Data data;


  public:
    Window() {}
    Window(std::string name, glm::ivec2 size)
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

    Window(Window &&other) noexcept : data(std::exchange(other.data, {})) {}

    Window &operator=(Window other) noexcept
    {
        std::swap(data, other.data);
        return *this;
    }

    ~Window()
    {
        if (*this)
        {
            SDL_DestroyRenderer(data.m_renderer);
            SDL_DestroyWindow(data.m_window);
            SDL_Quit();
        }
    }

    explicit operator bool() const
    {
        return bool(data.m_window);
    }

    void ProcessEvents()
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

    void SwapBuffers()
    {
        assert(*this);
        SDL_RenderPresent(data.m_renderer);
    }

    glm::ivec2 Size() const
    {
        assert(*this);
        return data.m_size;
    }

    // This flag can set by `ProcessEvents()`.
    // It resets to `false` next time `ProcessEvents()` is called.
    bool ExitRequested() const
    {
        assert(*this);
        return data.m_exit_requested;
    }

    // This flag can set by `ProcessEvents()`.
    // It resets to `false` next time `ProcessEvents()` is called.
    bool Resized() const
    {
        assert(*this);
        return data.m_resized;
    }
};
