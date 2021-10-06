#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <fstream>

int main() {
  constexpr std::size_t kFramesPerSecond{30};   //I change started speed to lower
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  //saving data for file
  std::ofstream data_to_write;
  data_to_write.open("Sessions.txt");
    if (!data_to_write){
        std::count << "problems with write result to file " << std::endl;
    } else {
        data_to_write << "User:" << game.GetUserName() << "\n";
        data_to_write << "Level: " << game.GetLevel() << "\n"
        data_to_write << "Score: " << game.GetScore() << "\n";
        data_to_write << "Size: " << game.GetSize() << "\n";
        data_to_write << "Lifes: " << game.GetLifes() << "\n\n";
        data_to_write.close();
    }

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Level: " << game.GetLevel() << "\n"
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Lifes: " << game.GetLifes() << std::endl;
  return 0;
}