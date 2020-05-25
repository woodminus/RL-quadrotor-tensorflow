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
