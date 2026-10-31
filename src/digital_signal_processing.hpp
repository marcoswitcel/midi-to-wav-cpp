#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits>

void increase_volume(double gain_db, int16_t* sample_data, size_t sample_length)
{
  double gain_factor = std::pow(10.0, gain_db / 20.0);

  for (size_t i = 0; i < sample_length; i++)
  {
    auto &sample = sample_data[i] ;
    // aplica o fator de ganho em decibel (db)
    sample = sample * gain_factor;
  }
}

