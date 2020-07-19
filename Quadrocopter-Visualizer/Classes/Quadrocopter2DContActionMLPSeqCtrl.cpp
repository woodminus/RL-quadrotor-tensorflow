//
//  Quadrocopter2DContActionMLPSeqCtrl.cpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 26/10/16.
//
//

#include "Quadrocopter2DContActionMLPSeqCtrl.hpp"
#include "Quadrocopter2DBrain.hpp"
#include "Lib.h"

const int actionSize = 2;

Quadrocopter2DContActionMLPSeqCtrl::Quadrocopter2DContActionMLPSeqCtrl (
	int id,
	Quadrocopter2D& simulationModel
) : Quadrocopter2DCtrl (id, simulationModel)
{
	actionCont.resize(actionSize);
}

void Quadrocopter2DContActionMLPSeqCtrl::calcReward () {

	//награда за приближение к точке
	float prevR = prevState [2];
	float nextR = nextState [2];

	reward = 0.1 * (prevR - nextR);
	if (reward > 0) reward *= 0.9;

	if (simulationModel.isCollided()) {
//std::cout << "--- collided " << std::endl;
		reward = - 1;
	}

}

void Quadrocopter2DContActionMLPSeqCtrl::act () {

	//getting prev state
	readState(prevState);
	
	Quadrocopt