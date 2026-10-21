#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits>

#include "./wav.hpp"

struct Playing_Note_Command
{
  float frequency;
  float duration_in_seconds;
};

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

void sinthesize_notes(std::string filename, uint32_t sample_rate_in_hertz, size_t notes_length, Playing_Note_Command note_commands[])
{
  WAV_File wav_file;
  float total_duration_in_seconds = 0;

  // agrega total
  for (size_t i = 0; i < notes_length; i++)
  {
    auto &note_command = note_commands[i];
    total_duration_in_seconds += note_command.duration_in_seconds;
  }

  // calcula e aloca
  uint32_t number_of_samples = total_duration_in_seconds * sample_rate_in_hertz;
  uint32_t data_size_in_bytes = number_of_samples * 2; // 2 por ser 16-bits
  int16_t* data_sample = new int16_t[number_of_samples];

  // @todo João, volume configurável?
  float amplitude = 0.5f;
  uint32_t number_of_samples_done = 0;
  for (size_t i = 0; i < notes_length; i++)
  {
    auto &note_command = note_commands[i];
    generate_sine_wave(note_command.frequency, note_command.duration_in_seconds, sample_rate_in_hertz, amplitude, &data_sample[number_of_samples_done]);
    number_of_samples_done += note_command.duration_in_seconds * sample_rate_in_hertz;
  }

  init_wav_file(wav_file, sample_rate_in_hertz, 1, reinterpret_cast<uint8_t*>(data_sample), data_size_in_bytes);

  export_wav(filename, wav_file);
}
