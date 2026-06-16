#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{

}

ScalarConverter::~ScalarConverter()
{

}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void) other;
	return *this;
}

std::string	ScalarConverter::convert(std::string _rep)
{
	size_t len = 0;
	while (_rep[len])
		len++;

	_type j = matchType(_rep, len);
	switch(j)
	{
		case	PSEUDO:
			// std::cout << "test" << std::endl;
			printPseudo
		case	CHAR:

		case	INT:

		case	FLOAT:

		case	DOUBLE:
			
		case	INVALID:
			std::cout << BOLDRED << "Invalid input" << DEFAULT << std::endl;
	}
	
	
}

_type	matchType(const std::string _rep, size_t &len)
{
	size_t	dot = _rep.find('.');
	size_t	f = _rep.find('f');

	if (dot = std::string::npos)
	{

	}
	if (f = std::string::npos)
	{

	}
}