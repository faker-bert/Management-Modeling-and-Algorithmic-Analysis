

#include "scenario/ExternalForcing.h"

#include <utility>

#include "netcdfpp.h"

namespace acclimate {

ExternalForcing::ExternalForcing(std::string filename, std::string variable_name) {
    file.open(std::move(filename), 'r');
    variable = std::make_unique<netCDF::Variable>(file.variable(std::move(variable_name)).require());
    time_variable = std::make_unique<netCDF::Variable>(file.variable("time").require());
    time_index_count = time_variable->size();
    time_index = 0;
}

ExternalForcing::~ExternalForcing() = default;  // needed to use forward declares for std::unique_ptr

int ExternalForcing::next_timestep() {
    if (time_index >= time_index_count) {
        return -1;
    }
    read_data();
    auto day = time_variable->get<int, 1>({time_index});
    time_index++;
    return day;
}

std::string ExternalForcing::calendar_str() const { return time_variable->attribute("calendar").require().get_string(); }

std::string ExternalForcing::time_units_str() const { return time_variable->attribute("units").require().get_string(); }
}  // namespace acclimate
