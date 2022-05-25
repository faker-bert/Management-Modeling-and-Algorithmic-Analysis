

#include "model/EconomicAgent.h"

#include <utility>

#include "acclimate.h"
#include "model/Region.h"
#include "model/Storage.h"

namespace acclimate {

EconomicAgent::EconomicAgent(id_t id_p, Region* region_p, EconomicAgent::type_t type_p) : id(std::move(id_p)), region(region_p), type(type_p) {}

EconomicAgent::~EconomicAgent() = default;  // needed to use forward declares for std::unique_ptr

Model* EconomicAgent::model() { return region->model(); }
const Model* EconomicAgent::model() const { return region->model(); }

Parameters::AgentParameters const& EconomicAgent::parameters_writable() const {
    debug::assertstep(this, IterationStep::INITIALIZATION);
    return parameters_;
}

void EconomicAgent::set_forcing(const Forcing& forcing_p) {
    debug::assertstep(this, IterationStep::SCENARIO);
    assert(forcing_p >= 0.0);
    forcing_m = forcing_p;
}

}  // namespace acclimate
