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
static bool run_as_daemon = false;
static char *pid_file;

extern sigset_t mask;
static pthread_t tid_signal_handler;

/* uds server as entry point for (xfce)-panel applications */
// static pthread_t tid_uds_server;
static char *kdo_uds_file;
static int kdo_socket_uds = -1;

/* inet server for device managment */
static pthread_t tid_inet_server;
static int kdo_socket_inet = -1;

/* control can/lin environment */
// static pthread_t tid_can_server;
static char *kdo_can_file;
static int kdo_can_uds = -1;

/* control time triggert environment */
// static pthread_t tid_ttenv_server;
static char *kdo_ttenv_file;
static int kdo_ttenv_uds = -1;

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

	if (unlink(kdo_uds_file) != 0)
		baa_errno_msg(_("could not remove %s"), kdo_uds_file);

	if (kdo_can_uds != -1)
		baa_wrap_close(kdo_can_uds);

	if (unlink(kdo_can_file) != 0)
		baa_errno_msg(_("could not remove %s"), kdo_can_file);

	if (kdo_ttenv_uds != -1)
		baa_wrap_close(kdo_ttenv_uds);

	if (unlink(kdo_ttenv_file) != 0)
		baa_errno_msg(_("could not remove %s"), kdo_ttenv_file);

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
	baa_info_msg(_("        -d   run as daemon                      "));
	baa_info_msg(_("        -i   start inet server                  "));
	baa_info_msg(_("        -l   start local server (in progress)   "));
	baa_info_msg(_("        -c   start can/lin-env server (not yet) "));
	baa_info_msg(_("        -t   start tt-env server (not yet)      "));
	baa_info_msg(_("        -f   baalued.conf -> use config file    "));
	baa_info_msg(_("             (this will override kdo arguments!)"));
	baa_info_msg(_("        -h   show help                          "));
	putchar('\n');

	exit(status);
}

static void
daemon_handling(void)
{
	int err = baa_become_daemon();
	if (err != 0)
		baa_error_exit("become_daemon() != 0");

	baa_enable_syslog(true, program_name);

	pid_file = baa_create_file_with_pid(program_name, BAA_VAR_RUN_DIR);
	if (pid_file == NULL)
		baa_error_exit("could not create %s", pid_file);
}

static void
setup_inet_server(void)
{
	kdo_socket_inet = baa_inet_dgram_server(baalued_port);
	if (kdo_socket_inet == -1)
		baa_error_exit("could not create inet kdo socket");

	int err = pthread_create(&tid_inet_server, NULL,
				 baa_device_mgmt_th, (void *) &kdo_socket_inet);
	if (err != 0)
		baa_th_error_exit(err, "could not create pthread");
}

static void
setup_local_server(void)
{
	// do something
}

static void
setup_can_server(void)
{
	// do something
}

static void
setup_ttenv_server(void)
{
	// do something
}

int
main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	char *config_file = NULL;
	struct baalued_config conf;
	memset(&conf, 0, sizeof(conf));

	baa_set_program_name(&program_name, argv[0]);

	int c;
	while ((c = getopt(argc, argv, "hdilcf:")) != -1) {
		switch (c) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'd':
			conf.run_as_daemon = true;
			break;
		case 'i':
			conf.start_inet_server = true;
			break;
		case 'l':
			conf.start_local_server = true;
			break;
		case 'c':
			conf.start_can_server = true;
			break;
		case 't':
			conf.start_ttenv_server = true;
			break;
		case 'f':
			config_file = optarg;
			break;
		default:
			baa_error_msg(_("ERROR: no valid argument\n"));
			usage(EXIT_FAILURE);
		}
	}

	int err = atexit(cleanup);
	if (err != 0)
		exit(EXIT_FAILURE);

	if (config_file != NULL)
		err = read_config(config_file, &conf); /* override kdo args */
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
	if (run_as_daemon)
		daemon_handling();

	/*
	 * signal handling -> a thread for signal handling
	 */
	sigfillset(&mask);
	err = pthread_sigmask(SIG_BLOCK, &mask, NULL);
	if (err != 0)
		baa_th_error_exit(err, "could not set sigmask");

	err = pthread_create(&tid_signal_handler, NULL,
			     signal_handler, (void *) run_as_daemon);
	if (err != 0)
		baa_th_error_exit(err, "could not create pthread");

	/*
	 * setup inet udp server device managment thread
	 */
	if (conf.start_inet_server)
		setup_inet_server();

        /*
	 * setup unix domain server gateway to baalue-nodes
	 */
	if (conf.start_local_server)
		setup_local_server();

        /*
	 * setup can daemon
	 */
	if (conf.start_can_server)
		setup_can_server();

	/*
	 * setup control daemon for time-triggert infrastructure
	 */
	if (conf.start_ttenv_server)
		setup_ttenv_server();

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
	// (void) pthread_join(tid_can_server, NULL);
	// (void) pthread_join(tid_time_triggert_server, NULL);
	(void) pthread_join(tid_inet_server, NULL);
	(void) pthread_join(tid_signal_handler, NULL);

	return EXIT_SUCCESS;
}
