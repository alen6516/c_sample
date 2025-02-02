

bool wordPattern(char* pattern, char* s) {
    char *word_arr[300];
    char *word;
    int word_count = 0;

    word = strtok(s, " ");

    while (word) {
        word_arr[word_count++] = word;
        word = strtok(NULL, " ");
    }

    if (word_count != strlen(pattern)) return false;

}

// my solution, not finished
bool wordPattern(char* pattern, char* s) {
    int hop = 0;    // how many hop between 2 same patterns

    for (int i=0; pattern[i] != 0; i++) {
        if (pattern[i] == '-') continue; // processed

        hop = 1;
        for (int j=i+1; pattern[j] != 0; j++) {

            if (pattern[i] == pattern[j])
                // compare in s
                for (int k=0; s[k] != 0; k++) {

                    if (sh == i) start = k;
                }
            else {
                hop++;
            }
        }

    }
}
