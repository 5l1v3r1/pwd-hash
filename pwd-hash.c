/*
    Copyright (C) vladz <vladz@devzero.fr>

    This file is part of pwd-hash.

    Pwd-hash is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pwd-hash is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pwd-hash.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "echo.h"
#include "pwd-hash.h"
#include "version.h"
#include "schemes.h"

#define MAX_LEN 126


void fatal(char *s) {

  fprintf(stderr, "fatal: %s\n", s);
  exit(1);
}


void remove_newline(char *str) {
  char *p = NULL;

  if ((p = strchr(str, '\n')) != NULL)
    *p = '\0';
}


int main(int argc, char *argv[]) {

  int c;
  char clear_passwd[MAX_LEN];
  int salt_size, needed_salt_size;
  int do_enc_md5 = 0;
  int do_enc_des = 0;
  int do_enc_sha = 0;
  int do_enc_grub = 0;
  int do_not_echo = 0;
  char *salt = NULL;

 /* if (argc == 1)
    usage(argv[0]);*/

  while (1) {

    static struct option long_options[] = {
      {"md5", no_argument, 0, 1},
      {"des", no_argument, 0, 2},
      {"sha", no_argument, 0, 3},
      {"grub", no_argument, 0, 4},
      {"noecho", no_argument, 0, 'n'},
      {"version", no_argument, 0, 'v'},
      {"help", no_argument, 0, 'h'},
      {"salt", required_argument, 0, 0},
      {0, 0, 0, 0}
    };

    int option_index = 0;

    c = getopt_long(argc, argv, "vhn", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {

    case 0:
      if (long_options[option_index].flag != 0)
	break;
      if (optarg)
        salt=optarg;
      break;

    case 1:
      do_enc_md5 = 1;
      needed_salt_size = 8;
      break;

    case 2:
      do_enc_des = 1;
      needed_salt_size = 2;
      break;

    case 3:
      do_enc_sha = 1;
      needed_salt_size = 8;
      break;

    case 4:
      do_enc_grub = 1;
      needed_salt_size = 6;
      break;

    case 'n':
      do_not_echo = 1;
      break;

    case 'v':
      printf("pwd-hash version %s\n", VERSION);
      return 0;

    case 'h':
      usage(argv[0]);

    default:
      return 1;
    }

  }

  /* to many schemes ! Abort. */
  if ((do_enc_md5 + do_enc_des + do_enc_sha + do_enc_grub) > 1)
    fatal("You can only use ONE scheme");

  /* set default encoding scheme to MD5 */
  if ((do_enc_md5 + do_enc_des + do_enc_sha + do_enc_grub) == 0) {
    fprintf(stderr, "No scheme specified, default scheme set to MD5\n");
    do_enc_md5 = 1;
    needed_salt_size = 8;
  }

  if (salt) {

    salt_size = strlen(salt);

    if ((salt_size > 0) && (salt_size != needed_salt_size)) {
      fprintf(stderr, "Correct salt length for this scheme is %d\n", needed_salt_size);
      return 1;
    }
  }

  if (do_not_echo) {

    if (set_local_echo(0) != 0)
      fatal("Can't disable local echo");

    fgets(clear_passwd, MAX_LEN - 1, stdin);

    if (set_local_echo(1) != 0)
      fatal("Can't enable local echo... Type: \"stty echo\"");

  } else
    fgets(clear_passwd, MAX_LEN - 1, stdin);

  remove_newline(clear_passwd);

  if (do_enc_md5) {
    enc_md5(clear_passwd, salt);
  } else if (do_enc_des) {
    enc_3des(clear_passwd, salt);
  } else if (do_enc_sha) {
    enc_sha(clear_passwd, salt);
  } else if (do_enc_grub) {
    enc_grub(clear_passwd, salt);
  }

  return 0;
}
