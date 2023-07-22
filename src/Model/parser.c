#include "parser.h"

void parser(char *filename, vector *vector_v, vector_int *vector_f) {
  char *buffer = NULL;
  size_t len = MAX_LENGHT;

  FILE *fp = fopen(filename, "r");

  while ((getline(&buffer, &len, fp)) != -1) {
    if (buffer[0] == 'v') {
      get_v(buffer, vector_v);
    } else if (buffer[0] == 'f') {
      get_f(buffer, vector_f);
    }
  }
  free(buffer);

  fclose(fp);
}

void get_v(char *buffer, vector *vector_v) {
  int result;
  float number1, number2, number3;

  result = sscanf(buffer, "v %f %f %f", &number1, &number2, &number3);

  if (result == 3) {
    s21_push(vector_v, number1);
    s21_push(vector_v, number2);
    s21_push(vector_v, number3);
  }
}

void get_f(char *buffer, vector_int *vector_f) {
  unsigned count = 0;
  unsigned num = 0;
  int space_flag = 0;
  int k = 0;
  char new_buf[MAX_LENGHT] = {};

  for (int i = 1; buffer[i] != '\0'; i++) {
    if (is_digit(buffer[i]) && buffer[i - 1] == ' ') {
      while (is_digit(buffer[i])) {
        space_flag = 1;
        new_buf[k] = buffer[i];
        k++;
        i++;
      }
    }

    if ((buffer[i] == ' ' || buffer[i] == '\n') && space_flag == 1) {
      sscanf(new_buf, "%u", &num);
      if (count == 0) {
        s21_push_int(vector_f, num - 1);
        count = num;
      } else {
        s21_push_int(vector_f, num - 1);
        s21_push_int(vector_f, num - 1);
      }
      memset(new_buf, '\0', MAX_LENGHT);

      space_flag = 0;
      k = 0;
      num = 0;
    }
  }
  s21_push_int(vector_f, count - 1);
}

int is_digit(char buffer) { return (buffer >= '0' && buffer <= '9'); }
