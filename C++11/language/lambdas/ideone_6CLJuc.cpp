// Lambda Expressions
#include <iostream>
#include <cmath>
#include <functional>

int main() 
{
	// Minimal Lambda
	// Empty Capture List , Empty Parameter List, Empty Compund Statement body
	[](){};

	std::function<double(double,double)> hfun = [](double x, double y) -> double { return std::sqrt(x*x + y*y);};

	int n = [] (int x, int y) { return x + y; }(5, 4);
   std::cout << n << std::endl;
   
	// The following lambda expression contains a nested lambda expression.
    int timestwoplusthree = [](int x) { return [](int y) { return y * 2; }(x) + 3; }(5);

    // Print the result.
    std::cout << timestwoplusthree << std::endl;
    
    // The following code declares a lambda expression that returns 
    // another lambda expression that adds two numbers. 
    // The returned lambda expression captures parameter x by value.
    auto addtwointegers = [](int x) -> function<int(int)> 
    { 
        return [=](int y) { return x + y; }; 
    };

    // The following code declares a lambda expression that takes another
    // lambda expression as its argument.
    // The lambda expression applies the argument z to the function f
    // and multiplies by 2.
    auto higherorder = [](const function<int(int)>& f, int z) 
    { 
        return f(z) * 2; 
    };

    // Call the lambda expression that is bound to higherorder. 
    auto answer = higherorder(addtwointegers(7), 8);

    // Print the result, which is (7+8)*2.
    cout << answer << endl;    
	return 0;
}