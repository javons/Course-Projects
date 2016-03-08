/**********************************************************************
 *
 * Project 5b: Print out the Checkerboard
 *
 * This program will draw a 8 x 8 checkerboard containing alternating 
 * balck and red squares. User can click the next button to quit.
 *
 * Author: Tianmao Jiang
 * Date: August 20 2015
 *
 **********************************************************************/

#include "Simple_window.h"    
#include "Graph.h" 


using namespace Graph_lib;


int main ()
{
    cout << "Click the next button to quit the program!\n";
      	    
    // screen coordinate tl for top-left corner
    // window size(550*480)
    // title: Checkerboard
    Point tl{100,100};
    Simple_window win{tl,550,480,"Checkerboard"};

    // a reference vector to contain rectangles
    Vector_ref<Rectangle> vr;

    for (int i = 0; i < 8; ++i){
	for (int j = 0; j < 8; ++j){
	    vr.push_back(new Rectangle(Point{i*60,j*60},60,60));
	    // to fill black and red color alternatively into squares
	    if (i%2 == 0 && j%2 == 1 || (i%2 == 1 && j%2 == 0))
		vr[vr.size()-1].set_fill_color(Color::black);
	    else
		vr[vr.size()-1].set_fill_color(Color::red);
	    win.attach(vr[vr.size()-1]);
	}
    }
	    
    win.wait_for_button();               // Display!
}


