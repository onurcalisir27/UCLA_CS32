#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north):m_Board(b), m_North(north), m_South(south)
{
	// initialize private members, Player south has the first move
}
//Construct a Game to be played with the indicated players on a copy of the board b.
//The player on the south side always moves first.
void Game::display() const
{
	cout << "     " << m_North->name() << "   " << endl;

	for (int i = 1; i <= m_Board.holes(); i++)
		cout << "  " << m_Board.beans(NORTH, i) << "  ";

	cout << endl;
	cout << m_Board.beans(NORTH, POT) << "";

	for (int i = 1; i <= m_Board.holes(); i++)
		cout << "    ";

	cout << "    " << m_Board.beans(SOUTH, POT) << endl;

	for (int i = 1; i <= m_Board.holes(); i++)
		cout << "  " << m_Board.beans(SOUTH, i) << "  ";

	cout << endl;
	cout << "     " << m_South->name() << "   " << endl;
}
//Display the game's board in a manner of your choosing, provided you show the names of the players and
	//a reasonable representation of the state of the board.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_Board.beansInPlay(NORTH) != 0 && m_Board.beansInPlay(SOUTH) != 0)
	{
		over = false;
		return;
	}
	over = true;
	if (over == true)
	{
		if (m_Board.beans(NORTH, POT) > m_Board.beans(SOUTH, POT))
		{
			hasWinner = true;
			winner = NORTH;
		}
		else if (m_Board.beans(NORTH, POT) < m_Board.beans(SOUTH, POT))
		{
			hasWinner = true;
			winner = SOUTH;
		}
		else
			hasWinner = false;
	}

}
//If the game is over(i.e., the move member function has been called and returned false), set over to true;
	//otherwise, set over to false and do not change anything else.If the game is over, set hasWinner to true
	//if the game has a winner, or false if it resulted in a tie.If hasWinner is set to false,
	//leave winner unchanged; otherwise, set it to the winning side.

bool Game::move(Side s)
{
	m_toMove = s;
	if (m_Board.beansInPlay(s) == 0 || m_Board.beansInPlay(opponent(s)) == 0) // checking if the game is over
		return false;
	Side es; // keep track of sow()
	int eh;
	if (s == SOUTH)
	{
		int choice = m_South->chooseMove(m_Board, s);
		if (m_South->isInteractive() == false)
			cout << "Player " << m_South->name() << " chooses hole: " << choice << endl;
		if (m_Board.sow(s, choice, es, eh)) // if sow() returns true
		{
			if (es == s) // check if the player gets another move
			{
				if (eh != POT && m_Board.beans(s, eh) == 1 && m_Board.beans(opponent(s), eh) > 0) //capturing move
				{
					m_Board.moveToPot(es, eh, es);
					m_Board.moveToPot(opponent(es), eh, es);
				}
				else if (eh == POT) // player gets another turn
				{
					display();
					if (m_Board.beansInPlay(s) != 0)
					{
						cout << "Player " << m_South->name() << " has another turn!" << endl;
						return move(s);
					}

				}
			}
		}
	}
	if (s == NORTH)
	{
		int choice = m_North->chooseMove(m_Board, s);
		if (m_North->isInteractive() == false)
			cout << "Player " << m_North->name() << " chooses hole: " << choice << endl;
		if (m_Board.sow(s, choice, es, eh)) // if sow() returns true
		{
			
			if (es == s) // check if the player gets another move
			{
				if (eh != POT && m_Board.beans(s, eh) == 1 && m_Board.beans(opponent(s), eh) > 0) //capturing move
				{
					
					m_Board.moveToPot(es, eh, es);
					m_Board.moveToPot(opponent(es), eh, es);
				}
				else if (eh == POT) // player gets another turn
				{
					display();
					if (m_Board.beansInPlay(s) != 0)
					{
						cout << "Player " << m_North->name() << " has another turn!" << endl;
						return move(s);
					}

				}
			}
		}
	}
	m_toMove = opponent(m_toMove);
	if (m_Board.beansInPlay(s) == 0 && m_Board.beansInPlay(opponent(s)) != 0) // if no moves possible.
	{
		display();
		for (int i = 1; i <= m_Board.holes(); i++)
		{
			m_Board.moveToPot(opponent(s), i, opponent(s));
			
		}
		return false;

	}
	
	return true;

}
//Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds 
	//from a hole and takes any additional turns required or completes a capture.Whenever the player gets 
	//an additional turn, you should display the board so someone looking at the screen can follow what's happening.
	//If the move can be completed, return true; if not, because the move is not yet completed but side s has no 
	//holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and 
	//return false.

void Game::play()
{
	bool over = false;
	bool hasWinner = false;
	Side winner;
	display();
	while (over == false)
	{
		move(m_toMove);
		display();
		if (m_South->isInteractive() == false && m_North->isInteractive() == false)
		{
			cout << "Press Enter to continue." << endl;
			cin.ignore(1000, '\n');
		}
		status(over, hasWinner, winner);
	}
	if (hasWinner == true)
	{
		if (winner == SOUTH)
		{
			cout << "Winner is " << m_South->name() << endl;
		}
		else
			cout << "Winner is " << m_North->name() << endl;
	}
	else
		cout << "Tie game" << endl;
}
//Play the game.Display the progress of the game in a manner of your choosing, provided that someone looking at
	//the screen can follow what's happening. If neither player is interactive, then to keep the display from 
	//quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to 
	//press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams 
	//is useful here.) Announce the winner at the end of the game. You can apportion to your liking the
	//responsibility for displaying the board between this function and the move function.
int Game::beans(Side s, int hole) const
{
	return m_Board.beans(s,hole);
}
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. 
	//This function exists so that we and you can more easily test your program.