#include "Board.h"


Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0) m_Holes = 1 + 1; //+1 is the player's pot
	else m_Holes = nHoles + 1;

	if (nInitialBeansPerHole < 0) nInitialBeansPerHole = 0;
	
	m_Beans = (nHoles * nInitialBeansPerHole * 2); // total number of beans in the game
	
	North.push_back(0); // set North's pot as 0
	South.push_back(0); // set South's pot as 0

	for (int i = 1; i < m_Holes; i++) // all other holes should start with the assigned number of beans
	{
		North.push_back(nInitialBeansPerHole);
		South.push_back(nInitialBeansPerHole);
	}
}
//Construct a Board with the indicated number of holes per side (not counting the pot)
//and initial number of beans per hole. If nHoles is not positive, act as if it were 1; 
//if nInitialBeansPerHole is negative, act as if it were 0.

int Board::holes() const
{
	return m_Holes - 1; // not counting the pot
}
//Return the number of holes on a side (not counting the pot).

int Board::beans(Side s, int hole) const
{
	if (hole < 0 || hole > holes()) return -1;
	
	if (s == NORTH) 
	{
		return North[hole];
	}
	else if (s == SOUTH)
	{
		return South[hole];
	}
	else
		return -1;
}
//Return the number of beans in the indicated hole or pot, or −1 if the hole number 
//is invalid.

int Board::beansInPlay(Side s) const
{
	int num_beans = 0;
	if (s == NORTH)
	{
		for (int i = 1; i < North.size(); i++) // not counting the pot
		{
			num_beans += North[i];
		}
		return num_beans;
	}
	else if (s == SOUTH)
	{
		for (int i = 1; i < South.size(); i++) // not counting the pot
		{
			num_beans += South[i];
		}
		return num_beans;
	}
    else 
		return -1;
}

//Return the total number of beans in all the holes on the indicated side, 
//not counting the beans in the pot.

int Board::totalBeans() const
{
	return m_Beans;
}
//Return the total number of beans in the game, including any in the pots.

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole <= 0 || hole > holes())
		return false;
	int next_hole = hole;
	Side next_side = s;

	if (s == NORTH) // North sowing
	{
		if (North[hole] == 0) return false;

		while (North[hole] > 0)
		{
			if (next_hole == 0) // Norths pot
				next_side = SOUTH; // Souths 1st hole is after North's pot

			if (next_side == NORTH)
			{
				if (next_hole > 0) // not North's pot
				{
					next_hole--;
					North[next_hole]++;
					
				}
			}
			if (next_side == SOUTH)
			{
				if (next_hole < m_Holes - 1) // Traversing South's Holes
				{
					next_hole++;
					South[next_hole]++;
				}
				else  // Skip South's Pot
				{
					next_side = NORTH;
					North[next_hole]++;
				}
			}
			North[hole]--;
		}

	}
	if (s == SOUTH)
	{
		if (South[hole] == 0)
			return false;
		while (South[hole] > 0)
		{
			if (next_hole == 0) // if at South's pot switch
			{
				next_side = NORTH;
				next_hole = m_Holes; // Norths hole after souths pot
			}
			if (next_side == SOUTH)
			{
				if (next_hole < m_Holes - 1)
				{
					next_hole++;
					South[next_hole]++;
				}
				else // next hole is pot
				{
					next_hole = 0;
					South[next_hole]++;
				}
			}
			if (next_side == NORTH)
			{
				if (next_hole > 1) // holes other than Norths pot
				{
					next_hole--;
					North[next_hole]++;
				}
				else // next hole is pot
				{
					next_side = SOUTH;
					South[next_hole]++; // curr_hole should be South's first hole;
				}
			}
			South[hole]--;
		}
	}
	if (next_hole == 0 || next_hole == m_Holes)
		next_hole = 0;

	endHole = next_hole;
	endSide = next_side;
	return true;
}
//If the hole indicated by(s, hole) is empty or invalid or a pot, this function 
//returns false without changing anything.
// Otherwise, it will return true after sowing 
//the beans : the beans are removed from hole(s, hole) and sown counterclockwise, 
//including s's pot if encountered, but skipping s's opponent's pot. 
//The function sets the parameters endSide and endHole to the side and hole where 
//the last bean was placed. (This function does not make captures or multiple turns; 
//different Kalah variants have different rules about these issues, so dealing 
//with them should not be the responsibility of the Board class.)

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole <= 0 || hole > holes())
		return false;
	if (potOwner != NORTH && potOwner != SOUTH)
		return false;

	if (s == NORTH)
	{
		if (potOwner == NORTH)
			North[0] += North[hole];
		if (potOwner == SOUTH)
			South[0] += North[hole];
		North[hole] = 0;
		return true;
	}
	else if (s == SOUTH)
	{
		if (potOwner == NORTH)
			North[0] += South[hole];
		if (potOwner == SOUTH)
			South[0] += South[hole];
		South[hole] = 0;
		return true;
	}
	else
		return false;

}
//If the indicated hole is invalid or a pot, return false without changing anything.
//Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwner
//and return true.

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole<0 || hole > holes() || beans < 0)
		return false;
	int initial_beans = 0;
	if (s == NORTH)
	{
		initial_beans = North[hole];
		North[hole] = beans;
	}
	if (s == SOUTH)
	{
		initial_beans = South[hole];
		South[hole] = beans;
	}
	else
		return false; // if invalid side
	m_Beans = m_Beans + beans - initial_beans;
	return true;
}
//If the indicated hole is invalid or beans is negative, this function returns false 
//without changing anything.Otherwise, it will return true after setting the number of beans
//in the indicated hole or pot to the value of the third parameter. 
//(This could change what beansInPlay and totalBeans return if they are called later.) 
//This function exists solely so that we and you can more easily test your program : 
//None of your code that implements the member functions of any class is allowed to call 
//this function directly or indirectly. (We'll show an example of its use below.)