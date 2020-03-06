#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <boost/serialization/vector.hpp>

class AUdp
{
public:
virtual ~AUdp() = default;
  virtual void start() = 0;
};