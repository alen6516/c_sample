#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>

#define filename "file"

int main () {
    struct timeval time_start;
    struct timeval time_end;
    unsigned long tmp_time_interval;
    unsigned long size = 0;
    FILE *fp;


    // open and count
    gettimeofday(&time_start, NULL);


    fp = fopen(filename, "r");
    int c=0;
    while ((c=getc(fp))!=EOF) {
        size ++;
    }


    gettimeofday(&time_end, NULL);
    tmp_time_interval = 1000000*(time_end.tv_sec - time_start.tv_sec) + time_end.tv_usec - time_start.tv_usec;    
    printf("size = %lu\n", size);
    printf("open time_interval = %lu\n", tmp_time_interval);
    fclose(fp);

    // stdlib
    gettimeofday(&time_start, NULL);


    fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);


    gettimeofday(&time_end, NULL);
    tmp_time_interval = 1000000*(time_end.tv_sec - time_start.tv_sec) + time_end.tv_usec - time_start.tv_usec;    
    printf("size = %lu\n", size);
    printf("stdlib time_interval = %lu\n", tmp_time_interval);
    fclose(fp);

    
    // stat.h
    gettimeofday(&time_start, NULL);


    struct stat st;
    stat(filename, &st);
    size = st.st_size;
    
    
    gettimeofday(&time_end, NULL);
    tmp_time_interval = 1000000*(time_end.tv_sec - time_start.tv_sec) + time_end.tv_usec - time_start.tv_usec;    
    printf("size = %lu\n", size);
    printf("stat time_interval = %lu\n", tmp_time_interval);

}
