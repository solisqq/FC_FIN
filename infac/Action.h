#pragma once
#ifndef ACTION_H
#define ACTION_H
//#include <string>
class Action {
public:
    virtual void execute(const List<String> &params) = 0;
};

#endif