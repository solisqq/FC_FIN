#pragma once
#ifndef ACTION_H
#define ACTION_H
//#include <string>
class Action {
public:
    virtual void execute(String *params) = 0;
};

#endif