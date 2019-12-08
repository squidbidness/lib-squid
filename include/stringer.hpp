#pragma once

#include <sstream>
#include <string>

namespace squid {

    template< typename... Args >
    std::string stringer( Args &&...args ) {
        std::ostringstream oss;
        ( oss << ... << args );
        return oss.str();
    }

}
