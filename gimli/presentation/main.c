#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16

extern char *otp_fixed(char *ct, char *msg, char *key);
extern size_t strlen(const char* s);

int min(int x, int y) { return x < y ? x : y; }

char get_printable(const char c) { return (0 == isprint(c) ? '?' : c); }

void print_string(char* s) {
  for (size_t i = 0; i < N; i++) {
    printf("0x%02x ", s[i]);
  }
  printf("\b");
}

int main(int argn, char **argv) {
  if (argn != 3) {
    printf("ERROR: invalid number of arguments.\n");
    return EXIT_FAILURE;
  }

  char *inp_msg = argv[1];
  char *inp_key = argv[2];

  char msg[N];
  for (size_t i = 0; i < N; i++) {
    msg[i] = i < strlen(inp_msg) ? inp_msg[i] : 0;
  }

  char key[N];
  for (size_t i = 0; i < N; i++) {
    key[i] = i < strlen(inp_key) ? inp_key[i] : 0;
  }

  printf("msg            = '");
  print_string(msg);
  printf("'\n");
  printf("key            = '");
  print_string(key);
  printf("'\n");

  char ct[N];
  otp_fixed(ct, msg, key);

  printf("ct = msg ^ key = '");
  print_string(ct);
  printf("'\n");

  char dt[N];
  otp_fixed(dt, ct, key);

  printf("dt = ct  ^ key = '");
  print_string(dt);
  printf("'\n");

  return EXIT_SUCCESS;
}
