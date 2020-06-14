//
//  Quadrocopter2D.hpp
//  Quadrocopter-Box2D
//
//  Created by anton on 24/05/16.
//  Copyright © 2016 anton. All rights reserved.
//

#ifndef Quadrocopter2D_hpp
#define Quadrocopter2D_hpp

#include <vector>
#include <iostream>

#include "World.hpp"
#include "QuadrocopterModelIFace.hpp"
#include "WorldObjectInfo.hpp"

class Quadrocopter2D : public QuadrocopterModel2DIFace {

public:

	Quadrocopter2D ();
	~Quadrocopter2D () override;
	
	void createIn (World2D& w);

	const b2Vec2& getPosition ();
	void setCoords (const b2Vec2& pos, float angle) override;
	float getRotation 