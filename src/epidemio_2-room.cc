// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#include "epidemio_2-room.h"
#include "sim-param.h"

int main(int argc, const char** argv) {
  // register parameters that are specific for this simulation
  bdm::Param::RegisterModuleParam(new bdm::SimParam());
  return bdm::Simulate(argc, argv);
}
