#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("input k:");
    int k;
    scanf("%d", &k);

    int *arr = (int *) malloc(sizeof(int)*k); // в два раза больший массив
    if(arr == NULL)
        return 1;

    printf("input array:");
    for (int i = 0; i < k; ++i)
        scanf("%d", &arr[i]);

    printf("input n:");
    int n;
    scanf("%d", &n);

    n %= k;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k-1; ++j)
        {
           int temp = arr[j];
           arr[j] = arr[j+1];
           arr[j+1] = temp;
        }
    }

    for(int i = 0; i < k; i++)
        printf("%d ", arr[i]);

    return 0;
}
