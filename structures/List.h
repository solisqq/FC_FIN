#pragma once
#ifndef LISTT_H
#define LISTT_H

template<class Type>
class List {
public:
    class Node {
    public:
        Type val;
        Node(){}
        Node(Type v):val(v){}
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    Node *front = nullptr, *back = nullptr;
    int Count=0;
    List(){}
    void pushFront(Type value) {
        Count++;
        if(front==nullptr) {
            front = back = new Node(value);
            return;
        }
        Node* newItem = new Node(value);
        newItem->next = front;
        front->prev = newItem;
        front = newItem;
    }
    void pushBack(Type value) {
        Count++;
        if(front==nullptr) {
            front = back = new Node(value);
            return;
        }
        Node* newItem = new Node(value);
        newItem->prev = back;
        back->next = newItem;
        back = newItem;
    }
    void popBack() {
        if(Count<=0) return;
        Count--;
        if(Count==1) {
            delete front;
            front = nullptr;
            return;
        }
        Node* backup = back;
        backup->prev->next = nullptr;
        back = backup->prev;
        delete backup;
    }
    void popFront() {
        if(Count<=0) return;
        Count--;
        if(Count==1) {
            delete front;
            front = nullptr;
            return;
        }
        front->next->prev = nullptr;
        Node* backup = front->next;
        delete front;
        front = backup;
    }
    bool remove(const Type &_val) {
        Node *current = front;
        while(current!=nullptr) {
            if(current->val==_val) {
                if(current==front) {
                    popFront();
                    return true;
                }
                if(current==back) {
                    popBack();
                    return true;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    Node* top() { return front;}
    Node* last() { return back;}
};

#endif