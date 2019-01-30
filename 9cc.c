#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid arguments\n");
    return 1;
  }

  printf(".global main\n");
  printf(".ent main\n");
  printf("$main..ng:\n");
  printf("main:\n");

  printf("  lda $0, %d($31)\n", atoi(argv[1]));
  printf("  ret\n");
  printf("  .end main\n");
  return 0;
}

