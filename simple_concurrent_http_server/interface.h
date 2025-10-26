#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
enum {client_port = 3000};
enum {server_port = 4000};
enum {http_default_port = 8080};
enum {sleep_time = 3};
enum {max_num_client_server_want_to_handle = 2};
create_socket(fd, domain, type);
bind_socket(fd, port);
reuse_port(fd);
listening(fd, queue_size);
accept_connection(fd, rfd, address);
connect_to_a_server(fd, server_port);
non_blocking_io_mode(fd, flag);
send_message(fd, message);
recieve_message(fd, message, length);
close_connection(fd);
#endif
