/* sb_tst.c - self-test. */

/* This work is dedicated to the public domain under CC0 1.0 Universal:
 * http://creativecommons.org/publicdomain/zero/1.0/
 * 
 * To the extent possible under law, Steven Ford has waived all copyright
 * and related or neighboring rights to this work. In other words, you can 
 * use this code for any purpose without any restrictions.
 * This work is published from: United States.
 * Project home: https://github.com/fordsfords/sb
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "err.h"
#include "sb.h"


#define ASSRT(cond_expr) do { if (!(cond_expr)) { fprintf(stderr, "ASSRT failed at %s:%d (%s)\n", ERR_BASENAME(__FILE__), __LINE__, #cond_expr); fflush(stderr); abort(); } } while (0)


int main(int argc, char **argv)
{
  err_t *err;
  char *sb_str;
  size_t str_len;
  sb_t *sb;

  err = sb_constructor(&sb, 5);  ERR_A(err);
  err = sb_destructor(sb);  ERR_A(err);

  err = sb_constructor(&sb, 0);
  ASSRT(err != ERR_OK && err->code == EINVAL);
  err_dispose(err);

  err = sb_constructor(&sb, 5);  ERR_A(err);
  err = sb_append_char(sb, '1');  ERR_A(err);
  err = sb_append_char(sb, '2');  ERR_A(err);
  err = sb_append_char(sb, '3');  ERR_A(err);
  err = sb_append_char(sb, '4');  ERR_A(err);
  err = sb_append_char(sb, '5');  ERR_A(err);
  err = sb_append_char(sb, '6');  ERR_A(err);
  err = sb_append_char(sb, '7');  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "1234567"));
  ASSRT(sb->alloc_size == 9);

  err = sb_append_str(sb, "89012345678");  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "123456789012345678"));

  err = sb_append_int(sb, -1);  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "123456789012345678-1"));

  err = sb_append_uint(sb, -1);  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "123456789012345678-118446744073709551615"));

  err = sb_append_bytes(sb, "xyz", 3);  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "123456789012345678-118446744073709551615xyz"));

  err = sb_str_len(sb, &str_len);  ERR_A(err);
  ASSRT(str_len == strlen("123456789012345678-118446744073709551615xyz"));

  err = sb_set_len(sb, 3);  ERR_A(err);
  err = sb_str_ref(sb, &sb_str);  ERR_A(err);
  ASSRT(0 == strcmp(sb_str, "123"));

  err = sb_set_len(sb, 4);
  ASSRT(err != ERR_OK && err->code == EINVAL);
  err_dispose(err);

  err = sb_destructor(sb);  ERR_A(err);

  fprintf(stderr, "OK\n"); fflush(stderr);

  return 0;
}  /* main */
