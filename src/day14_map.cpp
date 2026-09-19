#include <iostream>
#include <random>
#include <vector>

const int ROWS = 10;
const int COLS = 10;

struct Position{
    int row;
    int col;
};

enum class Cell{
    Free,
    Obstacle
};

enum class Direction{
    up,
    down,
    left,
    right
};

using Grid = std::vector<std::vector<Cell>>;
Grid grid(
    ROWS,
    std::vector<Cell>(
        COLS, 
        Cell::Free
    )
);


Position robot{2, 1};

bool isInsideMap(Position a){
    return a.row>=0 &&
           a.col>=0 &&
           a.row < ROWS &&
           a.col < COLS;
}

bool isWalkable (
    const Grid& gird ,
    Position a
){
    return isInsideMap(a) && 
           grid[a.row][a.col]==Cell::Free;
}


int countValidNeighbors(const Grid& grid, Position robot)
{
    int count = 0;

    Position up{robot.row - 1, robot.col};
    Position down{robot.row + 1, robot.col};
    Position left{robot.row, robot.col - 1};
    Position right{robot.row, robot.col + 1};

    if (isWalkable(grid, up)) count++;
    if (isWalkable(grid, down)) count++;
    if (isWalkable(grid, left)) count++;
    if (isWalkable(grid, right)) count++;

    return count;
}

Position calculateNextPosition(Position current, Direction direction)
{
    Position next = current;

    switch (direction) {
        case Direction::up:
            next.row--;
            break;
        case Direction::down:
            next.row++;
            break;
        case Direction::left:
            next.col--;
            break;
        case Direction::right:
            next.col++;
            break;
    }

    return next;
}

bool tryMove(const Grid& grid, Position& robot, Direction direction)
{
    Position next = calculateNextPosition(robot, direction);

    if (!isWalkable(grid, next)) {
        return false;
    }

    robot = next;
    return true;
}


int main(){
    grid[2][2] = Cell::Obstacle;

    if (tryMove(grid, robot, Direction::right)){
        std::cout << "可以向右移动\n"
                  << "当前机器人位置为："
                  << robot.row <<robot.col
                  << std::endl;
    } else{
        std::cout << "右边有障碍，不可移动";
    }
    
    return 0;

}