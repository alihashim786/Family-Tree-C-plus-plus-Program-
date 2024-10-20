
#include <iostream>
#include <ctime>
using namespace std;
class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }
};
class Person
{
private:
    string name;
    char gender;
    Date dob;
    int noOfChildren;

public:
    Person **children;
    Person() : name(""), gender(' '), noOfChildren(0), children(nullptr) {}
    Person(string n, char g, int day, int month, int year) : name(n), gender(g), dob(day, month, year), noOfChildren(0), children(nullptr) {}
    ~Person()
    {
        if (children != nullptr)
        {
            delete[] children;
        }
    }
    void setName(string &n) { name = n; }
    void setGender(char g) { gender = g; }
    void setDOB(int day, int month, int year) { dob = Date(day, month, year); }
    string getName() { return name; }
    char getGender() { return gender; }
    Date getDOB() { return dob; }
    int getNoOfChildren() { return noOfChildren; }
    void displayData()
    {
        cout << "Name: " << name << endl;
        cout << "Gender: " << gender << endl;
        cout << "Date of Birth: " << dob.getDay() << "/" << dob.getMonth() << "/" << dob.getYear() << endl;
        cout << "Number of Children: " << noOfChildren << endl;
    }
    int calcAge()
    {
        time_t now = time(0);
        tm *currentTime = localtime(&now);
        int currentYear = 1900 + currentTime->tm_year;
        int currentMonth = 1 + currentTime->tm_mon;
        int currentDay = currentTime->tm_mday;
        int age = currentYear - dob.getYear();
        if (currentMonth < dob.getMonth() || (currentMonth == dob.getMonth() && currentDay < dob.getDay()))
        {
            age--;
        }
        return age;
    }
    void addChild(Person &child)
    {
        if (noOfChildren < 3)
        {
            if (children == nullptr)
            {
                children = new Person *[3];
            }
            children[noOfChildren] = &child;
            noOfChildren++;
        }
    }
};
class FamilyTree
{
private:
    Person *foreFather;

public:
    FamilyTree(Person *foreFather) : foreFather(foreFather) {}
    ~FamilyTree() { delete foreFather; }
    void registerChild(Person &p, Person &child)
    {
        p.addChild(child);
        p.displayData();
    }
    Person *findYoungestChildOf(Person &p)
    {
        Person *youngestChild = nullptr;
        int lowestAge = 100;
        if (p.getNoOfChildren() > 0)
        {
            for (int i = 0; i < p.getNoOfChildren(); i++)
            {
                Person *child = p.children[i];
                int age = child->calcAge();
                if (age < lowestAge)
                {
                    lowestAge = age;
                    youngestChild = child;
                }
            }
        }
        return youngestChild;
    }
    void displayFamilyOf(Person &p)
    {
        cout << "Family of " << p.getName() << ":" << endl;
        if (p.getNoOfChildren() > 0)
        {
            for (int i = 0; i < p.getNoOfChildren(); i++)
            {
                Person *child = p.children[i];
                cout << "Child " << i + 1 << ": " << child->getName() << endl;
            }
        }
        else
        {
            cout << "No children registered." << endl;
        }
    }
    Person *findEldestGrandsonOf(Person *grandfather)
    {
        Person *eldestGrandson = nullptr;
        int highestAge = 0;
        if (grandfather->getNoOfChildren() > 0)
        {
            for (int i = 0; i < grandfather->getNoOfChildren(); i++)
            {
                Person *child = grandfather->children[i];
                if (child->getNoOfChildren() > 0)
                {
                    for (int j = 0; j < child->getNoOfChildren(); j++)
                    {
                        Person *grandson = child->children[j];
                        int age = grandson->calcAge();
                        if (age > highestAge)
                        {
                            highestAge = age;
                            eldestGrandson = grandson;
                        }
                    }
                }
            }
        }
        return eldestGrandson;
    }
    void displayTree(Person *p)
    {
        if (p != nullptr)
        {
            cout << "Father: " << p->getName() << endl;
            if (p->getNoOfChildren() > 0)
            {
                for (int i = 0; i < p->getNoOfChildren(); i++)
                {
                    Person *child = p->children[i];
                    cout << "Child " << i + 1 << ": " << child->getName() << endl
                         << endl
                         << endl;
                    if (child->children != NULL)
                    {
                        cout << "Grandsons of:" << p->getName() << endl
                             << endl;
                        displayTree(child);
                    }
                }
            }
        }
    }
};
