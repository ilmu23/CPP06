// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ScalarConverter.cpp>>

#include <cmath>
#include <regex>
#include <cctype>
#include <limits>
#include <cstdint>
#include <iostream>
#include "ScalarConverter.hpp"

#define _CHAR	0
#define _INT	1
#define _FLOAT	2
#define _DOUBLE	3
#define _NONE	4

#define _INT_MIN	std::numeric_limits<int>::min()
#define _INT_MAX	std::numeric_limits<int>::max()
#define _FLT_MIN	std::numeric_limits<float>::min()
#define _FLT_MAX	std::numeric_limits<float>::max()

#define isascii(x)			(x >= 0x0 && x <= 0x7F)
#define inrange(m, x, y)	(n >= x && n <= y)

#define _zero(n)	((!std::isnan(n) && !std::isinf(n) && n == std::round(n)) ? ".0" : "")

#define _val(n, t)	(static_cast<t>(n))

static inline uint8_t	_getType(const std::string &lit);
static inline void		_pchr(const char &c);
static inline void		_pint(const int &n);
static inline void		_pflt(const float &n);
static inline void		_pdbl(const double &n);

void	ScalarConverter::convert(const std::string &lit)
{
	switch (_getType(lit)) {
		case _CHAR:
			_pchr((lit.length() == 1) ? lit.at(0) : lit.at(1));
			break ;
		case _INT:
			try {
				_pint(std::stoi(lit));
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of 32-bit int range\n";
			}
			break ;
		case _FLOAT:
			try {
				_pflt(std::stof(lit));
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of float range\n";
			}
			break ;
		case _DOUBLE:
			try {
				_pdbl(std::stod(lit));
			} catch (std::exception &e) {
				std::cout << "sc: literal " << lit << " outside of double range\n";
			}
			break ;
		default:
			std::cout << "sc: invalid literal " << lit << "\n";
	}
}

static inline uint8_t	_getType(const std::string &lit)
{
	std::regex	rchr("^[^0-9]$|^'.'$");
	std::regex	rint("^[0-9]+$");
	std::regex	rflt("^[0-9]+\\.[0-9]*f$");
	std::regex	rdbl("^[0-9]+\\.[0-9]*$");

	if (std::regex_match(lit, rchr))
		return _CHAR;
	if (std::regex_match(lit, rint))
		return _INT;
	if (lit == "inff" || lit == "+inff" || lit == "-inff" || std::regex_match(lit, rflt))
		return _FLOAT;
	if (lit == "inf" || lit == "+inf" || lit == "-inf" || lit == "nan" || std::regex_match(lit, rdbl))
		return _DOUBLE;
	return _NONE;
}

static inline void	_pchr(const char &c)
{
	std::cout << "char   : '" << c << "'\n";
	std::cout << "int    : " << _val(c, int) << "\n";
	std::cout << "float  : " << _val(c, float) << _zero(_val(c, float)) << "\n";
	std::cout << "double : " << _val(c, double) << _zero(_val(c, double)) << "\n";
}

static inline void	_pint(const int &n)
{
	if (isascii(n) && std::isprint(n))
		std::cout << "char   : '" << _val(n, char) << "'\n";
	else
		std::cout << "char   : not applicable\n";
	std::cout << "int    : " << n << "\n";
	std::cout << "float  : " << _val(n, float) << _zero(_val(n, float)) << "\n";
	std::cout << "double : " << _val(n, double) << _zero(_val(n, double)) << "\n";
}

static inline void	_pflt(const float &n)
{
	int	_n;

	if (inrange(n, _val(_INT_MIN, float), _val(_INT_MAX, float))) {
		_n = static_cast<int>(std::roundf(n));
		if (isascii(_n) && std::isprint(_n))
			std::cout << "char   : '" << _val(_n, char) << "'\n";
		else
			std::cout << "char   : not applicable\n";
		std::cout << "int    : " << _n << "\n";
	} else {
		std::cout << "char   : not applicable\n";
		std::cout << "int    : not applicable\n";
	}
	std::cout << "float  : " << n << _zero(n) << "f\n";
	std::cout << "double : " << _val(n, double) << _zero(_val(n, double)) << "\n";
}

static inline void	_pdbl(const double &n)
{
	int	_n;

	if (inrange(n, _val(_INT_MIN, double), _val(_INT_MAX, double))) {
		_n = static_cast<int>(std::round(n));
		if (isascii(_n) && std::isprint(_n))
			std::cout << "char   : '" << _val(_n, char) << "'\n";
		else
			std::cout << "char   : not applicable\n";
		std::cout << "int    : " << _n << "\n";
	} else {
		std::cout << "char   : not applicable\n";
		std::cout << "int    : not applicable\n";
	}
	if (inrange(n, _val(_FLT_MIN, double), _val(_FLT_MAX, double)))
		std::cout << "float  : " << _val(n, float) << _zero(_val(n, float)) << "f\n";
	else
		std::cout << "float  : not applicable\n";
	std::cout << "double : " << n << _zero(n) << "\n";
}
