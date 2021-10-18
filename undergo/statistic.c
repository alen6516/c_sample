#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TOTAL_NUM 10

int total_num;

void stats_1(int *arr)
{
    int num_samples = 0;
    int sum = 0;
    float mean, std_dev;
    for (int i=0; i<total_num; i++) {
        if (arr[i]) {
            sum += arr[i];
            num_samples ++;
        }
    }
    mean = (float)sum / num_samples;

    float _sum = 0;
    for (int i=0; i<total_num; i++) {
        if (arr[i]) {
            _sum += pow((double)(arr[i]-mean), 2.0);
        }
    }
    std_dev = sqrt((double)(_sum/num_samples));

    printf("====== in stats_1 =======\n");
    printf("num_samples = %d\n", num_samples);
    printf("mean = %f\n", mean);
    printf("std_dev = %f\n", std_dev);
}

void stats_2(int *arr)
{
    int num_samples = 0;
    int sum = 0;
    float mean, _mean, std_dev, _std_dev;
    mean = _mean = arr[0];
    std_dev = _std_dev = 0.0;

    for (int i=0; i<total_num; i++) {
        if (arr[i]) {
            //printf("-------------\n");
            //printf("Mk = %f, Mk' = %f, Sk = %f, Sk' = %f\n", mean, _mean, std_dev, _std_dev);
            num_samples ++;
            //printf("Mk = Mk' + (Xk-Mk')/k\n");
            mean = _mean + (arr[i]-_mean) / num_samples;
            //printf("%f = %f + (%f-%f)/%d\n", mean, _mean, (float)arr[i], _mean, num_samples);
            //printf("Sk = Sk' + (Xk-Mk') * (Xk-Mk)\n");
            std_dev = _std_dev + (arr[i]-_mean) * (arr[i]-mean);
            //printf("%f = %f + (%f-%f) * (%f-%f)\n", std_dev, _std_dev, (float)arr[i], _mean, (float)arr[i], mean);

            _mean = mean;
            _std_dev = std_dev;
        }
    }

    printf("====== in stats_2 =======\n");
    printf("num_samples = %d\n", num_samples);
    printf("mean = %f\n", mean);
    printf("std_dev = %f\n", sqrt((double)std_dev/num_samples));
}

int main (int argc, char *argv[])
{
    if (argc > 1) {
        total_num = strtol(argv[1], NULL, 10);
    } else {
        total_num = TOTAL_NUM;
    }

    srand(time(NULL));
    int *arr = (int*) malloc(sizeof(int)*total_num);
    for (int i=0; i<total_num; i++) {
        arr[i] = rand() % 100;
        if (!(rand() % 3)) {
            arr[i] *= (rand() % 5);
        }
    }

    printf("arr = ");
    for (int i=0; i<total_num; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    stats_1(arr);
    stats_2(arr);
}
