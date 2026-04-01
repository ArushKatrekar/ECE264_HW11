// ***
// *** You MUST modify this file
// ***

#include "solver.h"
#include "list.h"
#include "mazehelper.h"
#include "path.h"

PathLL* solveMaze(Maze* m) {

    PathLL* successPaths = buildPaths();
    char* retval = malloc(((m->height * m->width) + 1) * sizeof(char));

    MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
    depthFirstSolve(m, mp, retval, 0, successPaths);

    free(retval);

    return successPaths;
}

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
                     PathLL* successPaths) {
    if (atEnd(curpos,m)) {
        path[step] = '\0';
        addNode(successPaths, path);
        return;
    }
    m->maze[curpos.ypos][curpos.xpos].visited = true;

    //North
    MazePos next = {curpos.xpos,curpos.ypos - 1};
    if (squareOK(next,m)) {
        path[step] = 'N';
        depthFirstSolve(m, next, path, step + 1, successPaths);
    }
    //South
    next = (MazePos){curpos.xpos, curpos.ypos + 1};
    if (squareOK(next,m)) {
        path[step] = 'S';
        depthFirstSolve(m, next, path, step + 1, successPaths);
    }
    //East
    next = (MazePos){curpos.xpos + 1, curpos.ypos};
    if (squareOK(next,m)) {
        path[step] = 'E';
        depthFirstSolve(m, next, path, step + 1, successPaths);
    }
    //West
    next = (MazePos){curpos.xpos - 1, curpos.ypos};
    if (squareOK(next,m)) {
        path[step] = 'W';
        depthFirstSolve(m, next, path, step + 1, successPaths);
    }
    m->maze[curpos.ypos][curpos.xpos].visited = false;

    return;
}
