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
	dynamicBox.SetAsBox(0.4, 0.1);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 4.0f; // 0.4 x 0.4 x 4 = 0.64 kg
	fixtureDef.friction = 0.3f;
	//filtering collisions between quadrocopters
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0004;
	body->CreateFixture(&fixtureDef);



	b2BodyDef motorDef;
	motorDef.type = b2_dynamicBody;
	motorDef.position.Set(-0.25f, 0.0f);
	motorDef.linearDamping = 0.0f;
	motorDef.angularDamping = 0.1f;
	motor1Def = motorDef;

	motor1 = w.world->CreateBody(&motorDef);
	motor1->SetUserData(worldObjectInfo.get());
	b2PolygonShape motorShape;
	motorShape.SetAsBox(0.1f, 0.2f);
	
	b2FixtureDef motorFixtureDef;
	motorFixtureDef.shape = &motorShape;
	motorFixtureDef.density = 4.0f; // 0.4 x 0.4 x 4 = 0.64 kg
	motorFixtureDef.friction = 0.3f;
	//filtering collisions between quadrocopters
	motorFixtureDef.filter.categoryBits = 0x0002;
	motorFixtureDef.filter.maskBits = 0x0004;
	
	motor1->CreateFixture(&motorFixtureDef);

	motorDef.position.Set(0.25f, 0.0f);
	motor2Def = motorDef;
	motor2 = w.world->CreateBody(&motorDef);
	motor2->SetUserData(worldObjectInfo.get());
	motor2->CreateFixture(&motorFixtureDef);

	b2WeldJointDef motor1Joint;
	motor1Joint.Initialize(body, motor1, motor1Def.position);
	motor1Joint.collideConnected = false;
	w.world->CreateJoint(&motor1Joint);

	b2WeldJointDef motor2Joint;
	motor2Joint.Initialize(body, motor2, motor2Def.position);
	motor2Joint.collideConnected = false;
	w.world->CreateJoint(&motor2Joint);
}

const b2Vec2& Quadrocopter2D::getPosition () {
	return body->GetPosition ();
}

void Quadrocopter2D::setCoords (const b2Vec2& pos, float angle) {

	angle = degToRad(angle);

//	body->SetLinearVel