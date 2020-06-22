//
//  WorldBase.hpp
//  Quadrocopter-Box2D
//
//  Created by anton on 24/06/16.
//  Copyright © 2016 anton. All rights reserved.
//

#ifndef WorldBase_hpp
#define WorldBase_hpp

#include <vector>
#include <functional>
#include <iostream>

template <typename QuadrocopterType, typename ObstacleType>
class WorldBase {

public:

	virtual ~WorldBase () {};

	typedef std::function<void (
		ObstacleType& obstacle,
		QuadrocopterType& copter
	)> CollideListener;

	std::vector<QuadrocopterType>& getQuadrocopters ();
	QuadrocopterType& getQuadrocopter (int i) { return quadrocopters [i]; }
	ObstacleType& getObstacle (int i);
	
	std::vector<ObstacleType>& getObstacles () {
		return obstacles;
	}
	
	virtual void step () {
		for (auto& q : quadrocopters) {
			q.step();
		}
		for (auto& o : obstacles) {
			o.step();
		}
	}
	
	virtual void afterStep () {
		for (auto& q : quadrocopters) {
			q.clearSensors ();
			for (auto& o : obstacles) {
				q.sense (o);
			}
		}
	}

	virtual QuadrocopterType& createQuadrocopter ();
	virtual ObstacleType& createObstacle ();
	
	void setCollideListener (CollideListener listener) {
		collideListener = listener;
	}

protected:

	std::vector<QuadrocopterType> quadrocopters;
	std::vector<ObstacleType> obsta