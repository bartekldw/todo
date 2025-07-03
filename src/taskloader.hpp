#ifndef TASKLOADER_H
#define TASKLOADER_H

#include <iostream>
#include <vector>
#include "taskdata.hpp"
class TaskLoader{
private:
    std::string file_name;
    bool find_attribute(const std::string& line, int& current_index, int& data, char ending_char = ';', bool ending = false);
    bool find_attribute(const std::string& line, int &current_index, std::string& data, char ending_char = ';');
    bool find_attribute(const std::string& line, int &current_index, bool&data, char ending_char = ';');
    
public:
    bool divide_line(const std::string& line, std::vector<TaskData>& tasks);
    TaskLoader(const std::string& file_name);
    bool export_tasks(std::vector<TaskData>& tasks);
    void export_categories(const std::vector<TaskData>& tasks, std::vector<std::string>& categories);
};
#endif
