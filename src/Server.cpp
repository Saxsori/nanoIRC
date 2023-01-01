/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:10:46 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/01 04:14:25 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

Server::Server()
{
	this->_masterSocket = 0;
	this->_opt = 1;
	this->_address.sin_family = AF_INET;  
    this->_address.sin_addr.s_addr = INADDR_ANY;  
    this->_address.sin_port = htons(PORT);
    this->_addrlen = sizeof(this->_address);
}

int	Server::creatSocket()
{
	// ? create a socket for a server
	if (!(this->_masterSocket = socket(AF_INET , SOCK_STREAM , 0)))  
    {
		std::cout << "Socket: " << strerror(errno) << std::endl;
		return (0);
    }
	// /*
	// 	! optional to add
	// */
    // if (setsockopt(this->_masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&this->_opt, sizeof(this->_opt)) < 0)  
    // {
	// 	std::cout << "Setsockopt: " << strerror(errno) << std::endl;
	// 	return (0);
    // }
	return (1);
}

int	Server::bindSocket()
{
	// * bind the socket to the the address (localhost) and to the port  
	if (bind(this->_masterSocket, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)  
    {
		std::cout << BRED << "Bind: " << strerror(errno) << DEFCOLO << std::endl;
		return (0);
	}
	std::cout << BCYN << "Listener on port " << PORT << DEFCOLO << std::endl;
	
	/*
	? make server waits for the client connect
	? define the length of queue of pending connection for the server
	? if a connection request arrives when the queue is full, the client will be rejected 
	*/
	if (listen(this->_masterSocket, 1) < 0) 
    {
		std::cout << BRED << "Listen: " << strerror(errno) << DEFCOLO << std::endl;
		return (0);
    }
	return (1);
}

void	Server::resetClients()
{
	// ? clear the fds from the set, used to initialize the fds set
	FD_ZERO(&this->_readfds);
	
	// ? adding server socket to the set
	FD_SET(this->_masterSocket, &this->_readfds);
	
	// ? adding client's socket fds to the set
	for (std::vector<int>::iterator it = this->_clientSocket.begin(); it != this->_clientSocket.end(); it++)
		FD_SET(*it, &this->_readfds);
	
	// ? geting the max fd
	if (!this->_clientSocket.empty())
		this->_maxSocketfd = *max_element(this->_clientSocket.begin(), this->_clientSocket.end());
	else
		this->_maxSocketfd = this->_masterSocket;
}

int	Server::connectClients()
{
	// ? indicate which of the specified fds is ready to reading
	if (((this->_totalBitSet = select(this->_maxSocketfd + 1, &this->_readfds, NULL, NULL, NULL)) < 0) && (errno != EINTR))
		std::cout << BRED << "Select: " << strerror(errno) << DEFCOLO << std::endl;
	
	// ? if select function was interrupted by the signal SIGINT (ctrl-c), it will return -1 and errno will be set to EINTR
	if (this->_totalBitSet == -1 && errno == EINTR)
		throw TerminateServer();

	// ? if the fd is still in the set
	if (FD_ISSET(this->_masterSocket, &this->_readfds))
	{
		// ? extract the 1st connection request on the queue of the pending connection for the listening socket
		// ? create a new connected socket and return its fd
		if ((this->_newSocket = accept(this->_masterSocket, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen)) < 0)  
		{
			std::cout << BRED << "Accept: " << strerror(errno) << DEFCOLO << std::endl;
			return (0);
		}
		std::cout << BCYN << "💬 New connection: socket fd is " << this->_newSocket << ", ip address is " << inet_ntoa(this->_address.sin_addr) << ", port is " << ntohs(this->_address.sin_port) << std::endl;
		
		// ? send a welcome message to the connected socket
		if (send(this->_newSocket, WLCMSG, strlen(WLCMSG), 0) != strlen(WLCMSG))
			std::cout << BRED << "Send: " << strerror(errno) << DEFCOLO << std::endl;
		std::cout << BBLU << "📤 Welcome message sent successfully" << DEFCOLO << std::endl;

		// ? add the connected socket to the client list
		this->_clientSocket.push_back(this->_newSocket);
		this->_msgStorage.push_back("");
		std::cout << "Adding to list of sockets as " << this->_clientSocket.size() - 1 << std::endl;
	}
	return (1);
}

void	Server::getClientMsg()
{
	for (size_t i = 0; i < this->_clientSocket.size(); i++)  
	{
		if (FD_ISSET(this->_clientSocket[i], &this->_readfds))  
		{
			// ? read the message recieved
			if ((this->_readbyte = read(*(this->_clientSocket.begin()+i), this->_msgBuffer, 1024)) == 0)  
			{
				// ? assign the address if the peer connected to the socket(_clientSocket[i]) in the buffer pointed to by adress
				getpeername(*(this->_clientSocket.begin()+i), (struct sockaddr*)&this->_address, (socklen_t*)&this->_addrlen);  
				std::cout << BCYN << "🛑 Disconnection: socket fd is " << *(this->_clientSocket.begin()+i) << ", ip address is " << inet_ntoa(this->_address.sin_addr) << ", port is" << ntohs(this->_address.sin_port) << std::endl;
				close(*(this->_clientSocket.begin()+i));
				this->_clientSocket.erase(this->_clientSocket.begin() + i);
				this->_msgStorage.erase(this->_msgStorage.begin() + i);
				if (this->_clientSocket.empty())
					break ;
			}
			else
			{
				// ? when the client receive partial data it doesn't end with new line
				// ? the _msgStorage used to save each data and join them till it get completed
				this->_msgBuffer[this->_readbyte] = '\0';
				if (strchr(_msgBuffer, '\n'))
				{
					_msgStorage[i] += _msgBuffer;
					// ? print the message received
					std::cout << BBLU << std::endl << "📥 Received: " << this->_msgStorage[i] << DEFCOLO << std::endl;
					
					// ? send message to the client 
					std::string msg ("Server received this message: ");
					msg += this->_msgBuffer;
					send(*(this->_clientSocket.begin()+i), msg.c_str(), msg.length(), 0);
					_msgStorage[i] = "";					
				}
				else
					_msgStorage[i] += _msgBuffer;
			}
		}
	}
}

Server::~Server(){}