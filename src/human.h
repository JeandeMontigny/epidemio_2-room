#ifndef HUMAN_H_
#define HUMAN_H_

#include "core/sim_object/cell.h"
#include "core/biology_module/biology_module.h"

namespace bdm {

/// Possible states
enum State { kHealthy, kInfected, kRecovered };

class Human : public Cell {
  BDM_SIM_OBJECT_HEADER(Human, Cell, 1, state_, recovery_counter_);

 public:
  Human() {}
  Human(const Event& event, SimObject* other, uint64_t new_oid = 0)
      : Base(event, other, new_oid) {}
  explicit Human(const Double3& position) : Base(position) {}

  /// This data member stores the current state of the agent.
  int state_ = State::kHealthy;
  /// Once the agent becomes infected, this counter is set to the
  /// recovery duration.
  double recovery_counter_ = 0;
};

}  // namespace bdm

#endif // HUMAN_H_
