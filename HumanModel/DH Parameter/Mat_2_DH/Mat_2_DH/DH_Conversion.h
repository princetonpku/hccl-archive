
#pragma once
#include "DH_Parameter.h"
#include "TransMat.h"
#include "RotMat.h"


DH_Param ConvertDH2Param (const TransMat& mat); // determines the 4 D-H parameters from the transformation matrix

