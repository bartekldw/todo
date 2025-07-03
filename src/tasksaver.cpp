#include "tasksaver.hpp"
#include "lib/colours.hpp"
#include <iostream>
#include <vector>
#include <fstream>
TaskSaver::TaskSaver(const std::string& file_name){
    this->file_name = file_name;
}

void TaskSaver::save(TaskData task_data_to_save, const std::vector<TaskData> tasks){
    std::ofstream file_save(this->file_name, std::ios::out | std::ios::app);
    if(file_save.is_open()){
       file_save << tasks.size() << ";" << task_data_to_save.title << ";" << task_data_to_save.category << ";" << task_data_to_save.priority << ";" << task_data_to_save.isDone << ";" << task_data_to_save.dueDate.year << "-" << task_data_to_save.dueDate.month << "-" << task_data_to_save.dueDate.day << "-" << task_data_to_save.dueDate.hour << "-" << task_data_to_save.dueDate.minute << "\n";
       file_save.close();
    }
    else{
        std::cout << "[" << color::red << "?" << color::reset << "] Error while trying to save file!" << std::endl;
    }
}

void TaskSaver::save_bulk(const std::vector<TaskData>tasks){
    std::ofstream file_save(this->file_name, std::ios::out | std::ios::trunc);
    if(file_save.is_open()){
       for(const auto& element : tasks){
            file_save << tasks.size() << ";" << element.title << ";" << element.category << ";" << element.priority << ";" << element.isDone << ";" << element.dueDate.year << "-" << element.dueDate.month << "-" << element.dueDate.day << "-" << element.dueDate.hour << "-" << element.dueDate.minute << "\n";
       }
       file_save.close();
    }
    else{
        std::cout << "[" << color::red << "?" << color::reset << "] Error while trying to save file!" << std::endl;
    }
}
