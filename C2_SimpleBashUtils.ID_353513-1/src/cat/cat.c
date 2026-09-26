#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 2048

typedef enum {FLAG_b, FLAG_e, FLAG_n, FLAG_s, FLAG_t, FLAG_v} FLAG;


int parser(int args, const char* argv[], unsigned int* flags, int arr_files[], int* size);
void read_file(const char* file_name, unsigned int flags);
void write_str(const char[], int flags, int* is_last_str_blank, int* count_nonblank_str, int* count);

int main(int argc, char* argv[]){

  unsigned int flags = 0;
  int arr_files[argc - 1];
  int size = 0;

  


}

