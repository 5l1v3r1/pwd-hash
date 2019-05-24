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

#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "random_str.h"

#define SCHAR_MAX 64


/* retrieve len random characters and store them into buf */
int random_str(int len, char *buf) {

  char charset[64];
  char *p;
  int i=0, c;

  if (len == 0)
    return 1;

  p=charset;

  /* [a-z] */
  for(c=97; c<=122; c++)
    *p++=c;
  /* [A-Z] */
  for(c=65; c<=90; c++)
    *p++=c;
  /* [0-9] */
  for(c=48; c<=57; c++)
    *p++=c;
  *p++ = '.';
  *p = '/';

  while (i < len)
    buf[i++] = charset[urand() % SCHAR_MAX];
  buf[i] = '\0';

  return 0;
}

/* return a random integer from /dev/urandom */
int urand(void) {

  unsigned char c;
  int fd;

  if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
    fprintf(stderr, "Open /dev/urandom failed.\n");
    exit(1);
  }

  read(fd, (void *) &c, sizeof(c));

  close(fd);
  return c;
}
