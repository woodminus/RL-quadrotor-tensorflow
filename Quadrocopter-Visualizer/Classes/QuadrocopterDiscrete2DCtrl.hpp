//
//  QuadrocopterDiscrete2DCtrl.hpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 18/06/16.
//
//

#ifndef QuadrocopterDiscrete2DCtrl_hpp
#define QuadrocopterDiscrete2DCtrl_hpp

#include "Simulation.hpp"
#include "WorldDiscrete.hpp"
#include "QuadrocopterDiscrete2D.hpp"

class QuadrocopterDiscrete2DCtrl {
public:
	
	QuadrocopterDiscrete2DCtrl (int id, QuadrocopterDiscrete2D& simulationModel);
	
	void act ();
	void storeExperience ();
	void calcReward ();
	void reset ();
	void resetAction ();
	double getReward ();
	void setState (const std: