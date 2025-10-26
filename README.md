# simple_fancy_http_server
turning a simple tcp server into a http server that can handle GET and POST requests

#How to write a basic and simple http server.

Im not going to dive deep and write an elaborate article about a process of building a simple http server, because really under the hood, our http server is basically a simple concurrent TCP/IP server. This server can handle multiple clients requests, by creating a child process, for each request, and handling a request within a child process. All you need to do is bind your socket to a default http port 80 or a popular port 8080, read GET request from a a clinet, in our example, client is a web broweser.

#Basic steps to build a TCP/IP server.

Here i will describe a process of building a TCP/IP server. First we create a straming server`s socket, that will use IPv4 address. Next, we will bind out socket with a port 8080, which is a default http port. After you youve done all this.
We need to mark out socket as listening, so it accept incoming requests from a web broweser client. Next we move into an infinite loop, where we accepting connection from broweser, returning a file descriptor that we will be using to communicate. Also dont forget to use a non blocking I/O mode. After you read a request, we create a child process, and inside this child process we build a http response and send it back to a broweser, and with this being done, you terminate a child process. And keep running a for loop.

So in a nutshell

  * Create server socket
  * bind socket to a port 80 or 8080
  * mark server socket as listening
  * start accepting connection
  * build a http response
  * send response back to a client


# An example of a server reading a GET request from a broweser

<img width="1385" height="433" alt="Screenshot from 2025-10-26 13-22-18" src="https://github.com/user-attachments/assets/0f339552-fd63-4fc7-9afa-69cdb5cbaa47" />


# Server sending a http response to a client

<img width="1852" height="690" alt="Screenshot from 2025-10-26 13-22-33" src="https://github.com/user-attachments/assets/7cba007f-6a66-40df-b59f-95ad4e3d0676" />


So couple words, before we finish. Building a http server actually is really easy process, you create a TCP/IP server using streaming socket, and you just handle a http requests.


