#include <iostream>

using namespace std;

#ifndef LIB_COLORS_H_INCLUDED
#define LIB_COLORS_H_INCLUDED

struct Color4f  {float r,g,b,a;};

class Colors {

	private:

		float *convert(Color4f c) {
			float *tab = new float [4];
			tab[0] = c.r; tab[1] = c.g; tab[2] = c.b; tab[3] = c.a;
			return tab;
		}

	public :

		static const Color4f red;
		static const Color4f green;
		static const Color4f blue;

		static const Color4f black;
		static const Color4f white;

		float *white4f;
		float *black4f;
		float *red4f;

		Colors(void) {
			this->white4f = this->convert(white);
			this->black4f = this->convert(black);
			this->red4f   = this->convert(red);
		}

		virtual ~Colors() {}
};


#endif
