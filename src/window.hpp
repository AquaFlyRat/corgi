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
    Window();

    Window(std::string name, glm::ivec2 size);

    Window(Window &&other) noexcept;
    Window &operator=(Window other) noexcept;

    ~Window();

    explicit operator bool() const;

    void ProcessEvents();

    void SwapBuffers();

    glm::ivec2 Size() const;

    // These flags can set by `ProcessEvents()`.
    // They reset to `false` next time `ProcessEvents()` is called.
    bool ExitRequested() const;
    bool Resized() const;
};
