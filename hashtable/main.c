// main.c
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    ht_hash_table* ht = ht_new();

   char* nibble = ht_search(ht,"brap");

    puts(nibble);
    
    ht_insert(ht,"brap","hog");
    ht_insert(ht,"noot","noot2");
    ht_insert(ht,"glugger","fish");

 
    
}
