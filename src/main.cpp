#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "login.h"
#include <fstream>
#include <sstream>
#include <stdio.h>

std::string save_data_to_file(Game *gamePtr, std::string user, std::ofstream& data_to_write){
    /// places between words needed for simplify read procedure
    data_to_write << "User: " << user << " " << "Level: " << gamePtr->GetLevel() << " ";
    data_to_write << "Score: " << gamePtr->GetScore() << " " << "Size: " << gamePtr->GetSize() << " ";
    data_to_write << "Lifes: " << gamePtr->GetLifes() << "\n";
}

int main() {
  constexpr std::size_t kFramesPerSecond{45};   //I change started speed to lower
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

    const std::string MAIN_FILE = "../Session.txt";
    const std::string TEMP_FILE = "../temp.txt";

    std::string user_name = "";

    Login login(user_name);


    std::string word, levelStr, scoreStr, sizeStr, lifeStr;
    bool isRestored = false;
    int user_name_length = 6 + user_name.length();
    if (user_name != "" || user_name != "unauthorized"){
        std::cout << "normal name" << std::endl;

        std::ifstream read_file_stream;
        read_file_stream.open(MAIN_FILE);
        if (read_file_stream.is_open()){
            std::cout << "file for search starter value is open" << std::endl;
            std::string li;
            while (std::getline(read_file_stream, li)){
                std::cout << "substr: " << li.substr(0, user_name_length) << std::endl;
                if (li.substr(0, user_name_length) == "User: "+user_name)
                {
                    isRestored = true;
                    std::istringstream lstream(li);
                    lstream >> word >> word >> word >> levelStr >> word >> scoreStr >> word >> sizeStr >> word >> lifeStr;
                }

            }
            read_file_stream.close();
        } else
        {
            std::cout << "problem with open start files" << std::endl;
        }
        

    }

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

        int levelInt, scoreInt, lifeInt;
    if (isRestored){
        std::cout << "is restored" << std::endl;
        levelInt = std::stoi(levelStr);
        std::cout << "level int " << levelInt<< std::endl;
        scoreInt = std::stoi(scoreStr);
        std::cout << "score " << scoreStr << std::endl;
        lifeInt = std::stoi(lifeStr);
        std::cout << "life " << lifeInt<< std::endl;
     } 
       Game game(kGridWidth, kGridHeight, levelInt, scoreInt, lifeInt);
   
  game.Run(controller, renderer, kMsPerFrame);
  //saving data for file
  if(game.GetLifes() >= 1){
  std::fstream data_to_write;
  data_to_write.open(MAIN_FILE, std::ios::out | std::ios::in);
    if (!data_to_write.is_open()){
        std::cout << "problems with write result to file " << std::endl;
    } else {
        std::string line;
        std::ofstream temp_file(TEMP_FILE.c_str());
     //   std::string user_name = game.GetUserName();
        bool isPresent = false;
        Game* ptrGame = &game;
        while (std::getline(data_to_write, line)){
            std::cout << "substr: " << line.substr(0, user_name_length) << std::endl;
            if (line.substr(0, user_name_length) == "User: "+user_name){
                save_data_to_file(ptrGame, user_name, temp_file);
                isPresent = true;
            } else {
                temp_file << line << "\n";
            }
        }
        if (!isPresent){
            save_data_to_file(ptrGame, user_name, temp_file);
        }

        data_to_write.close();
        temp_file.close();
        remove(MAIN_FILE.c_str());
        rename(TEMP_FILE.c_str(), MAIN_FILE.c_str());

    }

  }
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Level: " << game.GetLevel() << "\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Lifes: " << game.GetLifes() << std::endl;
  return 0;
}