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
	

    b2Fixture *f = body->GetFixtureList();
    body->DestroyFixture(f);
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(a * 0.5, b * 0.5);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//filtering collisions between quadrocopters
	fixtureDef.filter.categoryBits = 0x0004;
	fixtureDef.filter.maskBits = 0x0002;
	body->CreateFixture(&fixtureDef);

}

void Obstacle2D::getCoords (
	float& centerX,
	float& centerY,
	float& a,
	float& b,
	float& angle
) const {
	centerX = body->GetPosition().x;
	centerY = body->GetPosition().y;
	a = this->a;
	b = this->b;
	angle = radToDeg(body->GetAngle());
}

void Obstacle2D::getPoints (
	float& x0,
	float& y0,
	float& x1,
	float& y1,
	float& x2,
	float& y2,
	float& x3,
	float& y3
) const {

	float a2, b2, px0, py0, px1, py1, px2, py2, px3, py3;
	float angle = body->GetAngle() + M_PI_2;
	
	float x = body->GetPosition().x;
	float y = body->GetPosition().y;
	
	a2 = a * 0.5;
	b2 = b * 0.5;

	px0 = - a2; py0 = + b