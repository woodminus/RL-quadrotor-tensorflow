//
//  Lib.h
//  QuizGeek
//
//  Created by anton on 13.11.14.
//
//

#ifndef __QuizGeek__Lib__
#define __QuizGeek__Lib__

#include <vector>

class Lib {

public:
	
	static void randomize ();
	static int randInt (int min, int max);
	static float randFloat (float LO, float HI);
	static long long getTimestampInMillis ();
	
	static float degToRad (float deg);
	static float radToDeg (