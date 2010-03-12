
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "logging.h"
#include "ei.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "show_msg.h"

ei_cnode ec;
int fd = -1;

static void usage(void) {
	die("USAGE: erlua-node node_name cookie server_node_name");
}

int receive_message(int fd, erlang_msg *msg, ei_x_buff *ibuf) {
	info("receive_message()");
	int status = ei_xreceive_msg(fd, msg, ibuf);
	return status;
}

int main(int argc, char **argv)
{

	// argument safety
	if (argc < 2) {
		usage();
	}

	info("erlua-node: starting up...");

	if (ei_connect_init(&ec, argv[1], argv[2], 0) == -1) {
		die("ERROR: failed to initialize connection");
	}

	fd = ei_connect(&ec, argv[3]);
	if (fd < 0) {
		die("ERROR: failed to connect to erlang node: %s", argv[3]);
	}

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	assert( lua_gettop(L) == 0 );

	int stop = 0;

	int status;
	erlang_msg msg;
	ei_x_buff ibuf;
	ei_x_new(&ibuf);

	while (!stop) {
		status = receive_message(fd, &msg, &ibuf);
		ei_show_recmsg(stderr, &msg, (char *)&ibuf);
	}

	return(0);
}
