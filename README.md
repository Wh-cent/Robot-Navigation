程序 LOGIC

# Part 1: 前置内容

目前，地图的ROWS与COLS属于“手动输入不变量”

# Part 2: 函数逻辑


## isInsideMap
- 目的：判断某物是否在地图内

- 逻辑：输入（
    机器人/目标等「Position结构」的坐标信息
）{
    只用输入Position坐标信息即可
    因为地图Size是const量，无需输入
    比较输入的position与Grip的长宽

}   输出：bool值（判断类）




## isWalkable
- 目的：判断该点位置是否合理「在内部+FREE」

- 逻辑：输入（
    Position坐标信息 && const 地图信息
）{
    需要借助insideMap的逻辑，加上对地图信息本身的判断

}   输出：bool值



## generateFreePosition
- 目的：随机生成坐标信息

- 逻辑：输入（
    const 地图信息
）{
    在该函数内部定义Position position，用随机器直接赋值
    然后判断该随机值是否合理，即是否满足 Walkable
    只要不满足，就一直随机，所以用while循环
    - 若isWalkable函数返回值为否，则！为真，执行循环

}   输出：在该函数内部随机出的position信息



## isSamePosition
- 目的：判断随机生成的坐标是否重合

- 逻辑：输入（
    需要比较的两个 position 信息
）{
    比较 position 的两个信息点
    直接返回比较结果的bool值

}   输出：bool值



## calculateNextPosition
- 目的：计算在指定移动方向下的未来坐标信息，不直接改变原 position，起缓冲作用

- 逻辑：输入（
    拷贝一份当前robot的坐标信息 && 指定移动方向
）{
    关键：先将输入的坐标信息存储在 函数内部的next position中
    使用switch，对 枚举类Direction 进行判断
    不同case下，对next坐标作修改

}   输出：未来预期坐标信息


## tryMove
- 目的：基于未来预期坐标信息，判断该坐标是否合理，若合理，则赋值给 robot

- 逻辑：输入（
    const 地图信息 && 外部robot坐标信息 && 指定移动方向
）{
    使用 calculateNextPosition 函数，得到未来预期坐标信息
    使用 isWalkable 判断该预期坐标是否合理
    - 若合理，则赋值给外部robot坐标
    - 若不合理，则返回「否」

}   输出：bool值「有概率修改外部坐标信息」



## commandToDirection
- 目的：判断用户输入的command是否合理，若合理，则转化为指定移动坐标

- 逻辑：输入（
    command信息 && 外部指定移动方向信息
）{
    由于direction也是枚举类，使用switch-case进行分类判断
    - 对不同合理的command，吸纳大小写广泛输入形式，修改外部方向信息，并返回true
    - 若command不合理，则返回false

}   输出：bool值「有概率修改外部指定移动坐标信息」




## generateObstacles
- 目的：随机生成障碍物

- 逻辑：输入（
    外部地图信息 && 指定障碍物生成数量
）{
    先生成计数器，进入循环体
    由于循环次数较多，使用while判断「数量达不到指定数量」
    - 地图上随机一个坐标，判断是否有障碍物
    - 若「if」没有，则将该点改为障碍物，计数器加一

}   输出：void




## renderMap
- 目的：渲染地图

- 逻辑：输入（
    const 地图信息 && robot和target坐标信息
）{
    两层For循环搭建横纵坐标的生成骨架
    - ROWS
    - COLS
    用横纵信息与输入的坐标/地图信息进行匹配
    if / else if / else if / else顺序筛查

}   输出：void「执行该函数就是在输出」


# Part 3: main函数逻辑
1. 使用vector初始化地图，在该地图上生成指定数量的障碍物
2. 避开障碍物，随机生成robot和target坐标，直至二者不相同
3. while（true）进行robot实时移动程序
- 实时渲染地图 / 打印robot实时坐标 / 输入小提示
- 指令输入控制
    - 初始化command，输入command
    - 判断该command是否合法，
        1. 退出指令优先级最高
        2. 错误方向指令判断其次
        3. 正确方向指令更次，并进一步判断该合法指令是否指向合理的移动
            若不合理，则提示无法移动，进入新的while循环



# Part 4: 逻辑补丁
1. 函数定义中使用的地图信息是基于main函数中修改后的信息输入的，不是从上至下未修改的初始化地图

2. 只要涉及到 Position信息是否合理，就需要借助const Grid& grid

3. generateObstacles不需要返回值，是因为它直接修改外部唯一的地图，函数内便完成了赋值闭环。而同为生成式的 generateFreePosition，由于设计，是指向所有 position类的生成器，所以必须要有外部接口

4. readerMap的逻辑在于，为了防止每一次robot移动，都要重新修改地图信息，故作分层处理，第一层是障碍物和Free格子，第二层是机器人和目标；这样只需要做实时判断，robot就可以在地图上实时移动
- 由于在随机坐标生成时，用的是Free判断，于是只要在main函数中控制障碍物生成与随机坐标生成的顺序，即便优先渲染robot与target，也不会导致障碍物被覆盖。最后一步渲染权重最低的Free格子

