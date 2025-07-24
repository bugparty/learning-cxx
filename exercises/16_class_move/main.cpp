#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>
#include <cassert>
class DynFibonacci {
    size_t *cache=nullptr; // 使用指针动态分配缓存空间
    int cached=0;

public:
    // TODO: 实现动态设置容量的构造器
     DynFibonacci(int capacity): cache(new size_t[capacity]), cached(3) {
        assert(capacity >= 3);
        assert(cache != nullptr);
        cache[0] = 0;
        cache[1] = 1;
        cache[2] = 1;
    }
    

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&rhs) noexcept{
        cache = rhs.cache; // 交换缓存指针
        cached = rhs.cached; // 交换缓存计数
        rhs.cache = nullptr; // 清空右值的缓存指针，避免析构时释放
        rhs.cached = 0; // 重置右值的缓存计数
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&rhs) noexcept{
        if (this != &rhs) { // 检查是否移动到自身
            if (cache != nullptr) {
                delete[] cache; // 释放当前缓存空间
            }
            cache = rhs.cache; // 交换缓存指针
            cached = rhs.cached; // 交换缓存计数
            rhs.cache = nullptr; // 清空右值的缓存指针，避免析构时释放
            rhs.cached = 0; // 重置右值的缓存计数
        }
        return *this; // 返回当前对象的引用
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        if (cache != nullptr)
        {
            delete[] cache; // 释放动态分配的缓存空间
            cache = nullptr; // 避免悬空指针
        }
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
