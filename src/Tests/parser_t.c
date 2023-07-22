#include "../Model/parser.h"
#include "tests.h"

START_TEST(parser_normal_behavior) {
  vector vector_v = s21_create_vector();
  vector_int vector_f = s21_create_vector_int();

  parser("./cub.obj", &vector_v, &vector_f);

  int bigger = 0;
  int biggerInt = 0;

  if (vector_v.size > 10 && vector_f.size > 10) {
    bigger = 1;
    biggerInt = 1;

    ck_assert_int_eq(bigger, biggerInt);
  }

  free(vector_v.data);
  free(vector_f.data);
}
END_TEST

Suite *parser_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("parser_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, parser_normal_behavior);
  suite_add_tcase(s, tc_core);

  return s;
}

int parser_t() {
  int not_failed = 0;
  Suite *s;
  SRunner *sr;

  s = parser_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed;
}