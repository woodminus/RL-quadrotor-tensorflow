//
//  Obstacle2D.cpp
//  Quadrocopter-Box2D
//
//  Created by anton on 24/06/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include <Box2D/Box2D.h>

#include "Obstacle2D.hpp"

void Obstacle2D::createIn (World2D& w) {

	world = &w;
	worldObjectInfo = std::shared_ptr<WorldObjectInfo> (new WorldObjectInfo (WorldObjectInfo::Type::Obstacle, getId()));

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(0.0f, 0.0f);

	a = 1;
	b = 1;

	body = w.world->CreateBody(&bodyDef);
	body->SetUserData(worldObjectInfo.get());

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(a, b);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//filtering collisions between quadrocopters
	fixtureDef.filter.categoryBits = 0x0004;
	fixtureDef.filter.maskBits = 0x0002;
	body->CreateFixture(&fixtureDef);
	
}

float randFloat (float LO, float HI) {
    return LO + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

void Obstacle2D::reset () {

	a = randFloat(5, 40);
	b = randFloat(5, 40);
	float x = randFloat(-100, 100);
	float y = randFloat(-100, 100);
	float angle = randFloat(0, 2 * M_PI);
	body->SetTransform (b2Vec2(x, y), angle);
	

    b2Fixture *f = body->GetFixtureList