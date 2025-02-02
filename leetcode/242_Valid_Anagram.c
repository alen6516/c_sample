// chatgpt solution
// Runtime 0 ms Beats 100.00%
// Memory 8.28 MB Beats 52.12%
#include <string.h>
bool isAnagram(char* s, char* t) {
    if (strlen(s) != strlen(t)) return false;

    int count[26] = {0};

    for (int i=0; s[i]!=0; i++) {
        count[s[i]-'a'] ++;
        count[t[i]-'a'] --;
    }

    for (int i=0; i<26; i++)
        if (count[i] != 0) return false;
    return true;
}

// my solution, time limit exceeded
bool isAnagram(char* s, char* t) {
    int i=0;
    int j;
    int max_j = 0;

    while (s[i] != 0) {
        j = 0;
        while (1) {
            if (s[i] == t[j]) {
                t[j] = '-';
                if (j > max_j) max_j = j;
                break;
            } else if (t[j] == 0) {
                return false;
            }
            j++;
        }
        i++;
    }

    if (max_j >= i) return false;   // t longer than s
    if (t[i] != 0) return false;    // t longer than s

    return true;
}
