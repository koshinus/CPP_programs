// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <numeric>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <array>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <thread>
using namespace boost::asio;
const size_t BUF_SIZE = 20;
using sock = ip::tcp::socket;



// TODO: reference additional headers your program requires here
