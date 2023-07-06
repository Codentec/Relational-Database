#include <iostream>
#include "rdb.h"
using namespace std;

bool IntAttr::operator==(const Attr &right)
{
    const IntAttr *ptr = dynamic_cast<const IntAttr *>(&right);
    if (ptr == nullptr)
    {
        // right is not an IntAttr object
        return false;
    }
    return value == ptr->value;
}

bool IntAttr::operator!=(const Attr &right)
{
    return !(*this == right);
}

bool IntAttr::operator<(const Attr &right)
{
    const IntAttr *ptr = dynamic_cast<const IntAttr *>(&right);
    if (ptr == nullptr)
    {
        // right is not an IntAttr object
        return false;
    }
    return value < ptr->value;
}

bool IntAttr::operator<=(const Attr &right)
{
    return (*this < right) || (*this == right);
}

bool IntAttr::operator>(const Attr &right)
{
    return !(*this <= right);
}

bool IntAttr::operator>=(const Attr &right)
{
    return !(*this < right);
}

bool FloatAttr::operator==(const Attr &right)
{
    const FloatAttr *rhs = dynamic_cast<const FloatAttr *>(&right);
    return rhs && (value == rhs->value);
}

bool FloatAttr::operator!=(const Attr &right)
{
    return !(*this == right);
}

bool FloatAttr::operator<(const Attr &right)
{
    const FloatAttr *rhs = dynamic_cast<const FloatAttr *>(&right);
    return rhs && (value < rhs->value);
}

bool FloatAttr::operator<=(const Attr &right)
{
    const FloatAttr *rhs = dynamic_cast<const FloatAttr *>(&right);
    return rhs && (value <= rhs->value);
}

bool FloatAttr::operator>(const Attr &right)
{
    const FloatAttr *rhs = dynamic_cast<const FloatAttr *>(&right);
    return rhs && (value > rhs->value);
}

bool FloatAttr::operator>=(const Attr &right)
{
    const FloatAttr *rhs = dynamic_cast<const FloatAttr *>(&right);
    return rhs && (value >= rhs->value);
}

bool StringAttr::operator==(const Attr &right)
{
    const StringAttr *rhs = dynamic_cast<const StringAttr *>(&right);
    return rhs && (value == rhs->value);
}

bool StringAttr::operator!=(const Attr &right)
{
    return !(*this == right);
}

bool StringAttr::operator<(const Attr &right)
{
    const StringAttr *rhs = dynamic_cast<const StringAttr *>(&right);
    return rhs && (value < rhs->value);
}

bool StringAttr::operator<=(const Attr &right)
{
    const StringAttr *rhs = dynamic_cast<const StringAttr *>(&right);
    return rhs && (value <= rhs->value);
}

bool StringAttr::operator>(const Attr &right)
{
    const StringAttr *rhs = dynamic_cast<const StringAttr *>(&right);
    return rhs && (value > rhs->value);
}

bool StringAttr::operator>=(const Attr &right)
{
    const StringAttr *rhs = dynamic_cast<const StringAttr *>(&right);
    return rhs && (value >= rhs->value);
}

// bool IntAttr::operator==(const Attr &right)
// {
//     return (value == static_cast<const IntAttr &>(right).value);
// }
// bool IntAttr::operator!=(const Attr &right)
// {
//     return value != static_cast<const IntAttr &>(right).value;
// }
// bool IntAttr::operator<(const Attr &right)
// {
//     return value < static_cast<const IntAttr &>(right).value;
// }
// bool IntAttr::operator<=(const Attr &right)
// {
//     return value <= static_cast<const IntAttr &>(right).value;
// }
// bool IntAttr::operator>(const Attr &right)
// {
//     return value > static_cast<const IntAttr &>(right).value;
// }
// bool IntAttr::operator>=(const Attr &right)
// {
//     return value >= static_cast<const IntAttr &>(right).value;
// }

// bool FloatAttr::operator==(const Attr &right)
// {
//     return value == static_cast<const FloatAttr &>(right).value;
// }
// bool FloatAttr::operator!=(const Attr &right)
// {
//     return value != static_cast<const FloatAttr &>(right).value;
// }
// bool FloatAttr::operator<(const Attr &right)
// {
//     return value < static_cast<const FloatAttr &>(right).value;
// }
// bool FloatAttr::operator<=(const Attr &right)
// {
//     return value <= static_cast<const FloatAttr &>(right).value;
// }
// bool FloatAttr::operator>(const Attr &right)
// {
//     return value > static_cast<const FloatAttr &>(right).value;
// }
// bool FloatAttr::operator>=(const Attr &right)
// {
//     return value >= static_cast<const FloatAttr &>(right).value;
// }

// bool StringAttr::operator==(const Attr &right)
// {
//     return value == static_cast<const StringAttr &>(right).value;
// }
// bool StringAttr::operator!=(const Attr &right)
// {
//     return value != static_cast<const StringAttr &>(right).value;
// }
// bool StringAttr::operator<(const Attr &right)
// {
//     return value < static_cast<const StringAttr &>(right).value;
// }
// bool StringAttr::operator<=(const Attr &right)
// {
//     return value <= static_cast<const StringAttr &>(right).value;
// }
// bool StringAttr::operator>(const Attr &right)
// {
//     return value > static_cast<const StringAttr &>(right).value;
// }
// bool StringAttr::operator>=(const Attr &right)
// {
//     return value >= static_cast<const StringAttr &>(right).value;
// }

// int main()
// {
//     vector<Attr*> attrs;
//     attrs.push_back(new IntAttr(10));
//     attrs.push_back(new FloatAttr(5.5));
//     attrs.push_back(new StringAttr("Hello"));

//     for (auto attr : attrs)
//     {
//         cout << attr->operator<(IntAttr(5)) << endl;
//         delete attr;
//     }

//     return 0;
// }