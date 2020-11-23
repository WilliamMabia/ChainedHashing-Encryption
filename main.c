//
//  main.c
//  Created by William Mabia on 2020-11-23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashTable_size = 10;

struct HashTablenode {
    int value;
    struct HashTablenode *next;
};

typedef struct HashTablenode Node;

//Hash Method
int hashMethod(int key){
    int hashValue;
    hashValue = key % hashTable_size
}

int asciiSum(char user[]) {
    //ascii sum of characters
    int i = 0, total = 0;
    //get ascii sum
    while (user[i] != '\0') {
        total += user[i];
        i += 1;
    }
    return total;
}

