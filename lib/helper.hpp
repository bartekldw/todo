#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <cstdlib>
#include <limits> 
#include <ctime>
#include <vector>
#include "colours.hpp"
#include "src/taskdata.hpp"
namespace helper{
    void clear_console();
    void clean_cin();
    void print_task_info(std::string name, std::string theme_colour);
    void print_task_info(std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour);
    void print_task_info(std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour, int priority);
    void print_task_info(bool should_use_diffrent_colour_scheme, std::vector<std::string> categories, std::string name, std::string category, std::string theme_colour, int priority);
    std::vector<int> current_date();
    bool valid_month(int year, int month, int days);
    bool compare_by_object_id(const TaskData& a, const TaskData& b);
    bool compare_by_object_priority(const TaskData& a, const TaskData& b);
    bool compare_by_object_due_date(const TaskData& a, const TaskData& b);
    int show_tasks_basic_mode(const std::string& theme_colour, const std::vector<TaskData>& tasks);
    void print_header(const std::string& theme_colour, const std::string& msg, bool bold_mode = false);
    void print_header(const std::string& theme_colour, const std::string& msg, const std::string& sec_msg, const std::string& third_msg, bool bold_mode = false);
    void print_header(const std::string& theme_colour, const std::string& msg, int data, const std::string& sec_msg, bool bold_mode = false);
    void input_msg(const std::string& theme_colour, const std::string& msg);
    void input_msg(const std::string& theme_colour, const std::string& msg, int data, const std::string& sec_msg);
    void display_error(TodoManager::WarningType warning, const std::string& mode = "", const std::vector<int>& time = {});
}
#endif
