#include <stdbool.h>
#include <threads.h>

#define MAX_THREADS 8           // 1、2、4、8……所创建线程数量的最大值
#define MIN_BLOCK_SIZE 100      // 一个数组块的最小值
typedef struct                  // 函数parallel_sum()的参数
{
    float *start;       // 传递给parallel_sum()的数组块的起始地址
    int len;            // 数组块长度
    int block_size;     // 最小数组块的大小
    double sum;                 // 求和结果
} Sum_arg;

int parallel_sum(void *arg);    // 线程函数的原型

// ---------------------------------------------------------------
// 计算数组元素的和，并写入*sumPtr
// sum()调用函数parallel_sum()进行并行处理
// 返回值：如果没有发生错误，则返回true；否则，返回false
bool sum(float arr[], int len, double *sumPtr) {
    int block_size = len / MAX_THREADS;
    if (block_size < MIN_BLOCK_SIZE) block_size = len;

    Sum_arg args = {arr, len, block_size, 0.0};
    if (parallel_sum(&args)) {
        *sumPtr = args.sum;
        return true;
    }
    else
        return false;
}

// ---------------------------------------------------------------
// 递归辅助函数，用以将工作分解到几个线程中处理
int parallel_sum(void *arg) {
    Sum_arg *argp = (Sum_arg *) arg;              // 指向参数的指针

    if (argp->len <= argp->block_size)                 // 如果length <= block_size，
        // 对所有元素求和
    {
        for (int i = 0; i < argp->len; ++i)
            argp->sum += argp->start[i];
        return 1;
    } else                                                // 如果length > block_size，
        // 分解数组
    {
        int mid = argp->len / 2;
        Sum_arg arg2 = {argp->start + mid, argp->len - mid,
                        argp->block_size, 0};       // 指定后一半数组
        argp->len = mid;                     // 前一半数组的长度

        thrd_t th;                              // 在新线程中处理前一半数组
        int res = 0;
        if (thrd_create(&th, parallel_sum, arg) != thrd_success)
            return 0;                           // 没能成功创建新线程

        if (!parallel_sum(&arg2))   // 在当前线程下，以递归方式处理后一半数组
        {
            thrd_detach(th);
            return 0;          // 递归调用失败
        }
        thrd_join(th, &res);
        if (!res)
            return 0;            // 同级线程报告执行失败

        argp->sum += arg2.sum;
        return 1;
    }
}