// Bit-sets
#include <iostream>
#include <bitset>
#include <typeinfo>

int main() {
	std::bitset<4> nibble1;	// 0000
	
	// Toggle, set, reset
	nibble1.flip(2);		// 0100
	nibble1.set(1); 		// 0110
	nibble1.reset(1);		// 0100
	
	const int n = 8;
	std::bitset<n> byte1(9); // 0000_1001
	std::bitset<12> ByteAndAHalf("1010101000011101"); // Will be truncated. Extra LSbits are truncated
	std::bitset<4> nibble2("ABBA", 4, 'A', 'B'); // A ~ 0, B ~1, ABBA ~ 0110
	
	// print
	std::cout << "Nibble1: " << nibble1 << std::endl;
	std::cout << "Byte11: " << byte1 << std::endl;
	std::cout << "ByteAndAHalf:" << ByteAndAHalf << std::endl;
	std::cout << "Nibble2 \"ABBA\": " << nibble2 << std::endl;
	std::cout << "typeid(ByteAndAHalf).name():" << typeid(ByteAndAHalf).name() << std::endl;
	
	// Bit-wise or, xor, and
	std::cout << "Nibble1 | Nibble2: " << ( nibble1 | nibble2 ) << std::endl;
	std::cout << "Nibble1 ^ Nibble2: " << ( nibble1 ^ nibble2 ) << std::endl;
	std::cout << "Nibble1 & Nibble2: " << ( nibble1 & nibble2 ) << std::endl;
	
	// Complement
	std::cout << "~byte1: " << ~byte1 << std::endl;
	
	// Compiler error: sizes dont match
	// std::cout << "Nibble1 & byte1: " << ( nibble1 & byte1 ) << std::endl;
	
	// Bitwise operation with hexadeciaml constants
	byte1 |= 0xA9;
	std::cout << "(byte1 |= 0xA9): " << byte1 << std::endl;
	
	// Shift
	std::cout << "( byte1 >> 1 ): " << ( byte1 >> 1 ) << std::endl;
	std::cout << "( byte1 << 2 ): " << ( byte1 << 2 ) << std::endl;
	
	// Fancy output
	std::cout << "Nibble1: " << nibble1.to_string() << std::endl;
	std::cout << "Nibble1: " << nibble1.to_string('O', 'I') << std::endl;
	std::cout << "11100011: " << std::bitset<8>("11100011").to_string('_', '-') << std::endl;
	return 0;
}