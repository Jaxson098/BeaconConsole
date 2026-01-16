// C program to resize dynamic array using realloc()
// function

#include <stdio.h>
#include <stdlib.h>

int main() {

    int input = 5;

    size_t count = (size_t)input;

    int* ptr = calloc(count,sizeof(int));

    for (int i = 0; i < count; i++) {
        ptr[i] = i + 1;
    }

    printf("Array is: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    while (1) {
        if(scanf("%d",&input)){
            count = (size_t)input;
            printf("new size: %d\n", input);
            ptr = realloc(ptr,count * sizeof(int));
            for (int i = 5; i<input; i++) {
                ptr[i] = i+1;
            }
            printf("New Arr is: ");
            for (int i = 0; i < count; i++) {
                printf("%d ", ptr[i]);
            }
            printf("\nenter number to remove\n");
            while (1) {
                if (scanf("%d", &input)) {
                    for (int i = input-1; i<count; i++) {
                        ptr[i] = ptr[i+1];
                    }
                    count = count-1;
                    ptr = realloc(ptr,count * sizeof(int));
                    printf("New Arr is: ");
                    for (int i = 0; i < count; i++) {
                        printf("%d ", ptr[i]);
                    }
                    printf("\ncount = %d\n",count);
                    ptr[count+1] = 10;
                    printf("last = %d",ptr[count+1]);
                }
            }
        }
    }

    // struct scoreStruct { 
    //     char arr[255];
    //     char arr2[30];
    // };

    // struct score1 
 
    // size_t count = 5;

    // struct scoreStruct * scores = calloc(count,sizeof(struct scoreStruct));

    // printf("%s\n",scores[0].arr);



    return 0;
} 