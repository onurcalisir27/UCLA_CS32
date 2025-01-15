#include "Player.h"

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0) return -1;
	int hole(0);
	cout << "Select a move, " << name() << ": ";
	cin >> hole;
	while (hole <= POT || hole > b.holes() || b.beans(s, hole) == 0)
	{
		if (hole <= POT || hole > b.holes())
			cout << "The hole number must be from 1 to " << b.holes() << endl;
		else if (b.beans(s, hole) == 0)
			cout << "There are no beans in that hole " << endl;
		cout << "Select a move, " << name() << ": ";
		cin >> hole;
	}
	return hole;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) > 0) // choose the first hole that is empty
			return i;
	}
	return -1; // if every hole is empty
}

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};
// Advance jumpy timer only after jumpInterval calls to elapsed
class JumpyTimer
{
public:
	JumpyTimer(int jumpInterval)
		: m_jumpInterval(jumpInterval), m_callsMade(0)
	{
		actualElapsed();
	}
	double elapsed()
	{
		m_callsMade++;
		if (m_callsMade == m_jumpInterval)
		{
			m_lastElapsed = m_timer.elapsed();
			m_callsMade = 0;
		}
		return m_lastElapsed;
	}
	double actualElapsed()
	{
		m_lastElapsed = m_timer.elapsed();
		return m_lastElapsed;
	}
private:
	Timer m_timer;
	int m_jumpInterval;
	int m_callsMade;
	int m_lastElapsed;
};
//========================================================================

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int value;
	int besthole;
	int depth = 0;

	JumpyTimer timer(1000);
	SmartMove(b, s, besthole, value, depth, timer);
	return besthole;
	
}

void SmartPlayer::SmartMove(const Board& b, Side s, int& besthole, int& value, int depth, JumpyTimer& timer) const
{
	if (timer.actualElapsed() > 4990 || b.beansInPlay(s) == 0 || depth > 6)
	{
		besthole = -1;
		value = evaluate(b);
		return;
	}
	
	int legal_move = 1; //legal move
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) == 0)
		{
			legal_move++; // first valid hole
			continue;
		}
			Side es; //endside
			Board brdcpy(b); // make a copy of the board
			int eh, h2, h3; // placeholder variables
			int newvalue; // value to compare with
			brdcpy.sow(s, i, es, eh); // play a move
			if (eh == POT) // could only be the sowing player pot bc sow skips the opponents pot
			{
				SmartMove(brdcpy, s, h3, newvalue, depth, timer); // gets another move
			}
			else
			{
				if (es == s && brdcpy.beans(s, eh) == 1 && brdcpy.beans(opponent(s), eh) > 0) // capturing move
				{
					brdcpy.moveToPot(opponent(s), eh, s);
					brdcpy.moveToPot(s, eh, s);
				}
				SmartMove(brdcpy, opponent(s), h2, newvalue, depth + 1, timer); // opponent turn now
				
			}
			if (i == legal_move)
			{
				value = newvalue;
				besthole = i;
			}
			if (s == SOUTH)
			{
				if (newvalue > value)
				{
					value = newvalue;
					besthole = i;
				}
			}
			else
			{
				if (newvalue < value)
				{
					value = newvalue;
					besthole = i;
				}
			}
			if (timer.elapsed() > 5000)
			{
				break;
			}
    }
	return;
}

int SmartPlayer::evaluate(const Board& b) const
{
	int north_beans = b.beansInPlay(NORTH) + b.beans(NORTH, 0);
	int south_beans = b.beansInPlay(SOUTH) + b.beans(SOUTH, 0);
	
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
	{
		if (south_beans > north_beans)
		{
			return 10000;
		}
		if (south_beans < north_beans)
		{
			return (-10000);
		}
		else
			return 0;
	}
	return (south_beans - north_beans);

}