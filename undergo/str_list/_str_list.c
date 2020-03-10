#include <stdio.h>
#include <string.h>

struct str_list_t {
    char *str;
    struct str_list_t *next;
};

int join_str_list(struct str_list_t* str_list, char *ret, size_t max_len) {

    str_list_t* curr = str_list;
    size_t curr_len = 0;
    size_t this_len = 0;

    while (curr) {
        this_len = strlen(curr->str);
        strncat(ret, curr->str, max_len-curr_len);
        
        if (max_len-curr_len < this_len) {
            return -1;
        }
        curr_len += this_len;
        curr = curr->next;
    }
    return curr_len;
}

int main () {
    
    const char* str = "123, 312";
    printf("%s\n", str);

}
