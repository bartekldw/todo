#ifndef TASKSAVER_H
#define TASKSAVER_H
#include <iostream>
#include <vector>
#include "taskdata.hpp"
#include "taskdata.hpp"
class TaskSaver{
private:
    std::string file_name;
public:
    TaskSaver(const std::string& file_name);
    void save(TaskData task_data_to_save, const std::vector<TaskData>tasks);
    void save_bulk(const std::vector<TaskData>tasks);
};
#endif
