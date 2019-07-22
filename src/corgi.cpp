#include "window.hpp"

int main(int, char **)
{
    Window window("Corgi!", glm::ivec2(800,600));
    while (1)
    {
        window.ProcessEvents();
        if (window.ExitRequested())
            break;

        window.SwapBuffers();
    }

    return 0;
}
