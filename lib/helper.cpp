#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <cstdlib>
#include <limits> 
#include <ctime>
#include <vector>
#include "helper.hpp"
#include "colours.hpp"
#include "src/taskdata.hpp"
#include "src/todomanager.hpp"
namespace helper{
    void clear_console(){
        #ifdef _WIN32
            system("cls");
        #else 
            system("clear");
        #endif
    }
    void clean_cin(){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void print_task_info(std::string name, std::string theme_colour){
        std::cout << "Task: "; color::print(theme_colour); std::cout << name << color::reset << std::endl;
    }
    void print_task_info(std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour){
        std::cout << "Task: "; color::print(theme_colour); std::cout << name << color::reset << " (category: ";
        try{
            int category_id = std::stoi(category);
            std::cout << categories[category_id-1];
        } catch(...){
            std::cout << category;
        }
        std::cout << ")" << std::endl;
    }
    void print_task_info(std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour, int priority){
        std::cout << "Task: "; color::print(theme_colour); std::cout << name << color::reset << " (category: ";
        try{
            int category_id = std::stoi(category);
            std::cout << categories[category_id-1];
        } catch(...){
            std::cout << category;
        }
        std::cout << ", priority: ";
        switch(priority){
            case 1:
                std::cout << "low";
                break;
            case 2:
                std::cout << "medium";
                break;
            case 3:
                std::cout << "high";
                break;
            default:
                break;
        }
        std::cout << ")\n";
    }
    void print_task_info(bool should_use_diffrent_colour_scheme, std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour, int priority){
        if(should_use_diffrent_colour_scheme){
            color::print(theme_colour); std::cout << "Task: " << color::reset;
            std::cout << name << " (category: ";
        }
        else{
            std::cout << "Task: "; color::print(theme_colour); std::cout << name << color::reset << " (category: ";
        }
        try{
            int category_id = std::stoi(category);
            std::cout << categories[category_id-1];
        } catch(...){
            std::cout << category;
        }
        std::cout << ", priority: ";
        switch(priority){
            case 1:
                std::cout << "low";
                break;
            case 2:
                std::cout << "medium";
                break;
            case 3:
                std::cout << "high";
                break;
            default:
                break;
        }
        std::cout << ")\n";
    }

    std::vector<int> current_date(){
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);

        int year = now->tm_year + 1900;
        int month = now->tm_mon + 1;
        int day = now->tm_mday;
        int hour = now->tm_hour;
        int minute = now->tm_min;

        return {year, month, day, hour, minute};
    }
    bool valid_month(int year, int month, int days){
        bool leap_year = (year % 4 == 0 && year % 100 != 0)||(year%400==0);
        if(month == 1 && days <= 31){
            return true;
        }
        else if(month == 2 && ((leap_year && days <= 29) || (!leap_year && days <= 28))){
            return true;
        }
        else if(month == 3 && days <= 31){
            return true;
        }
        else if(month == 4 && days <= 30){
            return true;
        }
        else if(month == 5 && days <= 31){
            return true;
        }
        else if(month == 6 && days <= 30){
            return true;
        }
        else if(month == 7 && days <= 31){
            return true;
        }
        else if(month == 8 && days <= 31){
            return true;
        }
        else if(month == 9 && days <= 30){
            return true;
        }
        else if(month == 10 && days <= 31){
            return true;
        }
        else if(month == 11 && days <= 30){
            return true;
        }
        else if(month == 12 && days <= 31){
            return true;
        }
        return false;
    }

    bool compare_by_object_id(const TaskData& a, const TaskData& b){
        return a.id > b.id;
    }
    bool compare_by_object_priority(const TaskData& a, const TaskData& b){
        return a.priority > b.priority;
    }
    bool compare_by_object_due_date(const TaskData& a, const TaskData& b){
        if (a.dueDate.year != b.dueDate.year) return a.dueDate.year < b.dueDate.year;
        if (a.dueDate.month != b.dueDate.month) return a.dueDate.month < b.dueDate.month;
        if (a.dueDate.day != b.dueDate.day) return a.dueDate.day < b.dueDate.day;
        if (a.dueDate.hour != b.dueDate.hour) return a.dueDate.hour < b.dueDate.hour;
        return a.dueDate.minute < b.dueDate.minute;
    }

    int show_tasks_basic_mode(const std::string& theme_colour, const std::vector<TaskData>& tasks){
        int count = 0;
        for(const auto& element : tasks){
            color::print(theme_colour); std::cout << ++count << ". " << color::reset << element.title << ":";
            std::cout << "\n\tCategory: " << element.category << std::endl;
            std::cout << "\tPriority: ";
            switch(element.priority){
                case 1:
                    std::cout << "1 - " << color::green << "low" << color::reset;
                    break;
                case 2:
                    std::cout << "2 - " << color::blue << "medium" << color::reset;
                    break;
                case 3:
                    std::cout << "3 - " << color::red << "high" << color::reset;
                    break;
            }
            std::cout << "\n\tIs done? " << (element.isDone ? "YES" : "NO") << std::endl;
            std::cout << "\tDue date: " << element.dueDate.year << "-" << (element.dueDate.month < 10 ? "0" : "") << element.dueDate.month << "-" << (element.dueDate.day < 10 ? "0" : "") << element.dueDate.day << " (" << element.dueDate.hour << ":" << element.dueDate.minute << ")" << std::endl;
        }
        return count;
    }

    void print_header(const std::string& theme_colour, const std::string& msg, bool bold_mode){
        color::print(theme_colour); std::cout << "---[TODO]---" << (bold_mode ? color::white : color::reset) << " " << msg << color::reset << std::endl;
    }
    void print_header(const std::string& theme_colour, const std::string& msg, int data, const std::string& sec_msg, bool bold_mode){
        color::print(theme_colour); std::cout << "---[TODO]---" << (bold_mode ? color::white : color::reset) << " " << msg << data << sec_msg << color::reset << std::endl;
    }
    void print_header(const std::string& theme_colour, const std::string& msg, const std::string& sec_msg, const std::string& third_msg, bool bold_mode = false){
        color::print(theme_colour); std::cout << "---[TODO]---" << (bold_mode ? color::white : color::reset) << " " << msg << sec_msg << third_msg << color::reset << std::endl;
    }
    void input_msg(const std::string& theme_colour, const std::string& msg){
        std::cout << "[" << color::yellow << "?" << color::reset << "]" << msg; color::print(theme_colour);
    }
    void input_msg(const std::string& theme_colour, const std::string& msg, int data, const std::string& sec_msg){
        std::cout << "[" << color::yellow << "?" << color::reset << "]" << msg << data << sec_msg; color::print(theme_colour);
    }

    void display_error(TodoManager::WarningType warning, const std::string& mode, const std::vector<int>& time){
        switch(warning){
            
            case TodoManager::WarningType::EmptyInput:
                if(mode == "name"){
                    std::cout << "[" << color::red << "!" << color::reset << "] A name cannot be empty!" << std::endl;
                }
                else if(mode == "category"){
                    std::cout << "[" << color::red << "!" << color::reset << "] A category name cannot be empty!" << std::endl;
                }
                else if(mode == "colours"){
                    std::cout << "[" << color::red << "!" << color::reset << "] A colour name cannot be empty!" << std::endl;
                }
                break;
            case TodoManager::WarningType::InvalidInput:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid data!" << std::endl;
                break;
            case TodoManager::WarningType::WrongNumber:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid number!" << std::endl;
                break;
            case TodoManager::WarningType::WrongDateYear:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a year after " << time[0]-1 << "!" << std::endl;
                break;
            case TodoManager::WarningType::WrongDateMonth:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a month after " << time[1]-1 << " (" << time[0] << ")!" << std::endl;
                break;
            case TodoManager::WarningType::WrongDateDay:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a day after " << time[2]-1 << " (" << time[0] << "-" << (time[1] < 10 ? "0" : "") << time[1] << ")!" << std::endl;
                break;
            case TodoManager::WarningType::WrongDateHour:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a hour after " << time[3]-1 << " (" << time[0] << "-" << (time[1] < 10 ? "0" : "") << time[1] << "-" << (time[2] < 10 ? "0" : "") << time[2] << ")!" << std::endl;
                break;
            case TodoManager::WarningType::WrongDateMinute:
                std::cout << "[" << color::red << "!" << color::reset << "] Please enter a hour after " << time[3]-1 << " (" << time[0] << "-" << (time[1] < 10 ? "0" : "") << time[1] << "-" << (time[2] < 10 ? "0" : "") << time[2] << ", " << time[3] << ")!" << std::endl;
                break;
            case TodoManager::WarningType::InvalidDate:
                if(mode == "month"){
                    std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid month! (1-12)" << std::endl;
                }
                else if(mode == "day"){
                    std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid day!" << std::endl;
                }
                else if(mode == "hour"){
                    std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid hour!" << std::endl;
                }
                else if(mode == "minute"){
                    std::cout << "[" << color::red << "!" << color::reset << "] Please enter a valid minute!" << std::endl;
                }
                break;
                
        }
    }

}
#endif
