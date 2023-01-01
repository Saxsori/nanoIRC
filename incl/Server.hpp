/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:09:31 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/01 04:25:15 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string.h> // strerror
#include <errno.h> 
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntoa
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <algorithm>
#include <vector>
#include <signal.h>
#define PORT 6666
#define	MAXCLNT 10
#define	WLCMSG "Welcome to nano server \r\n"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"
# define BPUR "\e[0;35m"
# define DEFCOLO "\033[0m"

class Server
{
	private:
		int							_masterSocket;
        int 						_opt;
   		struct sockaddr_in			_address;
		int							_addrlen;
		fd_set						_readfds; // fds set
    	int							_maxSocketfd; // will be used to define the range of the fds
		std::vector <int>			_clientSocket;
		std::vector <std::string>	_msgStorage;
		int							_totalBitSet;
		int							_newSocket;
		int							_readbyte;
		char						_msgBuffer[1025];
	public:
		Server();
		~Server();
		int		creatSocket();
		int		bindSocket();
		void	resetClients();
		int		connectClients();
		void	getClientMsg();
};

class TerminateServer : public std::exception
{
	public:
		const char* what() const throw()
		{
			return (BYEL"The server is terminated!");
		}
};

#endif