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


void usage(char *argv0) {

  printf("Usage: %s <option>\n\
Display the password hash of a string given on stdin.\n\n\
Options are:\n\n\
   --des\t\tTraditional DES-based scheme\n\
   --md5\t\tMD5-based scheme (this is the default)\n\
   --grub\t\tMD5-based scheme with a 6 bytes salt (as used in GRUB)\n\
   --sha\t\tSHA-based scheme (SHA-512), libc version >= 2.7\n\n\
   --salt <string>\tSpecify a salt instead of random string\n\
   -n, --noecho\t\tDo not echo input characters\n\
   -h, --help\t\tDisplay this help\n\
   -v, --version\tDisplay version\n\n\
Examples: \n\n\
   $ echo \"P4ssw0rD\" | pwd-hash --md5\n\
   $ pwd-hash --des <<<\"P4ssw0rD\"\n\
   $ pwd-hash --noecho --sha\n\
   $ pwd-hash --salt \"abcdefgh\" --md5\n\n\
Report bugs to <vladz@devzero.fr>.\n", argv0);

  exit(1);
}
