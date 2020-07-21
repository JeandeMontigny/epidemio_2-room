#ifndef UTILS_METHODS
#define UTILS_METHODS

#include "human.h"
#include "behavior.h"
#include "sim-param.h"

namespace bdm {
  using namespace std;

  // define human creator
  static void HumanCreator(double min, double max, int num_human, State state) {
    auto* sim = Simulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto* param = sim->GetParam();
    auto* sparam = param->GetModuleParam<SimParam>();
    auto* random = sim->GetRandom();

    for (int i = 0; i < num_human; i++) {
      Double3 position = {random->Uniform(min, max), random->Uniform(min, max), 150};

      Human* human = new Human(position);
      human->SetDiameter(sparam->human_diameter);
      human->state_ = state;
      human->recovery_counter_ = sparam->recovery_duration;

      human->AddBiologyModule(new InfectiousBehaviour());
      human->AddBiologyModule(new MoveRandomly());
      rm->push_back(human);
    }
  }  // end CellCreator


}

#endif
