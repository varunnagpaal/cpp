// Lambda Expressions: Constructs a closure i.e. an unnamed 
// function object capable of capturing variables in scope.
// in other words, 
// 1: its a function object. i.e its an object for which operator ()
//    is overloaded by compiler. Once a variable name is assigned to
//      this object, the object can be used as a function call.
//	  As lambda functions are objects, so they can also be created on heap
//    using new
// 
      
// 2: The capture list is to allow the lambda function when invoke to 
//    capture variables in its enclosing scope. When capture parameter 
//	  is passed by eference, it is captured from enclosing scope everytime
//	  lambda function call is made. If capture param pass by value, then its
//    value is capturted only during first invocation and not on subsequent invocations
//    Note that the capture parameter need to be any of the variables in the enclosing 
//    scope and there is no need to specify their type as variable already has a type 
//    defined in its declaration in enclosing scope.
//    The capture clause (lambda-introducer in the Standard syntax),
//    which specifies which variables are captured, and whether the 
//    capture is by value or by reference. Variables that have the 
//    ampersand (&) prefix are accessed by reference and variables that
//    do not have it are accessed by value.
//    An empty capture clause, [ ], indicates that the body of the lambda
//    expression accesses no variables in the enclosing scope. You can
//    use the default capture mode (capture-default in the Standard
//    syntax) to indicate how to capture any outside variables that are
//    referenced in the lambda: [&] means all variables that you refer
//    to are captured by reference, and [=] means they are captured by
//    value. You can use a default capture mode, and then specify the
//    opposite mode explicitly for specific variables. For example, if
//    a lambda body accesses the external variable total by reference
//    and the external variable factor by value, then the following
//    capture clauses are equivalent:
 /*
[]        //no variables defined. Attempting to use any external variables in the lambda is an error.
[x, &y]   //x is captured by value, y is captured by reference
[&]       //any external variable is implicitly captured by reference if used
[=]       //any external variable is implicitly captured by value if used
[&, x]    //x is explicitly captured by value. Other variables will be captured by reference
[=, &z]   //z is explicitly captured by reference. Other variables will be captured by value
[this]	  // The capture of this is special. It can only be captured by value, not 
             by reference. this can only be captured if the closest enclosing function 
             is a non-static member function. The lambda will have the same access
             as the member that created it, in terms of protected/private members
             If this is captured, either explicitly or implicitly, then the scope
             of the enclosed class members is also tested. Accessing members of this
             does not require explicit use of this-> syntax.
*/

/// 3: The parameter list is the parameters that user wants to pass to the 
//     function object when calling it as a function as if its passing the
//     parameters to real function.
#include <iostream>
#include <cmath>
#include <functional>

int main() 
{
	// Minimal Lambda
	// [capture](parameters) -> return_type { function_body }
	[/*capture list*/](/*parameters list*/){/*body*/};

	auto h = [](double x, double y) noexcept -> double 
			 { 
			 	return std::sqrt(x*x + y*y);
			 };
			 
	std::function<double(double,double)> i = [](double x, double y) noexcept -> double 
			 								 {
			 									return std::sqrt(x*x + y*y);
			 								 };
			 								 
	std::cout << "hyp(3,4): " << h(3.0,4.0) << std::endl;
	std::cout << "hyp(5,12): " << i(5.0,12.0) << std::endl;
	
	
	
	int x =2;
	int y=3;
	
	
	// pass x by value and y by refer4ence
	auto out = [x, &y](int a){ return x+y*a;};

	std::cout << "x=2, y=3, a = 5. x+y*a = " << out(5) <<std::endl;

	// We modify x and y but because lambda function passed x by value
	// so any change in x is noit captured by lambda function. 
	// So lambda function uses old x pass by value when lambda function was 1st
	// created. however as y was passed by reference so, its change in value is
	// captured by lambda function
	x = 10;
	y = 4;
	
	std::cout << "x=10, y=4, a = 5. x+y*a = " << out(5) <<std::endl;
	
	
	// To make the lambda function capture ALL local variables by value
	// we can use = in lambda capture list as shortuct to do this
	auto newout = [=](int a){ return x+y*a;};
	std::cout << "a = 5. x+y*a = " << newout(5) <<std::endl;
	
	// To make the lambda function capture ALL local variables by reference
	// we can use & in lambda capture list as shortuct to do this
	auto anotherout = [&](int a){ return x+y*a;};
	std::cout << "a = 5. x+y*a = " << anotherout(5) <<std::endl;
	
	x = 7;
	y = 2;
	std::cout << "a = 5. x+y*a = " << newout(5) <<std::endl;
	std::cout << "a = 5. x+y*a = " << anotherout(5) <<std::endl;
	
	// To make the lambda function capture ALL local variables by value
	// but exclude some variables, we can use = in lambda capture list 
	// followed by exlcuded parameters as shortuct to do this
	// all by value and x by reference 
	auto newout2 = [=, &x](int a){ return x+y*a;};
	std::cout << "a = 5. x+y*a = " << newout2(5) <<std::endl;
	
	// To make the lambda function capture ALL local variables by reference
	// but exclude some variables, we can use & in lambda capture list 
	// followed by exlcuded parameters as shortuct to do this
	// all by reference and x by value
	auto anotherout2 = [&, x](int a){ return x+y*a;};
	std::cout << "a = 5. x+y*a = " << anotherout2(5) <<std::endl;
	
	x = 7;
	y = 2;
	std::cout << "a = 5. x+y*a = " << newout2(5) <<std::endl;
	std::cout << "a = 5. x+y*a = " << anotherout2(5) <<std::endl;
	
	auto heaplambda = new auto( [&]() -> int { return x++; } );
	std::cout <<"Heap lambda: " <<  heaplambda << std::endl;
	
	
	/*
		A lambda expression with an empty capture specification 
		([]) can be implicitly converted into a function pointer
		with the same type as the lambda was declared with. 
		So this is legal:
	*/
	auto a_lambda_func = [](int x) { /*...*/ };
	void (* func_ptr)(int) = a_lambda_func;
	func_ptr(4); //calls the lambda.
	
	delete heaplambda;
	return 0;
}