

#include "model/GeoEntity.h"

#include "acclimate.h"
#include "model/TransportChainLink.h"

namespace acclimate {

GeoEntity::GeoEntity(Model* model_p, TransportDelay delay_p, GeoEntity::type_t type_p) : model_m(model_p), delay(delay_p), entity_type(type_p) {}

void GeoEntity::set_forcing_nu(Forcing forcing_nu_p) {
    for (auto link : transport_chain_links) {
        link->set_forcing_nu(forcing_nu_p);
    }
}

GeoEntity::~GeoEntity() {
    for (auto link : transport_chain_links) {
        link->unregister_geoentity();
    }
}

}  // namespace acclimate
