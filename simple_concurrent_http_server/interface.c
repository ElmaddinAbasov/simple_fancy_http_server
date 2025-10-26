#include "interface.h"

create_socket(fd, domain, type)
int* fd;
int domain;
int type;
{
	errno = 0;
	*fd = socket(domain, type, 0);
	if (*fd == -1)
	{
		perror("ERROR: failed to create a socket -> create_socket(fd, domain, type)");
		exit(1);
	}
}

bind_socket(fd, port)
int fd;
int port;
{
	struct sockaddr_in s;
	int res;
	socklen_t slen;
	s.sin_family = AF_INET;
	s.sin_port = htons(port);
	s.sin_addr.s_addr = htons(INADDR_ANY);
	slen = sizeof(s);
	errno = 0;
	res = bind(fd, (const struct sockaddr*)&s, slen);
	if (res == -1)
	{
		perror("ERROR: failed to bind a socket with port");
		exit(2);
	}
}

reuse_port(fd)
int fd;
{
	int res, n;
	n = 0;
	errno = 0;
	res = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&n, sizeof(n));
	if (res == -1)
	{
		perror("ERROR : Failed to reuse specified address -> reuse_port(fd)");
		exit(3);
	}
}

listening(fd, queue_size)
int fd;
int queue_size;
{
	int res;
	errno = 0;
	res = listen(fd, queue_size);
	if (res == -1)
	{
		perror("ERROR: Failed to mark a socket as a listening socket\n");
		exit(4);
	}
}

accept_connection(fd, rfd, address)
int fd;
int* rfd;
struct sockaddr_in* address;
{
	socklen_t len;
	errno = 0;
	*rfd = accept(fd, (struct sockaddr*)address, &len);
	if (*rfd == -1)
	{
		perror("ERROR: Failed to accept a connection from a client\n");
		exit(5);
	}
}

connect_to_a_server(fd, server_port)
int fd;
int server_port;
{
	int res;
	struct sockaddr_in server_address;
	socklen_t slen;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	errno = 0;
	res = connect(fd, (const struct sockaddr*)&server_address, slen);
	if (res == -1)
	{
		perror("ERROR: Failed to connect to a server\n");
		exit(6);
	}
}

non_blocking_io_mode(fd, flag)
int* fd;
int* flag;
{
	int flags, res;
	errno = 0;
	flags = fcntl(*fd, F_GETFL, 0);
	if (flags == -1)
	{
		perror("ERROR: Failed to get a flags from file descriptor\n");
		exit(7);
	}
	flags |= O_NONBLOCK;
	fcntl(*fd, F_SETFL, flags);
	*flag = 1;
}

send_message(fd, message)
int fd;
const char* message;
{
	int length;
	ssize_t cnt;
	length = strlen(message);
	errno = 0;
	cnt = write(fd, message, length);
	if (cnt == -1)
	{
		perror("ERROR: Failed to send a message\n");
		exit(7);
	}
}

recieve_message(fd, message, length)
int fd;
char* message;
{
	ssize_t cnt;
	for (;;)
	{
		sleep(sleep_time);
		errno = 0;
		cnt = read(fd, message, length);
		if (cnt == -1 || cnt == 0)
			break;
		if (cnt)
		{
			*(message + cnt) = 0;
			break;
		}
	}
}

close_connection(fd)
int fd;
{
	int res;
	errno = 0;
	res = close(fd);
	if (res == -1)
	{
		perror("ERROR: Failed to close a socket -> close_connection(fd)");
		exit(8);
	}
}
