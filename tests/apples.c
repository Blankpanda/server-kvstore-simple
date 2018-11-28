#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <stdlib.h>

#include "../hashtable/hash_table.h"

int main(int argc, char *argv[])
{
  ht_hash_table* ht = ht_new();
  
  char* nibble = ht_search(ht,"brap");

  if(nibble != NULL)
  {
       puts(nibble);
  }
  else
  {
       puts("apples and oranges and bears oh my!!");
  }
     
  ht_insert(ht,"brap","hog");
  ht_insert(ht,"noot","noot2");
  ht_insert(ht,"glugger","fish");

 
  return 0;
}

