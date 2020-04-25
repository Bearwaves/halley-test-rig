#!/bin/bash

cmake -DBUILD_HALLEY_TESTS=0 -DBUILD_HALLEY_TOOLS=1 \
  -DShaderConductor_INCLUDE_DIR=/Users/joel/Code/ShaderConductor/Include \
  -DShaderConductor_LIBRARY=/Users/joel/Code/ShaderConductor/Lib/libShaderConductor.dylib \
  ..
