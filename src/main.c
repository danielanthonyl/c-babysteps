// Example program:
// Using SDL2 to create an application window

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct
{
  int y;
  int x;
  SDL_Texture *texture;
} Player;

typedef struct
{
  SDL_Renderer *renderer;
  SDL_Window *window;
} App;

App app;
Player player;

SDL_Texture *loadTexture(char *filename)
{
  SDL_Texture *texture;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

  texture = IMG_LoadTexture(app.renderer, filename);

  return texture;
}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
  IMG_Init(IMG_INIT_PNG);   // Initialize SDL2_image

  app.window = SDL_CreateWindow(
      "An SDL2 window",        // window title
      SDL_WINDOWPOS_UNDEFINED, // initial x position
      SDL_WINDOWPOS_UNDEFINED, // initial y position
      640,                     // width, in pixels
      480,                     // height, in pixels
      SDL_RENDERER_ACCELERATED // flags - see below
  );

  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
  player.x = 100;
  player.y = 100;
  player.texture = loadTexture("./player.png");

  // SDL_Window *window; // Declare a pointer

  // Create an application window with the following settings:

  // Check that the window was successfully created
  if (app.window == NULL)
  {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  // The window is open: could enter program loop here (see SDL_PollEvent())
  while (app.window)
  {
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 250, 195, 235, 255);
    SDL_RenderCopy(app.renderer, player.texture, NULL, NULL);
    SDL_RenderPresent(app.renderer);

    SDL_Event event;

    while (SDL_PollEvent(&event))
    { // poll until all events are handled!
      // decide what to do with this event.
    }

    // update game state, draw the current frame
  }

  SDL_Delay(3000); // Pause execution for 3000 milliseconds, for example

  // Close and destroy the window
  SDL_DestroyWindow(app.window);

  // Clean up
  SDL_Quit();
  return 0;
}