# CPPND: Capstone Sneake Game Implementation

This is my implementetion repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives us a chance to integrate what you've learned throughout this program. 

## Rules and name/game story

At the begining I made a mistake in the word "snake" and wrote "snaek". But after that I think "Hm, Why not?"
And remane that to the "sneak" wich means "to go somewhere secretly and quietly". This have something with animals hunt process.

At first, I added the levels feature. For starter vertion, I constract next levels model:

1. Each level will have maximum "snake" length - "scope" - 5 times n, where n is the level number
   1 level  -  5
   2 level  - 10
   3 level  - 15
   
2. Each new level will start from "0"+n scope

May be in future I will make more complex level idea

Than I changed the speed increasing. Sincerelly, its a hight speed for scope 15, for example. And I think little bit more and start to change speed only for new level. For me, its good idea))

After that I saw part of code where we place food, particulary the coordinat check! It potential bug. We place the food and only after that we grow the body. But check contains only body, not a new + 1 squear. Or if we imagine that in our model during food place we go ahead, than we need to avoid the next squaer for "automatice eating" food. Thats why I made a decision to expand the prohibiden area for new food.

And I added the lifes. The user will have 3 lifes. Each new level lifes will be "zeroed" to 3. Game is over when no lifes left. If we will restore the game, we restore lifes count too. Every colision take 1 life. May be in future it will be more complex concept of lifes.

## Concepts covered

Hear I explane which concepts I covered by my code changes and in which way.

* The project uses Object Oriented Programming techniques: the project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  
  I created class Obstacle for all obstacles and their functinality.
  
* The project reads data from a file and process the data, or the program writes data to a file.

  After stop the game, if lifes left, we will safe data to the file, and for next start IF user prefer to continue game, we will restor info like level, score and lifes.

* The project accepts user input and processes the input.
   
  In the begining of the game, we ask user to wrote the nikename. Now I use this for have data from previously described file. But maybe in future I will safe best resalt and     make some rating or something like.
  
  Normally, in real life for saving data I use (like everyone) DB, but for porpouse of this course I make choise to simplify the idea of data saving to match some concepts.
  
* The project code is clearly organized into functions.
  
  I added function save_data_to_file to main.cpp for prevent repetitive code. We use in case if found the data for this specifice user and if not found them we write new data     using this function.
  
* Overloaded functions allow the same function to operate on different parameters: One function is overloaded with different signatures for the same function name.

 HandleInput function ovwrload for non-value too. I use this for login age user name input.
 
* Class constructors utilize member initialization lists.

  User for Login class and som other OOP tecniques.

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


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
