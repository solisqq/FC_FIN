#pragma once
#ifndef LISTTT_H
#define LISTTT_H

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
        if(Count==0) {
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
        if(Count==0) {
            delete front;
            front = nullptr;
            return;
        }
        front->next->prev = nullptr;
        Node* backup = front->next;
        delete front;
        front = backup;
    }
    void erase() {
        Node* current = front;
        Node* toDel;
        while(current!=nullptr) {
            toDel=current;
            current = current->next;
            delete toDel;
        }
        front = nullptr;
        back = nullptr;
        Count = 0;
    }
    Type getAndPopFront() {
        if(Count<=0) return (Type)0;
        Type toRet = front->val;
        Count--;
        if(Count==0) {
            delete front;
            front = nullptr;
            return toRet;
        }
        front->next->prev = nullptr;
        Node* backup = front->next;
        delete front;
        front = backup;
        return toRet;
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
                Count--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void clear() {
        Node* current = front;
        while(current->next!=nullptr) {
            Node *backup = current->next;
            delete current;
            current = backup;
        }
        delete current;
        Count = 0;
        front = back = nullptr;
    }
    String toString() const {
        String toRet="";
        Node *current = front;
        while(current!=nullptr) {
            toRet+=String(current->val)+", ";
            current = current->next;
        }
        return toRet;
    }
    Type getFront() {return front->val;}
    Type getBack() {return last->val;}
    Node* top() { return front;}
    Node* last() { return back;}
    void Union(List<Type> list) {
        if(front==nullptr) {
            front = list.front;
            back = list.back;
            Count = list.Count;
            return;
        }
        this->back->next = list.front;
        list.front->prev = this->back;
        this->back = list.back;
        this->Count += list.Count;
    }
    List<Type> operator+(Type b) {
		pushBack(b);
        return this;
	}
};

#endif