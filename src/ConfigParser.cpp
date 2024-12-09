#include "ConfigParser.hpp"

ConfigParser::ConfigParser()
{

}

ConfigParser::ConfigParser(const str &fn)
{
	if (!validFilename(fn))
		throw FilenameError("Invalid file name!");
}

ConfigParser::ConfigParser(const ConfigParser &copy)
{
	(void)copy;
}

bool ConfigParser::validFilename(const str &fn)
{
	std::size_t	n;

	n = fn.length();
	if (n < 4 || fn.find(".conf") == str::npos)
		return false;
	return (fn[n - 5] == '.' && fn[n - 4] == 'c'
		&& fn[n - 3] == 'o' && fn[n - 2] == 'n'
		&& fn[n - 1] == 'f');
}

bool	ConfigParser::parseLine(str line)
{

	return (true);
}

Engine ConfigParser::parse(const str &fn)
{
	if (!validFilename(fn))
		throw FilenameError("Invalid file name!");

	Engine			eng;
	str				line;
	int				i = 0;
	std::ifstream 	file(fn);

	if (!file)
		throw InvalidFileError("Could not open file!");

	while (getline(file, line))
	{
		i++;
		if (!parseLine(line))
			throw InvalidFileError("Syntax error in the file!\nLine" + to_string(i) + ": " + line);
	}
	return (eng);
}

ConfigParser::~ConfigParser()
{

}

const ConfigParser &ConfigParser::operator =(const ConfigParser &copy)
{
	(void)copy;
	return *this;
}

ConfigParser::FilenameError::FilenameError(const char* message): errmsg(message) {}
ConfigParser::FilenameError::FilenameError(const std::string& message): errmsg(message) {}
const char* ConfigParser::FilenameError::what() const throw()
{
	return errmsg.c_str();
}
ConfigParser::FilenameError::~FilenameError() throw() {}
ConfigParser::InvalidFileError::InvalidFileError(const char* message): errmsg(message) {}
ConfigParser::InvalidFileError::InvalidFileError(const std::string& message): errmsg(message) {}
const char* ConfigParser::InvalidFileError::what() const throw()
{
	return errmsg.c_str();
}
ConfigParser::InvalidFileError::~InvalidFileError() throw() {}