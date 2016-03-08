/**********************************************************************
 *
 * Project 2: Quadratic Equation Solver
 *
 * This program asks the user to enter the coefficients of a quadratic
 * polynomial ax^2 + bx + c = 0, and it gives out explanation for
 * the real root numbers and the result. And it will also find out 
 * the result with a stable method in order to avoid catastrophic
 * cancellation.
 *
 * Author: Tianmao Jiang
 * Date:   7 August 2015
 *
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

// function declarations
void solve_linear(double b, double c);
void solve_quadratic(double a, double b, double c);

int main()
{
   // input the coefficients of the polynomial
    
   double a, b, c;                      // coefficients of the polynomial
   cout << "Enter the coefficients of a quadratic polynomial a*x**2 + b*x + c:\n";
   cout << "  a? ";                      // inputs of the coefficients
   cin >> a;                             // a, b and c
   cout << "  b? ";
   cin >> b;
   cout << "  c? ";
   cin >> c;
   
   // handle degenerate case (linear equation) and genuine quadratic
   // equation case separately with the functions forged later
   
   if (a == 0)  // linear equation, not quadratic
      solve_linear(b, c);
   else  // genuine quadratic equation
      solve_quadratic(a, b, c);
}

// solve the linear equation b*x + c == 0

void solve_linear(double b, double c)
{
   cout << "Trying to solve linear equation "     
        << b << "*x + " << c << " == 0\n";       // print the equation
   if (b != 0)
       cout << "Linear equation, root x = "
	    << - c / b << "\n";                  // find out the root for 
   else if (b == 0 && c != 0)                    // linear equation and
       cout << "A contradiction\n";              // explain under different
   else if (b == 0 && c == 0)                    // conditions
       cout << "An identity\n";
}

// use classical quadratic formula to solve a genuine quadratic equation
// a*x^2 + b*x + c ==0, with a != 0

void solve_quadratic(double a, double b, double c)
{
   cout << "Trying to solve the quadratic equation "
        << a << "*x*x + " << b << "*x + " << c << " == 0\n"; //print
							     //the equation 
   
   // output results, explanation and
   // stable formula calculation for b*b - 4*a*c > 0 situation
   
   if (b*b - 4*a*c > 0){
       cout << "Using classical formula: Two real roots, x = "   
	    << (- b + sqrt(b*b - 4*a*c)) / (2*a) << " and x = "
	    << (- b - sqrt(b*b - 4*a*c)) / (2*a) << "\n";
       if (b >= 0)
	   cout << "Using stable formula: Two real roots, x= "
		<< (- b - sqrt(b*b - 4*a*c)) / (2*a) << " and x = "
		<< c / (a*((- b - sqrt(b*b - 4*a*c))/(2*a))) << "\n";
       else if (b < 0)
	   cout << "Using stable formula: Two real roots, x= "
		<< (- b + sqrt(b*b - 4*a*c)) / (2*a)<< " and x = "
		<< c / (a*((- b + sqrt(b*b - 4*a*c))/(2*a))) << "\n";
   }
   
   // report results and explaination for b*b - 4*a*c <= 0 situation
   
   else if (b*b - 4*a*c == 0)
       cout << "One double root, x = "
	    << (- b)/(2*a) << "\n";
   else if (b*b - 4*a*c < 0)
       cout << "No real roots\n"; 
       
}
