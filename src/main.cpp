/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:11:15 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/31 22:21:18 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

int	TERMFLAG = 0;

void close_server(int sig)
{
	(void)sig;
	std::cout << BYEL << "The server is terminated" << DEFCOLO << std::endl;
	TERMFLAG = 1;
}

int main()  
{
	Server	server;

	if (!server.creatSocket())
		return (1);
	if (!server.bindSocket())
		return (1);
	std::cout << "Waiting for connections ..." << std::endl;

	while (true)
	{
		signal(SIGINT, close_server);
		server.resetClients();
		if (!server.connectClients())
			return (1);
		if (TERMFLAG == 1)
			break ;
		server.getClientMsg();
	}
    return (0);  
}
