#include "ScalarConverter.hpp"

//javais declare un truc propre et tt pour les construc/destruct mais je suis idiot.
//vu que c4est mm pas instantiable on peut juster les laisser blank

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void) other;
	return *this;
}

//checks if the string is only digits, with an optional + or - in front
static bool	isInteger(const std::string &rep)
{
	size_t	i = 0;

	if (rep.empty())
		return false;
	if (rep[0] == '+' || rep[0] == '-')
		i = 1;
	if (i == rep.size())
		return false;
	for (; i < rep.size(); i++)
		if (!std::isdigit(rep[i]))
			return false;
	return true;
}

//checks if the string looks like a double: digits, optional sign, one dot
static bool	isDouble(const std::string &rep)
{
	size_t	i = 0;
	bool	hasDigit = false;
	bool	hasDot = false;

	if (rep.empty())
		return false;
	if (rep[0] == '+' || rep[0] == '-')
		i = 1;
	for (; i < rep.size(); i++)
	{
		if (rep[i] == '.' && !hasDot)
			hasDot = true;
		else if (std::isdigit(rep[i]))
			hasDigit = true;
		else
			return false;
	}
	return hasDigit && hasDot;
}

static _type	matchType(const std::string &rep)
{
	bool		hasF = false;
	std::string	body = rep;

	if (rep.size() == 1 && !std::isdigit(rep[0]))
		return CHAR;
	if (isInteger(rep))
		return INT;
	if (!rep.empty() && rep[rep.size() - 1] == 'f')
	{
		hasF = true;
		body = rep.substr(0, rep.size() - 1);
	}
	if (isDouble(body))
	{
		if (hasF)
			return FLOAT;
		else
			return DOUBLE;
	}
	return INVALID;
}

static void	printChar(double value)
{
	if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
	{
		std::cout << "char: impossible" << std::endl;
		return;
	}
	char	c = static_cast<char>(value);
	if (std::isprint(c))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
}

static void	printInt(double value)
{
	if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
	{
		std::cout << "int: impossible" << std::endl;
		return;
	}
	std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void	printFloat(double value)
{
	std::ostringstream	oss;

	oss << static_cast<float>(value);
	std::string	str = oss.str();
	if (str.find('.') == std::string::npos && str.find('e') == std::string::npos)
		str += ".0";
	std::cout << "float: " << str << "f" << std::endl;
}

static void	printDouble(double value)
{
	std::ostringstream	oss;

	oss << value;
	std::string	str = oss.str();
	if (str.find('.') == std::string::npos && str.find('e') == std::string::npos)
		str += ".0";
	std::cout << "double: " << str << std::endl;
}

//the pseudo literals are a fixed list of 6 possible strings, so we just
//print their known result directly instead of trying to convert them
static bool	printIfPseudo(const std::string &rep)
{
	if (rep == "nan" || rep == "nanf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return true;
	}
	if (rep == "+inf" || rep == "+inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return true;
	}
	if (rep == "-inf" || rep == "-inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return true;
	}
	return false;
}

void	ScalarConverter::convert(const std::string &representation)
{
	if (printIfPseudo(representation))
		return;

	double	value;
	_type	type = matchType(representation);

	if (type == CHAR)
		value = static_cast<double>(representation[0]);
	else if (type == INT || type == DOUBLE)
		value = std::strtod(representation.c_str(), NULL);
	else if (type == FLOAT)
		value = std::strtod(representation.substr(0, representation.size() - 1).c_str(), NULL);
	else
	{
		std::cout << BOLDRED << "Invalid input" << DEFAULT << std::endl;
		return;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
