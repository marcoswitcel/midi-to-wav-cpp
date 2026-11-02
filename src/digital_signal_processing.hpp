#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits>

/**
 * @brief 
 * @todo João, avaliar mais essa função...
 * 
 * @param gain_db 
 * @param limit_threshold 
 * @param sample_data 
 * @param sample_length 
 */
void increase_volume(double gain_db, double limit_threshold, int16_t* sample_data, size_t sample_length)
{
  double gain_factor = std::pow(10.0, gain_db / 20.0);
  constexpr double numeric_limit_of_type = std::numeric_limits<int16_t>::max();

  for (size_t i = 0; i < sample_length; i++)
  {
    // aplica o fator de ganho em decibel (db)
    double sample = static_cast<double>(sample_data[i]) * gain_factor / numeric_limit_of_type;

    // branchless limit
    sample = std::clamp(sample, -limit_threshold, limit_threshold);

    // @note aqui há a perca de um número no espaço negativo, 
    sample_data[i] = static_cast<int16_t>(sample * numeric_limit_of_type);
  }
}

