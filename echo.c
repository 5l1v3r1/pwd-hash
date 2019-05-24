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

#include <termios.h>

int set_local_echo(int status) {

  int ret;
  struct termios t, t_bkp;

  if ((ret = tcgetattr(0, &t)) == -1)
    return 1;

  t_bkp = t;

  if (status) 
     t.c_lflag = t.c_lflag | ECHO;
  else 
     t.c_lflag = t.c_lflag & (~ECHO);

  if ((ret = tcsetattr(0, TCSANOW, &t)) == -1)
    return 1;

  return 0;
}
