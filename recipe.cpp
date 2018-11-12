#include "recipe.h"


Recipe::Recipe()
{
    first = last = NULL;
    sz = 0;
}

Recipe::Recipe(const Recipe &src)
{
    first = last = NULL;
    sz = 0;
    Node *temp = src.first;
    while (temp != NULL)
    {
        this->push(temp->data);
        temp = temp->next;
    }
}

void Recipe::push(Item *object)
{
    Node *temp = new Node();
    temp->data = object;
    if (last == NULL)
    {
        first = temp;
        last = temp;
        first->next = last->next = NULL;
    }
    else
    {
        last->next = temp;
        last = temp;
        last->next = NULL;
    }
    ++sz;
}

Item* Recipe::pop()
{
    if (sz > 0)
    {
        Node *temp = new Node();
        temp = first;
        first = first->next;
        --sz;
        if (sz == 0)
        {
            first = last = NULL;
        }
        return temp->data;
    }
    else
    {
        return NULL;
    }
}

void Recipe::removeAll()
{
    while (sz > 0)
    {
        this->pop();
    }
    first = last = NULL;
}

int Recipe::size() const
{
    return sz;
}

void Recipe::writeToFile(std::string &path, std::string &title) const
{
    std::ofstream file;
    file.open(path);
    file << title << '\n';
    file << sz << '\n';
    for (iterator it = begin(); it != end(); it++)
    {
        if (it.object()->identify() == 1)
        {
            Ingridient *ing = dynamic_cast<Ingridient*>(it.object());
            file << "-Ingridient:" << '\n';
            file << ing->getName() << '\n';
            file << ing->getMeasure() << '\n';
            file << ing->getAmount() << '\n';
        }
        else
        {
            Operation *op = dynamic_cast<Operation*>(it.object());
            file << "-Operation:" << '\n';
            file << op->getName() << '\n';
            file << op->getDuration() << '\n';
            file << op->getMeasure() << '\n';
        }
    }
    file.close();
}

void Recipe::readFromFile(std::string &path, std::string &title)
{
    this->removeAll();
    std::ifstream file;
    file.open(path);
    if (file.is_open())
    {
        std::getline(file, title, '\n');
        std::string tmp;
        int size;
        std::getline(file, tmp, '\n');
        size = std::stoi(tmp);
        std::string name, measure, id;
        double amount;
        int duration;
        while (size > 0)
        {
            std::getline(file, id, '\n');
            if (id == "-Ingridient:")
            {
                std::getline(file, name, '\n');
                std::getline(file, measure, '\n');
                std::getline(file, tmp, '\n');
                amount = std::stod(tmp);
                Ingridient *ing = new Ingridient(name, measure, amount);
                this->push(ing);
            }
            else //id == "-Operation:"
            {
                std::getline(file, name, '\n');
                std::getline(file, tmp, '\n');
                duration = std::stoi(tmp);
                std::getline(file, measure, '\n');
                Operation *op = new Operation(name, duration, measure);
                this->push(op);
            }
            --size;
        }
        file.close();
    }
}
