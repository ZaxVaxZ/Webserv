#include "Server.hpp"

Server::Server(): BlockOBJ()
{

}

Server::Server(const Server &copy): BlockOBJ(copy)
{
	(void)copy;
}

Server::~Server()
{
	for(std::vector<Location *>::iterator it = locations.begin(); it != locations.end(); it++)
    	delete *it;
}

bool Server::handleDirective(std::queue<str> opts)
{
	(void) opts;
	return false;
}

BlockOBJ *Server::handleBlock(std::queue<str> opts)
{
	if (opts.size() < 2 || opts.front() != "location")
		return NULL;
	locations.push_back(new Location());
	return locations.back();
}

const Server &Server::operator =(const Server &copy)
{
	(void)copy;
	return *this;
}
