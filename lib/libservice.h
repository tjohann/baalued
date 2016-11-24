/*
  GPL
  (c) 2016, thorsten.johannvorderbrueggen@t-online.de

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#ifndef _LIBSERVICE_H_
#define _LIBSERVICE_H_

#ifndef __USE_GNU
#define __USE_GNU
#endif
#define _GNU_SOURCE

/* more or less common inc */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <wait.h>
#include <limits.h>
#include <linux/limits.h>
#include <sysexits.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/utsname.h>
#include <sched.h>
#include <time.h>
#include <sys/times.h>
#include <sys/sysinfo.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <grp.h>

/* inotify inc */
#include <sys/inotify.h>

/* more or less network related inc */
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netpacket/packet.h>

/* libconfig */
#include <libconfig.h>

/* autotools generated config */
#include <config.h>

/* getopt and locale realted inc */
#include <getopt.h>
#include <libintl.h>
#include <locale.h>
#include "gettext.h"

/* libcap-ng */
#include <cap-ng.h>

/* https://github.com/tjohann/libbaalue.git */
#include <libbaalue.h>

#define MAX_LEN_MSG 100

void
show_some_infos(void);

void *
signal_handler(void *args);

void *
baalue_server_th(void *args);

#endif
