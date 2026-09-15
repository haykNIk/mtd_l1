#include <limits.h> // 引入定义UCHAR_MAX宏的库
#include <stddef.h> // 这里定义了size_t类型
#include <stdlib.h> // 添加stdlib.h以使用exit函数

int a = 512; // 全局变量

int main()
{
    // 1. 变量类型。修改代码使结果为1764
    int theUltimateAnswer = 42; // 将unsigned char改为int，因为42 * 42=1764超过unsigned char范围(0-255)
    theUltimateAnswer *= theUltimateAnswer; // 计算42 * 42=1764
    size_t maxValue = UCHAR_MAX; // size_t是无符号整型，用于表示对象大小；UCHAR_MAX是unsigned char类型的最大值(255)

    // 2. 循环。将while循环的逻辑重写为for循环。
    // 说明：运算符&&检查两个表达式是否都为真（即非零）
    // 如果两者都为真，返回真；否则返回假（零）
    
    int i = 0, j = 1, a = 0;
    // while循环转换为for循环：将初始化、条件和更新整合到for语句中
    for (; i < 10 && j < 10; ) {
        a -= i * j;
        i += j;
        j += i;
    }

    // 3. 作用域。重写代码，使在作用域内设置的j值不会丢失，并加到`a`上
    ++a; // 等同于a++，先使用a的值，然后a自增1
    
    int saved_j = 0; // 添加变量保存j的值
    {    // 局部作用域
        int a = 3; // 此a是局部变量，覆盖外部a
        int i = 2 + a; // i = 2 + 3 = 5
        int j = 1 + i; // j = 1 + 5 = 6
        saved_j = j; // 保存j的值
    }
    a += saved_j; // 使用保存的j值(6)

    // 4. 静态存储类说明符
    // 变量在每次循环迭代中的值是多少？在注释中写出
    
    for (int i=0; i<3; i++)
	{
		static int nStatic = 100; // 静态变量，只初始化一次，生命周期贯穿整个程序
		int nLocal = 100;         // 局部变量，每次循环重新初始化
		nStatic++;                // 每次循环静态变量值保留
		nLocal++;                 // 每次循环局部变量重新从100开始
        // i = 0: nStatic = 101, nLocal = 101 (静态变量首次初始化后自增，局部变量每次重新初始化为100后自增)
        // i = 1: nStatic = 102, nLocal = 101 (静态变量保留上次值101自增，局部变量重新初始化为100后自增)
        // i = 2: nStatic = 103, nLocal = 101 (静态变量保留上次值102自增，局部变量重新初始化为100后自增)
	}

    // 5. 枚举（enum）
    // 修正代码，使得执行color = -1后，变量color中确实为值-1
    
    enum eColor // 类型声明
    {
        BLACK,    // 默认0
        BLUE,     // 默认1
        RED = 5,  // 显式设置为5
        YELLOW,   // 接着RED为6
        WHITE = RED + 4  // 5+4=9
    };

    enum eColor color; // 声明enum eColor类型的变量
    color = BLACK;     // 值为0
    color = BLUE;      // 值为1
    color = RED;       // 值为5
    color = WHITE;     // 值为9
    color = 1;         // 可行，C允许整数值赋给枚举变量
    color = (enum eColor)(-1); // 使用强制类型转换明确赋值为-1

    // 6. switch语句
    // 编写代码片段，使用switch实现以下逻辑：变量ch给定一个字符值
    // - 如果字符是'y'（即yes）不区分大小写，则将变量`y`赋值为`x`的值
    // - 如果字符是'n'（即no）不区分大小写，则将变量`y`赋值为(x * 2)
    // - 如果是其他字符，则报错退出程序（返回-1）
    
    char ch = 'Y', x = 5, y;
    
    // 使用switch语句处理不同情况
    switch(ch) {
        case 'y':
        case 'Y': // 不区分大小写，处理'y'和'Y'
            y = x; // 将y赋值为x的值
            break;
        case 'n':  
        case 'N': // 不区分大小写，处理'n'和'N'
            y = x * 2; // 将y赋值为x的2倍
            break;
        default:   // 其他所有情况
            exit(-1); // 报错退出程序，返回-1
    }

    return 0;
}