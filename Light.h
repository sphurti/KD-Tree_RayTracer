#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "Vector.h"

class Light{

	private:
		Vector pos;
	public:
		Light();
		~Light();
		Light(Vector p);
		Vector getPosition();
		void setPosition(Vector&);
};

#endif
