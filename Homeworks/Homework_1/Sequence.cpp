#include "Sequence.h"

Sequence::Sequence():m_size(0) // Create an empty sequence (i.e., one whose size() is 0).
{

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
    if (0 <= pos && pos <= m_size && m_size < DEFAULT_MAX_ITEMS)
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
     //Insert value into the sequence so that it becomes the item at
    //position pos.  
    //The original item at position pos and those that
   //follow it end up at positions one greater than they were at before.
    //Return pos if 0 <= pos <= size() and the value could be
    //inserted.  (It might not be, if the sequence has a fixed capacity,
    //e.g., because it's implemented using a fixed-size array.)  Otherwise,
    //leave the sequence unchanged and return -1.  Notice that
    //if pos is equal to size(), the value is inserted at the end.
}
int Sequence::insert(const ItemType& value)
{

     //Let p be the smallest integer such that value <= the item at
     //position p in the sequence; 
     //if no such item exists (i.e.,
     //value > all items in the sequence), let p be size(). 
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

      //Insert
     //value into the sequence so that it becomes the item in position
     //p.  The original item in position p and those that follow it end
     //up at positions one greater than before.  Return p if the value
     //was actually inserted.  Return -1 if the value was not inserted
     //(perhaps because the sequence has a fixed capacity and is full).
}
bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size)
    {
        return false;
    }
    for (int i(pos); i < m_size - 1; i++)
    {
        m_array[i] = m_array[i + 1];
    }
    m_size--;
    return true;
    // If 0 <= pos < size(), remove the item at position pos from
     //the sequence (so that all items that followed that item end up at
     //positions one lower than they were at before), and return true.
     //Otherwise, leave the sequence unchanged and return false.
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
     //Erase all items from the sequence that == value.  Return the
     //number of items removed (which will be 0 if no item == value).
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
     //If 0 <= pos < size(), copy into value the item in position pos
     //of the sequence and return true.  Otherwise, leave value unchanged
     //and return false.
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
    // If 0 <= pos < size(), replace the item at position pos in the
 //sequence with value and return true.  Otherwise, leave the sequence
 //unchanged and return false.
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
    // Let p be the smallest integer such that value == the item at
     //position p in the sequence; if no such item exists, let p be -1.
     //Return p.
}
void Sequence::swap(Sequence& other)
{
    int swapsize = other.size();
    other.m_size = m_size;
    m_size = swapsize;

    for (int i(0); i < DEFAULT_MAX_ITEMS; i++)
    {
        ItemType swapped = other.m_array[i];
        other.m_array[i] = m_array[i];
        m_array[i] = swapped;
    }
    
     //Exchange the contents of this sequence with the other one.

}



