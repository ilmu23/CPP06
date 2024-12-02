// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ScalarConverter.cpp>>

#include <cmath>
#include <cctype>
#include <limits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include "ScalarConverter.hpp"

#define _CHAR	0
#define _INT	1
#define _FLOAT	2
#define _DOUBLE	3
#define _NONE	4

#define isascii(x)	(x >= 0x0 && x <= 0x7F)

#define _zero(n)	((!std::isnan(n) && !std::isinf(n) && n == std::round(n)) ? ".0" : "")

#define _val(n, t)	(static_cast<t>(n))

static inline uint8_t	_getType(const std::string &lit);
static inline uint8_t	_isFloat(const std::string &lit);
static inline uint8_t	_isDouble(const std::string &lit);

void	ScalarConverter::convert(const std::string &lit)
{
	char	cval;
	int		ival;
	float	fval;
	double	dval;

	switch (_getType(lit)) {
		case _CHAR:
			cval = static_cast<char>(lit.front());
			ival = static_cast<int>(cval);
			fval = static_cast<float>(cval);
			dval = static_cast<double>(cval);
			std::cout << "char   : '" << cval << "'\n";
			std::cout << "int    : " << ival << "\n";
			std::cout << "float  : " << fval << _zero(fval) << "f\n";
			std::cout << "double : " << dval << _zero(dval) << "\n";
			break ;
		case _INT:
			try {
				ival = std::stoi(lit);
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of 32-bit int range\n";
				break ;
			}
			cval = (isascii(ival)) ? static_cast<char>(ival) : 0;
			fval = static_cast<float>(ival);
			dval = static_cast<double>(ival);
			if (std::isprint(cval))
				std::cout << "char   : '" << cval << "'\n";
			else
				std::cout << "char   : not applicable\n";
			std::cout << "int    : " << ival << "\n";
			std::cout << "float  : " << fval << _zero(fval) << "f\n";
			std::cout << "double : " << dval << _zero(dval) << "\n";
			break ;
		case _FLOAT:
			try {
				fval = std::stof(lit);
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of float range\n";
				break ;
			}
			if (fval <= _val(std::numeric_limits<int>::max(), float)
				&& fval >= _val(std::numeric_limits<int>::min(), float)) {
				ival = static_cast<int>(std::roundf(fval));
				cval = (isascii(ival)) ? static_cast<char>(std::roundf(fval)) : 0;
				if (std::isprint(cval))
					std::cout << "char   : '" << cval << "'\n";
				else
					std::cout << "char   : not applicable\n";
				std::cout << "int    : " << ival << "\n";
			} else {
				std::cout << "char   : not applicable\n";
				std::cout << "int    : not applicable\n";
			}
			dval = static_cast<double>(fval);
			std::cout << "float  : " << fval << _zero(fval) << "f\n";
			std::cout << "double : " << dval << _zero(dval) << "\n";
			break ;
		case _DOUBLE:
			try {
				dval = std::stod(lit);
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of double range\n";
				break ;
			}
			if (dval <= _val(std::numeric_limits<float>::max(), double)
				&& dval >= _val(std::numeric_limits<float>::min(), double)) {
				fval = static_cast<float>(dval);
				if (dval <= _val(std::numeric_limits<int>::max(), double)
					&& dval >= _val(std::numeric_limits<int>::min(), double)) {
					ival = static_cast<int>(std::roundf(dval));
					cval = (isascii(ival)) ? static_cast<char>(std::roundf(dval)) : 0;
					if (std::isprint(cval))
						std::cout << "char   : '" << cval << "'\n";
					else
						std::cout << "char   : not applicable\n";
					std::cout << "int    : " << ival << "\n";
				} else {
					std::cout << "char   : not applicable\n";
					std::cout << "int    : not applicable\n";
				}
				std::cout << "float  : " << fval << _zero(fval) << "f\n";
			} else {
				std::cout << "char   : not applicable\n";
				std::cout << "int    : not applicable\n";
				std::cout << "float  : not applicable\n";
			}
			std::cout << "double : " << dval << _zero(dval) << "\n";
			break ;
		case _NONE:
			std::cout << "sc: invalid literal " << lit << "\n";
	}
}

static inline uint8_t	_getType(const std::string &lit)
{
	if (lit.length() == 1 && !std::isdigit(lit.at(0)))
		return _CHAR;
	if (lit.find_first_not_of("0123456789") == std::string::npos)
		return _INT;
	if (lit == "inf" || lit == "+inf" || lit == "-inf")
		return _DOUBLE;
	if (_isFloat(lit))
		return _FLOAT;
	return (_isDouble(lit)) ? _DOUBLE : _NONE;
}

static inline uint8_t	_isFloat(const std::string &lit)
{
	size_t	i;

	if (lit == "inff" || lit == "+inff" || lit == "-inff")
		return 1;
	if (!std::isdigit(lit.at(0)))
		return 0;
	i = lit.find_first_of(".");
	if (i == std::string::npos)
		return 0;
	if (!std::isdigit(lit.at(i + 1)))
		return 0;
	if (lit.find_first_of("f") != lit.length())
		return 0;
	return 1;
}

static inline uint8_t	_isDouble(const std::string &lit)
{
	size_t	i;

	if (lit == "inf" || lit == "+inf" || lit == "-inf" || lit == "nan")
		return 1;
	if (!std::isdigit(lit.at(0)))
		return 0;
	i = lit.find_first_of(".");
	if (i == std::string::npos)
		return 0;
	if (!std::isdigit(lit.at(i + 1)))
		return 0;
	return 1;
}
