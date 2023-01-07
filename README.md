# Nano IRC Server 🐭

Internet Relay Chat (IRC) is Internet servers that use a specific protocol through which individuals can hold real-time online conversations. This was my own implementation of the server before applying the IRC protocols. This server has been created to understand the socket programming and to study the select function behavior. It was the very beginning step to our own [IRC server](https://github.com/i99dev/ft_irc).

## About Nano
Nono server is only capable to send and receive messages from muiltiple clients at the same time, and can manage receiving partial data from each one of them without interruption 🐁.

Each and every step was explained breifly in the comments on the top of each line, [chcek them out](https://github.com/Saxsori/nanoIRC/blob/main/src/Server.cpp).

The following conditions have been succesfully handeled in this server:
- Unxpected disconnection ex.terminate of the terminal that run the client or closing it using Ctrl-C.
- The server should be always running even if the client disconnect.
- Ctrl-C to terminate the server after usage without leaks.
- The partial data can be tested through nc, using Ctrl-D to cut the message.

## Select function
It is a system call that allows a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some type of I/O operation. It's useful in situations where you want to monitor multiple file descriptors. It's commonly used in network programming, where it can be used to monitor sockets for incoming data or connection requests. This function was mainly used in this program to monitor multi-clients at the same time.

``` ruby
int select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
```




https://user-images.githubusercontent.com/92129820/210158193-4d4a18ce-0af7-4f42-bb98-54af4c8adc39.mov





Resourses:
- [Socket programming](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Handeling multiple clients on Server](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/?ref=lbp)
