#include "game.h"
#include <iostream>
#include "SDL.h"
#include <algorithm>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height), grid_w(static_cast<int>(grid_width)), grid_h(static_cast<int>(grid_height)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

Game::Game(std::size_t grid_width, std::size_t grid_height, int level, int score, int life)
    : snake(grid_width, grid_height, score, level),
        engine(dev()), grid_w(static_cast<int>(grid_width)), grid_h(static_cast<int>(grid_height)),
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
    Update();
    renderer.Render(snake, food, obstacle);

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
            if (level > 1){
                if (level != 4){
                    int finish = std::max((level-1)%grid_w, 2);
                    for (int i = 0; i < level-1; ++i) {
                        if (x++ < grid_w){
                            if (!snake.SnakeCell(x, y) && food.x != x && food.y != y) {
                                SDL_Point o_point{static_cast<int>(x), static_cast<int>(y)};
                                obstacle.obstacle_points.push_back(o_point);
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    ///we will try make Rock obstacle, and for this we need to check rest of 3 poinst before post them
                    if (x+1<grid_w && y+1 < grid_h && !snake.SnakeCell(x+1, y) && !snake.SnakeCell(x+1, y+1) && !snake.SnakeCell(x, y+1)
                    && food.x != x && food.x != x+1 && food.y != y+1 && food.y != y){
                        SDL_Point rock_point_x1_y1{static_cast<int>(x+1), static_cast<int>(y+1)};
                        obstacle.obstacle_points.push_back(rock_point_x1_y1);
                        SDL_Point rock_point_x1{static_cast<int>(x+1), static_cast<int>(y)};
                        obstacle.obstacle_points.push_back(rock_point_x1);
                        SDL_Point rock_point_y1{static_cast<int>(x), static_cast<int>(y+1)};
                        obstacle.obstacle_points.push_back(rock_point_y1);
                    }
                }
            }
            obstacle.obstacle_type = DefineObstacleType(obstacle.obstacle_points.size());
            return;
        }

    }

}

Obstacle::ObstacleType Game::DefineObstacleType(int vector_size){
    if (vector_size == 1){
        return Obstacle::ObstacleType::FalseFood;
    } else if (vector_size < 4) {
        return Obstacle::ObstacleType::Barrier;
    } else if (vector_size == 4) {
        return Obstacle::ObstacleType::Rock;
    } else {
        return Obstacle::ObstacleType::Wall;
    }
}

void Game::RemovePrevObstacle(){
  obstacle.obstacle_points.clear();
}

void Game::Update() {
  if (!snake.alive){
     if (life>0)
     {
       life = 0;
     }
     
     return;
     }

  snake.Update();
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    RemovePrevObstacle();
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
      //checking for obstacle if it is not food
      std::cout << obstacle.obstacle_points.size() << std::endl;
      if (obstacle.obstacle_points.size()>0){
          for (int i = 0; i < obstacle.obstacle_points.size(); ++i) {
              if (obstacle.obstacle_points[i].x == new_x && obstacle.obstacle_points[i].y == new_y){
                  RemovePrevObstacle();
                  life--;
                  /// its lifes == 0, but just in case
                  if (life < 1){
                      snake.alive = false;
                      life = 3;
                      score = 0;
                      level = 1;
                  }
                  PlaceObstacle();
                  break;
              }
          }
      }
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