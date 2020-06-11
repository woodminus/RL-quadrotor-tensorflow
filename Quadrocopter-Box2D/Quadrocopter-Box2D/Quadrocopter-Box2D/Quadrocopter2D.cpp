//
//  Quadrocopter2D.cpp
//  Quadrocopter-Box2D
//
//  Created by anton on 24/05/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include <iostream>

#include "Quadrocopter2D.hpp"

Quadrocopter2D::Quadrocopter2D () {
	sensors.resize(sensorsCount);
}

Quadrocopter2D::~Quadrocopter2D () {};

void Quadrocopter2D::createIn (World2D& w) {

	world = &w;
	worldObjectInfo = std::shared_ptr<WorldObjectInfo> (new WorldObjectInfo (WorldObjectInfo::Type::Quadrocopter, id));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.1f;
//	bodyDef.fixedRotation = true;

	body = w.world->CreateBody(&bodyDef);
	body->SetUserData(worldObjectInfo.get());
	b2PolygonShape dynamicBox;