#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16

extern char *otp(char *ct, const char *msg, const char *key, const uint64_t n);
extern char *otp_fixed(char *ct, const char *msg, const char *key);

size_t min(size_t x, size_t y) { return x < y ? x : y; }

void print_string(const char *s, uint64_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("0x%02x ", s[i]);
  }
  printf("\b");
}

int check_otp(const char *msg, const char *key, uint64_t n) {
  printf("msg            = '");
  print_string(msg, n);
  printf("'\n");
  printf("key            = '");
  print_string(key, n);
  printf("'\n");

  char ct[n];
  otp(ct, msg, key, n);

  printf("ct = msg ^ key = '");
  print_string(ct, n);
  printf("'\n");

  char dt[n];
  otp(dt, ct, key, n);

  printf("dt = ct  ^ key = '");
  print_string(dt, n);
  printf("'\n");

  return 0;
}

int check_otp_fixed(const char *inp_msg, const char *inp_key) {
  char msg[N];
  for (size_t i = 0; i < N; i++) {
    msg[i] = i < strlen(inp_msg) ? inp_msg[i] : 0;
  }

  char key[N];
  for (size_t i = 0; i < N; i++) {
    key[i] = i < strlen(inp_key) ? inp_key[i] : 0;
  }

  printf("msg            = '");
  print_string(msg, N);
  printf("'\n");
  printf("key            = '");
  print_string(key, N);
  printf("'\n");

  char ct[N];
  otp_fixed(ct, msg, key);

  printf("ct = msg ^ key = '");
  print_string(ct, N);
  printf("'\n");

  char dt[N];
  otp_fixed(dt, ct, key);

  printf("dt = ct  ^ key = '");
  print_string(dt, N);
  printf("'\n");

  return 0;
}

int main(int argn, char **argv) {
  if (argn != 3) {
    printf("ERROR: invalid number of arguments.\n");
    return EXIT_FAILURE;
  }

  char *inp_msg = argv[1];
  char *inp_key = argv[2];

  size_t len_msg = strlen(inp_msg);
  size_t len_key = strlen(inp_key);

  if (len_key < len_msg) {
    printf("ERROR: key is too short.\n");
    return EXIT_FAILURE;
  }

  printf("Checking otp\n");
  int res = check_otp(inp_msg, inp_key, len_msg);
  printf("\nChecking otp_fixed\n");
  res |= check_otp_fixed(inp_msg, inp_key);

  return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
