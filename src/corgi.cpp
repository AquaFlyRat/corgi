#include <SDL.h>
#include <fmt/core.h>

int main()
{
  fmt::print("[libfmt Test] -> The answer is {0}.\n", 42);
  
  SDL_version version;
  SDL_GetVersion(&version);
  printf("[SDL Test]: Version -> %i.%i.%i\n", version.major, version.minor, version.patch);
  
  return 0;
}
