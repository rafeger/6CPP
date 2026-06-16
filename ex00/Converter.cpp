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

//is the whole string a valid pseudo-literal (nan/nanf/+-inf/+-inff) ?
static bool	isPseudo(const std::string &rep)
{
	if (rep == "-inf" || rep == "+inf" || rep == "nan"
		|| rep == "-inff" || rep == "+inff" || rep == "nanf")
		return 1;
	else
		return 0;
}

//optional sign followed by at least one digit, nothing else.
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
		if (!std::isdigit(static_cast<unsigned char>(rep[i])))
			return false;
	return true;
}

//optional sign, digits, exactly one dot, digits : needs at least a digit and the dot.
//(real C++ float/double literals require the dot, ex: 42.0f, not 42f)
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
		else if (std::isdigit(static_cast<unsigned char>(rep[i])))
			hasDigit = true;
		else
			return false;
	}
	return hasDigit && hasDot;
}

//same as a double, with a trailing 'f' (ex: 4.2f).
static bool	isFloat(const std::string &rep)
{
	if (rep.empty() || rep[rep.size() - 1] != 'f')
		return false;
	return isDouble(rep.substr(0, rep.size() - 1));
}

static _type	matchType(const std::string &rep)
{
	if (isPseudo(rep))
		return PSEUDO;
	if (rep.size() == 1 && !std::isdigit(static_cast<unsigned char>(rep[0])))
		return CHAR;
	if (isInteger(rep))
		return INT;
	if (isFloat(rep))
		return FLOAT;
	if (isDouble(rep))
		return DOUBLE;
	return INVALID;
}

static double	parsePseudo(const std::string &rep)
{
	if (rep == "nan" || rep == "nanf")
		return std::numeric_limits<double>::quiet_NaN();
	if (rep == "+inf" || rep == "+inff")
		return std::numeric_limits<double>::infinity();
	return -std::numeric_limits<double>::infinity();
}

static bool	isNan(double value)
{
	return value != value;
}

static bool	isInf(double value)
{
	return (value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity());
}

//formats a value the way a literal of type T would be written back out,
//appending suffix ("f" for float, "" for double) and a special-case label
//for nan/inf since they don't go through operator<<.
template <typename T>
static std::string	formatFloating(double value, const std::string &suffix)
{
	if (isNan(value))
		return "nan" + suffix;
	if (isInf(value))
		return (value > 0 ? "+inf" : "-inf") + suffix;

	std::ostringstream	oss;
	oss << static_cast<T>(value);
	std::string	str = oss.str();
	if (str.find('.') == std::string::npos
		&& str.find('e') == std::string::npos
		&& str.find('E') == std::string::npos)
		str += ".0";
	return str + suffix;
}

static void	printChar(double value)
{
	if (isNan(value) || isInf(value)
		|| value < static_cast<double>(std::numeric_limits<char>::min())
		|| value > static_cast<double>(std::numeric_limits<char>::max()))
	{
		std::cout << "char: impossible" << std::endl;
		return;
	}
	char	c = static_cast<char>(value);
	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
}

static void	printInt(double value)
{
	if (isNan(value) || isInf(value)
		|| value < static_cast<double>(std::numeric_limits<int>::min())
		|| value > static_cast<double>(std::numeric_limits<int>::max()))
	{
		std::cout << "int: impossible" << std::endl;
		return;
	}
	std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void	printResult(double value)
{
	printChar(value);
	printInt(value);
	std::cout << "float: " << formatFloating<float>(value, "f") << std::endl;
	std::cout << "double: " << formatFloating<double>(value, "") << std::endl;
}

//explain switch
void	ScalarConverter::convert(const std::string &representation)
{
	double	value;

	switch (matchType(representation))
	{
		case PSEUDO:
			value = parsePseudo(representation);
			break;
		case CHAR:
			value = static_cast<double>(static_cast<unsigned char>(representation[0]));
			break;
		case INT:
		case DOUBLE:
			value = std::strtod(representation.c_str(), NULL);
			break;
		case FLOAT:
			value = std::strtod(representation.substr(0, representation.size() - 1).c_str(), NULL);
			break;
		default:
			std::cout << BOLDRED << "Invalid input" << DEFAULT << std::endl;
			return;
	}
	printResult(value);
}
