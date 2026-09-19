#include <iostream>
#include <random>
#include <vector>

const int ROWS = 10;
const int COLS = 10;


//妈的，一直忘记定义函数时输入量需要定义类型
int randomInt(int minValue,int maxValue){
    static std::random_device randomDevice;
    static std::mt19937 randomEngine (randomDevice());
    std::uniform_int_distribution<int> distribution(minValue,maxValue);

    return distribution(randomEngine);
    //randomEngine 提供随机性，
    //distribution 把结果映射成 [minValue, maxValue] 范围内近似均匀分布的整数，
    //然后 return 返回这个整数
}


struct Position{
    int row;
    int col;
};


//还不是很理解，这种定义我还是先记下来再说，未来有需要再深化
enum class Cell{
    Free,
    Obstacle
};

//依旧不理解vector和这里的Grid初始化
//对于这样的嵌套逻辑，我始终无法很好的用流式的语言去表达，所以我不可能真的理解
//而且为什么这个初始化要放在main里面？我放在上面有啥问题不？
//我发现，如果把这个放在main中，很多函数的定义会出现Grid未定义的问题
using Grid = std::vector<std::vector<Cell>>;
Grid map(
    ROWS,
    std::vector<Cell>(
        COLS, 
        Cell::Free
    )
);


//Quary and Command：命令和查询分离，bool只判断是否状态，故为查询
//用position重写是否在地图内的代码
bool isInsideMap(Position a){
    return a.row>=0 &&
           a.col>=0 &&
           a.row < ROWS &&
           a.col < COLS;
}


bool isWalkable (
    //const Grid& map：const表示我只引用一下Grid类型的map，不修改
    //这里的&就是reference，指参考，这样就不用把整个map再重新输入一遍
    //&指的是把真实的东西拿过来，不去修正副本，修正副本改不了原型
    //Position a中的a，应该只是形式化的表达，表示我这里要输入一个Position类型的东西，但这个东西是什么名字我不知道，所以随便取个名为a
    //所以AI给的 Position position 其实只是更好看，对理解反而没什么帮助
    const Grid& map ,
    Position a
){
    return isInsideMap(a) && //这里的return insidemap只要输入一个a，不需要记录数据类型。数据类型是在定义函数时才需要规定的
           map[a.row][a.col]==Cell::Free;
    //注意&&的位置，先判断是否在地图里，再判断这个位置是否是空位，否则会陷入程序短路，部分程序不会被执行，这样的程序是不好的
}

//新的布尔值函数，让int更结构化，输入值为结构
bool isSamePosition (Position a , Position b){
    return a.row == b.row && a.col == b.col;
}

//似乎对于函数来说，小括号是istream，输入些parameter，然后在花括号内写运行的程序
//问题在于，不同的东西分号的位置也不同，有的在程序内部，有的居然在花括号外面……//

//随机合法坐标生成器·打包版
Position generateFreePosition(
    const Grid& map
){
    Position a{
        randomInt(0,ROWS-1),
        randomInt(0,COLS-1)
    };
    while(!isWalkable(map,a)){

        a.row = randomInt(0,ROWS-1);
        a.col = randomInt(0,COLS-1);
    }

    return a;
}

Position robot = generateFreePosition(map);
Position target = generateFreePosition(map);

//没招了，position如果放在main外面，robot又是未定义
//导致最后输出不了四个方向的性质
Position up{
    robot.row-1,
    robot.col
};

Position down{
    robot.row+1,
    robot.col
};

Position left{
    robot.row,
    robot.col-1
};

Position right{
    robot.row,
    robot.col+1
};

void generateObstacles (
    //这里的void指的是不需要反馈值，该函数的唯一作用就是修改map
    //对于void，不需要返回值
    Grid& map,
    int obstacleTarget
){
    int obstacleNum = 0;

    while (obstacleNum < obstacleTarget){

        int r = randomInt(0,ROWS-1);
        int c = randomInt(0,COLS-1);

        if (map[r][c] == Cell::Free){

            map[r][c] = Cell::Obstacle;
            obstacleNum ++; 
        }
    }
}


void renderMap(
    Grid& map,
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
                map[r][c] == Cell::Obstacle
            ){
                std::cout << '#';
            }
            
            else {
                std::cout << '.';
            }

        }
            std::cout << std::endl;
    }
}

int countValidNeighbors(
    const Grid& map,
    Position robot
){
    int count = 0;
    if (isWalkable(map,up)){
        count++;
    }
    if (isWalkable(map,down)){
        count++;
    }
    if (isWalkable(map,left)){
        count++;
    }
    if (isWalkable(map,right)){
        count++;
    }

    return count;
}


int main(){

    generateObstacles (
        map,
        20
    );

    //打印\n，让结果好看一点
    if (
        isSamePosition(robot,target)
    ){
        Position target = 
        generateFreePosition(map);
    }

    else {

        renderMap(
            map,
            robot,
            target
        );

        std::cout << "机器人与目标地坐标不重合\n";

        std::cout << "Robot: ("
                  << robot.row
                  << ", "
                  << robot.col
                  << ")\n";

        std::cout << "Target: ("
                  << target.row
                  << ", "
                  << target.col
                  << ")\n";
    }

    if (isWalkable(map, up)
    ){std::cout << "UP: FREE\n";
    }

    else {std::cout << "UP: BLOCKED\n";
    }


    if (isWalkable(map, down)
    ){std::cout << "DOWN: FREE\n";
    }

    else {std::cout << "DOWN: BLOCKED\n";
    }


    if (isWalkable(map, left)
    ){std::cout << "LEFT: FREE\n";
    }

    else {std::cout << "LEFT: BLOCKED\n";
    }


    if (isWalkable(map, right)
    ){std::cout << "RIGHT: FREE\n";
    }

    else {std::cout << "RIGHT: BLOCKED\n";
    }

    std::cout << "共有"
              << countValidNeighbors(map,robot)
              << "个Valid方向\n";

    return 0;
}