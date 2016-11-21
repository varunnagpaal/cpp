// Real-time C++
// Chapter - 1, LED Program
#include <iostream>
#include <cstdint>

// Left-shift x by p-positions where p=[0,n-1]
#define LEFTSHIFT(x,p) ( ( x ) << ( p ) )

// Right-shift x by p-positions where p=[0,n-1]
#define RIGHTSHIFT(x,p) ( ( x ) >> ( p ) )

// Set b-th bit in x where b = [0,n-1] where n = bit-size of x
#define SETBIT(x,b) ( ( x ) |= ( LEFTSHIFT(1,b) ) )

// Sets all n-bits in x
#define SETALLBITS(x) ( ( x ) |= ( 0xFF ) )

// Clear or reset b-th bit in x where b = [0,n-1] where n = bit-size of x
#define CLEARBIT(x,b)  ( ( x ) &= ( ~( LEFTSHIFT(1,b) ) ) )

// Clears all n-bits in x
#define CLEARALLBITS(x,b) (( x ) =  0 )

// Toggle b-th bit in x where b = [0,n-1] where n = bit-size of x
#define TOGGLEBIT(x,b)  ( ( x ) ^= ( LEFTSHIFT(1,b) ) )

#define TOGGLEALLBITS(x)  ( ( x ) ^= ( 0xFF ))

// Get bit value at b-th position in x where b = [0,n-1] where n = bit-size of x
#define GETBIT(x,b)  ( ( ( x ) >>  ( b ) ) & 1 )

// Set bit at b-th position in x to bit k where b = [0,n-1] where n = bit-size of x
#define SETABITVALUE(x,b,k) ( ( x ) >> ( b ) ) | ( k ) )

// Returns true if there is atleast one bit set
#define ISANYBITSET(x)

// Returns true if ALL bits are set
#define AREALLBITSET(x)

// Returns true if ALL bits are clear
#define ISNONEBITSET(x)



/* Examples

#define GETBIT(x,b) (( ( x ) & ( 1 << ( b ) ) ) >>  ( b ) )
x =10110111

GETBIT(x,3) = (( ( 10110111 ) & ( 1 << ( 3 ) ) ) >>  ( 3 ) )
	    = (( ( 10110111 ) & ( 00001000 ) ) >>  ( 3 ) )
	    = (( 00000000 ) >>  ( 3 ) )
	    = 0

GETBIT(x,0) = (( ( 10110111 ) & ( 1 << ( 0 ) ) ) >>  ( 0 ) )
	    = (( ( 10110111 ) & ( 00000001 ) ) >>  ( 0 ) )
	    = (( 00000001 ) >>  ( 0 ) )
	    = 00000001

GETBIT(x,7) = (( ( 10110111 ) & ( 1 << ( 7 ) ) ) >>  ( 7 ) )
	    = (( ( 10110111 ) & ( 10000000 ) ) >>  ( 7 ) )
	    = (( 10000000 ) >>  ( 0 ) )
	    = 00000001
	    
*/	    

class led
{
	public:
		using PortType = std::uint8_t;
		using ValueType = std::uint8_t;
		
		// Initialize LED ports
		led( const PortType p, const ValueType value ): _port(p), _value( value)
		{
			*((volatile const *)_port) = 
		}
		
		~led()
		{
			
		}
		
		void Toggle()
		{
			
		}
	
	private:
		PortType _port;
		ValueType _value;
	
	
};


int main() 
{
	led ledRed;
	
	// Toggle LED forever
	for(;;)
		ledRed.Toggle();
	return 0;
}