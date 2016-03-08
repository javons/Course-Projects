/**********************************************************************
*
* Project 1: Counting Coins
*
* Author: Tianmao Jiang
* Date: 6 August 2015
*
**********************************************************************/

#include <bjarne/std_lib_facilities.h>

int main()
{
    cout << "Enter the number of coins you have for each denomination.\n";
    cout << "  Pennies? ";
    double penny;
    cin >> penny;
    
    cout << "  Nickels? ";
    double nickel;
    cin >> nickel;
    
    cout << "  Dimes? ";
    double dime;
    cin >> dime;
    
    cout << "  Quarters? ";
    double quarter;
    cin >> quarter;
    
    cout << "  Half dollars? ";
    double half_dollar;
    cin  >> half_dollar;
    
    cout << "You have:\n";
    cout << "   " << penny << " pennies\n";
    cout << "   " << nickel << " nickels\n";
    cout << "   " << dime << " dimes\n";
    cout << "   " << quarter << " quarters\n";
    cout << "   " << half_dollar << " half dollars\n";
    
    double total = penny*1 + nickel*5 + dime*10 + quarter*25 + half_dollar*50;
    double usual_format = total/100;
    int a = int(total)%10;
    if (a!=0){
	cout << "The value of all your coins is " << total << " cents, which is $" << usual_format << ".\n";
    }
    else
	cout << "The value of all your coins is " << total << " cents, which is $" << setprecision(2) << usual_format << "0.\n";
	    
    return 0;
}
