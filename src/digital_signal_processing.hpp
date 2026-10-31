#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits>

void increase_volume(double gain_db, double limit_threshold, int16_t* sample_data, size_t sample_length)
{
  double gain_factor = std::pow(10.0, gain_db / 20.0);

  for (size_t i = 0; i < sample_length; i++)
  {
    // aplica o fator de ganho em decibel (db)
    double sample = sample_data[i] * gain_factor;

    // branchless limit
    sample = std::clamp(sample, -limit_threshold, limit_threshold);

    sample_data[i] = static_cast<int16_t>(sample);
  }
}

