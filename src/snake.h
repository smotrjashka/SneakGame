#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height);

  Snake(int grid_width, int grid_height, int score, int level);

  void Update();

  void GrowBody();
  void EraseBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.04f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  bool erase_body{false};
  int grid_width;
  int grid_height;
};

#endif