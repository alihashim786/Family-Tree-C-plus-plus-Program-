#include <iostream>
#include "familytree.h"
using namespace std;
int main()
{
    Person *foreFather = new Person("Ali", 'M', 1, 1, 1950);
    FamilyTree familyTree(foreFather);
    Person child1("Hashim", 'F', 1, 1, 1975);
    Person child2("Raza", 'M', 1, 1, 1980);
    Person child3("Shah", 'M', 1, 1, 1990);
    Person child4("Sam", 'M', 1, 1, 2019);
    familyTree.registerChild(*foreFather, child1);
    familyTree.registerChild(*foreFather, child2);
    familyTree.registerChild(*foreFather, child3);
    familyTree.registerChild(child3, child4);
    cout << "Family of forefather " << foreFather->getName() << ":" << endl
         << endl;
    familyTree.displayFamilyOf(*foreFather);
    Person *youngestChild = familyTree.findYoungestChildOf(*foreFather);
    if (youngestChild != nullptr)
    {
        cout << "Youngest child of " << foreFather->getName() << " is " << youngestChild->getName() << endl
             << endl;
    }
    else
    {
        cout << "No children registered for " << foreFather->getName() << endl
             << endl;
    }
    Person *eldestGrandson = familyTree.findEldestGrandsonOf(foreFather);
    if (eldestGrandson != nullptr)
    {
        cout << "Eldest grandson of " << foreFather->getName() << " is " << eldestGrandson->getName() << endl
             << endl;
    }
    else
    {
        cout << "No grandsons found for " << foreFather->getName() << endl
             << endl;
    }
    cout << "Family Tree:" << endl;
    familyTree.displayTree(foreFather);
    delete foreFather;
    return 0;
}
