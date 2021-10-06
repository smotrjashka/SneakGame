#ifndef SDL2TEST_LOGIN_H
#define SDL2TEST_LOGIN_H

#include <string>
#include "SDL.h"

class Login{
public:
    Login(const std::size_t screen_width, const std::size_t screen_height, std::string& user);
    ~Login();

private:
    std::string user_name{"unauthorized"};
};

#endif //SDL2TEST_LOGIN_H