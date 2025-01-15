
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec) // check if the maze is solved
        return true;
    maze[sr][sc] = '!'; // mark the starting location as encountered.

        if (maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != '!') // check if can move south
        {
            if (pathExists(maze, sr + 1, sc, er, ec)) return true;
        }
        if (maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != '!') // if can move east
        {
            if (pathExists(maze, sr, sc+1, er, ec)) return true;
        }
        if (maze[sr - 1][sc] != 'X' && maze[sr - 1][sc] != '!') // if can move north
        {
            if (pathExists(maze, sr-1, sc, er, ec)) return true;
        }
        if (maze[sr][sc - 1] != 'X' && maze[sr][sc - 1] != '!') // if can move west
        {
            if (pathExists(maze, sr, sc-1, er, ec)) return true;
        }
    return false;
}