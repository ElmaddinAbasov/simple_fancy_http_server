#include "interface.h"

main()
{
	int cfd;
	const char* message = "Hello";
	create_socket(&cfd, AF_INET, SOCK_STREAM);
	bind_socket(cfd, client_port);
	connect_to_a_server(cfd, server_port);
	send_message(cfd, message);
	reuse_port(cfd);
	close_connection(cfd);
	exit(0);
}
