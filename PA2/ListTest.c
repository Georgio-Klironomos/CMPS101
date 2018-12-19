#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    List A = newList();
    List C = copyList(A);
        int res = !equals(A, C);
        freeList(&C);
        if (res) {
            printf("1");
        }
        else {
            printf("0");
        }
        
    return 0;
}