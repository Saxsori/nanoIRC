# Nano IRC Server 🐭

Internet Relay Chat (IRC) is Internet servers that use a specific protocol through which individuals can hold real-time online conversations. This was my own implementation of the server before applying the IRC protocols. This server has been created to understand the socket programming and to study the select functionn behavior. It was the very beginning step on our own [IRC server](https://github.com/i99dev/ft_irc).

## About Nano
Nono server is only capable to send and receive messages from muiltiple clients at the same time, and can manage receiving partial data from each one of them without interruption 🐁.

Each and every step was explained breifly in the comments on the top of each line, [chcek them out](https://github.com/Saxsori/nanoIRC/blob/main/src/Server.cpp).

The following conditions have been succesfully handeled in this server:
- Unxpected disconnection ex.terminate of the terminal that run the client or closing it using ctrl-c.
- The server should be always running even if the client disconnect.
- Ctrl-C to terminate the server after usage without leaks.
- The partial data can be tested through nc, using ctrl-d to cut the message.

## Select function
It is a system call that allows a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some type of I/O operation. It's useful in situations where you want to monitor multiple file descriptors. It's commonly used in network programming, where it can be used to monitor sockets for incoming data or connection requests. This function was mainly used in this program to monitor multi-clients at the same time.

``` ruby
int select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
```



Resourses:
- [Socket programming](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Handeling multiple clients on Server](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/?ref=lbp)
