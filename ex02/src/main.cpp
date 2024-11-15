// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<main.cpp>>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdint>
#include <iostream>
#include <experimental/random>

static inline Base	*generate(void);
static inline void	identify(Base *p);
static inline void	identify(Base &p);

int	main(void)
{
	Base	*p;

	p = generate();
	identify(*p);
	identify(p);
	delete p;
}

static inline Base	*generate(void)
{
	switch (std::experimental::randint(0, 2)) {
		case 0:
			return new A;
		case 1:
			return new B;
		case 2:
			return new C;
	}
	return nullptr;
}

static inline void	identify(Base *p)
{
	if (p == dynamic_cast<A *>(p))
		std::cout << "*p: A\n";
	else if (p == dynamic_cast<B *>(p))
		std::cout << "*p: B\n";
	else if (p == dynamic_cast<C *>(p))
		std::cout << "*p: C\n";
}

static inline void	identify(Base &p)
{
	try {
		(void)dynamic_cast<A &>(p);
		std::cout << "&p: A\n";
		return ;
	} catch (std::exception &e) {}
	try {
		(void)dynamic_cast<B &>(p);
		std::cout << "&p: B\n";
		return ;
	} catch (std::exception &e) {}
	try {
		(void)dynamic_cast<C &>(p);
		std::cout << "&p: C\n";
		return ;
	} catch (std::exception &e) {}
}
