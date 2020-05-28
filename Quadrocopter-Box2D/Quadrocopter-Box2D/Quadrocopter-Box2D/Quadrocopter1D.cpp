//
//  Quadrocopter1D.cpp
//  Quadrocopter-Box2D
//
//  Created by anton on 27/04/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "Quadrocopter1D.hpp"
#include "World.hpp"

Quadrocopter1D::Quadrocopter1D () {}

Quadrocopter1D::~Quadrocopter1D () {};

void Quadrocopter1D::createIn (World1D& w) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.1f;
//	bodyDef.fixedRotation = true;
	body = w.world