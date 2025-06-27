#include <stdio.h>
#include <cs50.h>


float average(int n, int arr[]);


int main(void){
    const int N = get_int("Enter how many grades: ");

    int scores[N]; //syntax for defining a new array
    for (int i = 0; i < N; i++){
        scores[i] = get_int("Score: ");
    }

    printf("Average: %.2f\n", average(N, scores));
}


float average(int n, int arr[]){
    float sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum/n;
}