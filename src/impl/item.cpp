#include "item.h"

string Item::getDescription() const
{
	if (visible) return description;
	else return "";
}

void Item::setNames(string ns[], int num)
{
    for (int i = 0; i < num; i++)
    {
        names.insert(ns[i]);
    }
}
