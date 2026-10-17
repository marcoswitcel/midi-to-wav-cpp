#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "./command_line_utils.cpp"
#include "./midi.hpp"
#include "./wav.cpp"
#include "./synthesis.hpp"


int main(int argc, const char* argv[])
{
  bool is_verbose = is_string_present_in_argv("--verbose", argc, argv);
  
  if (is_verbose)
  {
    std::cout << "Modo Verboso: Ativo" << std::endl;
  }

  WAV_File wav_file;
  std::string filename = "teste1.wav";

  uint32_t sample_rate_in_hertz = 44100;
  float duration_in_seconds = 2.0;
  uint32_t number_of_samples = duration_in_seconds * sample_rate_in_hertz;
  uint32_t data_size_in_bytes = number_of_samples * 2; // 2 por ser 16-bits
  int16_t* data_sample = new int16_t[number_of_samples];

  float frequency = 440.0f; //nota musical A4
  float amplitude = 0.5f; // geralmente entre 0.2 e 0.8 pra evitar clipping
  generate_sine_wave(frequency, duration_in_seconds, sample_rate_in_hertz, amplitude, data_sample);

  init_wav_file(wav_file, sample_rate_in_hertz, 1, reinterpret_cast<uint8_t*>(data_sample), data_size_in_bytes);

  export_wav(filename, wav_file);

  return EXIT_SUCCESS;
}
