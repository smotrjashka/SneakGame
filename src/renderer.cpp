#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, Obstacle const obstacle) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  //Render Obstacle

    std::cout << "render obstacle" << std::endl;
    std::vector<int> rgb = ColorChoose(obstacle.obstacle_type);

    SDL_SetRenderDrawColor(sdl_renderer, rgb[0], rgb[1], rgb[2], 255);
    for (SDL_Point const &point : obstacle.obstacle_points) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    std::cout << "after render obstacle" << std::endl;

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

std::vector<int> Renderer::ColorChoose(Obstacle::ObstacleType obstacle_type){
    std::cout << "start color choose" << std::endl;
    std::vector<int> rgb;
    switch (obstacle_type) {
        case Obstacle::ObstacleType::FalseFood:
            rgb.push_back(229);
            rgb.push_back(20);
            rgb.push_back(0);
            break;
        case Obstacle::ObstacleType::Barrier:
            rgb.push_back(162);
            rgb.push_back(0);
            rgb.push_back(37);
            break;
        case Obstacle::ObstacleType::Rock:
            rgb.push_back(226);
            rgb.push_back(0);
            rgb.push_back(115);
            break;
        case Obstacle::ObstacleType::Wall:
        default:                //just in case for future
            rgb.push_back(250);
            rgb.push_back(104);
            rgb.push_back(0);
    }

    std::cout << "finish color choose" << std::endl;
    return rgb;
}

void Renderer::UpdateWindowTitle(int score, int fps, int level, int life) {
    std::string lifes = " ";
    for (int i = 0; i < life; ++i) {
        lifes += "\u2665";  //its hart symbol
    }
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Level: " + std::to_string(level) + " Life: " + lifes};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
