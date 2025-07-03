#include "optionsmenu.hpp"
#include <iostream>
#include <fstream>
OptionsMenu::OptionsMenu(const std::string& file_name){
    this->options_file_name = file_name;
}
void OptionsMenu::save_options(const std::string& data){
    std::ofstream file_save(this->options_file_name, std::ios::out);
    if(file_save.is_open()){
        file_save << "theme_colour;" << data;
        file_save.close();
    }
}

void OptionsMenu::load_options(std::string& data){
    std::ifstream file_load(this->options_file_name, std::ios::in);
    if(file_load.is_open() && file_load.good()){
        std::string line, option_type, colour;
        std::getline(file_load, line);

        int index = 0;
        while(line[index] != ';'){
            option_type += line[index++];
        }
        if(option_type == "theme_colour"){
            index++;
            while(index < line.size()){
                colour += line[index++];
            }
            data = colour;
        }
        else{
            data = "white";
        }
    }
    else{
        data = "white";
    }
}
