//
//  QuadrocopterContActionCtrl.cpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 13/08/16.
//
//

#include "QuadrocopterContActionCtrl.hpp"
#include "Quadrocopter2DBrain.hpp"
#include "Lib.h"

const int actionSize = 1;

QuadrocopterContActionCtrl::QuadrocopterContActionCtrl (int id, Quadrocopter1D& simulationModel) :
	QuadrocopterCtrl(id, simulationModel)
{
	actionCont.resize(actionSize);
}

void QuadrocopterContActionCtrl::calcReward () {

	//награда за приближение к точке
	float prevX = fabsf(prevState [0]);
	float nextX = fabsf(nextState [0]);

	reward = 2 * (prevX - nextX);
	if (reward > 0) reward *= 0.5;

}

void QuadrocopterContActionCtrl::act () {

	/