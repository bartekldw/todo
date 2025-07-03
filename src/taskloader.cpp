#include "taskloader.hpp"
#include "taskdata.hpp"
#include <iostream>
#include <fstream>
#include <vector>
TaskLoader::TaskLoader(const std::string& file_name){
    this->file_name = file_name;
}
bool TaskLoader::find_attribute(const std::string& line, int &current_index, int& data, char ending_char, bool ending){
    std::string data_string;
    while(ending ? current_index < line.size() : line[current_index] != ending_char){
        data_string += line[current_index];
        current_index++;
    }
    try{
        data = std::stoi(data_string);
    } catch(...){
        return false;
    }
    if(!ending){
        current_index++;
    }
    return true;
}
bool TaskLoader::find_attribute(const std::string& line, int &current_index, std::string& data, char ending_char){
    while(line[current_index]!= ending_char){
        data += line[current_index];
        current_index++;
    }
    current_index++;
    return true;
} 
bool TaskLoader::find_attribute(const std::string& line, int &current_index, bool&data, char ending_char){
    std::string data_string;
    while(line[current_index] != ending_char){
        data_string += line[current_index];
        current_index++;
    }
    try{
        data = std::stoi(data_string);
    } catch(...){
        return false;
    }
    current_index++;
    return true;
} 
 
bool TaskLoader::divide_line(const std::string& line, std::vector<TaskData>& tasks){
    int index = 0, priority, id;
    std::string title, category;
    bool isDone;
    //get the id
    if(!find_attribute(line,index,id)){return false;}
    //get the title
    if(!find_attribute(line,index,title)){return false;}
    //get the category
    if(!find_attribute(line,index,category)){return false;}
    //get the priority
    if(!find_attribute(line,index,priority)){return false;}
    //get the isDone attribute
    if(!find_attribute(line,index,isDone)){return false;}
    //export the date, it is divided into parts
    int year, month, day, hour, minute;
    //1. the year
    if(!find_attribute(line,index,year, '-')){return false;}
    //2. the month
    if(!find_attribute(line,index,month, '-')){return false;}
    //3. the day
    if(!find_attribute(line,index,day, '-')){return false;}
    //4. the hour
    if(!find_attribute(line,index,hour, '-')){return false;}
    //5. the minute
    if(!find_attribute(line,index,minute, '-', true)){return false;} //<- "true" boolean argument, as it's the end of our string
    
    Date DueDate{year,month,day,hour,minute};
    TaskData cur_task{static_cast<long unsigned int>(id), title,category,priority,isDone, DueDate};
    tasks.push_back(cur_task);
    return true;
}

bool TaskLoader::export_tasks(std::vector<TaskData>& tasks){
    std::ifstream file_open(file_name, std::ios::in);
    if(file_open.is_open() && file_open.good()){
        std::string line;
        while(std::getline(file_open, line)){
            if(!divide_line(line, tasks)){
                return false;
            }
        }
        file_open.close();
    }
    else{
        return false;
    }
    return true;
}
void TaskLoader::export_categories(const std::vector<TaskData>& tasks, std::vector<std::string>& categories){
    for(const auto& element : tasks){
        categories.push_back(element.category);
    }
    auto last = std::unique(categories.begin(), categories.end());
    categories.erase(last, categories.end());
}
