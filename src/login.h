#ifndef SDL2TEST_LOGIN_H
#define SDL2TEST_LOGIN_H

#include <string>

class Login{
public:
    Login(const std::size_t screen_width, const std::size_t screen_height, std::string& user_name);
    ~Login();

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    std::string user_name{"unauthorized"};

    const std::size_t screen_width;
    const std::size_t screen_height;
};



#endif //SDL2TEST_LOGIN_H