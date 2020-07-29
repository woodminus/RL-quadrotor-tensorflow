//
//  Visualizer2DScene.hpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 24/05/16.
//
//

#ifndef Visualizer2DScene_hpp
#define Visualizer2DScene_hpp

#include "cocos2d.h"
#include "QuadrocopterSimulator.hpp"
#include "main.h"

class Quadrocopter2DView {
public:
	
	void init ();
	void addTo (cocos2d::Node* parent);
	void setCoordsFrom (con