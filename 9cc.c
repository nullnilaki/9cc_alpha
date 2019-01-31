#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid arguments\n");
    return 1;
  }

  char *p = argv[1];

  printf(".global main\n");
  printf(".ent main\n");
  printf("$main..ng:\n");
  printf("main:\n");
  printf("  lda $1, %ld($31)\n", strtol(p, &p, 10));

  while (*p) {
    if (*p == '+') {
      p++;
      printf("  lda $2, %ld($31)\n", strtol(p, &p, 10));
      printf("  addl $2,$1,$1\n");
      continue;
    }

    if (*p == '-') {
      p++;
      printf("  lda $3, %ld($31)\n", strtol(p, &p, 10));
      printf("  subl $1,$3,$1\n");
      continue;
    }

    fprintf(stderr, "Unexpected value '%c'\n", *p);
    return 1;
  }

  printf("  mov $1,$0\n");
  printf("  ret\n");
  printf("  .end main\n");
  return 0;
}
