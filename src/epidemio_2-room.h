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
#ifndef EPIDEMIO_2_ROOM_H_
#define EPIDEMIO_2_ROOM_H_

#include "biodynamo.h"
#include "human.h"
#include "behavior.h"
#include "sim-param.h"
#include "geom.h"
#include "util_methods.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  Simulation simulation(argc, argv);

  auto* param = simulation.GetParam();
  auto* sparam = param->GetModuleParam<SimParam>();
  // initialize random number generators
  for (int i = 1; i < ThreadInfo::GetInstance()->GetMaxThreads(); i++) {
    simulation.GetAllRandom()[i]->SetSeed(4357 * i);
  }

  // create human population
  HumanCreator(param->min_bound_, param->max_bound_,
    sparam->initial_population_healthy, State::kHealthy);
  HumanCreator(param->min_bound_, param->max_bound_,
    sparam->initial_population_infected, State::kInfected);

  // create ROOT geometry
  BuildTwoRoom();
  // auto geom = BuildTwoRoom();

  // Run simulation for number_of_steps timestep
  for (uint64_t i = 0; i < sparam->number_of_steps; ++i) {
    simulation.GetScheduler()->Simulate(1);
  }

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // EPIDEMIO_2_ROOM_H_
