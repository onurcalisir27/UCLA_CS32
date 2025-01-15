#include <stack>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc)); // push the starting pos.
    maze[sr][sc] = '!'; // mark the starting location as encountered.

    while (!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();
        int r = current.r();
        int c = current.c();

        if (r == er && c == ec) // check if the maze is solved
            return true;
        
        if (maze[r + 1][c] != 'X' && maze[r + 1][c] != '!') // check if can move south
        {
            coordStack.push(Coord(r + 1, c));
            maze[r + 1][c] = '!'; // mark cell as visited
        }
        if (maze[r][c + 1] != 'X' && maze[r][c + 1] != '!') // if can move east
        {
            coordStack.push(Coord(r, c + 1));
            maze[r][c + 1] = '!';
        }
        if (maze[r - 1][c] != 'X' && maze[r - 1][c] != '!') // if can move north
        {
            coordStack.push(Coord(r - 1, c));
            maze[r - 1][c] = '!';
        }
        if (maze[r][c - 1] != 'X' && maze[r][c - 1] != '!') // if can move west
        {
            coordStack.push(Coord(r, c - 1));
            maze[r][c - 1] = '!';
        }

    }
    return false;
}
