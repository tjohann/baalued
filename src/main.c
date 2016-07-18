/*
 * example prog for autotool demo
 */

#ifndef __USE_GNU
#define __USE_GNU
#endif
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

// getopt and locale realted inc
#include <getopt.h>
#include <libintl.h>
#include <locale.h>
#include "gettext.h"


int main(void)
{
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);


	printf(_("\nautotool-demo says hello\n"));

	exit (EXIT_SUCCESS);
}
