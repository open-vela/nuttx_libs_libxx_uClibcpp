#include <iostream>
#include <cstdio>
#include <iterator>


extern "C" int main(){
	char buffer [5];
	int i = 0;

	std::cout << "Beginning streamiter tests" << std::endl;
	std::cout << "please enter at least 6 characters:" << std::endl;

	std::istream_iterator<char> s(std::cin);
	
	std::cin.unsetf(std::ios::skipws);

	while(*s != '\n' && i < 5){
		buffer[i++] = *s++;
	}
	buffer[i] = '\0';

	std::cout << "Read: " << buffer << std::endl;

	return 0;
}
