
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstddef>
#include <string>
#include <functional>
#include <utility>
#include <cstdlib>

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

std::string directionToText(Direction direction) {
    switch (direction) {
        case Direction::Up:
            return "上";
        case Direction::Down:
            return "下";
        case Direction::Left:
            return "左";
        case Direction::Right:
            return "右";
    }

    return "未知";
}

bool tryMove(
    const Grid& grid,
    Position& robot,
    Direction direction
) {
    Position before = robot;

    Position next =
        calculateNextPosition(robot, direction);

    bool moved = false;
    std::string reason;

    if (!isWalkable(grid, robot)) {
        reason = "起点不可通行";
    } else if (!isInsideMap(next)) {
        reason = "目标越界";
    } else if (!isWalkable(grid, next)) {
        reason = "目标是障碍";
    } else {
        robot = next;
        moved = true;
        reason = "可通行";
    }

    std::cout
        << "[动作] 前=("
        << before.row << ',' << before.col << ')'
        << " 方向=" << directionToText(direction)
        << " 候选=("
        << next.row << ',' << next.col << ')'
        << " 结果=" << (moved ? "成功" : "失败")
        << " 后=("
        << robot.row << ',' << robot.col << ')'
        << " 原因=" << reason << '\n';

    return moved;
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

    if (!isWalkable(grid, robot)) {
    std::cout << "机器人当前位置不可通行，无法执行\n";
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

std::vector<Position> getWalkableNeighbors(
    const Grid& grid,
    Position current
) {
    std::vector<Position> neighbors;

    if (!isWalkable(grid, current)) {
        return neighbors;
    }

    const std::vector<Direction> directions{
        Direction::Up,
        Direction::Down,
        Direction::Left,
        Direction::Right
    };

    for (std::size_t i = 0; i < directions.size(); i++) {
        Direction direction = directions[i];

        Position next = calculateNextPosition(
            current,
            direction
        );

        if (isWalkable(grid, next)) {
            neighbors.push_back(next);
        }
    }

    return neighbors;
}

bool canReach(
    const Grid& grid,
    Position start,
    Position target
) {
    if (!isWalkable(grid, start) ||
        !isWalkable(grid, target)) {
        return false;
    }

    std::queue<Position> pending;

    std::vector<std::vector<bool>> discovered(
        ROWS,
        std::vector<bool>(COLS, false)
    );

    discovered[start.row][start.col] = true;
    pending.push(start);

    while (!pending.empty()) {
        Position current = pending.front();
        pending.pop();

        std::cout << "正在检查：("
          << current.row << ", "
          << current.col << ")\n";

        if (isSamePosition(current, target)) {
            return true;
        }

        std::vector<Position> neighbors =
            getWalkableNeighbors(grid, current);

        for (std::size_t i = 0; i < neighbors.size(); i++) {
            Position next = neighbors[i];

            if (!discovered[next.row][next.col]) {
                discovered[next.row][next.col] = true;
                pending.push(next);
            }
        }
    }

    return false;
}

int shortestSteps(
    const Grid& grid,
    Position start,
    Position target
) {
    if (!isWalkable(grid, start) ||
        !isWalkable(grid, target)) {
        return -1;
    }

    std::queue<Position> pending;

    std::vector<std::vector<bool>> discovered(
        ROWS,
        std::vector<bool>(COLS, false)
    );

    std::vector<std::vector<int>> distance(
        ROWS,
        std::vector<int>(COLS, -1)
    );

    discovered[start.row][start.col] = true;
    distance[start.row][start.col] = 0;
    pending.push(start);

    while (!pending.empty()) {
        Position current = pending.front();
        pending.pop();

        if (isSamePosition(current, target)) {
            return distance[current.row][current.col];
        }

        std::vector<Position> neighbors =
            getWalkableNeighbors(grid, current);

        for (std::size_t i = 0; i < neighbors.size(); i++) {
            Position next = neighbors[i];

            if (!discovered[next.row][next.col]) {
                discovered[next.row][next.col] = true;

                distance[next.row][next.col] =
                    distance[current.row][current.col] + 1;

                std::cout << "首次发现：("
                          << next.row << ", "
                          << next.col << ")，步数："
                          << distance[next.row][next.col]
                          << '\n';

                pending.push(next);
            }
        }
    }

    return -1;
}



std::vector<Position> findShortestPath(
    const Grid& grid,
    Position start,
    Position target
) {
    if (!isWalkable(grid, start) ||
        !isWalkable(grid, target)) {
        return {};
    }

    std::queue<Position> pending;

    std::vector<std::vector<int>> distance(
        ROWS, std::vector<int>(COLS, -1)
    );

    std::vector<std::vector<Position>> parent(
        ROWS,
        std::vector<Position>(COLS, Position{-1, -1})
    );

    distance[start.row][start.col] = 0;
    pending.push(start);

    while (!pending.empty()) {
        Position current = pending.front();
        pending.pop();

        if (isSamePosition(current, target)) {
            break;
        }

        for (Position next :
             getWalkableNeighbors(grid, current)) {
            if (distance[next.row][next.col] != -1) {
                continue;
            }

            distance[next.row][next.col] =
                distance[current.row][current.col] + 1;

            parent[next.row][next.col] = current;

            pending.push(next);
        }
    }

    if (distance[target.row][target.col] == -1) {
        return {};
    }

    std::vector<Position> path;
    Position trace = target;

    while (!isSamePosition(trace, start)) {
        path.push_back(trace);
        trace = parent[trace.row][trace.col];
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

Grid makeTestMap() {
    Grid grid(
        ROWS,
        std::vector<Cell>(COLS, Cell::Obstacle)
    );

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            grid[row][col] = Cell::Free;
        }
    }

    grid[0][2] = Cell::Obstacle;
    grid[1][0] = Cell::Obstacle;
    grid[1][2] = Cell::Obstacle;
    grid[1][4] = Cell::Obstacle;
    grid[2][4] = Cell::Obstacle;
    grid[3][1] = Cell::Obstacle;
    grid[3][2] = Cell::Obstacle;

    return grid;
}

void check(
    bool condition,
    const std::string& name,
    int& failedCount
) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
        return;
    }

    ++failedCount;
    std::cout << "[FAIL] " << name << '\n';
}

int runChecks() {
    int failedCount = 0;

    // 第一组：正常规划与执行。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};
        Position target{3, 4};
        Position before = robot;

        std::vector<Position> path =
            findShortestPath(grid, robot, target);

        check(
            isSamePosition(robot, before),
            "规划不改变机器人位置",
            failedCount
        );

        check(
            path.size() == 8,
            "固定地图返回7步、8个坐标",
            failedCount
        );

        bool completed = executePath(grid, robot, path);

        check(
            completed && isSamePosition(robot, target),
            "执行完成并到达指定目标",
            failedCount
        );
    }

    // 第二组：终点被隔开。
    {
        Grid grid = makeTestMap();
        grid[3][3] = Cell::Obstacle;

        Position robot{0, 0};
        Position before = robot;

        std::vector<Position> path =
            findShortestPath(grid, robot, Position{3, 4});

        bool completed = executePath(grid, robot, path);

        check(
            path.empty() &&
            !completed &&
            isSamePosition(robot, before),
            "无路时返回空路径，执行失败且位置不变",
            failedCount
        );
    }

    // 第三组：合法起点与终点相同。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};
        Position before = robot;

        std::vector<Position> path =
            findShortestPath(grid, robot, robot);

        bool completed = executePath(grid, robot, path);

        check(
            path.size() == 1 &&
            completed &&
            isSamePosition(robot, before),
            "起终点相同时，零次移动并成功结束",
            failedCount
        );
    }

    // 第四组：路径起点与机器人位置不一致。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};
        Position before = robot;

        std::vector<Position> path{
            {0, 1}, {1, 1}
        };

        bool completed = executePath(grid, robot, path);

        check(
            !completed && isSamePosition(robot, before),
            "拒绝起点不一致的路径",
            failedCount
        );
    }

    // 第五组：先走一步，随后遇到非法跨格。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};

        std::vector<Position> path{
            {0, 0}, {0, 1}, {2, 1}
        };

        bool completed = executePath(grid, robot, path);

        check(
            !completed &&
            isSamePosition(robot, Position{0, 1}),
            "拒绝跨格，并保留已经完成的移动",
            failedCount
        );
    }

    // 第六组：规划后，原路线中新增障碍。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};

        std::vector<Position> path =
            findShortestPath(grid, robot, Position{3, 4});

        grid[2][2] = Cell::Obstacle;

        bool completed = executePath(grid, robot, path);

        check(
            !completed &&
            isSamePosition(robot, Position{2, 1}),
            "执行时检查当前地图，并停在障碍前",
            failedCount
        );
    }

    // 第七组：手动方向调用也不能穿过障碍。
    {
        Grid grid = makeTestMap();
        Position robot{0, 1};

        bool moved =
            tryMove(grid, robot, Direction::Right);

        check(
            !moved &&
            isSamePosition(robot, Position{0, 1}),
            "手动移动遇到障碍时位置不变",
            failedCount
        );
    }

    // 第八组：单坐标路径也必须具有合法起点。
    {
        Grid grid = makeTestMap();
        Position robot{1, 0};

        std::vector<Position> path{robot};

        bool completed = executePath(grid, robot, path);

        check(
            !completed &&
            isSamePosition(robot, Position{1, 0}),
            "拒绝位于障碍上的单坐标路径",
            failedCount
        );
    }

    // 第九组：方向合法，但下一格越界。
    {
        Grid grid = makeTestMap();
        Position robot{0, 0};

        std::vector<Position> path{
            {0, 0}, {-1, 0}
        };

        bool completed = executePath(grid, robot, path);

        check(
            !completed &&
            isSamePosition(robot, Position{0, 0}),
            "拒绝越界移动",
            failedCount
        );
    }

    std::cout << "失败检查数："
              << failedCount << '\n';

    if (failedCount == 0) {
        return 0;
    }

    return 1;
}

using Candidate = std::pair<int, char>;

void practicePriorityQueue() {
    std::priority_queue<
        Candidate,
        std::vector<Candidate>,
        std::greater<Candidate>
    > pending;

    // 处理 S 后发现的两个候选。
    pending.push(Candidate{8, 'A'});
    pending.push(Candidate{2, 'B'});

    Candidate current = pending.top();
    pending.pop();

    std::cout << "第一次取出："
              << current.second << ' '
              << current.first << '\n';

    // 处理 B 后，发现更便宜的 A，以及 T。
    pending.push(Candidate{3, 'A'});
    pending.push(Candidate{11, 'T'});

    current = pending.top();
    pending.pop();

    std::cout << "第二次取出："
              << current.second << ' '
              << current.first << '\n';

    // 处理 A 后，发现更便宜的 T。
    pending.push(Candidate{5, 'T'});

    // 展示此时容器里剩余的全部条目。
    while (!pending.empty()) {
        current = pending.top();
        pending.pop();

        std::cout << "剩余条目："
                  << current.second << ' '
                  << current.first << '\n';
    }
}

int manhattanDistance(Position a, Position b) {
    return std::abs(a.row - b.row)
         + std::abs(a.col - b.col);
}

struct SearchEntry {
    Position position;
    int g;
    int f;
};

struct LowerPriority {
    bool operator()(
        const SearchEntry& a,
        const SearchEntry& b
    ) const {
        return a.f > b.f;
    }
};

std::vector<Position> findPathAStar(
    const Grid& grid,
    Position start,
    Position target
) {
    if (!isWalkable(grid, start) ||
        !isWalkable(grid, target)) {
        return {};
    }

    std::vector<std::vector<int>> bestG(
        ROWS, std::vector<int>(COLS, -1)
    );

    std::vector<std::vector<Position>> parent(
        ROWS,
        std::vector<Position>(COLS, Position{-1, -1})
    );

    std::priority_queue<
        SearchEntry,
        std::vector<SearchEntry>,
        LowerPriority
    > pending;

    bestG[start.row][start.col] = 0;

    pending.push(SearchEntry{
        start,
        0,
        manhattanDistance(start, target)
    });

    bool found = false;

    while (!pending.empty()) {
        SearchEntry current = pending.top();
        pending.pop();

        Position position = current.position;

        if (current.g != bestG[position.row][position.col]) {
            continue;
        }

        if (isSamePosition(position, target)) {
            found = true;
            break;
        }

        for (Position next :
             getWalkableNeighbors(grid, position)) {
            int newG = current.g + 1;
            int oldG = bestG[next.row][next.col];

            if (oldG == -1 || newG < oldG) {
                bestG[next.row][next.col] = newG;
                parent[next.row][next.col] = position;

                int h = manhattanDistance(next, target);

                pending.push(SearchEntry{
                    next,
                    newG,
                    newG + h
                });
            }
        }
    }

    if (!found) {
        return {};
    }

    std::vector<Position> path;
    Position trace = target;

    while (!isSamePosition(trace, start)) {
        path.push_back(trace);
        trace = parent[trace.row][trace.col];
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

bool isValidPath(
    const Grid& grid,
    const std::vector<Position>& path,
    Position start,
    Position target
) {
    if (path.empty()) {
        return false;
    }

    if (!isSamePosition(path.front(), start) ||
        !isSamePosition(path.back(), target)) {
        return false;
    }

    for (Position position : path) {
        if (!isWalkable(grid, position)) {
            return false;
        }
    }

    for (std::size_t i = 1; i < path.size(); ++i) {
        int rowChange =
            std::abs(path[i].row - path[i - 1].row);

        int colChange =
            std::abs(path[i].col - path[i - 1].col);

        if (rowChange + colChange != 1) {
            return false;
        }
    }

    return true;
}

void checkSearchCase(
    const Grid& grid,
    Position start,
    Position target,
    int expectedSteps,
    const std::string& name,
    int& failedCount
) {
    std::vector<Position> bfsPath =
        findShortestPath(grid, start, target);

    std::vector<Position> astarPath =
        findPathAStar(grid, start, target);

    if (expectedSteps < 0) {
        check(
            bfsPath.empty() && astarPath.empty(),
            name + "：两者均返回空路径",
            failedCount
        );
        return;
    }

    check(
        isValidPath(grid, bfsPath, start, target) &&
        isValidPath(grid, astarPath, start, target),
        name + "：两条路径均合法",
        failedCount
    );

    std::size_t expectedSize = expectedSteps + 1;

    check(
        bfsPath.size() == expectedSize &&
        astarPath.size() == expectedSize,
        name + "：两者步数均符合预期",
        failedCount
    );
}

int runAStarChecks() {
    int failedCount = 0;

    Grid base = makeTestMap();

    checkSearchCase(
        base, {0, 0}, {3, 4}, 7,
        "可达样例", failedCount
    );

    Grid detour(
        ROWS,
        std::vector<Cell>(COLS, Cell::Free)
    );

    detour[0][1] = Cell::Obstacle;
    detour[1][1] = Cell::Obstacle;

    checkSearchCase(
        detour, {0, 0}, {0, 2}, 6,
        "绕路样例", failedCount
    );

    Grid blocked = makeTestMap();
    blocked[3][3] = Cell::Obstacle;

    checkSearchCase(
        blocked, {0, 0}, {3, 4}, -1,
        "不可达样例", failedCount
    );

    checkSearchCase(
        base, {0, 0}, {0, 0}, 0,
        "起终点相同", failedCount
    );

    checkSearchCase(
        base, {1, 0}, {1, 0}, -1,
        "相同但位于障碍", failedCount
    );

    checkSearchCase(
        base, {-1, 0}, {3, 4}, -1,
        "起点越界", failedCount
    );

    std::cout << "A* 失败检查数："
              << failedCount << '\n';

    if (failedCount == 0) {
        return 0;
    }

    return 1;
}

Grid makeFinalMap(bool detourOpen)
{
    Grid grid(
        ROWS,
        std::vector<Cell>(COLS, Cell::Obstacle)
    );

    const std::vector<Position> freeCells{
        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
        {2, 3}, {2, 5},
        {3, 3}, {3, 4}, {3, 5}
    };

    for (Position position : freeCells) {
        grid[position.row][position.col] = Cell::Free;
    }

    if (!detourOpen) {
        grid[2][5] = Cell::Obstacle;
    }

    return grid;
}

int main() 
{

return 0;

}