#ifndef TODOMANAGER_H
#define TODOMANAGER_H

#include <iostream>
#include <vector>
#include "taskdata.hpp"
class TodoManager{
private:
    std::string file_name;
    std::vector<TaskData> tasks;
    std::vector<std::string> categories;
    void sort_tasks_id(std::vector<TaskData>& tasks);
    void sort_tasks_priority(std::vector<TaskData>& tasks);
    void sort_tasks_date(std::vector<TaskData>& tasks);
public:
    enum class WarningType{
        None,
        EmptyInput,
        InvalidInput,
        WrongNumber,
        WrongDate,
        WrongDateYear,
        WrongDateMonth,
        WrongDateDay,
        WrongDateHour,
        WrongDateMinute,
        InvalidDate,
        InvalidDataInput,
        InvalidDayToMonth
    };
    TodoManager(const std::string& file_name, const std::vector<TaskData>& tasks, const std::vector<std::string>& categories);
    std::string theme_colour;
    bool file_exists(const std::string& file_name);
    void pair_tasks_to_vector();
    void add_task();
    void show_tasks(bool manage_tasks_mode = false);
    void manage_tasks(TaskData task_to_manage, int id);
    void construct_options(std::string& colour);
    void get_name(std::string& name, bool managing_task = false);
    void get_category(std::string& category, const std::string& task_name, bool managing_task = false);
    void get_priority(int &priority, const std::string& category, const std::string& task_name, bool managing_task = false);
    void get_done_attribute(bool& is_done);
    void get_date(int &year, int&month, int&day, int&hour, int&minute, int priority, const std::string& task_category, const std::string& task_name, bool managing_task = false);
    void display_menu(bool& should_exit);
};

#endif
