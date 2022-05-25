

#include "model/GeoRoute.h"

#include <cstddef>

#include "model/GeoEntity.h"

namespace acclimate {

std::string GeoRoute::name() const {
    std::string res;
    for (std::size_t i = 0; i < path.size(); ++i) {
        if (i > 0) {
            res += "->";
        }
        res += path[i]->name();
    }
    return res;
}

}  // namespace acclimate
