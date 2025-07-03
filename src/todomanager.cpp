#include "todomanager.hpp"
#include "tasksaver.hpp"
#include "taskdata.hpp"
#include "src/optionsmenu.hpp"
#include "src/tasksaver.hpp"
#include "lib/colours.hpp"
#include "lib/helper.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>
TodoManager::TodoManager(const std::string& file_name, const std::vector<TaskData>& tasks, const std::vector<std::string>& categories){ //constructor to import the data as tasks text file name, tasks and categories vector and the main theme colour
    this->file_name = file_name;
    this->tasks = tasks;
    this->categories = categories;
}

bool TodoManager::file_exists(const std::string& file_name){
    std::fstream file(file_name);
    return file.good();
}
void TodoManager::construct_options(std::string& colour){
    int colour_id;
    WarningType warning = WarningType::None;
    do{
        helper::clear_console();
        helper::print_header("white", " managing options!", true);
        std::cout << "1. "; helper::print_header("white", " white", false);
        std::cout << "2. "; helper::print_header("red", " red", false);
        std::cout << "3. "; helper::print_header("green", " green", false);
        std::cout << "4. "; helper::print_header("yellow", " yellow", false);
        std::cout << "5. "; helper::print_header("blue", " blue", false);
        std::cout << "6. "; helper::print_header("purple", " purple", false);
        std::cout << "7. "; helper::print_header("cyan", " cyan", false);
        helper::display_error(warning, "colours");
        helper::input_msg("white", " Please enter the colour theme you want to use in your TODO program: ");
        std::getline(std::cin, colour);
        
        try{
            colour_id = std::stoi(colour);
            if(colour_id < 1 || colour_id > 7){
                warning = WarningType::WrongNumber;
                continue;
            }
            else{
                switch(colour_id){
                    case 1:
                        colour = "white";
                        break;
                    case 2:
                        colour = "red";
                        break;
                    case 3:
                        colour = "green";
                        break;
                    case 4:
                        colour = "yellow";
                        break;
                    case 5:
                        colour = "blue";
                        break;
                    case 6:
                        colour = "purple";
                        break;
                    case 7:
                        colour = "cyan";
                        break;
                }
                break;
            }
        } catch(...){
            if(color::isValidColor(colour)){
                break;
            }
            else if(colour.empty()){
                warning = WarningType::EmptyInput;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
    } while(true);
    OptionsMenu save_option{"options.txt"};
    save_option.save_options(colour);
}
void TodoManager::display_menu(bool& should_exit){ //function to display the main menu of TODO program
    WarningType warning = WarningType::None;
    int operation;
    bool expand_menu = this->tasks.size() > 0;
    do{
        helper::clear_console();
        helper::print_header(this->theme_colour, "currently ", this->tasks.size(), (this->tasks.size() == 1 ? " task" :" tasks"));
        color::print(theme_colour); std::cout << "1. " << color::reset << "Add task" << std::endl;
        if(expand_menu){
            color::print(theme_colour); std::cout << "2. " << color::reset << "Show tasks" << std::endl;
            color::print(theme_colour); std::cout << "3. " << color::reset << "Manage tasks" << std::endl;
            color::print(theme_colour); std::cout << "4. " << color::reset << "Exit" << std::endl;
        }
        else{
            color::print(theme_colour); std::cout << "2. " << color::reset << "Exit" << std::endl;
        }
        switch(warning){
            case WarningType::InvalidInput:
                std::cout << "[" << color::red << "!" << color::reset << "] Enter the valid data!\n";
                break;
            case WarningType::WrongNumber:
                std::cout << "[" << color::red << "!" << color::reset << "] Enter a number between 1 and " << (expand_menu ? "5" : "2") << "!\n";
                break;
        }
        helper::input_msg(this->theme_colour, " Select operation: ");
        
        std::cin >> operation;

        if(std::cin.fail()){ //check if the cin entered fail state
            helper::clean_cin(); //if so, perform cin clearing actions AND
            warning = WarningType::InvalidInput; //enter the warning state (1 = cin fail state)
            continue;
        }
        else if((operation < 1 || operation > 2 && !expand_menu) || (operation < 1 || operation > 5 && expand_menu)){ //check if user entered the wrong number
            warning = WarningType::WrongNumber; //if so, enter the warning state (2 = wrong number state)
            continue;
        }
        else{
            break;
        }
        } while(true);
        if(operation == 1){ //if the oper
            helper::clean_cin(); //if so, clean the cin buffer AND
            TodoManager::add_task(); //induce the add_task function
        }
        else if(operation == 2 && expand_menu){
            helper::clean_cin();
            TodoManager::show_tasks();
        }
        else if(operation == 2 && !expand_menu || operation == 4 && expand_menu){
            should_exit = true;
        }
        else if(operation == 3 && expand_menu){
            helper::clean_cin();
            TodoManager::show_tasks(true);
        }
  
}


void TodoManager::get_name(std::string& name, bool managing_task){ //function that manages the task name
    //first, get the name of the task from the user
    WarningType warning = WarningType::None;
    do{
        helper::clear_console();
        helper::print_header(theme_colour, "adding a task!",true);

        helper::display_error(warning, "name");

        helper::input_msg(this->theme_colour, " Enter the name of your task: ");
        std::getline(std::cin, name);
        if(name.empty()){ //check if the task name is empty
            warning = WarningType::EmptyInput; //if so, turn on the "empty input" warning
            continue;
        }
        else{ //if no, break the loop 
            break;
        }
    } while(true);

}
void TodoManager::get_category(std::string& category, const std::string& task_name,bool managing_task){//function that manages the task category
    WarningType warning = WarningType::None;
    do{
        helper::clear_console();

        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(task_name, theme_colour);}
        if(!this->categories.empty()){ //check if there are categories, if so:
            int count = 0;
            std::cout << "Avaiable categories: " << std::endl;
            for(const auto& element : this->categories){ //print all categories
                std::cout << ++count << ". " << element << std::endl;
            }

            helper::display_error(warning, "category");

            helper::input_msg(this->theme_colour, " Enter the category of your task or create your own by typing its name: ");
            //std::cout << "[" << color::yellow << "?" << color::reset << "] Enter the category of your task or create your own by typing its name: "; color::print(theme_colour);
            std::getline(std::cin, category);
            try{ //try changning the string to a int, to make the task belong to already exsisting category 
                int category_id = std::stoi(category);
                if(category_id < 1 || category_id > categories.size()){ //check, if the user entered a wrong number, if so
                    warning = WarningType::WrongNumber; //enter the second warning_state (wrong number)
                    continue;
                }
                else{ //if the user entered the right category id, make the task belong to it
                    category = categories[category_id-1];
                    break;
                }
            } catch(...){ //user didn't enter a number, so try viewing as a classic string
                if(category.empty()){ //check if the category name is empty, if so:
                    warning = WarningType::EmptyInput; //enter the first warning_state (empty string)
                    continue;
                }
                else{ //if the user entered the right string, create this category and make the task belong to it
                    categories.push_back(category);
                    std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] Successfully created category ";
                    color::print(theme_colour);
                    std::cout << category << color::reset << " and added it to the task! (closing in a few seconds)" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    break;
                }
            }
        }
        else{ //if there are no categories:
            helper::display_error(warning, "category");
            helper::input_msg(this->theme_colour, " Create a category for your task by typing its name: ");
            
            std::getline(std::cin, category); //try getting the new category name
            if(category.empty()){ //check if the new category name is empty, if so:
                warning = WarningType::EmptyInput; //enter the first warning state (empty string)
                continue;
            }
            else{ //if the user entered the right string, create this category and make the task belong to it
                categories.push_back(category);
                std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] Successfully created category ";
                color::print(theme_colour);
                std::cout << category << color::reset << " and added it to the task! (closing in a few seconds)" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }
        }
    } while(true);
}
void TodoManager::get_priority(int &priority, const std::string& task_category, const std::string& task_name, bool managing_task){
    WarningType warning = WarningType::None;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour);}
        std::cout << "1. " << color::green << " low" << color::reset << std::endl;
        std::cout << "2. " << color::blue << " medium" << color::reset << std::endl;
        std::cout << "3. " << color::red << " high" << color::reset << std::endl;

        helper::display_error(warning);
        helper::input_msg(this->theme_colour, " Enter the task priority: ");
        std::cin >> priority;

        if(std::cin.fail()){ //check if the user entered the wrong data, if so:
            helper::clean_cin(); //clear the cin buffer AND
            warning = WarningType::InvalidInput; //enter the first warning state
            continue;
        }
        else if(priority < 1 || priority > 3){ //check if the user entered the wrong number, if so:
            warning = WarningType::WrongNumber; //enter the second warning state
            continue;
        }
        else{ //if not:
            helper::clean_cin();
            break; //break the loop
        }
    } while(true);
}
void TodoManager::get_done_attribute(bool& is_done){
    do{
        std::string done;
        helper::clear_console();
        helper::print_header(theme_colour, "managing a task",true);
        std::cout << "[" << color::yellow << "?" << color::reset << "]" << " Is this task done? (Y/n) "; color::print(theme_colour);
        std::getline(std::cin, done);
        if(done.empty()){
            is_done = true;
            break;
        }
        else if(done == "Y" || done == "y"){
            is_done = true;
            break;
        }
        else if(done == "N" || done == "n"){
            is_done = false;
            break;
        }
        else{
            continue;
        }
    } while(true);
    
}
void TodoManager::get_date(int &year, int&month, int&day, int&hour, int&minute, int priority, const std::string& task_category, const std::string& task_name, bool managing_task){
    std::vector<int> time = helper::current_date();
    WarningType warning = WarningType::None;
    //1. year
    std::string year_string;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour, priority);}
        helper::display_error(warning, "year", time);
        helper::input_msg(this->theme_colour, " Enter the due year of task: (default = ",time[0],") ");
        //std::cout << "[" << color::yellow << "?" << color::reset << "] Enter the due year of task: (default = " << time[0] << ") "; color::print(theme_colour);
        std::getline(std::cin, year_string);
        try{
            year = std::stoi(year_string);
        } catch(...){
            if(year_string.empty()){
                year = time[0];
                warning = WarningType::None;
                break;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
        if(year < time[0]){
            warning = WarningType::WrongDateYear;
            continue;
        }
        else{
            warning = WarningType::None;
            break;
        }
    } while(true);
    //2. month
    std::string month_string;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour, priority);}
        std::cout << year << "-?" << std::endl;
        helper::display_error(warning, "month", time);
        helper::input_msg(this->theme_colour, " Enter the due month of task: (default = ",time[1],") ");
        //std::cout << "[" << color::yellow << "?" << color::reset << "] Enter the due month of task: (default = " << time[1] << ") "; color::print(theme_colour);
        std::getline(std::cin, month_string);
        try{
            month = std::stoi(month_string);
        } catch(...){
            if(month_string.empty()){
                month = time[1];
                warning = WarningType::None;
                break;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
        
        if(month < time[1] && year == time[0]){
            if(month < 1 || month > 12){
                warning = WarningType::InvalidDate;
                continue;
            }
            else{
                warning = WarningType::WrongDateMonth;
            }
            continue;
        }
        else if(month < 1 || month > 12){
            warning = WarningType::InvalidDate;
            continue;
        }
        else{
            warning = WarningType::None;
            break;
        }
    } while(true);

    //3. day
    std::string day_string;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour, priority);}
        std::cout << year << "-" << (month < 10 ? "0" : "") << month << "-?" << std::endl;
        helper::display_error(warning, "day", time);
        helper::input_msg(this->theme_colour, " Enter the due day of task: (default = ",time[2],") ");
        //std::cout << "[" << color::yellow << "?" << color::reset << "] Enter the due day of task: (default = " << time[2] << ") "; color::print(theme_colour);
        std::getline(std::cin, day_string);
        try{
            day = std::stoi(day_string);
        } catch(...){
            if(day_string.empty()){
                day = time[2];
                warning = WarningType::None;
                break;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
        if(day < time[2] && month == time[1] && year == time[0]){
            if(day < 1 || day > 31){
                warning = WarningType::InvalidDate;
            }
            else{
                warning = WarningType::WrongDateDay;
            }
            
            continue;
        }
        else if(!helper::valid_month(year, month, day)){
            if(day < 1 || day > 31){
                warning = WarningType::InvalidDate;
            }
            else{
                warning = WarningType::InvalidDayToMonth;
            }
            continue;
        }
        else if(day < 1 || day > 31){
            warning = WarningType::InvalidDate;
            continue;
        }
        else{
            warning = WarningType::None;
            break;
        }
    } while(true);
    
    //4. hour
    std::string hour_string;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour, priority);}
        std::cout << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << "-?" << std::endl;
        helper::display_error(warning, "hour", time);
        helper::input_msg(this->theme_colour, " Enter the due hour of task: (default = ",time[3],") ");
        //std::cout << "[" << color::yellow << "?" << color::reset << "] Enter the due hour of task: (default = " << time[3] << ") "; color::print(theme_colour);
        std::getline(std::cin, hour_string);
        try{
            hour = std::stoi(hour_string);
        } catch(...){
            if(hour_string.empty()){
                hour = time[3];
               warning = WarningType::None;
                break;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
        if(hour < time[3] && day == time[2] && month == time[1] && year == time[0]){
            if(hour < 1 || hour > 24){
                warning = WarningType::InvalidDate;
            }
            else{
                warning = WarningType::WrongDateHour;
            }
            
            continue;
        }
        else if(hour < 1 || hour > 24){
            warning = WarningType::InvalidDate;
            continue;
        }
        else{
            warning = WarningType::None;
            break;
        }
    } while(true);

    //5. minute
    std::string minute_string;
    do{
        helper::clear_console();
        managing_task ? helper::print_header(theme_colour, "managing a task!",true) : helper::print_header(theme_colour, "adding a task!",true);
        if(!managing_task){helper::print_task_info(categories, task_name, task_category, theme_colour, priority);}
        std::cout << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << "-?" << std::endl;
        helper::display_error(warning, "minute", time);
        helper::input_msg(this->theme_colour, " Enter the due minute of task: (default = 30) ");
        std::getline(std::cin, minute_string);
        try{
            minute = std::stoi(minute_string);
        } catch(...){
            if(minute_string.empty()){
                minute = 30;
                warning = WarningType::None;
                break;
            }
            else{
                warning = WarningType::InvalidInput;
                continue;
            }
        }
        if(minute < time[4] && hour == time[3] && day == time[2] && month == time[1] && year == time[0]){
            if(minute < 1 || minute > 60){
                warning = WarningType::InvalidDate;
            }
            else{
                warning = WarningType::WrongDateMinute;
            }
            
            continue;
        }
        
        else if(minute < 1 || minute > 60){
            warning = WarningType::InvalidDate;
            continue;
        }
        else{
            warning = WarningType::None;
            break;
        }
    } while(true);
}
void TodoManager::add_task(){ //function that adds tasks and import them to Tasks vector, adding them to tasks text file
    std::string task_name, task_category, confirmation;
    int priority, year, month, day, hour, minute;;
    do{
        //first, get the name of the task from the user
        get_name(task_name);
        //secondly, get the wanted category
        get_category(task_category, task_name);
        //next, we want to get the priority of the task (1 - low, 2 - medium, 3 - high)
        get_priority(priority, task_category, task_name);
        //now, let's set the due date for the task, it is divided into parts:
        get_date(year, month, day, hour, minute, priority, task_category, task_name);
        std::string confirmation;
        do{
            helper::clear_console();
            helper::print_header(theme_colour, "adding a task!",true);
            helper::print_task_info(true, categories, task_name, task_category, theme_colour, priority);
            color::print(theme_colour); std::cout << "Due date: " << color::reset; 
            std::cout << color::reset << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << " (" << hour << ":" << minute << ")" << std::endl;
            std::cout << "[" << color::yellow << "?" << color::reset << "] Is this task info right? (Y/n) "; color::print(theme_colour);
            std::getline(std::cin, confirmation);
            if(confirmation.empty() || confirmation == "Y" || confirmation == "y"){
                break;
            }
            else{
            if(confirmation == "N" || confirmation == "n"){
                helper::print_header(theme_colour, "adding a task!",true);
                std::cout << "[" << color::red << "!" << color::reset << "] You would need to create the task once again. Click ENTER to continue... ";
                std::cin.get();
                continue;
            }
            else{
                continue;
            }
            }
    }while(true);
    break;
    }while(true);
    
    //after the user confirmed the task correctness, add the task info into an object
    Date task_date{year,month,day,hour,minute};
    TaskData cur_task{tasks.size(), task_name, task_category, priority, false, task_date};
    this->tasks.push_back(cur_task);
    TaskSaver saver(this->file_name);
    saver.save(cur_task, this->tasks);
}


void TodoManager::sort_tasks_id(std::vector<TaskData>& tasks){
    std::sort(tasks.begin(), tasks.end(), helper::compare_by_object_id);
}
void TodoManager::sort_tasks_priority(std::vector<TaskData>& tasks){
    std::sort(tasks.begin(), tasks.end(), helper::compare_by_object_priority);
}
void TodoManager::sort_tasks_date(std::vector<TaskData>& tasks){
    std::sort(tasks.begin(), tasks.end(), helper::compare_by_object_due_date);
}
void TodoManager::show_tasks(bool manage_tasks_mode){
    enum class WhichSort{
        id,
        priority,
        date
    };
    WhichSort sort_by = WhichSort::id;
    WarningType warning = WarningType::None;
    std::string output;
    do{
        helper::clear_console();
        if(manage_tasks_mode){
            color::print(theme_colour); std::cout << "---[TODO]---" << color::white << " managing tasks! " << std::endl;
        }
        else{
            color::print(theme_colour); std::cout << "---[TODO]---" << color::white << " showing all tasks! " << std::endl;
        }
        std::cout << color::reset << "Type 'exit' to exit..." << std::endl;
        std::cout << color::reset << "Click ENTER to change sorting type..." << std::endl;
        switch(sort_by){
            case WhichSort::id:
                sort_tasks_id(tasks);
                break;
            case WhichSort::priority:
                sort_tasks_priority(tasks);
                break;
            case WhichSort::date:
                sort_tasks_date(tasks);
                break;
        }
        int count = helper::show_tasks_basic_mode(this->theme_colour, this->tasks);
        if(manage_tasks_mode){
            helper::display_error(warning);
            color::print(theme_colour); std::cout << "----------- -[" << (sort_by == WhichSort::id ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- ";
            color::print(theme_colour); std::cout << "- -[" << (sort_by == WhichSort::priority ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- ";
            color::print(theme_colour); std::cout << "- - -[" << (sort_by == WhichSort::date ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- " <<std::endl;
            color::print(theme_colour); std::cout << "Sorting by: ";
            std::cout << color::reset << (sort_by == WhichSort::id ? color::yellow : color::white) << " id" << (sort_by == WhichSort::priority ? color::yellow : color::white) << "    priority" << (sort_by == WhichSort::date ? color::yellow : color::white) << "   date" << std::endl;
            helper::input_msg(this->theme_colour, " Enter the ID of the task you want to manage: ");
        }
        else{
            color::print(theme_colour); std::cout << "Sorting by: ";
            if(!manage_tasks_mode){
                std::cout << color::reset << (sort_by == WhichSort::id ? color::yellow : color::white) << " id" << (sort_by == WhichSort::priority ? color::yellow : color::white) << "    priority" << (sort_by == WhichSort::date ? color::yellow : color::white) << "   date" << std::endl;
                color::print(theme_colour); std::cout << "----------- -[" << (sort_by == WhichSort::id ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- ";
                color::print(theme_colour); std::cout << "- -[" << (sort_by == WhichSort::priority ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- ";
                color::print(theme_colour); std::cout << "- - -[" << (sort_by == WhichSort::date ? color::yellow : color::white) << "*"; color::print(theme_colour); std::cout << "]- ";
            }
        }
        
        std::getline(std::cin, output);
        if(output.empty()){
            switch(sort_by){
                case WhichSort::id:
                    sort_by = WhichSort::priority;
                    break;
                case WhichSort::priority:
                    sort_by = WhichSort::date;
                    break;
                case WhichSort::date:
                    sort_by = WhichSort::id;
                    break;
                default:
                    sort_by = WhichSort::id;
                    break;
            }
        }
        else{
            if(manage_tasks_mode){
                int task_id;
                try{
                    task_id = std::stoi(output);
                    if(task_id < 1 || task_id > count){
                        warning = WarningType::WrongNumber;
                        continue;
                    }
                    else{
                        manage_tasks(tasks[task_id-1], task_id);
                        break;
                    }
                } catch(...){
                    warning = WarningType::InvalidInput;
                    continue;
                }
            }
            else{
               break; 
            }
            
        }
    } while(true);
}

void TodoManager::manage_tasks(TaskData task_to_manage, int id){
    int num;
    WarningType warning = WarningType::None;
    do{
        helper::clear_console();
        helper::print_header(this->theme_colour, " managing task \"",task_to_manage.title, "\"");
        std::cout << "1. Name (" << task_to_manage.title << ")" << std::endl;
        std::cout << "2. Category (" << task_to_manage.category << ")" << std::endl;
        std::cout << "3. Priority (";
        switch(task_to_manage.priority){
            case 1:
                std::cout << "low";
                break;
            case 2:
                std::cout << "medium";
                break;
            case 3:
                std::cout << "high";
                break;
        }
        std::cout << ")" << std::endl;;
        std::cout << "4. Is done (" << (task_to_manage.isDone ? "yes" : "no") << ")" << std::endl;
        std::cout << "5. Due date: " << task_to_manage.dueDate.year << "-" << (task_to_manage.dueDate.month < 10 ? "0" : "") << task_to_manage.dueDate.month << "-" << (task_to_manage.dueDate.day < 10 ? "0" : "") << task_to_manage.dueDate.day << " (" << task_to_manage.dueDate.hour << ":" << task_to_manage.dueDate.minute << ")" << std::endl;
        helper::display_error(warning);
        helper::input_msg(this->theme_colour, " Select the attribute you want to change: ");
        std::cin >> num;
        if(std::cin.fail()){
            helper::clean_cin();
            warning = WarningType::InvalidInput;
            continue;
        }
        else if(num < 1 || num > 5){
            helper::clean_cin();
            warning = WarningType::WrongNumber;
            continue;
        }
        else{
            helper::clean_cin();
            break;
        }
    } while(true);

    switch(num){
        case 1: {
            std::string new_name;
            get_name(new_name, true);
            task_to_manage.title = new_name;
            break;
        }
        case 2: {
            std::string new_category;
            get_category(new_category, task_to_manage.title, true);
            task_to_manage.category = new_category;
            break;
        }
        case 3: {
            int new_priority;
            get_priority(new_priority, task_to_manage.category, task_to_manage.title, true);
            task_to_manage.priority = new_priority;
            break;
        }
        case 4: {
            bool is_done;
            get_done_attribute(is_done);
            task_to_manage.isDone = is_done;
            break;
        }
        case 5: {
            int year, month, day, hour, minute;
            get_date(year, month, day, hour, minute, task_to_manage.priority, task_to_manage.category, task_to_manage.title, true);
            Date new_date{year, month, day, hour, minute};
            task_to_manage.dueDate = new_date;
            break;
        }
    }
    this->tasks[id] = task_to_manage;
    TaskSaver saver{"tasks.txt"};
    saver.save_bulk(this->tasks);
}
