#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

using namespace std;

Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr)
{
    // Create the resulting relation
    Relation * result = new Relation();

    // Combine the attribute names from R1 and R2
    for (int i = 0; i < R1->nattr; i++)
    {
        result->addAttr(R1->attrnames[i]);
    }
    for (int i = 0; i < R2->nattr; i++)
    {
        bool shared = false;
        for (auto attrname : joinattr)
        {
            if (attrname == R2->attrnames[i])
            {
                shared = true;
                break;
            }
        }
        if (!shared)
        {
            result->addAttr(R2->attrnames[i]);
        }
    }

    // Find the indices of the join attributes in R1 and R2
    vector<int> joinattr_inds_R1;
    vector<int> joinattr_inds_R2;
    for (auto attrname : joinattr)
    {
        int ind_R1 = -1;
        int ind_R2 = -1;
        for (int i = 0; i < R1->nattr; i++)
        {
            if (R1->attrnames[i] == attrname)
            {
                ind_R1 = i;
                break;
            }
        }
        for (int i = 0; i < R2->nattr; i++)
        {
            if (R2->attrnames[i] == attrname)
            {
                ind_R2 = i;
                break;
            }
        }
        if (ind_R1 != -1 && ind_R2 != -1)
        {
            joinattr_inds_R1.push_back(ind_R1);
            joinattr_inds_R2.push_back(ind_R2);
        }
    }

    // Perform the join
    for (auto rec_R1 : R1->recs)
    {
        for (auto rec_R2 : R2->recs)
        {
            bool match = true;
            for (int i = 0; i < joinattr_inds_R1.size(); i++)
            {
                if (*rec_R1->attrptr[joinattr_inds_R1[i]] != *rec_R2->attrptr[joinattr_inds_R2[i]])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                // Create a new record with the attributes from both relations
                Record * newrec = new Record();
                for (int i = 0; i < rec_R1->attrptr.size(); i++)
                {
                    newrec->attrptr.push_back(rec_R1->attrptr[i]);
                }
                for (int i = 0; i < rec_R2->attrptr.size(); i++)
                {
                    bool shared = false;
                    for (auto attrname : joinattr)
                    {
                        if (attrname == R2->attrnames[i])
                        {
                            shared = true;
                            break;
                        }
                    }
                    if (!shared)
                    {
                        newrec->attrptr.push_back(rec_R2->attrptr[i]);
                    }
                }
                result->addRec(newrec);
            }
        }
    }

    return result;
}

// void print(Relation people)
// {
//     // Print out the records in the relation.
//     for (auto rec : people.recs)
//     {
//         for (int i = 0; i < people.nattr; i++)
//         {
//             Attr *attr = rec->attrptr[i];
//             if (dynamic_cast<StringAttr *>(attr))
//             {
//                 cout << dynamic_cast<StringAttr *>(attr)->value << " ";
//             }
//             else if (dynamic_cast<IntAttr *>(attr))
//             {
//                 cout << dynamic_cast<IntAttr *>(attr)->value << " ";
//             }
//             else if (dynamic_cast<FloatAttr *>(attr))
//             {
//                 cout << dynamic_cast<FloatAttr *>(attr)->value << " ";
//             }
//         }
//         cout << endl;
//     }
// }
// 
// int main()
// {
//     Relation people;
//     people.attrnames = {"name", "age", "height"};
//     people.nattr = 3;

//     // Add some records to the relation.
//     Record *rec1 = new Record();
//     rec1->attrptr.push_back(new StringAttr("Alice"));
//     rec1->attrptr.push_back(new IntAttr(25));
//     rec1->attrptr.push_back(new FloatAttr(1.65));
//     people.recs.push_back(rec1);

//     Record *rec2 = new Record();
//     rec2->attrptr.push_back(new StringAttr("Bob"));
//     rec2->attrptr.push_back(new IntAttr(30));
//     rec2->attrptr.push_back(new FloatAttr(1.8));
//     people.recs.push_back(rec2);

//     Record *rec3 = new Record();
//     rec3->attrptr.push_back(new StringAttr("Charlie"));
//     rec3->attrptr.push_back(new IntAttr(35));
//     rec3->attrptr.push_back(new FloatAttr(1.75));
//     people.recs.push_back(rec3);

//     Relation animal;
//     animal.attrnames = {"age", "height"};
//     animal.nattr = 3;

//     // Add some records to the relation.
//     Record *rec4 = new Record();
//     rec4->attrptr.push_back(new IntAttr(25));
//     rec4->attrptr.push_back(new FloatAttr(1.65));
//     animal.recs.push_back(rec4);

//     Record *rec5 = new Record();
//     rec5->attrptr.push_back(new IntAttr(24));
//     rec5->attrptr.push_back(new FloatAttr(1.2));
//     animal.recs.push_back(rec5);

//     Record *rec6 = new Record();
//     rec6->attrptr.push_back(new IntAttr(36));
//     rec6->attrptr.push_back(new FloatAttr(1.3));
//     animal.recs.push_back(rec6);

//     cout << "People:" << endl;
//     print(people);
//     cout << "Animal:" << endl;
//     print(animal);

//     list<string> l{"age"};
//     Relation *R3 = naturaljoin(&people, &animal, l);
//     print(*R3);
//     return 0;
// }