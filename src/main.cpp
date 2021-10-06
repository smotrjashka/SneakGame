#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "login.h"
#include <fstream>

std::string save_data_to_file(Game game, std::fstream data_to_write){
    /// places between words needed for simple read procedure
    data_to_write << "User: " << game.GetUserName() << " " << "Level: " << game.GetLevel() << " ";
    data_to_write << "Score: " << game.GetScore() << " " << "Size: " << game.GetSize() << " ";
    data_to_write << "Lifes: " << game.GetLifes() << "\n";
}

int main() {
  constexpr std::size_t kFramesPerSecond{30};   //I change started speed to lower
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
    const std::string MAIN_FILE = "Sessions.txt";
    const std::string TEMP_FILE = "temp.txt";
    std::string user_name = "";
    Login login(kScreenWidth, kScreenHeight, &user_name);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  mtx.unlock();
  //saving data for file
  std::fstream data_to_write;
  data_to_write.open(MAIN_FILE, std::ios::out | std::ios::in);
    if (!data_to_write.is_open()){
        std::count << "problems with write result to file " << std::endl;
    } else {
        std::string line;
        std::fstream temp_file;
        temp_file.open(TEMP_FILE, std::ios::out | std::ios::in);
     //   std::string user_name = game.GetUserName();
        int user_name_length = 6 + user_name.length();
        bool isPresent = false;
        while (std::getline(data_to_write, line)){
            std::cout << "substr: " << line.substr(0, user_name_length) << std::endl;
            if (line.substr(0, user_name_length) == "User: "+user_name){
                save_data_to_file(game, temp_file);
                isPresent = true;
            } else {
                temp_file << line << "\n";
            }
        }
        if (!isPresent){
            save_data_to_file(game, temp_file);
        }

        data_to_write.close();
        temp_file.close();
        remove(MAIN_FILE);
        rename(TEMP_FILE, MAIN_FILE);

    }

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Level: " << game.GetLevel() << "\n"
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Lifes: " << game.GetLifes() << std::endl;
  return 0;
}