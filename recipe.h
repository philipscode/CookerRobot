#ifndef RECIPE_H
#define RECIPE_H


#include "ingridient.h"
#include "operation.h"


class Recipe
{
public:
    //Node description
    struct Node
    {
        Item *data;
        Node *next;
    };

    //Iterator class
    class iterator
    {
    public:
        iterator()
            : itr(NULL)
        {
        }
        iterator(Node* ptr)
            : itr(ptr)
        {
        }
        iterator& operator++ ()
        {
            itr = itr->next;
            return *this;
        }
        iterator operator++ (int)
        {
            iterator temp(*this);
            itr = itr->next;
            return temp;
        }
        bool operator ==(const iterator& rs) const
        {
            return itr == rs.itr;
        }
        bool operator !=(const iterator& rs) const
        {
            return itr != rs.itr;
        }
        Item* operator *()
        {
            return itr->data;
        }
        Item* object()
        {
            return itr->data;
        }
    private:
        Node *itr;
    };

    //Functions for working with iterators
    iterator begin() const
    {
        return iterator(first);
    }
    iterator end() const
    {
        if (last == NULL)
            return iterator(last);
        else
            return iterator(last->next);
    }

    //Container interface
    Recipe(); //default constructor
    Recipe(const Recipe&); //copy constructor
    void push(Item*); //insert to the end
    Item* pop(); //remove from the front
    void removeAll(); //remove all
    int size() const; //the number of elements
    void writeToFile(std::string&, std::string&) const; //write to file
    void readFromFile(std::string&, std::string&); //read from file
private:
    Node *first, *last;
    int sz;
};

#endif // RECIPE_H
