
#include<iostream>
#include<random>
#include<vector>

int randomInt (int minValue, int maxValue){
    static std::random_device randomDevice;
    static std::mt19937 randomEngine (randomDevice());
    std::uniform_int_distribution<int> distribution(minValue,maxValue);

    return distribution(randomEngine);
}

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
    Up,
    Down,
    Left,
    Right
};

using Grid = std::vector<std::vector<Cell>>;


bool isInsideMap(Position a){
    return a.row>=0 &&
           a.col>=0 &&
           a.row < ROWS &&
           a.col < COLS;
}

bool isWalkable (
    const Grid& grid ,
    Position position
){
    return isInsideMap(position) && 
           grid[position.row][position.col]==Cell::Free;
}


Position generateFreePosition(
    const Grid& grid
){
    Position position{
        randomInt(0,ROWS-1),
        randomInt(0,COLS-1)
    };
    while(!isWalkable(grid,position)){

        position.row = randomInt(0,ROWS-1);
        position.col = randomInt(0,COLS-1);
    }

    return position;
}


bool isSamePosition (Position a , Position b){
    return a.row == b.row && a.col == b.col;
}


Position calculateNextPosition(Position current, Direction direction)
{
    Position next = current;

    switch (direction) {
        case Direction::Up:
            next.row--;
            break;
        case Direction::Down:
            next.row++;
            break;
        case Direction::Left:
            next.col--;
            break;
        case Direction::Right:
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

bool commandToDirection(
    char command,
    Direction& direction
) {
    switch (command) {
        case 'w':
        case 'W':
            direction = Direction::Up;
            return true;

        case 's':
        case 'S':
            direction = Direction::Down;
            return true;

        case 'a':
        case 'A':
            direction = Direction::Left;
            return true;

        case 'd':
        case 'D':
            direction = Direction::Right;
            return true;

        default:
            return false;
    }
}

void generateObstacles (
    Grid& grid,
    int obstacleTarget
){
    int obstacleNum = 0;

    while (obstacleNum < obstacleTarget){

        int r = randomInt(0,ROWS-1);
        int c = randomInt(0,COLS-1);

        if (grid[r][c] == Cell::Free){

            grid[r][c] = Cell::Obstacle;
            obstacleNum ++; 
        }
    }
}

void renderMap(
    const Grid& grid,
    Position robot,
    Position target
){
    for (int r = 0; r < ROWS; r++) {

        for (int c = 0; c < COLS; c++) {

            if (
                r == robot.row && 
                c == robot.col
            ){
                std::cout << 'R';
            }
            
            else if (
                r == target.row && 
                c == target.col
            ){
                std::cout << 'T';
            }
            
            else if (
                grid[r][c] == Cell::Obstacle
            ){
                std::cout << '#';
            }
            
            else {
                std::cout << '.';
            }

        }
            std::cout << '\n';
    }
}

std::vector<Position> path{
    {5, 2},
    {5, 3},
    {4, 3},
    {4, 4},
    {4, 5},
    {5, 5},
    {5, 6}
};

bool stepToDirection(
    Position current,
    Position next,
    Direction& direction
) {
    int rowDifference = next.row - current.row;
    int colDifference = next.col - current.col;

    if (rowDifference == -1 && colDifference == 0) {
        direction = Direction::Up;
        return true;
    }

    if (rowDifference == 1 && colDifference == 0) {
        direction = Direction::Down;
        return true;
    }

    if (rowDifference == 0 && colDifference == -1) {
        direction = Direction::Left;
        return true;
    }

    if (rowDifference == 0 && colDifference == 1) {
        direction = Direction::Right;
        return true;
    }

    return false;
}

bool executePath(
    const Grid& grid,
    Position& robot,
    const std::vector<Position>& path
) {
    if (path.empty()) {
        std::cout << "路径为空，无法执行\n";
        return false;
    }

    if (!isSamePosition(robot, path.front())) {
        std::cout << "机器人不在路径起点\n";
        return false;
    }

    for (std::size_t i = 1; i < path.size(); i++) {
        Direction direction = Direction::Up;

        bool validStep = stepToDirection(
            robot,
            path[i],
            direction
        );

        if (!validStep) {
            std::cout << "路径中的这一步不合法，停止执行\n";
            return false;
        }

        bool moved = tryMove(grid, robot, direction);

        if (!moved) {
            std::cout << "下一格越界或存在障碍，停止执行\n";
            return false;
        }

        std::cout << "已到达：("
                  << robot.row << ", "
                  << robot.col << ")\n";
    }

    return true;
}

int main()
{
    Grid grid(
        ROWS,
        std::vector<Cell>(COLS, Cell::Free)
    );

    Position robot{5, 2};
    Position target = {5, 6};

    generateObstacles (
        grid,
        20
    );

    renderMap(grid, robot, target);

    bool completed = executePath(grid, robot, path);

    renderMap(grid, robot, target);

    if (completed && isSamePosition(robot, target)) {
        std::cout << "人工路径执行完成，机器人到达目标\n";
    }
    else {
        std::cout << "未到达目标，机器人停在：("
                << robot.row << ", "
                << robot.col << ")\n";
    }

    return 0;
}