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

#include "libservice.h"


static char *program_name;
static int running_mode = RUN_AS_APPLICATION;

static void
__attribute__((noreturn)) usage(int status)
{
	putchar('\n');
	fprintf(stdout, _("Usage: %s [options]              \n"), program_name);
	fprintf(stdout, _("Options:                                       \n"));

	fprintf(stdout, _("        -h                 \
show help                                             \n"));
	fprintf(stdout, _("        -a                 \
run as application in foreground                      \n"));
	fprintf(stdout, _("        -s                 \
run as service/daemon in background (syslog enabled)  \n"));
	putchar('\n');

	exit(status);
}

static void
cleanup(void)
{
	fprintf(stdout, _("Finalize cleanup -> cheers %s\n"), getenv("USER"));
}


int
main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	baa_set_program_name(&program_name, argv[0]);

	int c;
	while ((c = getopt(argc, argv, "hasf:d:")) != -1) {
		switch (c) {
		case 'a':
			running_mode = RUN_AS_APPLICATION;
			break;
		case 's':
                        running_mode = RUN_AS_DAEMON;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			fprintf(stderr, _("ERROR: no valid argument\n"));
			usage(EXIT_FAILURE);
		}
	}

	if (atexit(cleanup) != 0)
		exit(EXIT_FAILURE);

	if (running_mode == RUN_AS_DAEMON) {
		if (baa_become_daemon() != 0) {
			baa_error_exit(_("become_daemon() != 0"));
		} else {
			baa_info_msg(_("now i'm a daemon"));
		}
	} else {
		baa_info_msg(_("run in foreground as application"));
	}




	// only for testing
	sleep(20);

	return EXIT_SUCCESS;
}
