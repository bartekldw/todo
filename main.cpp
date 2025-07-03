#include <iostream>
#include <vector>
#include "src/todomanager.hpp"
#include "src/tasksaver.hpp"
#include "src/taskloader.hpp"
#include "src/taskdata.hpp"
#include "src/optionsmenu.hpp"
#include "lib/helper.hpp"

int main(){
    std::vector<TaskData> tasks;
    std::vector<std::string> categories;
    TaskLoader loader{"tasks.txt"};
    loader.export_tasks(tasks);
    loader.export_categories(tasks,categories);
    TodoManager manager_main("tasks.txt",tasks, categories);
    std::string colour;
    if(!manager_main.file_exists("options.txt")){
        manager_main.construct_options(colour);
    }
    else{
        OptionsMenu colour_setter{"options.txt"};
        colour_setter.load_options(colour);
    }
    manager_main.theme_colour = colour;
    bool end {false};
    do{
        manager_main.display_menu(end);
    } while(!end);
    return 0;
}
