#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
    public:
        Person();
        Person(std::string name, int age, double height);
        void set_name(std::string name);
        void set_age(int age);
        void set_height(double height);
        std::string get_name();
        int get_age();
        double get_height();
    private:
        std::string _name; 
        int _age;
        double _height; 
};

#endif