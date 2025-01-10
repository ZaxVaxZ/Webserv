#include "Server.hpp"

const str	Server::directives[] = { "root", "listen", "index", "server_name", "error_page", "client_max_body_size", "min_delete_depth", "autoindex", "return", "" };

Server::Server() : BlockOBJ()
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

bool Server::handleAddress(str address)
{
	int	colon_cnt;
	int	last_colon;

	colon_cnt = 0;
	for (unsigned int i = 0; i < address.length(); i++)
	{
		if (address[i] != ':' && address[i] < '0' && address[i] > '9')
			return false;
		else if (address[i] == ':')
		{
			if (i == 0 || i == address.length() - 1 || address[i - 1] == ':' || address[i + 1] == ':')
				return false;
			colon_cnt++;
			last_colon = i;
		}
	}
	if (colon_cnt == 0)
		ports.push_back(address);
	else if (colon_cnt == 3)
		ips.push_back(address);
	else if (colon_cnt == 3)
	{
		ips.push_back(address.substr(0, last_colon));
		ports.push_back(address.substr(last_colon + 1));
	}
	else
		return false;
	return true;
}

bool Server::handleDirective(std::queue<str> opts)
{
	bool			parent_ret;

	if (opts.size() == 0 || !inDirectives(opts.front(), directives))
		return false;
	parent_ret = BlockOBJ::handleDirective(opts);
	if (opts.front() == "listen" && opts.size() == 2)
	{
		opts.pop();
		return (handleAddress(opts.front()));
	}
	else if (opts.front() == "server_name" && opts.size() >= 2)
	{
		opts.pop();
		while (opts.size() > 0)
		{
			if (opts.front().length() == 0)
				return false;
			names.push_back(opts.front());
			opts.pop();
		}
	}
	else if (opts.front() == "return" && opts.size() >= 2 && opts.size() <= 3)
	{
		opts.pop();
		ret_code = std::stoi(opts.front());
		opts.pop();
		if (opts.size() > 0)
			ret_str = opts.front();
	}
	else
		return parent_ret;
	return true;
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
