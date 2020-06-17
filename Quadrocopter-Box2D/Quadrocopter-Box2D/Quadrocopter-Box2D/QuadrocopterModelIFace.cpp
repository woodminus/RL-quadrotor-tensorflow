//
//  QuadrocopterModelIFace.cpp
//  Quadrocopter-Box2D
//
//  Created by anton on 18/06/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "QuadrocopterModelIFace.hpp"

void QuadrocopterModel2DIFace::setId (int id)
{
	this->id = id;
}

int QuadrocopterModel2DIFace::getId () const
{
	return id;
}

void QuadrocopterModel2DIFace::setCollided (bool collided) {
	this->collided =collided;
	for (auto& s : getSensors()) {
		s = sensorsMagnitude;
	}
}

bool QuadrocopterModel2DIFace::isCollided () const {
	return collided;
}

void QuadrocopterModel2DIFace::clearSensors () {
	for (auto& s : sensors) {
		s = sensorsMagnitude;
	}
}

std::vector<float>& QuadrocopterModel2DIFace::getSensors () const {
	return sensors;
}

bool getLineSegmentsIntersection (
	float p0_x, float p0_y, //first line points
	float p1_x, float p1_y,
	float p2_x, float p2_y, //sencond lise points
	float p3_x, float p3_y,
	float& i_x, float& i_y,
	float& t//intersection point in part of length of first line
) {
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom;
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s32_x = p3_x - p2_x;
    s32_y = p3_y - p2_y;

    denom = s10_x * s32_y - s32_x * s10_y;
    if (denom == 0)
        return false; // Collinear
    bool denomPositive = denom > 0;

    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
    s_numer = s10_x * s02_y - s10_y * s02_x;
    if ((s_numer < 0) == denomPositive)
        return false; // No collision

    t_numer = s32_x * s02_y - s32_y * s02_x;
    if ((t_numer <