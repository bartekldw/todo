#include <chrono>
#include <thread>
#include <iostream>
#include "taskdata.hpp"
#include "lib/colours.hpp"

Date::Date(int year_, int month_, int day_, int hour_, int minute_){
        constexpr int waiter = 5;
        year = year_; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] DATA: Successfully added year to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        month = month_; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] DATA: Successfully added month to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        day = day_; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] DATA: Successfully added day to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        hour = hour_; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] DATA: Successfully added hour to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        minute = minute_; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] DATA: Successfully added minute to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
    }
void Date::print(){
        std::cout << year << "-"
                  << (month < 10 ? "0" : "") << month
                  << (day < 10 ? "0" : "") << day
                  << (minute < 10 ? "0" : "") << minute 
                  << std::endl;
}

TaskData::TaskData(long unsigned int id, std::string title, std::string category, int priority, bool isDone, Date dueDate){
        constexpr int waiter = 5;
        this->id = id; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added id to data object " << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        this->title = title; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added title to data object " << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        this->category = category; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added category to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        this->priority = priority; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added priority to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        this->isDone = isDone; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added isDone atribute to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
        this->dueDate = dueDate; std::cout << color::reset << "[" << color::green << "SUCCESS" << color::reset << "] TASK: Successfully added dueDate to data object "<< std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(waiter));
} 
