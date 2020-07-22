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
#include "population_creation.h"
#include "util_methods.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  Simulation simulation(argc, argv);

  auto* param = simulation.GetParam();
  auto* sparam = param->GetModuleParam<SimParam>();
  auto* rm = simulation.GetResourceManager();
  simulation.GetRandom()->SetSeed(5649); // rand() % 10000

  // create ROOT geometry
  BuildTwoRoom();
  // auto geom = BuildTwoRoom();

  // create human population
  HumanCreator(-990, 990, -490, 490,
    sparam->initial_population_healthy, State::kHealthy);
  HumanCreator(-990, 990, -490, 490,
    sparam->initial_population_infected, State::kInfected);
  std::cout << "population created" << std::endl;

  // Run simulation for number_of_steps timestep
  for (uint64_t i = 0; i < sparam->number_of_steps; ++i) {
    simulation.GetScheduler()->Simulate(1);
  }

  double infected = 0;
  rm->ApplyOnAllElements([&](SimObject* so) {
    auto* human = bdm_static_cast<Human*>(so);
    infected += human->state_ == State::kInfected;
    infected += human->state_ == State::kRecovered;
  });
  std::cout << infected << " are or have been infected" << std::endl;

  std::cout << "done" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // EPIDEMIO_2_ROOM_H_
