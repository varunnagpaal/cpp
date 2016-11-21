#include <iostream>
#include <array>
using namespace std;

// const: promises that after initilization of symbolic constant(at compile-time or run-time), 
// its value cannot be modified. It restricts the ways in which an object can be used, rather
// than specifying how the constant is to be allocated.
//
// Core Constant expressions: compile-time constants or "expressions which are evaluated
// to a constant value and bound to a symbol by the compiler only at compile-time
// and not run-time". Compile time constants defined this way have clearly defined
// type information at compile time unlike macros where no type information
// is associated with the expression at compile time
//
// Ultimately, a core constant expression must start out with an integral value, 
// a floating-point value, or an enumerator, and we can combine those using
// operators and constexpr functions that in turn produce values.
// 
// Difference between const and constexpr
// A variable marked const may be evaluated and initialized at compile-time or at runtime but it cannot be modified at run-time
// A variable marked constexpr is evaluated and initialized at compile-time and it cannot be initialized at run-time

// compile-time constants are required in following places at compile-time
// - template parameters
// - labels of case statement of switch construct
// - array bounds: must be a constant expression
//
// constexpr for example might come handy to evaluate expressions to calculate
// - array-bounds 
// - values of non-type template parameters
// - labels of case statement
// - complex compile time value based on complex formulaes
//
// initilization done by constexpr at compile-time ensures no thread-races
// which could happen with const initialized by multiple threads at run-time

void doSmthing( int &a)
{
	a = a+3;
}

void doSmthng( int const &a)
{
}

int getInt( int x)
{
	return x++;
}

// "constexpr functions" are superior to define because they have clearly defined 
// type at compile-time and in some-ways constexpr functions are basically type-checked macros
// This same function may be used for
// - non-constant arguments but in this case result is not a core constant expression
// - in contexts that donot reauire core constant expressions and so can pass non core constant 
//   expression argument ...so basically we dont have to define the same function
//   once for constexpr and once for variables
#define GETINTCNSTEXPR(x) ((x)/3)
constexpr int getIntCnstExp( int x)
{
 return x/3;	
}

int main() 
{
   int a1;
   doSmthng(a1); // modify a1
   const int a2 = a1; // OK: initializaion of constant a2 happens at runtime

   // If the initializer expression for a symbol marked as constexpr can’t be
   // evaluated at compile time, the compiler will give an error. 
   // constexpr int a3 = a1; // Not ok: value of a1 unknown at compile time
   
   const int a4 = 10; // Ok: initialization of constant at compile-time
   constexpr int a5 = a4; // Ok since calue of a4 known at compile-time
   
   const int a6 = getInt(10);// ok: initialization of constant at run-time
   // constexpr int a7 = getInt(a6); // not ok: since value of function is unknown at compile-time, a6 value also unknown at compile-time
   // constexpr int a8 = getInt(a5); // not ok: a5 is known at compile-time, but getInt(a5) unknown at compile-time. 
   
   constexpr int a9 = getIntCnstExp( a5 ); // a5: known at compile-time, value of getIntCnstExp(a5) is also known at compile-time
   
   // this is strange: passing constexpr to a macro ?
   // This is ok because first CPP(preprocessor) replaces the macro by "a5/3". 
   // Now as a5 is defined to be constexpr, so is a5/3 a constexpr
   constexpr int a10 = GETINTCNSTEXPR( a5 ); 
   
   
   // std::array<int,a1> ar1; // error: since template parameters must be known at compile-time but a1 is unknown at compile-time
   // std::array<int,a2> ar2; // error: since template parameters must be known at compile-time but a2 is unknown at compile-time
   std::array<int,a4> ar4; // OK: since template parameters must be known at compile-time and a4 is known at compile-time 
   // std::array<int,a6> ar6; // error: since template parameters must be known at compile-time but is a6 unknown at compile-time
   std::array<int,a9> ar9; // Ok: since template parameters must be known at compile-time and a9 is known at compile-time and 
   
   int amyar1[a1];
   int amyar2[a2];
   int amyar4[a4];
   int amyar5[a5];
   int amyar6[a6];
   int amyar9[a9];
   int amyar10[a10];
   
   
   return 0;
}