#include <stdio.h>
#include <string.h>

int main() {
    char buf[100];
    int len = fread(buf, 1, sizeof(buf), stdin);
    // 打印关键日志
    printf("[TEST] 输入长度：%d，内容（前32字节）：", len);
    for (int i=0; i<len && i<32; i++) {
        isprint(buf[i]) ? printf("%c", buf[i]) : printf("\\x%02x", buf[i]);
    }
    printf("\n");

    // 打印关键日志-多分支触发不同覆盖
    if (len == 3 && buf[0] == 'a') {
        printf("[TEST] 分支1：初始种子（abc）覆盖\n");
    } else if (len == 3 && buf[0] == 'b') {
        printf("[TEST] 分支2：Deterministic比特翻转覆盖（新分支）\n");
    } else if (len == 6 && buf[0] == 'A') {
        printf("[TEST] 分支3：Havoc兴趣值替换覆盖（新分支）\n");
        *(int*)0 = 0; // 触发崩溃（验证变异影响）
    } else if (len > 6 && buf[2] == '9') {
        printf("[TEST] 分支4：Splicing拼接变异覆盖（新分支）\n");
    } else {
        printf("[TEST] 分支5：默认分支\n");
    }
    return 0;
}