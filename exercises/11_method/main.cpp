#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    #ifdef _MSC_VER
    Fibonacci fib;
    fib.cache[0]=0;
    fib.cache[1]=1;
    fib.cache[1]=1;
    fib.cached = 3;
    #else
    Fibonacci fib {
        .cache = {0, 1, 1}, // 初始化前两个斐波那契数
        .cached = 3      // 已缓存的斐波那契数个数
    };
    #endif
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    
    return 0;
}
