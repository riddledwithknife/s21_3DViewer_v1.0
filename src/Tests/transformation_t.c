#include "../Model/transformation.h"
#include "tests.h"

START_TEST(scale_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  int fail = 0;

  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  scale(&vector_v, value);

  if (vector_v.data[0] != 0) {
    fail = 1;
  }

  if (vector_v.data[1] != 2) {
    fail = 1;
  }

  if (vector_v.data[2] != 2) {
    fail = 1;
  }

  ck_assert_int_eq(fail, 0);

  free(vector_v.data);
}
END_TEST

START_TEST(move_x_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  int fail = 0;

  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  move_x(&vector_v, value);

  if (vector_v.data[0] != 2) {
    fail = 1;
  }

  ck_assert_int_eq(fail, 0);

  free(vector_v.data);
}
END_TEST

START_TEST(move_y_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  int fail = 0;

  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  move_y(&vector_v, value);

  if (vector_v.data[1] != 3) {
    fail = 1;
  }

  ck_assert_int_eq(fail, 0);

  free(vector_v.data);
}
END_TEST

START_TEST(move_z_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  int fail = 0;

  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  move_z(&vector_v, value);

  if (vector_v.data[2] != 3) {
    fail = 1;
  }

  ck_assert_int_eq(fail, 0);

  free(vector_v.data);
}
END_TEST

START_TEST(rotate_x_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  rotate_x(&vector_v, value);

  free(vector_v.data);
}
END_TEST

START_TEST(rotate_y_normal_behavior) {
  vector vector_v = s21_create_vector();
  double value = 200;
  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  rotate_y(&vector_v, value);

  free(vector_v.data);
}
END_TEST

START_TEST(centralize_normal_behavior) {
  vector vector_v = s21_create_vector();
  vector vector_v2 = s21_create_vector();
  s21_push(&vector_v, 0);
  s21_push(&vector_v, 1);
  s21_push(&vector_v, 1);

  s21_push(&vector_v2, 0);
  s21_push(&vector_v2, 1);
  s21_push(&vector_v2, 2);

  centralize(&vector_v);
  centralize(&vector_v2);

  free(vector_v.data);
  free(vector_v2.data);
}
END_TEST

Suite *transformation_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("transformation_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, scale_normal_behavior);
  tcase_add_test(tc_core, move_x_normal_behavior);
  tcase_add_test(tc_core, move_y_normal_behavior);
  tcase_add_test(tc_core, move_z_normal_behavior);
  tcase_add_test(tc_core, rotate_x_normal_behavior);
  tcase_add_test(tc_core, rotate_y_normal_behavior);
  tcase_add_test(tc_core, centralize_normal_behavior);
  suite_add_tcase(s, tc_core);

  return s;
}

int transformation_t() {
  int not_failed = 0;
  Suite *s;
  SRunner *sr;

  s = transformation_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed;
}