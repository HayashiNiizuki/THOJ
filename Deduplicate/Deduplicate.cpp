#include <cstdio>
#include <cstring>

#define Mod 119993
#define step 4999

struct wordSet {
    char name[41];
    short count = 0;
};

wordSet dic[Mod];

void hash(wordSet *dic, char *word) {
    int set = 0;
    short n = strlen(word);
    for (int j = 0; j < n; j += 4) {
        set += word[j] * step;
    }
    set %= Mod;
    int i = 1;
    while (dic[set].count && strcmp(dic[set].name, word)) {
        set += i * i;
        i++;
        set % Mod;
    }
    if (!dic[set].count) {
        strcpy(dic[set].name, word);
    } else if (dic[set].count == 1) {
        printf("%s\n", word);
    }
    dic[set].count++;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    char tempName[41];
    for (int i = 0; i < n; i++) {
        scanf("%s", tempName);
        hash(dic, tempName);
    }
    return 0;
}