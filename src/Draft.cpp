// #include <iostream>
// using namespace std;

// int main() {
//     int steps = 10;
//     char direction = 'N'; // N for North, S for South, E for East, W for West
//     int robotX =1, robotY = 1;

//     cout <<"the robot will move " << steps << " steps towards " << direction << endl;
//     cout <<"move directioin: " << direction << endl;
//     cout <<"robot a: (" << robotX << ", " << robotY << ")" << endl;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// int main (){
//     cout<<"============== Robot Navigation ========"<<endl;
//     int x , y ;
//     cout<<"please input the robot positionX: ";
//     cin>>x;
//     cout<<"please input the robot positionY: ";
//     cin>>y;
//     int a = x, b = y;
//     int rposition;
//     cout<<"robot a: ("<<a<<", "<<b<<")"<<endl;

//     return 0;



// }


// #include <iostream>
// using namespace std;
// int main() {
//     double a=3,b=4;
//     cout<<"a+b="<< a+b <<endl;
//     cout<<"a-b="<< a-b <<endl;
//     cout<<"a*b="<< a*b <<endl;
//     cout<<"a/b="<< a/b <<endl;

//     return 0;
// }


// #include <iostream>
// using namespace std;

// bool isInsideMap(int r, int c, int row, int cols){
//     return(r>=0 && r<row && c>=0 && c<cols);

// } 
   
// int main(){
//     int robotrow,robotcol,row,cols;
//     cout<<"please enter the row/cols of map"<<endl;
//     cin>>row>>cols;
//     cout<<"please enter the robot's initial a (row col): ";
//     cin>>robotrow>>robotcol;

//     // check the even/odd status of the robot's a
//     if (robotrow %2==0){
//         cout<<"robot is on even row"<<endl;
//     }else{
//         cout<<"robot is on odd row"<<endl;
//     }

//     if (robotcol %2==0){
//         cout<<"robot is on even col"<<endl;
//     }else{
//         cout<<"robot is on odd col"<<endl;
//     }

// // check where the robot is located on the map
//     if (robotrow^2+robotcol^2==0 || (robotrow==row-1 && robotcol==cols-1) || (robotrow==0 && robotcol==cols-1) || (robotrow==row-1 && robotcol==0)){
//         cout<<"robot is on the corner"<<endl;
//     } else if (robotrow==0 || robotrow==row-1 || robotcol==0 || robotcol==cols-1){
//         cout<<"robot is on the edge"<<endl;
//     } else if (isInsideMap(robotrow,robotcol,row,cols)==false){
//         cout<<"robot is outside the map"<<endl;
//     } else {
//         cout<<"robot is inside the map"<<endl;


//     }
    


//     return 0;
// }


// #include <iostream>
// using namespace std;

// //判断机器人是否在地图内
// bool isInsideMap(int r, int c, int row, int cols){
//     return(r>=0 && r<row && c>=0 && c<cols);
// }

// bool isValidMove()

// #include <iostream>
// using namespace std;

// int random



//----------------------------------------------------九月十日------------------------------------------------------------

// #include <iostream>
// using namespace std;

// const int row = 10;
// const int COLS = 10;

// char map[row][COLS];



//------------------------------------------
// #include <iostream>
// #include <random>
// using namespace std;

// //建立常量地图大小，便于阅读
// const int row = 10;
// const int COLS = 10;

// int randomInt(int minValue, int maxValue) {
//     static random_device randomDevice;
//     static mt19937 randomEngine(randomDevice());

//     uniform_int_distribution<int> distribution(minValue, maxValue);

//     return distribution(randomEngine);
// }

// //判断机器人是否在地图内
// bool isInsideMap(int r, int c) {
//     return r >= 0 &&
//            r < row &&
//            c >= 0 &&
//            c < COLS;
// }


// bool isValidMove(int r, int c, char map[row][COLS]) {

//     return isInsideMap(r, c) &&
//            map[r][c] != '#';
// }

// int main() {

//     char map[row][COLS];

//     // Initialize map
//     for (int r = 0; r < row; r++) {

//         for (int c = 0; c < COLS; c++) {
//             map[r][c] = '.';
//         }
//     }

//     // Generate obstacles
//     int obstacleCount = 0;

//     while (obstacleCount < 20) {

//         int r = randomInt(0, row - 1);
//         int c = randomInt(0, COLS - 1);

//         if (map[r][c] == '.') {

//             map[r][c] = '#';
//             obstacleCount++;
//         }
//     }

//     // Generate robot

//     int robotR = randomInt(0, row - 1);
//     int robotC = randomInt(0, COLS - 1);

//     while (map[robotR][robotC] != '.') {

//         robotR = randomInt(0, row - 1);
//         robotC = randomInt(0, COLS - 1);
//     }

//     map[robotR][robotC] = 'R';

//     // Generate target
//     int targetR = randomInt(0, row - 1);
//     int targetC = randomInt(0, COLS - 1);

//     while (map[targetR][targetC] != '.') {

//         targetR = randomInt(0, row - 1);
//         targetC = randomInt(0, COLS - 1);
//     }

//     map[targetR][targetC] = 'T';

//     // Print map
//     for (int r = 0; r < row; r++) {

//         for (int c = 0; c < COLS; c++) {
//             cout << map[r][c] << " ";
//         }

//         cout << endl;
//     }

//     cout << endl;

//     // Check available actions
//     cout << "Available movement:" << endl;

//     cout << "UP: "
//          << (isValidMove(robotR - 1, robotC, map)
//              ? "VALID" : "BLOCKED")
//          << endl;

//     cout << "DOWN: "
//          << (isValidMove(robotR + 1, robotC, map)
//              ? "VALID" : "BLOCKED")
//          << endl;

//     cout << "LEFT: "
//          << (isValidMove(robotR, robotC - 1, map)
//              ? "VALID" : "BLOCKED")
//          << endl;

//     cout << "RIGHT: "
//          << (isValidMove(robotR, robotC + 1, map)
//              ? "VALID" : "BLOCKED")
//          << endl;

//     return 0;
// }




// #include <iostream>
// #include<random>
// using namespace std;


// const int row = 10;
// const int COLS = 10;

// char map[row][COLS];

// int randomInt(int minValue, int maxValue){
//     static random_device randomDevice;
//     static mt19937 randomengine(randomDevice());
//     uniform_int_distribution<int> distribution(minValue, maxValue);

//     return distribution(randomengine);
// }


// bool isInsideMap(int r, int c){
//     return r>=0 && r<row && c>=0 && c<COLS;
// }

// //在给定的行、列信息以及地图信息后，判断这个行列是否在给定的地图内部，并判断该处是否有障碍物
// bool isWalkableCell(int r, int c, char map[row][COLS]){
//     return isInsideMap (r, c) && map[r][c] != '#';

// }

// int main(){

//     //Initialize Map
//     for (int r=0 ; r<row ; r++){
//         for (int c=0 ; c<COLS ; c++){
//             map[r][c]='.';
//         }
//     }



// } 


// #include<iostream>
// using namespace std;

// int robotR =4;
// int robotC =3;

// struct position_R {
//     int robotR;
//     int robotC;
// };
// int main (){
//     position_R p{robotR,robotC};
//     cout << p.robotR<<endl;
//     return 0;
// }


//-------------------------------2026.09.11-------------------------------

// #include <iostream>
// #include <random>
// #include <vector>
// //逐渐考虑删去using namespace std

// //initialize the size of Map / not to change
// const int ROWS = 6;
// const int COLS = 6;


// int randomInt (int minValue, int maxValue){
//     //didn't understand what does it mean……
//     static std::random_device randomDevice;
//     static std::mt19937 randomEngine (randomDevice());

//     std::uniform_int_distribution<int> distribution(minValue, maxValue);
//     //返回一个在均匀整数分布下的、由Engine产生的一个数？
//     return distribution(randomEngine);
//     //让 distribution 使用 randomEngine 生成一个符合当前范围规则的整数
//     //然后把这个整数返回
// }

// struct Position{
//     //更新：将过去int robotRow ; int robotCol 同类型的数据合并
//     //struct是一种结构，一种组织形式，想要表达的是一种东西长什么样
//     //而函数是一种执行，是做事情
//     //row col为单数，表示一个状态的单一位置
//     int row;
//     int col;
// };

// enum class Cell{
//     Free,
//     Obstacle
//     //部分格式和strcut类似
//     //这里的enum class不是在定义变量类型，而是在告诉程序，我要开始定义新的类型了
//     //而Cell就是定义出来的新的类型，这个类型只能由Free和Obstacle赋值
//     //创造一种新的类型 Cell，而这个类型允许的状态由我列出来
// };

// //将cell的内容保存在vector中，并双层嵌套，形成二维
// using Grid = std::vector<std::vector<Cell>>;

// int main(){

//     Grid map(
//         ROWS,
//         std::vector<Cell>(COLS, Cell::Free)
//     );
//     //为何用Grid去组织map，map还是以数组的形式呈现的:map[][]??
    
//     //设置障碍与计数
//     int obstacleNum = 0;

//      while (obstacleNum <20){
//         int r = randomInt(0,ROWS-1);
//         int c = randomInt(0,COLS-1);
//         if (map[r][c]==Cell::Free){
//             map[r][c] = Cell::Obstacle;
//             obstacleNum+=1;
//         }
//      }

//     //两个position：randomInt position内部赋值
//     //观感更好
//     Position robot{
//         randomInt(0,ROWS-1),
//         randomInt(0,COLS-1)
//     };

//     int adjustRobotnum =0;
//     while (map[robot.row][robot.col] == Cell::Obstacle){
//         robot.row = randomInt(0,ROWS-1);
//         robot.col = randomInt(0,COLS-1);

//         adjustRobotnum +=1;
//     }

//     Position target{
//         randomInt(0,ROWS-1),
//         randomInt(0,COLS-1)
//     };

//     int adjustTargetnum = 0;
//     while (map[target.row][target.col] == Cell::Obstacle ||
//     (target.row == robot.row &&
//      target.col == robot.col)
//     ) {
//     target.row = randomInt(0, ROWS - 1);
//     target.col = randomInt(0, COLS - 1);

//     adjustTargetnum +=1;
//     }

//     //Print the map:
//     // for (int r = 0; r < ROWS; r++) {

//     //     for (int c = 0; c < COLS; c++) {
//     //         if (map[r][c] == Cell::Free){
//     //             std::cout << '.';
//     //         }else if (map[r][c] == Cell::Obstacle){
//     //             std::cout << '#';
            
//     //         //写了个unreachable branch……
//     //         }else if (r == robot.row && c == robot.col){
//     //             std::cout << 'R';
//     //         }else {
//     //             std::cout << 'T';
//     //         }
//     //     }

//     //     std::cout << std::endl;
//     // }

//         for (int r = 0; r < ROWS; r++) {

//             //注意分层设计，上层的先判断，
//             //Cell的Free与Obstacle是本质，不能被覆盖，所以放在下层
//             for (int c = 0; c < COLS; c++) {
//                 if (r == robot.row && c == robot.col){
//                     std::cout << 'R';
//                 }else if (r == target.row && c == target.col) {
//                     std::cout << 'T';
//                 }else if (map[r][c] == Cell::Obstacle){
//                     std::cout << '#';
//                 }else {
//                     std::cout << '.';
//                 }

//             }
//             std::cout << std::endl;
//         }


//     std::cout << "目的地坐标已修正"
//               << adjustTargetnum
//               << "次";
//     std::cout << std::endl;

//     std::cout << "机器人坐标已修正"
//               << adjustRobotnum
//               << "次";
//     std::cout << std::endl;

//     //回退到简单ostream形式，复杂的struct输出形式不懂
//     std::cout << "Robot: ("
//               << robot.row
//               << ", "
//               << robot.col
//               << ")\n";

//     std::cout << "Target: ("
//               << target.row
//               << ", "
//               << target.col
//               << ")\n";

//     std::cout << "obstacleNum = "
//               << obstacleNum
//               << "\n";

//     return 0;
// }


//-----------------------------------2026.09.12---------------------------------------

// #include <iostream>
// #include <random>
// #include <vector>

// const int ROWS = 10;
// const int COLS = 10;


// //妈的，一直忘记定义函数时输入量需要定义类型
// int randomInt(int minValue,int maxValue){
//     static std::random_device randomDevice;
//     static std::mt19937 randomEngine (randomDevice());
//     std::uniform_int_distribution<int> distribution(minValue,maxValue);

//     return distribution(randomEngine);
//      //randomEngine 提供随机性，
//     //distribution 把结果映射成 [minValue, maxValue] 范围内近似均匀分布的整数，
//     //然后 return 返回这个整数
// }


// struct Position{
//     int row;
//     int col;
// };


// enum class Cell{
//     Free,
//     Obstacle
// };

// //依旧不理解vector和这里的Grid初始化
// //而且为什么这个初始化要放在main里面？我放在上面有啥问题不？
// //我发现，如果把这个放在main中，很多函数的定义会出现Grid未定义的问题
// using Grid = std::vector<std::vector<Cell>>;
// Grid map(
//     ROWS,
//     std::vector<Cell>(
//         COLS, 
//         Cell::Free
//     )
// );


// //Quary and Command：命令和查询分离，bool只判断是否状态，故为查询
// //用position重写是否在地图内的代码
// bool isInsideMap(Position a){
//     return a.row>=0 &&
//            a.col>=0 &&
//            a.row < ROWS &&
//            a.col < COLS;
// }


// bool isWalkable (
//     //const Grid& map：const表示我只引用一下Grid类型的map，不修改
//     //这里的&就是reference，指参考，这样就不用把整个map再重新输入一遍
//     //&指的是把真实的东西拿过来，不去修正副本，修正副本改不了原型
//     //Position a中的a，应该只是形式化的表达，表示我这里要输入一个Position类型的东西，但这个东西是什么名字我不知道，所以随便取个名为a
//     const Grid& map ,
//     Position a
// ){
//     return isInsideMap(a) && //这里的return insidemap只要输入一个a，不需要记录数据类型。数据类型是在定义函数时才需要规定的
//            map[a.row][a.col]==Cell::Free;
//     //注意&&的位置，先判断是否在地图里，再判断这个位置是否是空位，否则会陷入程序短路，部分程序不会被执行，这样的程序是不好的
// }

// //新的布尔值函数，让int更结构化，输入值为结构
// bool isSamePosition (Position a , Position b){
//     return a.row == b.row && a.col == b.col;
// }


// //随机合法坐标生成器·打包版
// Position generateFreePosition(
//     const Grid& map
// ){
//     Position a{
//         randomInt(0,ROWS-1),
//         randomInt(0,COLS-1)
//     };
//     while(!isWalkable(map,a)){

//         a.row = randomInt(0,ROWS-1);
//         a.col = randomInt(0,COLS-1);
//     }

//     return a;
// }

// Position robot = generateFreePosition(map);
// Position target = generateFreePosition(map);

// //没招了，position如果放在main外面，robot又是未定义
// //导致最后输出不了四个方向的性质
// Position up{
//     robot.row-1,
//     robot.col
// };

// Position down{
//     robot.row+1,
//     robot.col
// };

// Position left{
//     robot.row,
//     robot.col-1
// };

// Position right{
//     robot.row,
//     robot.col+1
// };

// void generateObstacles (
//     //这里的void指的是不需要反馈值，该函数的唯一作用就是修改map
//     //对于void，不需要返回值
//     Grid& map,
//     int obstacleTarget
// ){
//     int obstacleNum = 0;

//     while (obstacleNum < obstacleTarget){

//         int r = randomInt(0,ROWS-1);
//         int c = randomInt(0,COLS-1);

//         if (map[r][c] == Cell::Free){

//             map[r][c] = Cell::Obstacle;
//             obstacleNum ++; 
//         }
//     }
// }


// void renderMap(
//     Grid& map,
//     Position robot,
//     Position target
// ){
//     for (int r = 0; r < ROWS; r++) {

//         for (int c = 0; c < COLS; c++) {

//             if (
//                 r == robot.row && 
//                 c == robot.col
//             ){
//                 std::cout << 'R';
//             }
            
//             else if (
//                 r == target.row && 
//                 c == target.col
//             ){
//                 std::cout << 'T';
//             }
            
//             else if (
//                 map[r][c] == Cell::Obstacle
//             ){
//                 std::cout << '#';
//             }
            
//             else {
//                 std::cout << '.';
//             }

//         }
//             std::cout << std::endl;
//     }
// }

// int countValidNeighbors(
//     const Grid& map,
//     Position robot
// ){
//     int count = 0;
//     if (isWalkable(map,up)){
//         count++;
//     }
//     if (isWalkable(map,down)){
//         count++;
//     }
//     if (isWalkable(map,left)){
//         count++;
//     }
//     if (isWalkable(map,right)){
//         count++;
//     }

//     return count;
// }


// int main(){

//     generateObstacles (
//         map,
//         20
//     );

//     //打印\n，让结果好看一点
//     if (
//         isSamePosition(robot,target)
//     ){
//         Position target = 
//         generateFreePosition(map);
//     }

//     else {

//         renderMap(
//             map,
//             robot,
//             target
//         );

//         std::cout << "机器人与目标地坐标不重合\n";

//         std::cout << "Robot: ("
//                   << robot.row
//                   << ", "
//                   << robot.col
//                   << ")\n";

//         std::cout << "Target: ("
//                   << target.row
//                   << ", "
//                   << target.col
//                   << ")\n";
//     }

//     if (isWalkable(map, up)
//     ){std::cout << "UP: FREE\n";
//     }

//     else {std::cout << "UP: BLOCKED\n";
//     }


//     if (isWalkable(map, down)
//     ){std::cout << "DOWN: FREE\n";
//     }

//     else {std::cout << "DOWN: BLOCKED\n";
//     }


//     if (isWalkable(map, left)
//     ){std::cout << "LEFT: FREE\n";
//     }

//     else {std::cout << "LEFT: BLOCKED\n";
//     }


//     if (isWalkable(map, right)
//     ){std::cout << "RIGHT: FREE\n";
//     }

//     else {std::cout << "RIGHT: BLOCKED\n";
//     }

//     std::cout << "共有"
//               << countValidNeighbors(map,robot)
//               << "个Valid方向\n";

//     return 0;
// }



/*
对于Day7，我的逻辑是：
1.定义不变的地图大小 / 定义随机化程序
2.定义Position变量 / 新类型Cell
3.将Cell的vector定义为Grid
4.定义「判断位置是否在地图内」函数
5.定义「判断该点是否能放置RT」函数，需用到234
6.定义「判断RT是否在同一位置」函数，需用到2
7.定义「随机合法坐标生成器」，需用到1235
8.为R、T随机坐标 / 以R坐标锚定四面坐标Position
9.定义「随机障碍生成器」，需用到13

*/




// //------------------------------------九月十三日---------------------------------------
// #include <iostream>
// #include <random>
// #include <vector>

// const int ROWS = 10;
// const int COLS = 10;

// struct Position{
//     int row;
//     int col;
// };

// enum class Cell{
//     Free,
//     Obstacle
// };

// enum class Direction{
//     up,
//     down,
//     left,
//     right
// };

// using Grid = std::vector<std::vector<Cell>>;
// Grid grid(
//     ROWS,
//     std::vector<Cell>(
//         COLS, 
//         Cell::Free
//     )
// );


// Position robot{2, 1};

// bool isInsideMap(Position a){
//     return a.row>=0 &&
//            a.col>=0 &&
//            a.row < ROWS &&
//            a.col < COLS;
// }

// bool isWalkable (
//     const Grid& gird ,
//     Position a
// ){
//     return isInsideMap(a) && 
//            grid[a.row][a.col]==Cell::Free;
// }


// int countValidNeighbors(const Grid& grid, Position robot)
// {
//     int count = 0;

//     Position up{robot.row - 1, robot.col};
//     Position down{robot.row + 1, robot.col};
//     Position left{robot.row, robot.col - 1};
//     Position right{robot.row, robot.col + 1};

//     if (isWalkable(grid, up)) count++;
//     if (isWalkable(grid, down)) count++;
//     if (isWalkable(grid, left)) count++;
//     if (isWalkable(grid, right)) count++;

//     return count;
// }

// Position calculateNextPosition(Position current, Direction direction)
// {
//     Position next = current;

//     switch (direction) {
//         case Direction::up:
//             next.row--;
//             break;
//         case Direction::down:
//             next.row++;
//             break;
//         case Direction::left:
//             next.col--;
//             break;
//         case Direction::right:
//             next.col++;
//             break;
//     }

//     return next;
// }

// bool tryMove(const Grid& grid, Position& robot, Direction direction)
// {
//     Position next = calculateNextPosition(robot, direction);

//     if (!isWalkable(grid, next)) {
//         return false;
//     }

//     robot = next;
//     return true;
// }


// int main(){
//     grid[2][2] = Cell::Obstacle;

//     if (tryMove(grid, robot, Direction::right)){
//         std::cout << "可以向右移动\n"
//                   << "当前机器人位置为："
//                   << robot.row <<robot.col
//                   << std::endl;
//     } else{
//         std::cout << "右边有障碍，不可移动";
//     }
    
//     return 0;

// }




// #include<iostream>
// #include<random>
// #include<vector>

// int randomInt (int minValue, int maxValue){
//     static std::random_device randomDevice;
//     static std::mt19937 randomEngine (randomDevice());
//     std::uniform_int_distribution<int> distribution(minValue,maxValue);

//     return distribution(randomEngine);
// }

// const int ROWS = 10;
// const int COLS = 10;

// struct Position{
//     int row;
//     int col;
// };

// enum class Cell{
//     Free,
//     Obstacle
// };

// enum class Direction{
//     Up,
//     Down,
//     Left,
//     Right
// };

// using Grid = std::vector<std::vector<Cell>>;


// bool isInsideMap(Position a){
//     return a.row>=0 &&
//            a.col>=0 &&
//            a.row < ROWS &&
//            a.col < COLS;
// }

// bool isWalkable (
//     const Grid& grid ,
//     Position position
// ){
//     return isInsideMap(position) && 
//            grid[position.row][position.col]==Cell::Free;
// }


// Position generateFreePosition(
//     const Grid& grid
// ){
//     Position position{
//         randomInt(0,ROWS-1),
//         randomInt(0,COLS-1)
//     };
//     while(!isWalkable(grid,position)){

//         position.row = randomInt(0,ROWS-1);
//         position.col = randomInt(0,COLS-1);
//     }

//     return position;
// }


// bool isSamePosition (Position a , Position b){
//     return a.row == b.row && a.col == b.col;
// }


// Position calculateNextPosition(Position current, Direction direction)
// {
//     Position next = current;

//     switch (direction) {
//         case Direction::Up:
//             next.row--;
//             break;
//         case Direction::Down:
//             next.row++;
//             break;
//         case Direction::Left:
//             next.col--;
//             break;
//         case Direction::Right:
//             next.col++;
//             break;
//     }

//     return next;
// }

// bool tryMove(const Grid& grid, Position& robot, Direction direction)
// {
//     Position next = calculateNextPosition(robot, direction);

//     if (!isWalkable(grid, next)) {
//         return false;
//     }

//     robot = next;
//     return true;
// }

// bool commandToDirection(
//     char command,
//     Direction& direction
// ) {
//     switch (command) {
//         case 'w':
//         case 'W':
//             direction = Direction::Up;
//             return true;

//         case 's':
//         case 'S':
//             direction = Direction::Down;
//             return true;

//         case 'a':
//         case 'A':
//             direction = Direction::Left;
//             return true;

//         case 'd':
//         case 'D':
//             direction = Direction::Right;
//             return true;

//         default:
//             return false;
//     }
// }

// void generateObstacles (
//     //这里的void指的是不需要反馈值，该函数的唯一作用就是修改map
//     //对于void，不需要返回值
//     Grid& grid,
//     int obstacleTarget
// ){
//     int obstacleNum = 0;

//     while (obstacleNum < obstacleTarget){

//         int r = randomInt(0,ROWS-1);
//         int c = randomInt(0,COLS-1);

//         if (grid[r][c] == Cell::Free){

//             grid[r][c] = Cell::Obstacle;
//             obstacleNum ++; 
//         }
//     }
// }

// void renderMap(
//     Grid& grid,
//     Position robot,
//     Position target
// ){
//     for (int r = 0; r < ROWS; r++) {

//         for (int c = 0; c < COLS; c++) {

//             if (
//                 r == robot.row && 
//                 c == robot.col
//             ){
//                 std::cout << 'R';
//             }
            
//             else if (
//                 r == target.row && 
//                 c == target.col
//             ){
//                 std::cout << 'T';
//             }
            
//             else if (
//                 grid[r][c] == Cell::Obstacle
//             ){
//                 std::cout << '#';
//             }
            
//             else {
//                 std::cout << '.';
//             }

//         }
//             std::cout << '\n';
//     }
// }

// int main()
// {
//     Grid grid(
//         ROWS,
//         std::vector<Cell>(COLS, Cell::Free)
//     );

//     generateObstacles (
//         grid,
//         20
//     );

//     Position robot = generateFreePosition(grid);
//     Position target = generateFreePosition(grid);  


//     if (
//         isSamePosition(robot,target)
//     ){
//         Position target = 
//         generateFreePosition(grid);
//     }


//     while (true) {
//         renderMap(grid, robot, target);

//         std::cout << "机器人位置：("
//                   << robot.row << ", "
//                   << robot.col << ")\n";

//         std::cout << "请输入 W/A/S/D 移动，Q 退出：";

//         char command;
//         std::cin >> command;

//         if (command == 'q' || command == 'Q') {
//             std::cout << "导航结束\n";
//             break;
//         }

//         Direction direction = Direction::Up;
//         bool hasValidDirection = true;

//         switch (command) {
//             case 'w':
//             case 'W':
//                 direction = Direction::Up;
//                 break;

//             case 's':
//             case 'S':
//                 direction = Direction::Down;
//                 break;

//             case 'a':
//             case 'A':
//                 direction = Direction::Left;
//                 break;

//             case 'd':
//             case 'D':
//                 direction = Direction::Right;
//                 break;

//             default:
//                 hasValidDirection = false;
//                 break;
//         }

//         if (!hasValidDirection) {
//             std::cout << "未知命令，请重新输入\n\n";
//             continue;
//         }

//         if (tryMove(grid, robot, direction)) {
//             std::cout << "移动成功\n\n";
//         }
//         else {
//             std::cout << "移动失败：目标位置越界或存在障碍物\n\n";
//         }
//     }

//     return 0;
// }




// #include<iostream>
// #include<random>
// #include<vector>

// int randomInt (int minValue, int maxValue){
//     static std::random_device randomDevice;
//     static std::mt19937 randomEngine (randomDevice());
//     std::uniform_int_distribution<int> distribution(minValue,maxValue);

//     return distribution(randomEngine);
// }

// const int ROWS = 10;
// const int COLS = 10;

// struct Position{
//     int row;
//     int col;
// };

// enum class Cell{
//     Free,
//     Obstacle
// };

// enum class Direction{
//     Up,
//     Down,
//     Left,
//     Right
// };

// using Grid = std::vector<std::vector<Cell>>;


// bool isInsideMap(Position a){
//     return a.row>=0 &&
//            a.col>=0 &&
//            a.row < ROWS &&
//            a.col < COLS;
// }

// bool isWalkable (
//     const Grid& grid ,
//     Position position
// ){
//     return isInsideMap(position) && 
//            grid[position.row][position.col]==Cell::Free;
// }


// Position generateFreePosition(
//     const Grid& grid
// ){
//     Position position{
//         randomInt(0,ROWS-1),
//         randomInt(0,COLS-1)
//     };
//     while(!isWalkable(grid,position)){

//         position.row = randomInt(0,ROWS-1);
//         position.col = randomInt(0,COLS-1);
//     }

//     return position;
// }


// bool isSamePosition (Position a , Position b){
//     return a.row == b.row && a.col == b.col;
// }


// Position calculateNextPosition(Position current, Direction direction)
// {
//     Position next = current;

//     switch (direction) {
//         case Direction::Up:
//             next.row--;
//             break;
//         case Direction::Down:
//             next.row++;
//             break;
//         case Direction::Left:
//             next.col--;
//             break;
//         case Direction::Right:
//             next.col++;
//             break;
//     }

//     return next;
// }

// bool tryMove(const Grid& grid, Position& robot, Direction direction)
// {
//     Position next = calculateNextPosition(robot, direction);

//     if (!isWalkable(grid, next)) {
//         return false;
//     }

//     robot = next;
//     return true;
// }

// bool commandToDirection(
//     char command,
//     Direction& direction
// ) {
//     switch (command) {
//         case 'w':
//         case 'W':
//             direction = Direction::Up;
//             return true;

//         case 's':
//         case 'S':
//             direction = Direction::Down;
//             return true;

//         case 'a':
//         case 'A':
//             direction = Direction::Left;
//             return true;

//         case 'd':
//         case 'D':
//             direction = Direction::Right;
//             return true;

//         default:
//             return false;
//     }
// }

// bool stepToDirection(
//     Position current,
//     Position next,
//     Direction& direction
// ) {
//     int rowDifference = next.row - current.row;
//     int colDifference = next.col - current.col;

//     if (rowDifference == -1 && colDifference == 0) {
//         direction = Direction::Up;
//         return true;
//     }

//     if (rowDifference == 1 && colDifference == 0) {
//         direction = Direction::Down;
//         return true;
//     }

//     if (rowDifference == 0 && colDifference == -1) {
//         direction = Direction::Left;
//         return true;
//     }

//     if (rowDifference == 0 && colDifference == 1) {
//         direction = Direction::Right;
//         return true;
//     }

//     return false;
// }

// bool executePath(
//     const Grid& grid,
//     Position& robot,
//     const std::vector<Position>& path
// ) {
//     if (path.empty()) {
//         std::cout << "路径为空，无法执行\n";
//         return false;
//     }

//     if (!isSamePosition(robot, path.front())) {
//         std::cout << "机器人当前位置与路径起点不一致\n";
//         return false;
//     }

//     for (std::size_t i = 1; i < path.size(); i++) {
//         Direction direction;

        
//     if (!stepToDirection(robot, path[i], direction)) {
//         std::cout << "路径中的两个位置不相邻，停止执行\n";
//         return false;
//     }

//     if (!tryMove(grid, robot, direction)) {
//         std::cout << "下一步存在障碍或超出地图，停止执行\n";
//         return false;
//     }

//     std::cout << "已到达：("
//             << robot.row << ", "
//             << robot.col << ")\n";
//     }

//     return true;
// }

// void generateObstacles (
//     Grid& grid,
//     int obstacleTarget
// ){
//     int obstacleNum = 0;

//     while (obstacleNum < obstacleTarget){

//         int r = randomInt(0,ROWS-1);
//         int c = randomInt(0,COLS-1);

//         if (grid[r][c] == Cell::Free){

//             grid[r][c] = Cell::Obstacle;
//             obstacleNum ++; 
//         }
//     }
// }

// void renderMap(
//     const Grid& grid,
//     Position robot,
//     Position target
// ){
//     for (int r = 0; r < ROWS; r++) {

//         for (int c = 0; c < COLS; c++) {

//             if (
//                 r == robot.row && 
//                 c == robot.col
//             ){
//                 std::cout << 'R';
//             }
            
//             else if (
//                 r == target.row && 
//                 c == target.col
//             ){
//                 std::cout << 'T';
//             }
            
//             else if (
//                 grid[r][c] == Cell::Obstacle
//             ){
//                 std::cout << '#';
//             }
            
//             else {
//                 std::cout << '.';
//             }

//         }
//             std::cout << '\n';
//     }
// }

// int main()
// {
//     Grid grid(
//         ROWS,
//         std::vector<Cell>(COLS, Cell::Free)
//     );

//     Position robot{5, 2};
//     Position target{5, 6};

//     std::vector<Position> path{
//         {5, 2},
//         {5, 3},
//         {4, 3},
//         {4, 4},
//         {4, 5},
//         {5, 5},
//         {5, 6}
//     };

//     while (true) {
//         renderMap(grid, robot, target);

//         std::cout << "机器人位置：("
//                   << robot.row << ", "
//                   << robot.col << ")\n";

//         std::cout << "请输入 W/A/S/D 移动, Q 退出：";

//         char command;
//         std::cin >> command;

//         if (command == 'q' || command == 'Q') {
//             std::cout << "导航结束\n";
//             break;
//         }

//         Direction direction;

//         if (!commandToDirection(command, direction)) {
//             std::cout << "未知命令，请重新输入\n\n";
//             continue;
//         }

//         if (tryMove(grid, robot, direction)) {
//              std::cout << "移动成功\n\n";

//             if (isSamePosition(robot, target)) {
//                 renderMap(grid, robot, target);
//                 std::cout << "机器人已到达目标，导航成功！\n";
//                 break;
//             }
//         }
//         else {
//             std::cout << "移动失败：目标位置越界或存在障碍物\n\n";
//         }
//     }

//     return 0;
// }


// #include<iostream>


// const int ROWS = 10;
// const int COLS = 10;

// enum class Cell{
//     Free,
//     Obstacles
// };

// struct Position{
//     int row;
//     int col;
// };

// enum class Direction{
//     Up,
//     Down,
//     Left,
//     Right
// };

// using Grid = 
//     std::vector<std::vector<Cell>>;

// bool isInsideMap(
//     Position position
// ){
//     return position.row >= 0 &&
//            position.row < ROWS &&
//            position.col >=0 &&
//            position.col < COLS;
// }

// bool isWalkbale(
//     const Grid& grid, 
//     Position position
// ){
//     return isInsideMap(position) && 
//            grid[position.row][position.col] == Cell::Free;
// }


// bool commandToDirection(
//     char command,
//     Direction& direction
// ){
//     switch (command){
//         case 'w':
//         case 'W':
//             direction = Direction::Up;
//             return true;

//         case 's':
//         case 'S':
//             direction = Direction::Down;
//             return true;

//         case 'a':
//         case 'A':
//             direction = Direction::Left;
//             return true;

//         case 'd':
//         case 'D':
//             direction = Direction::Right;
//             return true;

//         default:
//             return false;
// }

// Position calculateNextPosition(
//     Position current, 
//     Direction direction
// ){
//     Position next = current;
//     switch (direction){
//         case Direction::Up:
//             next.row --;
//             break;
//         case Direction::Down:
//             next.row ++;
//             break;
//         case Direction::Left:
//             next.col --;
//             break;
//         case Direction::Right:
//             next.row ++;
//             break;
//     }

//     return next;
// }


// bool tryMove(
//     const Grid& grid, 
//     Position robot, 
//     Direction direction
// ){
    
// }