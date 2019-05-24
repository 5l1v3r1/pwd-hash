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
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "random_str.h"


int enc_3des(char *clear_passwd, char *s) {

  int salt_size = 2;
  char salt[salt_size + 1];

  if (s == NULL) {

    if (random_str(salt_size, salt)) {
      printf("random_str(salt_size,salt): failed\n");
      return 1;
    }

  } else {

    strncpy(salt, s, salt_size+1);
  } 
  
  printf("%s\n", crypt(clear_passwd, salt));

  return 0;
}


int enc_grub(char *clear_passwd, char *s) {

  int salt_size = 6;
  char salt[salt_size + 1];
  char saltmd[salt_size + 5];

  if (s == NULL) {

    if (random_str(salt_size, salt)) {
      printf("random_str(salt_size,salt): failed\n");
      return 1;
    }

  } else {

    strncpy(salt, s, salt_size+1);
  }

  sprintf(saltmd, "$1$%s$", salt);
  printf("%s\n", crypt(clear_passwd, saltmd));

  return 0;
}


int enc_md5(char *clear_passwd, char *s) {

  int salt_size = 8;
  char salt[salt_size + 1];
  char saltmd[13];

  if (s == NULL) {

    if (random_str(salt_size, salt)) {
      printf("random_str(salt_size,salt): failed\n");
      return 1;
    }

  } else {

    strncpy(salt, s, salt_size+1);
  }

  sprintf(saltmd, "$1$%s$", salt);
  printf("%s\n", crypt(clear_passwd, saltmd));

  return 0;
}

int enc_sha(char *clear_passwd, char *s) {

  int salt_size = 8;
  char salt[salt_size + 1];
  char saltmd[salt_size + 5];

  if (s == NULL) {

    if (random_str(salt_size, salt)) {
      printf("random_str(salt_size,salt): failed\n");
      return 1;
    }

  } else {

    strncpy(salt, s, salt_size+1);
  }

  sprintf(saltmd, "$6$%s$", salt);
  printf("%s\n", crypt(clear_passwd, saltmd));

  return 0;
}
