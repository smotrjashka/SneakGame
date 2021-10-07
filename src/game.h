#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <string>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  Game(std::size_t grid_width, std::size_t grid_height, int level, int score, int life);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetLevel() const;
  int GetLifes() const;
  void SetScore(int score);
  void SetLevel(int level);
  void SetLifes(int lifes);
  std::string GetUserName() const;

 private:
  Snake snake;
  SDL_Point food;
  Obstacle obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int level{1};
  int score_for_next_level{5};
  int life{3};
  std::string user_name{"unauthorized"};

  void PlaceFood();
  void PlaceObstacle();
  void Update();
};

#endif