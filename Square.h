#ifndef SQUARE_H
#define SQUARE_H

#include <Graph.h>

namespace Graph_lib {

    struct Square: Shape {
    
    public:
	Square(Point x, int ss): s{ss} {
	    add(x);
	}
	Square(Point p, Point q): s{q.x - p.x} {
	    int h = q.y - p.y;
	    if (s <= 0)
		error("Bad square: non-positive side length");
	    else if (s!= h)
		error("Bad square: width, height not equal");
	    else {
		add(p);
	    }
	}

	void draw_lines() const;
	int side() const { return s; };
    
    private:
	int s;
    };
}
#endif
