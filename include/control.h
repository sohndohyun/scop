#pragma once

#include "dsgm.h"

void initControl();
void computeMatricesFromInputs(float deltaTime);
t_mat4 getProjectionMatrix();
t_mat4 getViewMatrix();