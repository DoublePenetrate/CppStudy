#include <func.h>
#include <pthread.h>
void* start_routine(void* args) {
    // 新线程的执行流程
    long long* arr = (long long*)args;
    long long* sum = malloc(sizeof(long long));
    long long result = 0;
    for (long long i = arr[0]; i <= arr[1]; i++) {
        result += i;
    }
    *sum = result;
    return (void*)sum;
}

int main(void) {
    long long n;
    printf("Please input a long long int: ");
    scanf("%lld", &n);

    // 创建两个线程
    // 第一个线程对区间[1, n/2] 累加
    // 第二个线程对区间[n/2, n] 累加
    pthread_t tid_01; // 传出参数，用来接受新线程的 ID
    pthread_t tid_02;
    long long arr_01[2] = {1, n/2};
    long long arr_02[2] = {n/2, n};
    int err_01 = pthread_create(&tid_01, NULL, start_routine, (void*)arr_01);
    if (err_01) {
        error(1, err_01, "pthread_create 01");
    }
    
    int err_02 = pthread_create(&tid_02, NULL, start_routine, (void*)arr_02);
    if (err_02) {
        error(1, err_02, "pthread_create 02");
    }
    // 主线程等待两个子线程结束，并接收他们的计算的结果
    void* retval_01;
    void* retval_02;
    pthread_join(tid_01, &retval_01); // 阻塞等待 tid 线程结束
    pthread_join(tid_02, &retval_02);
    // 输出最终结果
    long long result_01 = *(long long*)retval_01;
    long long result_02 = *(long long*)retval_02;

    printf("The final result: %lld\n", result_01 + result_02);
    return 0;
}
