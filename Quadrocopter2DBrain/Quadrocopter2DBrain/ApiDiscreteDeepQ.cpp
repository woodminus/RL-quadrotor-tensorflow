//
//  ApiDiscreteDeepQ.cpp
//  Quadrocopter2DBrain
//
//  Created by anton on 20/03/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "ApiDiscreteDeepQ.hpp"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "Unity/IUnityGraphics.h"

#include "Main.h"
#include "QuadrocopterBrain.hpp"
#include "ExpLambdaFilter.hpp"

using namespace std;

const int numOfQuadrocopters = 50;
