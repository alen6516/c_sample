#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define filename "file"

int main () {


    struct stat attrib;
    stat(filename, &attrib);

    char date[50];

    strftime(date, 40, "local time = %H:%M:%S-%d-%m-%Y", localtime(&(attrib.st_ctime)));
    printf("%s\n", date);


    strftime(date, 40, "  GMT time = %H:%M:%S-%d-%m-%y", gmtime(&(attrib.st_ctime)));
    printf("%s\n", date);
}

