//
//  ObstacleDiscrete2D.cpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 23/06/16.
//
//

#include "ObstacleDiscrete2D.hpp"
#include "Lib.h"
#include <Box2D/Box2D.h>

void ObstacleDiscrete2D::step () {
	x += vx;
	y += vy;
	angle += w;
}

void ObstacleDiscrete2D::reset () {
	a = Lib::randFloat(5, 40);
	b = Lib::randFloat(5, 40);
	a2 = a * 0.5;
	b2 = b * 0.5;
	x = Lib::randFloat(-100, 100);
	y = Lib::randFloat(-100, 100);
	angle = Lib::randFloat(0, 2 * M_PI);
	
	vx = 0;//Lib::randFloat(-0.2, 0.2);
	vy = 0;//Lib::randFloat(-0.2, 0.2);
	w = 0;//Lib::randFloat(-0.02, 0.02);
}

bool ObstacleDiscrete2D::isCollidedW