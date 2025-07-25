#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    auto &cached = cache.cached;
    auto &cache_ref = cache.cache;
    for (; cached<=i; ++cached) {
        cache_ref[cached] = cache_ref[cached - 1] + cache_ref[cached - 2];
    }
    return cache_ref[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    #ifdef _MSC_VER
    FibonacciCache fib;
    fib.cache[0]=0;
    fib.cache[1]=1;
    fib.cache[1]=1;
    fib.cached = 3;
    #else
    FibonacciCache fib{
        .cache = {0, 1,1}, // 初始化前两个斐波那契数
        .cached = 3      // 已缓存的斐波那契数个数
    };
    #endif
    
    //std::cout << fibonacci(fib, 3) << std::endl;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
