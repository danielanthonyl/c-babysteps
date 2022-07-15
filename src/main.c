// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -lSDL2_image -ldl

// C++ Standard Libraries
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file)
{
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = IMG_Load(file);
  if (surface)
  {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }
  return texture;
}

int main(int argc, char *argv[])
{
  // Create a window data type
  // This pointer will point to the
  // window that is allocated from SDL_CreateWindow
  SDL_Window *window = NULL;

  // Initialize the video subsystem.
  // iF it returns less than 1, then an
  // error code will be received.
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    // std::cout << "SDL could not be initialized: " << SDL_GetError();
    printf("SDL could not be initialized: %s\n", SDL_GetError());
  }
  else
  {
    // std::cout << "SDL video system is ready to go\n";
    printf("SDL video system is ready to go\n");
  }
  // Request a window to be created for our platform
  // The parameters are for the title, x and y position,
  // and the width and height of the window.
  window = SDL_CreateWindow("C++ SDL2 Window", 20, 20, 640, 480, SDL_WINDOW_SHOWN);

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Setup and initialize the SDL2_Image library
  // with our supported formats
  int flags = IMG_INIT_PNG;
  int initStatus = IMG_Init(flags);
  if ((initStatus & flags) != flags)
  {
    // std::cout << "SDL2_Image format not available" << std::endl;
    printf("SDL2_Image format not available\n");
  }

  SDL_Surface *image;
  image = IMG_Load("./images/mario.png");
  if (!image)
  {
    // std::cout << "Image not loaded..." << std::endl;
    printf("Image not loaded...\n");
  }

  SDL_Texture *ourPNG = SDL_CreateTextureFromSurface(renderer, image);

  // Infinite loop for our application
  int gameIsRunning = 1;
  // Main application loop
  while (gameIsRunning)
  {
    SDL_Event event;

    // (1) Handle Input
    // Start our event loop
    while (SDL_PollEvent(&event))
    {
      // Handle each specific event
      if (event.type == SDL_QUIT)
      {
        gameIsRunning = 0;
      }
    }
    // (2) Handle Updates

    // (3) Clear and Draw the Screen
    // Gives us a clear "canvas"
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, ourPNG, NULL, NULL);

    // Finally show what we've drawn
    SDL_RenderPresent(renderer);
  }

  // We destroy our window. We are passing in the pointer
  // that points to the memory allocated by the
  // 'SDL_CreateWindow' function. Remember, this is
  // a 'C-style' API, we don't have destructors.
  SDL_DestroyWindow(window);

  // Free our png image surface
  SDL_FreeSurface(image);
  // And destroy our texture
  SDL_DestroyTexture(ourPNG);

  IMG_Quit();

  // Quit our program.
  SDL_Quit();
  return 0;
}