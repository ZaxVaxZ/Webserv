#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <exception>

typedef std::string str;

class Engine
{
	private:
		str	username;
		int	workers;
		t_pid pid;

	public:
		Engine();
		Engine(const Engine &copy);
		~Engine();
		const Engine &operator =(const Engine &copy);
};

#endif