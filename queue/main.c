#include <stdio.h>
#include <time.h>

int main() {
    // 1. 获取「此刻」的Unix时间戳（动态，每次运行都不同）
    time_t current_timestamp = time(NULL);
    printf("当前实时时间戳：%ld\n", current_timestamp);

    // 2. 转换为北京时间（本地时间，自动适配UTC+8）
    struct tm* local_time = localtime(&current_timestamp);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y年%m月%d日 %H:%M:%S", local_time);
    printf("对应的北京时间：%s\n", time_str);

    return 0;
}