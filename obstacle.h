#ifndef SDL2TEST_OBSTACLE_H
#define SDL2TEST_OBSTACLE_H

#include "SDL.h"

class Obstacle {

public:
    //enum of obstacle types consisted 4 types
    //Barrier will be a short line from 2 to 5 "points"
    //FalseFood will be just like food only red colored
    //Wall will be a long line from 6 to 15 "points"
    //Rock will have a foursquare form and will have the width and height
    //of 2. May be in future I will make random or level-based parameters for rock
    enum class ObstacleType{Barrier, FalseFood, Rock, Wall};
    //for start all obstacles will be rendered red color but may be in future I will make a random color

    Obstacle();


};



#endif //SDL2TEST_OBSTACLE_H
