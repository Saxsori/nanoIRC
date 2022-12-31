/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:11:15 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/31 23:10:32 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

int	TERMFLAG = 0;

void close_server(int sig)
{
	(void)sig;
	std::cout << BYEL << " The ctrl-c was hit" << DEFCOLO << std::endl;
	TERMFLAG = 1;
}

int main()  
{


	std::cout << BCYN << "  _   _                  ___________  _____ " << std::endl;
	std::cout << " | \\ | |                |_   _| ___ \\/  __ \\ " << std::endl;
	std::cout << " |  \\| | __ _ _ __   ___  | | | |_/ /| /  \\/ " << std::endl;
	std::cout << " | . ` |/ _` | '_ \\ / _ \\ | | |    / | |    " << std::endl;
	std::cout << " | |\\  | (_| | | | | (_) || |_| |\\ \\ | \\__/\\" << std::endl;
	std::cout << " \\_| \\_/\\__,_|_| |_|\\___/\\___/\\_| \\_| \\____/" << std::endl;                                 
	std::cout <<BYEL<< "       _   _" << std::endl;
	std::cout << "      (q\\_/p)" << std::endl;
	std::cout << "       /. .\\" << std::endl;
	std::cout << "      =\\_t_/=   __" << std::endl;
	std::cout << "       /   \\   (" << std::endl;
	std::cout << "      ((   ))   )" << std::endl;
	std::cout << "      /\\) (/\\  /" << std::endl;
	std::cout << "      \\  Y  /-'" << std::endl;
	std::cout << "       nn^nn" << DEFCOLO << std::endl;
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
		try
		{
			if (!server.connectClients())
				return (1);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << DEFCOLO << '\n';
			break ;
		}
		if (TERMFLAG == 1)
			break ;
		server.getClientMsg();
	}
    return (0);  
}
