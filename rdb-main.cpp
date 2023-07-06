#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

// int main()
// {
//     cout<<"Welcome to Our Relational valuebase Managing Software !!!"<<endl;
//     cout << "Lets start with different operations and features." << endl;
//     cout<<"1. Enter 1 to create a new empty table"<<endl
// }

void display()
{
    cout << "press 1 to create a new table" << endl;
    cout << "press 2 to enter a new record in a specified table" << endl;
    cout << "press 3 to delete a table" << endl;
    cout << "press 4 to print a specific table" << endl;
    cout << "press 5 to create a new table using some existing tables" << endl;
}
void createTable(vector<Relation *> &v)
{
    cout << "Please enter attribute names:" << endl;
    Relation *R = new Relation();
    R->nattr = 0;
    R->nrecs = 0;
    int t;
    int i = 1;
    string s;
    while (i != 0)
    {
        cout << "Please enter attribute name:";
        cin >> s;
        R->attrnames.push_back(s);
        cout << "Please enter attribute value type:(press 1 for int) (press 2 for string) (press 3 for float)";
        cin >> t;
        R->attrinds.push_back(t);
        R->nattr++;
        cout << "Press 0 to stop or press 1 to continue giving more attribute names";
        cin >> t;
        i = t;
    }
    i = 1;
    cout << "please enter records:";
    while (i != 0)
    {
        Record *c = new Record();
        float l;
        for (int j = 0; j < R->nattr; j++)
        {
            cout << "Enter the entry for attribute name" << R->attrnames[j] << " ";
            if (R->attrinds[j] == 1)
            {
                cin >> t;
                IntAttr *p = new IntAttr(t);
                c->attrptr.push_back(p);
            }
            else if (R->attrinds[j] == 2)
            {
                cin >> s;
                StringAttr *p = new StringAttr(s);
                c->attrptr.push_back(p);
            }
            else if (R->attrinds[j] == 3)
            {
                cin >> l;
                FloatAttr *p = new FloatAttr(l);
                c->attrptr.push_back(p);
            }
        }
        R->recs.push_back(c);
        cout << "do you want to enter more record if yes then press 1 else press 0:";
        cin >> i;
    }
    v.push_back(R);
    return;
}
void AR(vector<Relation *> &v, int i)
{
    if (i >= v.size())
    {
        cout << "no relation with given index" << endl;
        return;
    }
    Relation *R = v[i];
    cout << "Enter record :" << endl;
    int t;
    string s;
    float l;
    Record *c = new Record();
    for (int j = 0; j < R->nattr; j++)
    {
        cout << "Enter the entry for attribute name-" << R->attrnames[j] << ": ";
        if (R->attrinds[j] == 1)
        {
            cin >> t;
            IntAttr *p = new IntAttr(t);
            c->attrptr.push_back(p);
        }
        else if (R->attrinds[j] == 2)
        {
            cin >> s;
            StringAttr *p = new StringAttr(s);
            c->attrptr.push_back(p);
        }
        else if (R->attrinds[j] == 3)
        {
            cin >> l;
            FloatAttr *p = new FloatAttr(l);
            c->attrptr.push_back(p);
        }
    }
    R->recs.push_back(c);
    cout << "Record added" << endl;
}
void deleteTable(vector<Relation *> &v, int i)
{
    if (i >= v.size())
    {
        cout << "no relation with given index" << endl;
        return;
    }
    Relation *r = v[i];
    v.erase(v.begin() + i);
    delete (r);
    return;
}
/*void print(vector<Relation *> &v, int i)
{
    if (i >= v.size())
    {
        cout << "no relation with given index" << endl;
        return;
    }
    Relation *R = v[i];
    for (auto t : R->attrnames)
    {
        cout << t << " ";
    }
    cout << endl;
    for (auto rec : R->recs)
    {
        for (auto attr : rec->attrptr)
        {
            cout<< (*attr) << " ";
        }
        cout << endl;
    }
    return;
}*/
void print(Relation &people)
{
    // Print out the records in the relation.
    for (auto rec : people.recs)
    {

        for (int i = 0; i < people.nattr; i++)
        {
            Attr *attr = rec->attrptr[i];
            // cout<<"1";
            if (dynamic_cast<StringAttr *>(attr))
            {
                cout << dynamic_cast<StringAttr *>(attr)->value << " ";
            }
            else if (dynamic_cast<IntAttr *>(attr))
            {
                cout << dynamic_cast<IntAttr *>(attr)->value << " ";
            }
            else if (dynamic_cast<FloatAttr *>(attr))
            {
                cout << dynamic_cast<FloatAttr *>(attr)->value << " ";
            }
        }
        cout << endl;
    }
}
int main()
{
    vector<Relation *> tables;
    int i = 1;
    int t;
    while (i != 0)
    {
        display();
        cout << "Please enter your choice:";
        cin >> t;
        if (t == 1)
        {
            createTable(tables);
        }
        else if (t == 2)
        {
            cout << "please enter the index of the table in which record is to be added:";
            cin >> i;
            AR(tables, i);
        }
        else if (t == 3)
        {
            cout << "please enter the index of the table  which is to be deleted:";
            cin >> i;
            deleteTable(tables, i);
        }
        else if (t == 4)
        {
            cout << "please enter the index of the table  which is to be printed:";
            cin >> i;
            if (i >= tables.size())
            {
                cout << "no relation with given index" << endl;
                continue;
            }
            print(*tables[i]);
        }
        else if (t == 5)
        {
            cout << "press 1 to find union of two tables\n press 2 to find difference of two tables \n press 3 to find cartesian product of two tables \n press 4 to find projection of a table " << endl;
            cout << "press 5 to find selection of a table \n press 6 to find the natural joint of two tables \n press 7 to rename a table\n"
                 << endl;
            cin >> t;
            int l, j;
            if (t == 1)
            {
                cout << "please enter the index of the tables whose union is to be found";
                cin >> j >> l;
                Relation *R3 = union_(tables[j], tables[l]);
                tables.push_back(R3);
                print(*R3);
            }
            else if (t == 2)
            {
                cout << "please enter the index of the left operand:";
                cin >> j;
                cout << "please enter the index of the right operand:";
                cin >> l;
                Relation *R3 = difference_(tables[j], tables[l]);
                tables.push_back(R3);
                print(*R3);
            }
            else if (t == 3)
            {
                cout << "please enter the index of the tables whose cartesian product is to be found";
                cin >> j >> l;
                Relation *R3 = cartesianProduct(tables[j], tables[l]);
                tables.push_back(R3);
                print(*R3);
            }
            else if (t == 4)
            {
                list<string> projectattr;
                string st;
                j = 1;
                while (j != 0)
                {
                    cout << "please enter string";
                    cin >> st;
                    projectattr.push_back(st);
                    cout << "to continue press 1 else press 0:";
                    cin >> j;
                }
                cout << "enter index of table:";
                cin >> l;
                Relation *R3 = projection(tables[l], projectattr);
                tables.push_back(R3);
                print(*R3);
            }
            else if (t == 5)
            {
                DNFformula d;
                string s, k;
                float f;
                char a;
                cout << "enter dnf formula" << endl;
                j = 1;
                int q;
                while (j != 0)
                {
                    cout << "enter string:";
                    cin >> s;
                    cout << "enter character:";
                    cin >> a;
                    cout << "enter value type of attribute";
                    cin >> l;
                    cout << "enter attr:";
                    Attr *y;
                    if (l == 1)
                    {
                        cin >> q;
                        y = new IntAttr(q);
                    }
                    else if (l == 2)
                    {
                        cin >> k;
                        y = new StringAttr(k);
                    }
                    else
                    {
                        cin >> f;
                        y = new FloatAttr(f);
                    }
                    list<tuple<string, char, Attr *>> conj1;

                    conj1.push_back(make_tuple(s, a, y));
                    d.push_back(conj1);
                    cout << "To enter more conjunctions press 1 else press 0:";
                    cin >> j;
                }
                cout << "please enter index of the table whose selection is to be done:";
                cin >> j;
                Relation *R = union_(tables[j], &d);
                print(*R);
            }
            else if (t == 6)
            {
                cout << "please enter the index of the tables whose natural join is to be found";
                cin >> j >> l;

                list<string> ls;
                cout << "Enter the number of strings in the joinattr(join attributes)" << endl;
                int x;
                cin >> x;
                string s;
                while (x--)
                {
                    cin >> s;
                    ls.push_back(s);
                }

                Relation *R3 = naturaljoin(tables[j], tables[l], ls);
                tables.push_back(R3);
                print(*R3);
            }
            else if (t == 7)
            {
                cout << "please enter the index of the table whose attribute you want to rename:" << endl;
                cin >> i;
                cout << "Enter the attribute name you want to change" << endl;
                string s1, s2;
                cin >> s1;
                cout << "Enter the new attribute name you want to apply" << endl;
                cin >> s2;
                Relation *R3 = difference(tables[i], s1, s2);
                tables.push_back(R3);
                print(*R3);
            }
        }
        cout << "To continue press 1 else press 0:";
        cin >> i;
    }
    return 0;
}