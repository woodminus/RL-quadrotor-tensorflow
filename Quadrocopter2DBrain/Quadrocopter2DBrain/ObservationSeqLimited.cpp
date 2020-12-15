//
//  ObservationSeqLimited.cpp
//  Quadrocopter2DBrain
//
//  Created by anton on 12/03/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "ObservationSeqLimited.hpp"

ObservationSeqLimited::ObservationSeqLimited () {}

ObservationSeqLimited::ObservationSeqLimited (int limit) {
	setLimit(limit);
}

ObservationSeqLimited::ObservationSeqLimited (const std::vector <float>& data) {
	setLimit(1);
	push(Observation(data));
}

void ObservationSeqLimited::setLimit (int limit) {
	this->limit = limit;
	observations.resize(limit);
}

void ObservationSeqLimited::initWith (const Observation& ob) {
	for (int i=0;