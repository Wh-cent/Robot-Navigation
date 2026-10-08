# Part 1: 前言
该轮短暂的学习有90%都是ChatGPT「Astra·max」推进的，越到后期，越发觉其中的不对劲：
- 初期，由于从未用AI学过代码，不清楚高效的使用体验如何，且由于初期难度较低以及各种我没分析到的原因，我一度认为只使用ChatGPT学习代码是较高效的行为
- 中期，状态下滑，这也是可以预估的，时间投入低，这与AI没什么关系
- 后期，我为了赶进度，认真浏览ChatGPT给的学习思路与代码解释，发现：
    1. ChatGPT并不清楚我究竟理解到了哪一步，且我并没有很严格的提问，ChatGPT的回复总是会在不定的程度上与我真正的困惑错开
    2. 项目逻辑与代码逻辑实际上是两个东西「或许」，而ChatGPT并没有明确区分二者，甚至从未辨析过，这导致我在零基础的情况下学的很痛苦
    3. 至于其他暂时分析不出，两点较为突出的问题已经够我喝一壶的了

总之我曾经一度认为是我理解力的问题，但DeepSeekV4在后期的学习过程中，总能以更高效、无需预设教学性格、近乎一遍就让我明白的方式，推进项目进度
我有理由认为，后续我应该多用我母语国家的AI模型

我会把这些状况的进一步分析与解决放在下一个项目中，并调整AI在工作中的占比，以及不同AI间的占比
若有机会，后续会转向动态地图的python优化阶段，本人由于部分原因，暂时将方向调整为SRE学习


# Part 2: 未优化的函数逻辑梳理


## randomInt 
- 目的：前置的整数随机化工具

- 逻辑：输入（
    拟定的最小值、最大值随机化区间
）{
    依旧没有理解内部代码的逻辑，故暂不做展开

}   输出：随机整数



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


## directionToText
这个函数就是一个功能性函数，只要单一的输入一个方向，然后自动的在函数内部通过switch case把它翻译成中文字符就行了，然后最后再预设一个未知符号


## tryMove
- 目的：基于未来预期坐标信息，判断该坐标是否合理，若合理，则赋值给 robot

- 逻辑：输入（
    const 地图信息 && 外部robot坐标信息 && 指定移动方向
）{
    使用 calculateNextPosition 函数，得到未来预期坐标信息
    使用 isWalkable 判断该预期坐标是否合理
    - 若合理，则赋值给外部robot坐标
    - 若不合理，则返回「否」

    新增的内容是对不同的错误报告做一个更加具体的划分，以及最后的输出上，让整个函数的输出更加透明：一开始的坐标是什么？方向是什么？那么预期的坐标是什么？是否执行成功了，输出它执行后的坐标，最后再解释一下成功/失败的原因

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


## stepToDirection
- 目的：将路径中的相邻步骤转化为robot可识别的方向

- 逻辑：输入（
    直接输入path相邻项是符合直觉的，但较难理解，故选择低级的代码模式，通过输入robot当下坐标「若合法，则相当于path[i]的坐标信息」以及path[i+1]，以及外部初始化之后的direction，用于储存方向信息
）{
    通过比较前后坐标信息的差值，去分类对应四个方向，要注意不合法的结果预处理，在这个函数中，不合法输入的设计包含在了函数返回值这个模块中，只要不合法，通过四个if筛查下来不符合正常逻辑，就直接返回false给函数，让返回值作为不合法的象征

}   输出：若合法，改变方向；返回bool值


## executePath
- 目的：通过预定的path执行坐标转移

- 逻辑：输入（
    由于需要判断路径上是否存在障碍，而障碍是直接保存在grid信息中的，不独立显示，所以必须直接调用外部地图信息；根据stepToDirection，也需要robot坐标信息和整个path信息
）{
    先进行预处理，使用path.empty()检验情况，若path为空，直接返回错误；使用isSamePosition(robot, path.front())，若robot不在path起点，同样返回错误，这一点后续应当改进，应作为单独的提醒；若以上两种都排除，则进入具体的判断流程：
    
    使用for遍历路径坐标，在内部进行第二轮预处理，相较于第一轮对外部坐标信息接口是否一致的问题，这一轮主要处理路径本身是否合法的问题，这一点应当在路径设计时就被处理掉，这里由于阶段性人工设计，需要进行后置判断；若路径也是合理的，则按照相邻步骤转化方向去移动robot，并在grid信息中判定每一步的移动是否合法，即使用isWalkable进行判断，此处个人认为，tryMove函数的设计是不合理的，在大致功能上它与iaWalkable高度重合，我不清楚现代工程是否允许小差异独立包装的情况，不清楚这是否属于代码冗余，总之我认为简单的基础函数已经能较好的判断，额外的包装属于嵌套与整合，我不清楚这样的价值究竟在哪

}   输出：可能改变的robot坐标与bool值


## getWalkableNeighbors
- 目的：统计某一坐标四周的可移动数量

- 逻辑：输入（
    由于需要辨别是否有障碍物，所以地图信息是必须的；以及一个当下的或者是需要被判别的坐标信息
）{
    先预处理，初始化向量组neighors，再初始化一个方向向量组，用于遍历，区别于外部储存的方向，这个方向有序号，映射于数字，用途似乎更广

    在for循环中，将方向赋值给内部方向储存器，利用caculateNextPosition计算next坐标，放进isWalkable进行判断，若可以走，则push_back至neighbors中

}   输出：向量组neighbors


## canReach
- 目的：判断在不预定路径的情况下，robot是否能从起始点走到目的地，即判断robot这一路上有没有合法解

- 逻辑：输入（
    要判断，肯定要看地图，以及起始点与目的地的坐标信息
）{
    首先，进行预处理：
    先判断起始点与目的地的坐标上是否存在障碍物或者超过地图边界，也就是是否能够正常行动，用iswalkable判断，外部套上if与！，用或逻辑串上两层判断，只有当两层判断都正常时，该if才不会运行返回false

    然后初始化一个队列，名为pending，里面装position信息，顾名思义，是储存需要被处理但由于外部判断先放进来存着的储存器
    对于该队列，与正常的vector组是不完全一致的？

    然后初始化一个二维向量组，存放bool值，相当于是对grid的独立性质渲染，名为discovered，初始化时所有格子里都是false，因为都还没有被发现过

    然后，我们将起始点的discovered改为true，把起始点坐标push进pending中，此处就是与vector不一样的，queue似乎默认把新的东西push到最后面，也就是在执行效果上。与push_back一致「先改后放」

    然后进入一个while循环，该循环是条件语句为真时进行；于是，如果pending里面没有空，！就是true，就会执行while：
    - 我们取出pending第一个格子里的东西，pending.front（），将其储存在current中。作为一个临时处理器，然后使用pop（）把第一个格子里的东西删掉「先取后删」
    - 文字提示当前正在处理哪一个current的坐标，透明化
    - 有一个同位判断，如果当下取出来的current正好是target一致的位置，就直接结束整个函数，返回true，如果不是就继续判断，那为何这个判断要放在这个位置呢？？
    - 利用getWalkableNeighbors获得current四周合法的格子然后将这个获得的格子作为遍历的锚点，把一个个合法的邻居格子暂时存放进next中，然后重新上方if判别是否discover，这里的discovered就合grid的使用方式一样

    如果最后循环到pending空了，还是没有sameposition，说明到不了，最后就直接返回一个false就行

}   输出：bool值/独立渲染


## shortestSteps
- 目的：发现从起始点到目的地的最短步数

- 逻辑：输入（
    和canReach一致
）{
    基本与canReach是一致的，从一开始的预处理，到pending初始化，到记录false的独立性质渲染，再到预先判断起始点，再利用pending空不空去while循环，去循环push/pop next到pending中，并修改false渲染层，最后如果计数失败，直接返回-1

    不同的地方在于，为了计数，这里又有新的独立性质渲染层：储存整数的、与grid对应的二维向量组，这里默认每个格子里储存-1，起始点为0，只有当false-true的逻辑生效，自动同步在前一父代的格子基础上+1，达到阶梯式增加的步数计数功能

}   输出：整数值/独立渲染


## findShortestPath
- 目的：

- 逻辑：输入（
    与上面一致
）{
    前部分基本逻辑还是和上面的类似，不过由于需要找到最短路径，所以会再新建一个独立性质渲染，这层渲染专门用于储存每一个walkable坐标的父坐标是谁：std::vector<std::vector<Position>> parent

    if(!isWalkable(grid, start) ||
       !isWalkable(grid, target)){
        return {};
       }
    
    对应的初始化就是{-1, -1}

    在while循环中的for循环里，这里用Position next: getWalkableNeighbors(),而不是i标号，这里直接循环position本身

    在while循环后，依旧老规矩，如果循环完了还是达不到目的地，也要返回一个值给函数，接下来是按照父子关系逆向整理整个path：
    - 首先初始化path，将确认已经可以被达到的目的地赋值给追踪器trace
    - 由于一个父代可以有多个子代，但是一个子代只能有一个父代，于是逆向追踪必然是唯一的一条path
    - while循环，只要这个追踪器还没有逆向到atart，就把这个trace push_back到path中，再修改trace为再往前的父代
    - 但由于while的判断是基于trace是否和start一致进行的，而trace的添加是在while中进行的，于是执行到最后，会出现末尾无法进入循环内部执行相关操作的状况，所以需要单独加一下
    - 直到相同后，得到一条反向的path，我们需要把它翻过来，用std::reverse(path.begin(), path.end());
    「为何begin和end后面要加个括号呢？是为了格式统一吗？还是的确可以加点什么东西」

}   输出：向量


## makeTestMap
- 目的：在自动化前，建立可以手动检验的小型测试地图

- 逻辑：输入（  
    不需要输入，我成尊便是了
）{
    依旧初始化，不过这里先全部初始化为obstacle
    用双层for循环，规定解锁的小型区域

    再手动规定几个obstacle，返回grid
}


## check
- 目的：建立一套统一的检查小代码块，便于在

- 逻辑：输入（
    需要输入一个自身携带布尔值的condition，然后是一个你在判断什么的一个文字解释，这个解释直接constantly引用外部的东西，不修改；最后直接引用外部的failedcount参数，这里是需要做累加的，所以说每次check引用的都是同一个failedcount
）{
    check函数本身的执行其实是在输入里的，里面的condition相当于是一个执行器，其本身会得到一个bool值，而后根据这个bool值，在check内直接判断是输出pass还是fail

    pass和fail比较，是直接以if作为判断逻辑，去判断condition的布尔值：如果真，直接输出pass；如果不是，则不用额外添加语句，只需后面直接对failedcount加一，再直接输出fail

    问题在于，这个check函数似乎只能检查自身携带布尔值的东西？有待改进

}   输出：一串解释


## runchecks
对runchecks函数不想过多解释，因为我也不想看，这就是对不同的一些并列情况进行了一个check调试，应该不重要


## practicePriorityQueue
傻逼函数，没啥意义，纯展示Dijkstra算法逻辑


## manhattenDistance
对应坐标之差绝对值的和 std::abs（）

struct SearchEntry {
    Position position;
    int g;
    int f;
};这是一个结构型的变量，是人为定义出来的，有SearchEntry.position, g为已知的代价/已经发生的代价，f为总代价

struct LowerPriority {
    bool operator()(
        const SearchEntry& a,
        const SearchEntry& b
    ) const {
        return a.f > b.f;
    }
}; 看不懂


## findPathStar
- 目的：也是找一条路径，不过采用的是AStar算法

- 逻辑：输入（
    外部地图和两个坐标，不必赘述
）{
    检查输入的两个坐标是否是不合法的，然后再进入下面的判断
    初始化：
    - 一份二维向量组代价表，未被探索的全部定义为-1
    - 一份前驱表，记录position
    - 一个优先队列，我还是看不懂，总之名字同样是pending/里面储存SearchEntry类型的变量，以向量的方式储存，并使用LowerPriority进行排序。LowerPriority是一种最小堆排列？不清楚，不了解

    start的代价改为0，然后把初始位置打包成一个SearchEntry，g=0，f=g+manhattenDistance()即预期的总代价 / 并把这个打包push进优先队列中

    定义一个为false的found，有何用？

    进入!pending.empty的while循环，开始边放边拿优先队列中的东西去做判断：
    - 首先把优先队列中第一个向量拿出来，放进SE型的current里，拿完后就删了 ——top/pop，当然，这里一开始拿的肯定是start，毕竟也没有其他的SE了
    - 由于需要做邻居判断，所以要把current的position放进position里
    - 且如果current的已知代价不等于最低代价，说明有一条路的代价更低，就直接跳过当前的SE。这行代码是在做 “过期队列元素检查”，也叫 lazy deletion / 惰性删除 —— 
    - 内部四方for循环，邻居检验；注意这里是假设有多条路径，所以要比较old与nex的g代价
    
    循环出来就来个尾部处理、后面就是正常的findshortestPath的尾部函数，转换path的前后

}   输出：向量组path


## isVaildPath
- 目的：判断生成出来的path是否合法
【我十分怀疑这个函数的必要性，path生成时都这么分门别类了，怎么可能还有问题？】







