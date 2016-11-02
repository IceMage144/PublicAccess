#ifndef __PGMDRAWER_H__
#define __PGMDRAWER_H__

#include "polygons.h"
#include <cstdio>

class Canvas {
public:
	bool save_pgm (const GraphicalObject& obj, FILE *output,
					int pix_per_unit, int sample_size) const;
};

#endif