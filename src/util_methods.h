// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef UTILS_METHODS_
#define UTILS_METHODS_

#include "human.h"
#include "behavior.h"
#include "sim-param.h"

namespace bdm {

  // define human creator
  static void HumanCreator(double min, double max,
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
        x = random->Uniform(min, max);
        y = random->Uniform(min, max);
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

#endif // UTILS_METHODS_
