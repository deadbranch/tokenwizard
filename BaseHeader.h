//
// Created by origin on 29.10.16.
//

#ifndef TOKENWIZARD_BASEHEADER_H
#define TOKENWIZARD_BASEHEADER_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <random>
#include <algorithm>
#include <cstdint>

using std::string;
using std::vector;

using std::cout;
using std::cerr;
using std::endl;

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>

#include "../../concurrent-guard/cg_shared_ptr.h"

using boost::make_shared;
using boost::asio::ip::tcp;


#endif //TOKENWIZARD_BASEHEADER_H
