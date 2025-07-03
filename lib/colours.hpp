#ifndef COLOR_H
#define COLOR_H
#include <iostream>
namespace color{
    inline constexpr const char* const red = "\033[1;31m";
    inline constexpr const char* const green = "\033[1;32m";
    inline constexpr const char* const yellow = "\033[1;33m";
    inline constexpr const char* const blue = "\033[1;34m";
    inline constexpr const char* const purple = "\033[1;35m";
    inline constexpr const char* const cyan = "\033[1;36m";
    inline constexpr const char* const white = "\033[1;37m";
    inline constexpr const char* const reset = "\033[0m";
    inline void print(const std::string& colour){
        if(colour == "red"){
            std::cout << red;
        }
        else if(colour == "green"){
            std::cout << green;
        }
        else if(colour == "yellow"){
            std::cout << yellow;
        }
        else if(colour == "blue"){
            std::cout << blue;
        }
        else if(colour == "purple"){
            std::cout << purple;
        }
        else if(colour == "cyan"){
            std::cout << cyan;
        }
        else if(colour == "white"){
            std::cout << white;
        }
    }

    inline bool isValidColor(const std::string& color) {
        return color == "red" ||
               color == "green" ||
               color == "yellow" ||
               color == "blue" ||
               color == "purple" ||
               color == "cyan" ||
               color == "white";
    }
}
#endif
