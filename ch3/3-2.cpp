#include <cstdio>

int write_to(char *str, size_t len, char c, size_t pos) {
  if (pos >= len) {
    return -1;
  }
  str[pos] = c;
  return 0;
}

char read_from(const char *str, size_t len, size_t pos) {
  if (pos >= len) {
    return -1;
  }
  return str[pos];
}
int main() {
  char lower[] = "abc?e";
  char upper[] = "ABC?E";
  char *upper_ptr = upper;

  auto lower_len = sizeof(lower) / sizeof(lower[0]);
  auto upper_len = sizeof(upper) / sizeof(upper[0]);

  write_to(lower, lower_len, 'd', 3);
  write_to(upper, upper_len, 'D', 3);
  char letter_d = read_from(lower, lower_len, 3);
  printf("lower[3] = %c\n", letter_d);

  char letter_D = read_from(upper_ptr, upper_len, 3);
  printf("upper[3] = %c\n", letter_D);

  printf("lower: %s\nupper: %s\n", lower, upper);
  if (write_to(lower, lower_len, 'g', 7) != -1) {
    printf("danger danger");
  }
}