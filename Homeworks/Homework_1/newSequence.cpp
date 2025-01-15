#include "newSequence.h"
#include <iostream>

Sequence::Sequence(int maxitems) :m_size(0), m_maxitems(maxitems)// Create an empty sequence (i.e., one whose size() is 0).
{
    if (maxitems < 0)
    {
        std::exit(1);
    }
    m_array = new ItemType[m_maxitems];

}
Sequence::Sequence(const Sequence& other) //content of other is to be copied into the sequence
{
    m_size = other.m_size;
    m_maxitems = other.m_maxitems;
    m_array = new ItemType[m_maxitems];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}
Sequence::~Sequence()
{
    delete[] m_array;
}
Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}
bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false.
{
    if (m_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Sequence::size() const    // Return the number of items in the sequence.
{
    return(m_size);
}
int Sequence::insert(int pos, const ItemType& value)
{
    if (0 <= pos && pos <= m_size && m_size < m_maxitems)
    {
        if (pos != m_size)
        {
            for (int i = pos; i < m_size; i++)
            {
                m_array[i + 1] = m_array[i]; // moves every item after pos one to the left
            }
        }
        m_array[pos] = value; // if pos == m_size no need to move the array elements
        m_size = m_size + 1;
        return (pos);

    }
    else
        return -1;
}
int Sequence::insert(const ItemType& value)
{
    int p = m_size;
    for (int i(0); i < m_size; i++)
    {
        if (m_array[i] >= value)
        {
            p = i;
            break;
        }
    }

    return(insert(p, value));
}
bool Sequence::erase(int pos)
{
    if (pos<0 || pos>=m_size)
    {
        return false;
    }
    for (int i(pos); i < m_size - 1; i++)
    {
        m_array[i] = m_array[i + 1];
    }
    m_size--;
    return true;
}
int Sequence::remove(const ItemType& value)
{
    int removed = 0;
    for (int i(0); i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            erase(i);
            removed++;
            i--;
        }
    }
    return(removed);
}
bool Sequence::get(int pos, ItemType& value) const
{
    if (pos >= 0 && pos < m_size)
    {
        value = m_array[pos];
        return true;
    }
    else
        return false;
}
bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >= 0 && pos < m_size)
    {
        m_array[pos] = value;
        return true;
    }
    else
        return false;
}
int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i(0); i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            p = i;
            break;
        }
        
    }
    return(p);
}
void Sequence::swap(Sequence& other)
{
    int swapsize = other.m_size;
    other.m_size = m_size;
    m_size = swapsize;

    int swapmaxitems = other.m_maxitems;
    other.m_maxitems = m_maxitems;
    m_maxitems = swapmaxitems;

    ItemType* swap = other.m_array;
    other.m_array = m_array;
    m_array = swap;
}



