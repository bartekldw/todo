#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <iostream>
class OptionsMenu{
private:
    std::string options_file_name;
public:
    OptionsMenu(const std::string& file_name);
    void save_options(const std::string& data);
    void load_options(std::string& data);
};
#endif
