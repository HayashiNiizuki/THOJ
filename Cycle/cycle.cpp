//没有对二叉堆进行封装，因为没有必要
#define _CRT_SECURE_NO_DEPRECATE
#define maxn 100001
#include <stdio.h>
#include <string.h>
using namespace std;
char str1[maxn];
char str2[maxn];
int find_in2(char *str1, char *str2) {
    auto mi = 0;
    while (str2[mi++] != str1[0])
        ;
    return --mi;
}
int answer = 0;
int position;
bool compare(int &head2, int l1, int head1, char *str1, char *str2) {
    position = head2;
    int second_start = 0;
    auto temp = head1;
    while (str1[head1++] == str2[head2++] && head2 < l1) {
        if (!second_start && str2[head2] == str1[temp])
            second_start = head2;
    }
    if (str1[head1 - 1] == str2[head2 - 1]) {
        answer = 1;
        return true;
    } else {
        if (second_start)
            head2 = second_start;
        else
            while (head2 < l1 && str2[head2] != str1[temp])
                head2++;
        return false;
    }
}
bool check_rest(int l1, char *str1, char *str2) {
    int i = 0, j = l1 - position;
    while (i < position && str2[i++] == str1[j++])
        ;
    return i == position ? true : false;
}
int main() {
#ifndef _OJ_
    freopen("cycle.txt", "r", stdin);
    // freopen("travelout.txt", "w", stdout);
#endif
    while (scanf("%s %s", &str1, &str2) != EOF) {
        answer = 0;
        int l1 = strlen(str1), l2 = strlen(str2);
        if (l1 == l2) {
            int compare_head = find_in2(str1, str2);
            auto temp = compare_head;
            while (!compare(compare_head, l1, 0, str1, str2) &&
                   compare_head < l1)
                ;
            if (answer && check_rest(l1, str1, str2))
                printf("YES\n");
            else
                printf("NO\n");
        } else
            printf("NO\n");
    }
}
