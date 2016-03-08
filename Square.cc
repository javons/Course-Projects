#include "Square.h"

namespace Graph_lib {

    void Square::draw_lines() const
    {
	if (fill_color().visibility()) {	// fill
	    fl_color(fill_color().as_int());
	    fl_rectf(point(0).x,point(0).y,s,s);
	    fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {	// edge on top of fill
	    fl_color(color().as_int());
	    fl_rect(point(0).x,point(0).y,s,s);
	}
    }
}
