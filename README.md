# Sneak Game

This is my implementetion repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for initial [repo](https://github.com/udacity/CppND-Capstone-Snake-Game) was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

All rights reserved

<img src="sneak1.jpg" style="max-width:30%;"/>

## Rules and name/game story

At the beginning I made a mistake in the word "snake" and wrote "sneak". But after that I think "Hm, Why not?"
And remane that to the "sneak" which means "to go somewhere secretly and quietly". This has something with animals hunt process.

At first, I added the levels feature. For starter version, I constract next levels model:

1. Each level will have maximum "snake" length - "scope" - 5 times n, where n is the level number
   1 level  -  5
   2 level  - 10
   3 level  - 15
   
2. Each new level will start from "0"+n scope

May be in future I will make more complex level idea

Then I changed the speed increasing. Sincerely, it's a high speed for scope 15, for example. And I think a little bit more and start to change speed only for the new level. For me, it's a good idea))

After that I saw part of the code where we place food, particularly the coordinate check! I't potential bug. We place the food and only after that we grow the body. But check contains only body, not a new + 1 square. Or if we imagine that in our model during food place we go ahead, than we need to avoid the next squaer for "automatic eating" food. That's why I made a decision to expand the prohibiden area for new food.

And I added the lifes. The user will have 3 lives. Each new level lifes will be "zeroed" to 3. Game is over when no lives left. If we will restore the game, we restore lives count too. Every colision take 1 life. May be in future it will be a more complex concept of lifes.
Pay attention, that every collision with obstacle take 1 life, but in snake "eat" herself, she died immediatly!!)) 

## Concepts covered

Here I explain which concepts I covered by my code changes and in which way.

* The project uses Object Oriented Programming techniques: the project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  
  I created class Obstacle for all obstacles and their functionality.
  
* The project reads data from a file and process the data, or the program writes data to a file.

  After stopping the game, if lifes left, we will save data to the file, and for next start IF user prefer to continue the game, we will restore info like level, score and lifes.

* The project accepts user input and processes the input.
   
  At the beginning of the game, we ask the user to write the nickname. Now I use this for have data from previously described file. But maybe in future I will safe best results and     make some rating or something like.
  
  Normally, in real life saving data I use (like everyone) DB, but for purposes of this course I make choosing to simplify the idea of data saving to match some concepts.
  
* The project code is clearly organized into functions.
  
  I added function save_data_to_file to main.cpp for preventing repetitive code. We use in case if found the data for this specific user and if not found them, we write new data using this function. And also another function in game class etc.
  
* Overloaded functions allow the same function to operate on different parameters: One function is overloaded with different signatures for the same function name.

  I created some overloaded function for different parameters, you can find them)
 
* Class constructors utilize member initialization lists.

  User when its possible, in most cases I need to make some check regardless data from file, for example.
  
* Classes use appropriate access specifiers for class members.

  Some added by me variables are prived and had getters and setters and some I made public.
  
* Classes encapsulate behavior.

  Snake, Obstacle, Game have this.
  
* The project makes use of references in function declarations.

  I'm not sure about at list two, but 1 I have for certain... But probably two... Lets see)
  

I think, that's enaught)) 
Or, may be not ...))))

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.
