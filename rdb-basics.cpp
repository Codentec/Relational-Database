#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

using namespace std;

Relation *union_(Relation *R1, Relation *R2)
{
    if (!(R1->iscompatible(R2)))
    {
        cout << "Relations are not compatible!!!";
        return nullptr;
    }

    auto R = new Relation;
    R->nattr = R1->nattr;
    for (auto record : R1->recs)
    {
        auto newRecord = new Record(*record);
        R->addRec(newRecord);
    }

    for (auto record : R2->recs)
    {
        auto newRecord = new Record(*record);
        bool alreadyExists = false;
        for (auto Rrecord : R->recs)
        {
            bool equal = true;
            auto r1attrs = Rrecord->attrptr;
            auto r2attrs = record->attrptr;
            for (int i = 0; i < r1attrs.size(); ++i)
            {
                if (!(*(r1attrs[i]) == *(r2attrs[i])))
                {
                    equal = false;
                    break;
                }
            }
            if (equal)
            {
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists)
        {
            R->addRec(newRecord);
        }
        else
        {
            delete newRecord;
        }
    }
    return R;
}

Relation *difference_(Relation *R1, Relation *R2)
{
    Relation *result = new Relation();

    // Check if R1 and R2 have the same attributes
    if (!(R1->iscompatible(R2)))
    {
        cout << "Relations are not compatible!!";
        return nullptr;
    }

    // Add the attributes to the result relation
    result->nattr = R1->nattr;
    result->attrnames = R1->attrnames;
    result->attrinds = R1->attrinds;

    // Iterate through the records in R1 and remove those that are in R2
    for (auto rec1 : R1->recs)
    {
        bool found = false;
        for (auto rec2 : R2->recs)
        {
            if ((*rec1) == (*rec2))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result->recs.push_back(new Record(*rec1));
        }
    }
    return result;
}

Relation *cartesianProduct(Relation *R1, Relation *R2)
{
    Relation *result = new Relation();

    for (int i = 0; i < R1->nattr; i++)
    {
        result->addAttr(R1->attrnames[i]);
    }
    for (int i = 0; i < R2->nattr; i++)
    {
        result->addAttr(R2->attrnames[i]);
    }

    // For each record in R1, create a new record for every record in R2 and append the concatenated record to the result relation
    for (auto rec1 : R1->recs)
    {
        for (auto rec2 : R2->recs)
        {
            Record *newRec = new Record();
            for (auto attr : rec1->attrptr)
            {
                if (dynamic_cast<IntAttr *>(attr))
                {
                    newRec->attrptr.push_back(new IntAttr(*(dynamic_cast<IntAttr *>(attr))));
                }
                else if (dynamic_cast<FloatAttr *>(attr))
                {
                    newRec->attrptr.push_back(new FloatAttr(*(dynamic_cast<FloatAttr *>(attr))));
                }
                else if (dynamic_cast<StringAttr *>(attr))
                {
                    newRec->attrptr.push_back(new StringAttr(*(dynamic_cast<StringAttr *>(attr))));
                }
            }
            for (auto attr : rec2->attrptr)
            {
                if (dynamic_cast<IntAttr *>(attr))
                {
                    newRec->attrptr.push_back(new IntAttr(*(dynamic_cast<IntAttr *>(attr))));
                }
                else if (dynamic_cast<FloatAttr *>(attr))
                {
                    newRec->attrptr.push_back(new FloatAttr(*(dynamic_cast<FloatAttr *>(attr))));
                }
                else if (dynamic_cast<StringAttr *>(attr))
                {
                    newRec->attrptr.push_back(new StringAttr(*(dynamic_cast<StringAttr *>(attr))));
                }
            }
            result->addRec(newRec);
        }
    }

    return result;
}

Relation *projection(Relation *R1, list<string> projectattrs)
{

    Relation *R2 = new Relation();
    for (auto attr : projectattrs)
    {
        R2->addAttr(attr);
    }

    // iterate through each record in R1 and create a new record with only the projected attributes
    for (auto rec : R1->recs)
    {
        Record *newrec = new Record();
        for (auto attr : projectattrs)
        {
            int attrIndex = find(R1->attrnames.begin(), R1->attrnames.end(), attr) - R1->attrnames.begin();
            if (attrIndex >= R1->nattr)
            {
                cerr << "Attribute " << attr << " not found in Relation R1." << endl;
                return nullptr;
            }
            newrec->attrptr.push_back(rec->attrptr[attrIndex]);
        }
        R2->addRec(newrec);
    }

    return R2;
}

Relation *union_(Relation *R1, DNFformula *f)
{
    Relation *result = new Relation(*R1);
    result->recs.clear();

    for (auto rec : R1->recs)
    {
        bool matched = false;
        for (auto conjunction : *f)
        {
            bool conjunctionMatched = true;
            for (auto comparison : conjunction)
            {
                string attrName;
                char op;
                Attr *value;
                tie(attrName, op, value) = comparison;

                int attrIndex = -1;
                for (int i = 0; i < R1->nattr; i++)
                {
                    if (R1->attrnames[i] == attrName)
                    {
                        attrIndex = i;
                        break;
                    }
                }
                if (attrIndex == -1)
                {
                    continue;
                }

                Attr *recordValue = rec->attrptr[attrIndex];
                bool comparisonResult = false;
                if (op == '=')
                {
                    comparisonResult = (*value == *recordValue);
                }
                else if (op == '<')
                {
                    comparisonResult = (*recordValue < *value);
                }
                else if (op == '>')
                {
                    comparisonResult = (*recordValue > *value);
                }

                if (!comparisonResult)
                {
                    // Comparison failed, so move on to the next conjunction
                    conjunctionMatched = false;
                    break;
                }
            }
            if (conjunctionMatched)
            {
                // Record matched at least one conjunction, so add it to the result
                matched = true;
                break;
            }
        }
        if (matched)
        {
            result->addRec(new Record(*rec));
        }
    }

    return result;
}

Relation *difference(Relation *R1, string s1, string s2)
{
    // Find the index of the old attribute name in the attribute names vector
    int index = -1;
    for (int i = 0; i < R1->attrnames.size(); i++)
    {
        if (R1->attrnames[i] == s1)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        // Attribute name not found
        cout << "Attribute " << s1 << " not found in relation" << endl;
        return nullptr;
    }

    // Rename the attribute name
    R1->attrnames[index] = s2;
    return R1;
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

// int main()
// {
//     Relation people;
//     people.attrnames = {"name", "age", "height"};
//     people.attrinds ={3,1,2};
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
//     animal.attrnames = {"name", "age", "height"};
//     animal.attrinds ={3,1,2};
//     animal.nattr = 3;

//     // Add some records to the relation.
//     Record *rec4 = new Record();
//     rec4->attrptr.push_back(new StringAttr("Alice"));
//     rec4->attrptr.push_back(new IntAttr(25));
//     rec4->attrptr.push_back(new FloatAttr(1.65));
//     animal.recs.push_back(rec4);

//     Record *rec5 = new Record();
//     rec5->attrptr.push_back(new StringAttr("B"));
//     rec5->attrptr.push_back(new IntAttr(24));
//     rec5->attrptr.push_back(new FloatAttr(1.2));
//     animal.recs.push_back(rec5);

//     Record *rec6 = new Record();
//     rec6->attrptr.push_back(new StringAttr("C"));
//     rec6->attrptr.push_back(new IntAttr(36));
//     rec6->attrptr.push_back(new FloatAttr(1.3));
//     animal.recs.push_back(rec6);

//     cout << "People:" << endl;
//     print(people);
//     cout << "Animal:" << endl;
//     print(animal);

//     Relation *R3 = union_(&people, &animal);
//     print(*R3);
//     cout << "Chalo" << endl;
//     R3 = difference_(&people, &animal);
//     print(*R3);
//     cout << "Chalo" << endl;
//     R3 = cartesianProduct(&people, &animal);
//     print(*R3);
//     list<string> l{"name", "age"};
//     R3 = projection(&people, l);
//     print(*R3);
//     cout << "Chalo" << endl;

//     DNFformula f;
//     list<tuple<string, char, Attr *>> conj1;
//     IntAttr *age_attr = new IntAttr(25);
//     conj1.push_back(make_tuple("age", '>', age_attr));
//     f.push_back(conj1);

//     R3 = union_(&people, &f);
//     print(*R3);
//     return 0;
// }