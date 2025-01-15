#include "RainfallList.h"


RainfallList::RainfallList():m_sequence()
{

}
// Create an empty rainfall list.

bool RainfallList::add(unsigned long rainfall)
{
	if (0 <= rainfall && rainfall <= 400)
	{
		if (m_sequence.insert(m_sequence.size(), rainfall) != -1)
		{
			return true;
		}
	}
		return false;
}
// If the rainfall is valid (a value from 0 to 400) and the rainfall list
// has room for it, add it to the rainfall list and return true.
// Otherwise, leave the rainfall list unchanged and return false.

bool RainfallList::remove(unsigned long rainfall)
{
	int remove = m_sequence.find(rainfall);
	if (remove != -1)
	{
		m_sequence.erase(remove);
		return true;
	}
	else
		return false;
}
// Remove one instance of the specified rainfall from the rainfall list.
// Return true if a rainfall was removed; otherwise false.

int RainfallList::size() const
{
	return(m_sequence.size());
}
// Return the number of rainfalls in the list.

unsigned long RainfallList::minimum() const
{
	
	if (m_sequence.size() == 0)
	{
		return(NO_RAINFALLS);
	}
	unsigned long min = NO_RAINFALLS;
	unsigned long other = 0;
	{
		for (int i(0); i < m_sequence.size(); i++)
		{
			m_sequence.get(i, other);
			if (other < min)
			{
				min = other;
			}
		}
		return(min);
	}
}
// Return the lowest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.

unsigned long RainfallList::maximum() const
{
	
	if (m_sequence.size() == 0)
	{
		return(NO_RAINFALLS);
	}
	unsigned long max = 0;
	unsigned long other = 0;
	{
		for (int i(0); i < m_sequence.size(); i++)
		{
			m_sequence.get(i, other);
			if (other > max)
			{
				max = other;
			}
		}
		return(max);
	}
	
}
// Return the highest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.
