
// chatgpt solution
// Runtime 0 ms Beats 100.00%
// Memory 8.07 MB Beats 59.44%
// TODO: change char[26] array to bitmap to save space
bool wordPattern(char* pattern, char* s) {
    char *word_arr[300];
    char *word;
    int word_count = 0;

    word = strtok(s, " ");

    while (word) {
        word_arr[word_count++] = word;
        word = strtok(NULL, " ");   // extract tokens from s
    }

    if (word_count != strlen(pattern)) return false;

    char p_map[26] = {0};
    char *w_map[26] = {0};

    int curr;
    for (int i=0; i<word_count; i++) {
        curr = pattern[i]-'a';

        // if not mapped
        if (p_map[curr] == 0) {

            // same mapping shouldn't exist
            for (int j=0; j<26; j++) {
                if (w_map[j] != 0 &&
                    0 == strcmp(word_arr[i], w_map[j]))
                    return false;
            }

            w_map[curr] = word_arr[i];
            p_map[curr] = 1;

        } else if (0 != strcmp(w_map[curr], word_arr[i])) {
            return false;
        }
    }

    return true;
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
