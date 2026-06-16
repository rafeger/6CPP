#pragma once

# include <iostream>
# include <iomanip>
# include <cmath>

# define BOLDWHITE "\e[1;37m"
# define BOLDRED "\e[1;91m"
# define DEFAULT "\x1b[0m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define CYAN 	"\e[0;36m"


//by puting the Constructors etc in the private section we prohibit their use.
//so no instanciating a ScalarConverter Class.
class ScalarConverter
{
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);
	public:
		static	std::string convert(std::string _representation);

};

//saw an Enum table with different types listed and found the idea rlly cool so 
//took it from there

enum	_type
{
	PSEUDO = 0,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

_type matchType(const std::string _rep, size_t &len);

void	printPseudo(const std::string &str, size_t &len)
void	pront
