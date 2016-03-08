/**********************************************************************
 *
 * Project 5a: Print out user's name 
 *
 * This program will first ask user's name and it will prompt the name
 * on the screen. 
 *
 * Author: Tianmao Jiang
 * Date: August 19 2015
 *
 **********************************************************************/

#include <Simple_window.h>    
#include <Graph.h>

using namespace Graph_lib;

int main ()
{
    string name;
    cout << "What is your name? ";
    getline(cin, name); // to get the full name

    // screen coordinate tl for top-left corner
    // window size(400*300)
    // title: Project 5a
    Point tl{100,100};  
    Simple_window win{tl,400,300,"Project 5a"};

    // create a text, set the font, size and color
    Text t{Point{75,150}, name};
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(30);
    t.set_color(Color::blue);
	
    win.attach(t);       
    win.wait_for_button();  // display!

} 
    


