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

static char *pid_file;
static char *kdo_file;
static int kdo_socket_uds = -1;
static int kdo_socket_inet = -1;

extern sigset_t mask;

/* 8101-8114   Unassigned */
const char baalued_port[] = "8111";

static void
cleanup(void)
{
#ifdef __DEBUG__
	baa_info_msg(_("finalize cleanup"));
#endif
	if (kdo_socket_inet != -1)
		baa_wrap_close(kdo_socket_inet);

	if (kdo_socket_uds != -1)
		baa_wrap_close(kdo_socket_uds);

	if (unlink(kdo_file) != 0)
		baa_errno_msg(_("could not remove %s"), kdo_file);

	if (unlink(pid_file) != 0)
		baa_errno_msg(_("could not remove %s"), pid_file);

	baa_info_msg(_("cheers %s"), getenv("USER"));
}

static void
__attribute__((noreturn)) usage(int status)
{
	putchar('\n');
	baa_info_msg(_("Usage: %s [options]                             "),
		     program_name);
	baa_info_msg(_("Options:                                        "));
	baa_info_msg(_("        -h   show help                          "));
	putchar('\n');

	exit(status);
}

int
main(int argc, char *argv[])
{
	pthread_t tid_signal_handler;
	// pthread_t tid_udp_server;
	pthread_t tid_inet_server;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	baa_set_program_name(&program_name, argv[0]);

	int c;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			baa_error_msg(_("ERROR: no valid argument\n"));
			usage(EXIT_FAILURE);
		}
	}

	int err = atexit(cleanup);
	if (err != 0)
		exit(EXIT_FAILURE);

	/*
	 * we dont need root rights
	 */
	//err = baa_drop_capability(CAP_SYS_NICE);
	//if (err == -1)
	//	exit(EXIT_FAILURE);

	show_some_infos();

	/*
	 * daemon handling
	 */
	err = baa_become_daemon();
	if (err != 0)
		baa_error_exit("become_daemon() != 0");

	baa_enable_syslog(true, program_name);

	pid_file = baa_create_file_with_pid(program_name, BAA_VAR_RUN_DIR);
	if (pid_file == NULL)
		baa_error_exit("could not create %s", pid_file);

	/*
	 * signal handling -> a thread for signal handling
	 */
	sigfillset(&mask);
	err = pthread_sigmask(SIG_BLOCK, &mask, NULL);
	if (err != 0)
		baa_th_error_exit(err, "could not set sigmask");

	err = pthread_create(&tid_signal_handler, NULL, signal_handler, 0);
	if (err != 0)
		baa_th_error_exit(err, "could not create pthread");

	/*
	 * setup inet udp server device managment thread
	 */
	kdo_socket_inet = baa_inet_dgram_server(baalued_port);
	if (kdo_socket_inet == -1)
		baa_error_exit("could not create inet kdo socket");

	err = pthread_create(&tid_inet_server, NULL,
			     baa_device_mgmt_th, (void *) &kdo_socket_inet);
	if (err != 0)
		baa_th_error_exit(err, "could not create pthread");

	/*
	 * the other threads/tasks:
	 *
	 * - time-triggert stuff (tid_udp_server)
	 * - can stuff
	 * - a20_sdk stuff (clone/pull /opt/a20_sdk/external/...)
	 * - hypervisor control stuff
	 * - libxbps stuff (update void-linux)
	 */

	// (void) pthread_join(tid_udp_server, NULL);
	(void) pthread_join(tid_inet_server, NULL);
	(void) pthread_join(tid_signal_handler, NULL);

	return EXIT_SUCCESS;
}
