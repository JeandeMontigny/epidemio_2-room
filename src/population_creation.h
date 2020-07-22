// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef POPULATION_CREATION_
#define POPULATION_CREATION_

#include "human.h"
#include "behavior.h"
#include "sim-param.h"
#include "geom.h"

namespace bdm {

  // define human creator
  static void HumanCreator(double min_x, double max_x,
                           double min_y, double max_y,
                           int num_human, State state) {

    auto* sim = Simulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto* param = sim->GetParam();
    auto* sparam = param->GetModuleParam<SimParam>();
    auto* random = sim->GetRandom();

    double x, y;
    double z = 150;
    for (int i = 0; i < num_human; i++) {
      do {
        x = random->Uniform(min_x, max_x);
        y = random->Uniform(min_y, max_y);
      } while (IsInsideStructure({x, y, z}));

      Human* human = new Human({x, y, z});
      human->SetDiameter(sparam->human_diameter);
      human->state_ = state;
      human->recovery_counter_ = sparam->recovery_duration;

      human->AddBiologyModule(new InfectiousBehaviour());
      human->AddBiologyModule(new MoveRandomly());
      rm->push_back(human);
    }
  }  // end CellCreator

}

#endif // POPULATION_CREATION_
