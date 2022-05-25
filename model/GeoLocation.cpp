
#include "model/GeoLocation.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>

#include "acclimate.h"
#include "model/GeoConnection.h"
#include "model/GeoPoint.h"

namespace acclimate {

GeoLocation::GeoLocation(Model* model_p, id_t id_p, TransportDelay delay_p, GeoLocation::type_t type_p)
    : GeoEntity(model_p, delay_p, GeoEntity::type_t::LOCATION), type(type_p), id(std::move(id_p)) {}

void GeoLocation::remove_connection(const GeoConnection* connection) {
    auto it = std::find_if(std::begin(connections), std::end(connections), [connection](const auto& c) { return c.get() == connection; });
    if (it == std::end(connections)) {
        throw log::error(this, "Connection ", connection->name(), " not found");
    }
    connections.erase(it);
}

GeoLocation::~GeoLocation() {
    for (auto& connection : connections) {
        connection->invalidate_location(this);
    }
}

void GeoLocation::set_centroid(FloatType lon_p, FloatType lat_p) {
    debug::assertstep(this, IterationStep::INITIALIZATION);
    centroid_m = std::make_unique<GeoPoint>(lon_p, lat_p);
}

}  // namespace acclimate
