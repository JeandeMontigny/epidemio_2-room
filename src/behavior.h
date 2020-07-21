// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny and Lukas Breitwieser.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "core/biology_module/biology_module.h"
#include "human.h"
#include "sim-param.h"
#include "geom.h"

namespace bdm {

  struct CheckSurrounding : public Functor<void, const SimObject*, double> {
    Human* self_;
    double recovery_duration_;

    CheckSurrounding(Human* self, double recovery_duration)
        : self_(self), recovery_duration_(recovery_duration) {}

    // This function operator will be called for every other human within
    // `infection_radius`
    void operator()(const SimObject* neighbor, double squared_distance) override {
      auto* other = bdm_static_cast<const Human*>(neighbor);
      // if a ROOT geometry structure is between humans
      if (ObjectInbetween(self_->GetPosition(), other->GetPosition())) {
        return;
      }
      // otherwise, infection
      if (other->state_ == State::kInfected) {
        self_->state_ = State::kInfected;
        self_->recovery_counter_ = recovery_duration_;
      }
    }
  }; // end CheckSurrounding

// ---------------------------------------------------------------------------
  struct InfectiousBehaviour : public BaseBiologyModule {
    BDM_STATELESS_BM_HEADER(InfectiousBehaviour, BaseBiologyModule, 1);

    InfectiousBehaviour() : BaseBiologyModule(gAllEventIds) {}

    void Run(SimObject* so) override {
      auto* sim = Simulation::GetActive();
      auto* param = sim->GetParam();
      auto* sparam = param->GetModuleParam<SimParam>();
      auto* ctxt = sim->GetExecutionContext();
      auto* human = bdm_static_cast<Human*>(so);

      // recovery time if infected
      if (human->state_ == kInfected) {
        if (human->recovery_counter_ <= 0) {
          human->state_ = State::kRecovered;
        } else {
          human->recovery_counter_--;
        }
      } // end if kInfected

      // infection
      if (human->state_ == kHealthy) {
        CheckSurrounding check(human, sparam->recovery_duration);
        ctxt->ForEachNeighborWithinRadius(check, *human,
           sparam->infection_radius);
      } // end infection

    } // end Run
  }; // end InfectiousBehaviour

// ---------------------------------------------------------------------------
struct MoveRandomly : public BaseBiologyModule {
  BDM_STATELESS_BM_HEADER(MoveRandomly, BaseBiologyModule, 1);

  MoveRandomly() : BaseBiologyModule(gAllEventIds) {}

  void Run(SimObject* so) override {
    auto* sim = Simulation::GetActive();
    auto* random = sim->GetRandom();
    auto* param = sim->GetParam();
    auto* sparam = param->GetModuleParam<SimParam>();

    auto* human = bdm_static_cast<Human*>(so);

    const auto& position = human->GetPosition();
    auto rand_movement = random->UniformArray<3>(-1, 1).Normalize();
    rand_movement[2] = 0;

    if (DistToWall(position, position + rand_movement * sparam->human_speed) > human->GetDiameter()/2) {
      human->SetPosition(position + rand_movement * sparam->human_speed);
    }
  } // end Run
}; // end MoveRandomly

}  // namespace bdm

#endif  // BEHAVIOR_H_
