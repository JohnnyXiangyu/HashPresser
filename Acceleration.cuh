#pragma once

#include <cuda_runtime.h>
#include <stdio.h>
#include <cassert>
#include <iostream>

__global__ void PerCharacter(std::string targetHash, int targetLength);
