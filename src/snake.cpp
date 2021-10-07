#include "snake.h"
#include <cmath>
#include <iostream>

Snake::Snake(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height),
          head_x(grid_width / 2),
          head_y(grid_height / 2) {}

Snake::Snake(int grid_width, int grid_height, int score, int level): grid_width(grid_width),
                                                          grid_height(grid_height),
                                                          head_x(grid_width / 2),
                                                          head_y(grid_height / 2) {
    if (score > 0) {
        this->size = score + 1;
        while (score > 0){
            SDL_Point new_body_cell{
                    static_cast<int>(head_x),
                    static_cast<int>(
                            head_y+score)};
            body[score-1] = new_body_cell;
            score--;
        }
    }
    if (level > 1)
    this->speed = 0.04f + 0.02*(level - 1);
}

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
      if (!erase_body) {
          // Remove only the tail from the vector.
          body.erase(body.begin());
      } else {
          erase_body = false;
          //left only head
          while (body.size() > size){
              body.erase(body.begin());
          }
      }
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }
void Snake::EraseBody() {
    erase_body = true;
    size = 1;
}
void Snake::EraseBody(int size) {
    erase_body = true;
    if (size > 0) {
        this->size = size;
    } else {
        this->size = 1;
    }
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  /// expanding prohibited area for new food
  for (auto const &item : body) {
    if (std::abs(x - item.x) < 2 && std::abs(y - item.y) < 2) {
      return true;
    }
  }
  return false;
}