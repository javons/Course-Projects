/**********************************************************************
 *
 * Project 6: Square Presentation 
 *
 * This program is to test the newly-defined class Square and its
 * implementation file by drawing some squares in GUI.
 *
 * Author: Tianmao Jiang
 * Date: August 21 2015
 *
 **********************************************************************/

#include <Simple_window.h>    
#include "Square.h"
#include <Graph.h>

using namespace Graph_lib;

int main ()
    try {
	// all measurements are in pixels
	Point tl{100,100};
	// upper left and lower right points for square 2
	Point x1{200,400}; Point y1{400,600};
	// text position
	Point txt{100,100};
        // upper left point for square 1
	Point p{150,150};
	// upper left and lower right points for square 3
	Point x2{100,200}; Point y2{300,800};
	
	Simple_window win{tl,800,800,"Project Square"};
    
	Square sq1{p, 200};
	Square sq2{x1, y1};
	
	sq1.set_color(Color::blue);
	sq2.set_color(Color::red);
	
        // show the square side-length by calling defined function
	ostringstream oss;
	oss << "The side-length of the blue-outlined square is "
	    << sq1.side() << " pixels.\n";
    
	Text title{Point{100,50},oss.str()};
	title.set_font_size(15);

	Text t1{txt,
		"Press the \"Next\" button to change the picture"};
	Text t2{txt,
		"Press the \"Next\" button to get an unpleasant error"};

	t1.set_font_size(15);
	t2.set_font_size(15);
	    
	win.attach(title);
	win.attach(t1);
	win.attach(sq1);
	win.attach(sq2);
	win.wait_for_button();  // click the button for next graph

	win.detach(t1);
	win.attach(t2);
	sq1.set_fill_color(Color::white);
	sq1.set_style(Line_style::dash);
	sq1.set_color(Color::black);
	sq2.move(200,100);
	win.wait_for_button();
	
	// the following square 3 is for the error testing and it
	// can be changed at the beginning to test the other error
	Square sq3{x2, y2};
	win.attach(sq3);
    } 
    catch (exception& e) {
	cerr << "Caught exception " << e.what() << "\n";
	return 1;
    }
    catch (...) {
	cerr << "what happened?\n";
	return 2;
    }

