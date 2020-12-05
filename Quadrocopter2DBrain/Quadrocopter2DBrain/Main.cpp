//
//  Main.cpp
//  QuadrocopterBrain
//
//  Created by anton on 18.10.15.
//  Copyright © 2015 anton. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "Unity/IUnityGraphics.h"

#include "Main.h"
#include "ApiDiscreteDeepQ.hpp"

// --------------------------------------------------------------------------
// Include headers for the graphics APIs we support

#if SUPPORT_D3D9
	#include <d3d9.h>
	#include "Unity/IUnityGraphicsD3D9.h"
#endif
#if SUPPORT_D3D11
	#include <d3d11.h>
	#include "Unity/IUnityGraphicsD3D11.h"
#endif
#if SUPPORT_D3D12
	#include <d3d12.h>
	#include "Unity/IUnityGraphicsD3D12.h"
#endif

#if SUPPORT_OPENGLES
	#if UNITY_IPHONE
		#include <OpenGLES/ES2/gl.h>
	#elif UNITY_ANDROID
		#include <GLES2/gl2.h>
	#endif
#elif SUPPORT_OPENGL
	#if UNITY_WIN || UNITY_LINUX
		#include <GL/gl.h>
	#else
		#include <OpenGL/gl.h>
	#endif
#endif

using namespace std;

// Prints a string
void DebugLog (std::string str)
{
#if UNITY_WIN
    OutputDebugStringA (str.c_str ());
#else
    fprintf(stderr, "%s\n", str.c_str ());
#endif
}

static void UNITY_INTERFACE_API OnRenderEvent(int even