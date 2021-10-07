#ifndef SDL2TEST_LOGIN_H
#define SDL2TEST_LOGIN_H

#include <string>

class Login{
public:
    Login(std::string &user);
    ~Login();

private:
    std::string user_name{"unauthorized"};
};

#endif //SDL2TEST_LOGIN_H