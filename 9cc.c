#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  TK_NUM = 256,
  TK_EOF,
};

// type of token
typedef struct {
  int ty;      // type
  int val;
  char *input;
} Token;

Token tokens[100];

void tokenize(char *p) {

  int i = 0;

  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (*p == '+' || *p == '-') {
      tokens[i].ty = *p;
      tokens[i].input = p;
      i++;
      p++;
      continue;
    }

    if (isdigit(*p)) {
      tokens[i].ty = TK_NUM;
      tokens[i].input = p;
      tokens[i].val = strtol(p, &p, 10);
      i++;
      continue;
    }

    fprintf(stderr, "tokenize failed: %s\n", p);
    exit(1);
  }

  tokens[i].ty = TK_EOF;
  tokens[i].input = p;
}

void error(int i) {
  fprintf(stderr, "unexpected token: %s\n",
          tokens[i].input);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid arguments\n");
    return 1;
  }

  tokenize(argv[1]);

  printf(".global main\n");
  printf(".ent main\n");
  printf("$main..ng:\n");
  printf("main:\n");

  if (tokens[0].ty != TK_NUM)
    error(0);

  printf("  lda $1, %d($31)\n", tokens[0].val);

  int i = 1;
  while (tokens[i].ty != TK_EOF) {
    if (tokens[i].ty == '+') {
      i++;

      if (tokens[i].ty != TK_NUM)
        error(i);

      printf("  lda $2, %d($31)\n", tokens[i].val);
      printf("  addl $2,$1,$1\n");
      i++;

      continue;

    }

    if (tokens[i].ty == '-') {
      i++;

      if (tokens[i].ty != TK_NUM)
        error(i);

      printf("  lda $3, %d($31)\n", tokens[i].val);
      printf("  subl $1,$3,$1\n");

      i++;
      continue;
    }

    error(i);
  }

  printf("  mov $1,$0\n");
  printf("  ret\n");
  printf("  .end main\n");
  return 0;
}
