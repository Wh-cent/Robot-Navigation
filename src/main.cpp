
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
    //这里的void指的是不需要反馈值，该函数的唯一作用就是修改map
    //对于void，不需要返回值
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
    Grid& grid,
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

int main()
{
    Grid grid(
        ROWS,
        std::vector<Cell>(COLS, Cell::Free)
    );

    generateObstacles (
        grid,
        20
    );

    Position robot = generateFreePosition(grid);
    Position target = generateFreePosition(grid);  


    if (
        isSamePosition(robot,target)
    ){
        Position target = 
        generateFreePosition(grid);
    }


    while (true) {
        renderMap(grid, robot, target);

        std::cout << "机器人位置：("
                  << robot.row << ", "
                  << robot.col << ")\n";

        std::cout << "请输入 W/A/S/D 移动，Q 退出：";

        char command;
        std::cin >> command;

        if (command == 'q' || command == 'Q') {
            std::cout << "导航结束\n";
            break;
        }

        Direction direction = Direction::Up;
        bool hasValidDirection = true;

        switch (command) {
            case 'w':
            case 'W':
                direction = Direction::Up;
                break;

            case 's':
            case 'S':
                direction = Direction::Down;
                break;

            case 'a':
            case 'A':
                direction = Direction::Left;
                break;

            case 'd':
            case 'D':
                direction = Direction::Right;
                break;

            default:
                hasValidDirection = false;
                break;
        }

        if (!hasValidDirection) {
            std::cout << "未知命令，请重新输入\n\n";
            continue;
        }

        if (tryMove(grid, robot, direction)) {
            std::cout << "移动成功\n\n";
        }
        else {
            std::cout << "移动失败：目标位置越界或存在障碍物\n\n";
        }
    }

    return 0;
}