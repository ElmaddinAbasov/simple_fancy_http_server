#include "interface.h"
enum {size = 512};
static char message[size];
static char http_response[] = "HTTP/1.1 200 OK\r\n"
				"Server: fancy_hhtp_server\r\n"
				"Content-Type: text/html\r\n\r\n"
				"<!DOCTYPE html>\r\n"
				"<html>\r\n"
				"<head>\r\n"
				"<title>Fancy HTTP server</title>\r\n"
				"</head>\r\n"
				"<body>\r\n"
				"<h1>Hello, from a server</h1>\r\n"
				"</body>\r\n"
				"</html>\r\n"
				;
main()
{
	int sfd, rfd, flag, length, num_of_clients;
	pid_t child_process;
	struct sockaddr_in client_address;
	create_socket(&sfd, AF_INET, SOCK_STREAM);
	bind_socket(sfd, http_default_port);
	listening(sfd, SOMAXCONN);
	flag = 0;
	num_of_clients = 0;
	for (;;)
	{
		accept_connection(sfd, &rfd, &client_address);
		errno = 0;
		child_process = fork();
		if (child_process == -1)
		{
			perror("ERROR: server failed to create a child process to handle a client request\n");
			exit(8);
		}
		if (child_process == 0)
		{
			close(sfd);
			if (!flag)
				non_blocking_io_mode(&rfd, &flag);
			recieve_message(rfd, message, size);
			length = strlen(message);
			if (length || !length)
				printf("message - %s\n", message);
			send_message(rfd, http_response);
			close(rfd);
			_exit(0);
		}
		wait(NULL);
		num_of_clients++;
		if (num_of_clients == max_num_client_server_want_to_handle)
			break;
	}
	reuse_port(sfd);
	close_connection(sfd);
	exit(0);
}
