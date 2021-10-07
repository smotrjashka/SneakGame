#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

Game::Game(std::size_t grid_width, std::size_t grid_height, int level, int score, int life)
    : snake(grid_width, grid_height, score, level),
        engine(dev()),
        random_w(0, static_cast<int>(grid_width - 1)),
        random_h(0, static_cast<int>(grid_height - 1))
        {
          SetLevel(level);
          SetScore(score);
          SetLifes(life);
    PlaceFood();
}


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  std::cout << "starter value for run " << level << " sc " << score << "li " << life << std::endl;
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  //proper title for first second of the game
  renderer.UpdateWindowTitle(score, 0, level, life);
  while (running) {
    frame_start = SDL_GetTicks();
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    std::cout << "update" << std::endl;
    Update();
    std::cout << "render" << std::endl;
    renderer.Render(snake, food, obstacle);
    std::cout << "after" << std::endl;

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, level, life);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceObstacle() {
    int x, y;
    while (true){
        x = random_w(engine);
        y = random_h(engine);

        if (!snake.SnakeCell(x, y) && food.x != x && food.y != y) {
            SDL_Point false_food_point{static_cast<int>(x), static_cast<int>(y)};
            obstacle.obstacle_points.push_back(false_food_point);
            return;
        }

    }

}

void Game::RemovePrevObstacle(){
  obstacle.obstacle_points.clear();
}

void Game::Update() {
  std::cout << "updtae start" << std::endl;
  if (!snake.alive) return;
  std::cout << "snake alive" << std::endl;

  snake.Update();
std::cout << "snake updated" << std::endl;
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
std::cout << "check if food" << std::endl;
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    //I added second condition check just in case that some other changes in future will drastically
    //impact on score number and for avoid future bugs. And, in general, I prefer that programming model when we
    // didnt trust code from another class
      if ((score % (5*level) == 0) && (score != 0)){
          score = score/5;
          std::cout << "new score after update " << score << std::endl;
          level++;
          snake.speed += 0.02;
          life = 3;
          PlaceFood();
          PlaceObstacle();
          // size of snake = score + head
          snake.EraseBody(score + 1);
      } else {
          PlaceFood();
          PlaceObstacle();
          // Grow snake and increase speed.
          snake.GrowBody();
      }
  } else {
    std::cout << "else" << std::endl;
      //checking for obstacle if it is not food
      //TODO vector check
      ///for now I only have a false food generator
      std::cout << obstacle.obstacle_points.size() << std::endl;
      if (obstacle.obstacle_points.size()>0
       && obstacle.obstacle_points[0].x == new_x && obstacle.obstacle_points[0].y == new_y){
          level--;
          /// its lifes == 0, but just in case
          if (life < 1){
              snake.alive = false;
              life = 3;
              score = 0;
              level = 1;
          }
      }
      std::cout << "else finished" << std::endl;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
// I added level and life concepts, and user pls read the README for more info
int Game::GetLevel() const {return level;}
int Game::GetLifes() const {return life;}
std::string Game::GetUserName() const {return user_name;}
void Game::SetScore(int score){
    if (score > 0)
    {
      this->score = score;
    }
  }

  void Game::SetLevel(int level){
    if (level > 0)
    {
      this->level = level;
    }
    
  }
  void Game::SetLifes(int lifes){
    if (lifes > 0 && lifes <= 3)
    {
    life = lifes;
    }
    
  }