
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "logging.h"
#include "ei.h"

ei_cnode ec;
int fd = -1;

static void usage(void) {
	die("USAGE: erlua-node node_name cookie server_node_name");
}

int main(int argc, char **argv)
{

	// argument safety
	if (argc < 2) {
		usage();
	}

	if (ei_connect_init(&ec, argv[1], argv[2], 0) == -1) {
		die("ERROR: failed to initialize connection");
	}

	fd = ei_connect(&ec, argv[3]);
	if (fd < 0) {
		die("ERROR: failed to connect to erlang node: %s", argv[3]);
	}

	return(0);
}
