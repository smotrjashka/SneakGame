#include "obstacle.h"

Obstacle::Obstacle(){}

Obstacle::Obstacle(int x, int y) {
    SDL_Point false_food_point( static_cast<int>(x), static_cast<int>(y));
    obstacle_points.push_back(false_food_point);
    obstacle_type = ObstacleType::FalseFood;
}

Obstacle::Obstacle(std::vector<SDL_Point>* ptrVector){
    *obstacle_points = ptrVector;
    int obstacle_size = obstacle_points.size();
    if (obstacle_size == 1){
        obstacle_type = ObstacleType::FalseFood;
    } else if (obstacle_size < 4){
        obstacle_type = ObstacleType::Barrier;
    } else if (obstacle_size == 4){
        obstacle_type = ObstacleType::Rock;
    } else {
        obstacle_size = ObstacleType::Wall;
    }
}

Obstacle::~Obstacle() {

}
