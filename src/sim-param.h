// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny and Lukas Breitwieser.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef SIM_PARAM_H_
#define SIM_PARAM_H_

#include "core/param/module_param.h"

namespace bdm {

/// This class defines parameters that are specific to this simulation.
struct SimParam : public ModuleParam {
  static const ModuleParamUid kUid;

  ModuleParam* GetCopy() const override;

  ModuleParamUid GetUid() const override;

  SimParam() {}

  uint64_t number_of_steps = 30;
  uint64_t initial_population_healthy = 1;
  uint64_t initial_population_infected = 1;
  double infection_radius = 10;
  double recovery_duration = 30;
  double human_diameter = 70; // cm
  double human_speed = 1;
  double infection_probablity = 0.1;

 protected:
  /// Assign values from config file to variables
  void AssignFromConfig(const std::shared_ptr<cpptoml::table>&) override;

 private:
  BDM_CLASS_DEF_OVERRIDE(SimParam, 1);
};

}  // namespace bdm

#endif  // SIM_PARAM_H_
