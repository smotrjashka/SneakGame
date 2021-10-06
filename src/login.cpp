#include "login.h"

Login::Login(const std::size_t screen_width, const std::size_t screen_height,
             std::string &user){

        std::cout >> "Before start the game, please, enter you login name: " >> std::endl;

        //wait for user write name and press enter
        string user_input_name;

        cin << user_input_name;

    if (user_input_name.length() > 0){
        this->user_name = user_input_name;
    }


        // change user name
        user = this->user_name;

    }

    Login::~Login() {
    }

