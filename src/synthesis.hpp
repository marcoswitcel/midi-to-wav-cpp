#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits>

/**
 * @brief gera os samples (amostras) para a frequência provida
 * 
 * @param frequency número de ciclos de onda completos por segundo, medido em Hertz(Hz)
 * @param duration_in_seconds duração em segundos
 * @param sample_rate_in_hertz número de amostras (samples) de áudio coletados e armazenados por segundo
 * @param amplitude Volume ou fator de escalonamento máximo da onda, limitado ao range 0.0f (silencio) e 1.0f (volume máximo). Recomendado: 0.5f
 * @param data_sample ponteiro da memória alocada para os 
 */
void generate_sine_wave(float frequency, float duration_in_seconds, uint32_t sample_rate_in_hertz, float amplitude, int16_t* data_sample)
{
  // @note no futuro dá pra fazer tempalte e passar o type
  constexpr auto numeric_limit_of_type = std::numeric_limits<int16_t>::max();
  
  size_t total_samples = static_cast<size_t>(sample_rate_in_hertz * duration_in_seconds);

  // limita a amplitude para previnir clipping
  amplitude = std::clamp(amplitude, 0.0f, 1.0f);

  int16_t max_amplitude = static_cast<int16_t>(numeric_limit_of_type * amplitude);

  for (size_t i = 0; i < total_samples; i++)
  {
    double time = static_cast<double>(i) / sample_rate_in_hertz;
    // calcula o ângulo da fase em radianos: 2 * PI * frequência * tempo 
    double angle = 2.0 * M_PI * frequency * time;

    // converte a onda senoidal (-1.0 a 1.0) para o range de inteiro 16-bit assinado 
    data_sample[i] = static_cast<int16_t>(std::sin(angle) * max_amplitude);
  }
}
