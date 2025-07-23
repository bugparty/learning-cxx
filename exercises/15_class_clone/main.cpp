#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>
#include <cassert>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(3) {
        assert(capacity >= 3);
        assert(cache != nullptr);
        cache[0] = 0;
        cache[1] = 1;
        cache[2] = 1;
        this->get(capacity-1);
    }
    DynFibonacci() = delete; // 禁止默认构造器
    DynFibonacci(DynFibonacci &&that) = delete; // 禁止移动构造器
    DynFibonacci &operator=(DynFibonacci &&that) = delete; // 禁止移动赋值
    // TODO: 实现复制构造器
    // DynFibonacci(DynFibonacci &that) = delete;
    DynFibonacci(DynFibonacci const &that){
        //this is not ready now ,dont use it
        cached = that.cached;
        cache = new size_t[that.cached];
        for (int i = 0; i < that.cached; ++i) {
            cache[i] = that.cache[i];
        }
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
    size_t get(int i) {
        //std::cout << "called "<< i << std::endl;
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        //std::cout << "fib " << i << " is " << cache[i] << std::endl;
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
