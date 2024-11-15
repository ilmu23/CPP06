// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<main.cpp>>

#include <cstring>
#include <iostream>
#include "Serializer.hpp"

int	main(void)
{
	Data	data = {.a = 255, .r = 255, .g = 20, .b = 170};
	Data	*datap;

	datap = Serializer::deserialize(Serializer::serialize(&data));
	std::cout << "&data: " << &data << "\n";
	std::cout << "datap: " << datap << "\n";
	std::cout << "memcmp(data, datap): " << std::memcmp(&data, datap, sizeof(data)) << "\n";
	return 0;
}
