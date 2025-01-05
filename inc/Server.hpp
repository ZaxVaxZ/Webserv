#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <exception>
#include <vector>
#include <queue>
#include "BlockOBJ.hpp"
#include "Location.hpp"

typedef std::string str;

class Server: public BlockOBJ
{
	private:
		std::vector<str>		names, ips;
		std::vector<int>		ports;
		std::vector<Location *>	locations;
	
	public:
		Server();
		Server(const Server &copy);
		~Server();

		bool		handleDirective(std::queue<str> opts);
		BlockOBJ	*handleBlock(std::queue<str> opts);

		const Server &operator =(const Server &copy);
};

#endif
