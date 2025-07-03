#ifndef TASKDATA_H
#define TASKDATA_H
#include <chrono>
#include <thread>
#include <iostream>
#include "lib/colours.hpp"
struct Date{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    Date(int year_, int month_, int day_, int hour_, int minute_);
    void print();
};
struct TaskData{
    long unsigned int id;
    std::string title;
    std::string category;
    int priority;
    bool isDone;
    Date dueDate = Date(2000,0,0,0,0);
    TaskData(long unsigned int id, std::string title, std::string category, int priority, bool isDone, Date dueDate);
};

#endif
