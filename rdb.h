#include <iostream>
#include <vector>
#include <list>
#include <tuple>
using namespace std;

class Attr
{
public:
    virtual ~Attr() {}

    virtual bool operator==(const Attr &right) = 0;
    virtual bool operator!=(const Attr &right) = 0;
    virtual bool operator<(const Attr &right) = 0;
    virtual bool operator<=(const Attr &right) = 0;
    virtual bool operator>(const Attr &right) = 0;
    virtual bool operator>=(const Attr &right) = 0;
};

class IntAttr : public Attr
{
public:
    int value;
    IntAttr(int val) : value(val) {}
    ~IntAttr() { value = 0; }
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>(const Attr &right);
    bool operator>=(const Attr &right);
};

class FloatAttr : public Attr
{
public:
    float value;
    FloatAttr(float val) : value(val) {}
    ~FloatAttr() {}
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>(const Attr &right);
    bool operator>=(const Attr &right);
};

class StringAttr : public Attr
{
public:
    ~StringAttr() {}
    string value;
    StringAttr(string val) : value(val) {}
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>(const Attr &right);
    bool operator>=(const Attr &right);
};



class Record
{
public:
    vector<Attr *> attrptr;

    // Constructor and Destructor
    Record() {}
    ~Record()
    {
        for (auto attr : attrptr)
        {
            delete attr;
        }
    }

    // Copy Constructor and Assignment Operator
    Record(const Record &other)
    {
        for (auto attr : other.attrptr)
        {
            if (dynamic_cast<IntAttr *>(attr))
            {
                attrptr.push_back(new IntAttr(*(dynamic_cast<IntAttr *>(attr))));
            }
            else if (dynamic_cast<FloatAttr *>(attr))
            {
                attrptr.push_back(new FloatAttr(*(dynamic_cast<FloatAttr *>(attr))));
            }
            else if (dynamic_cast<StringAttr *>(attr))
            {
                attrptr.push_back(new StringAttr(*(dynamic_cast<StringAttr *>(attr))));
            }
        }
    }
    Record &operator=(const Record &other)
    {
        if (this != &other)
        {
            for (auto attr : attrptr)
            {
                delete attr;
            }
            attrptr.clear();
            for (auto attr : other.attrptr)
            {
                if (dynamic_cast<IntAttr *>(attr))
                {
                    attrptr.push_back(new IntAttr(*(dynamic_cast<IntAttr *>(attr))));
                }
                else if (dynamic_cast<FloatAttr *>(attr))
                {
                    attrptr.push_back(new FloatAttr(*(dynamic_cast<FloatAttr *>(attr))));
                }
                else if (dynamic_cast<StringAttr *>(attr))
                {
                    attrptr.push_back(new StringAttr(*(dynamic_cast<StringAttr *>(attr))));
                }
            }
        }
        return *this;
    }

    bool operator==(const Record &a)
    {
        int it = 0;
        int ita = 0;
        for (it = 0; it < this->attrptr.size(); it++)
        {
            if (*(this->attrptr[it]) != *(a.attrptr[it]))
                return 0;
        }
        return 1;
    }
};

class Relation
{
public:
    int nattr, nrecs;
    vector<string> attrnames;
    vector<int> attrinds;
    list<Record *> recs;

    // Constructor and Destructor
    Relation() : nattr(0), nrecs(0) {}
    ~Relation()
    {
        for (auto rec : recs)
        {
            delete rec;
        }
    }

    // Copy Constructor and Assignment Operator
    Relation(const Relation &other)
    {
        nattr = other.nattr;
        nrecs = other.nrecs;
        attrnames = other.attrnames;
        attrinds = other.attrinds;
        for (auto rec : other.recs)
        {
            recs.push_back(new Record(*rec));
        }
    }
    Relation &operator=(const Relation &other)
    {
        if (this != &other)
        {
            nattr = other.nattr;
            nrecs = other.nrecs;
            attrnames = other.attrnames;
            attrinds = other.attrinds;
            for (auto rec : recs)
            {
                delete rec;
            }
            recs.clear();
            for (auto rec : other.recs)
            {
                recs.push_back(new Record(*rec));
            }
        }
        return *this;
    }

    // Other methods
    void addAttr(string name)
    {
        attrnames.push_back(name);
        attrinds.push_back(nattr++);
    }
    void addRec(Record *rec)
    {
        recs.push_back(rec);
        nrecs++;
    }

    bool iscompatible(Relation *R2)
    {
        if (this->nattr != R2->nattr)
        {
            return 0;
        }
        for (int i = 0; i < this->nattr; i++)
        {
            if (this->attrinds[i] != R2->attrinds[i])
                return 0;
        }
        return 1;
    }
    bool isPresent(Record *R)
    {
        list<Record *>::iterator it;
        for (it = (this->recs).begin(); it != (this->recs).end(); it++)
        {
            if (!(*(*it) == (*R)))
                return 0;
        }
        return 1;
    }
};

Relation *union_(Relation *R1, Relation *R2);
Relation *difference_(Relation *R1, Relation *R2);
Relation *cartesianProduct(Relation *R1, Relation *R2);
Relation *projection(Relation *R1, list<string> projectattrs);

typedef list<list<tuple<string, char, Attr *>>> DNFformula;
Relation *union_(Relation *R1, DNFformula *f);
Relation *difference(Relation *R1, string s1, string s2);

Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr);