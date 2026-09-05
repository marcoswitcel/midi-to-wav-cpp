#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "./command_line_utils.cpp"
#include "./midi.hpp"
#include "./wav.hpp"


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
  float duration_in_Seconds = 2.0;
  uint32_t data_size = duration_in_Seconds *  sample_rate_in_hertz;
  uint8_t* data_sample = new uint8_t[data_size];

  init_wav_file(wav_file, sample_rate_in_hertz, 1, data_sample, data_size);

  export_wav(filename, wav_file);

  return EXIT_SUCCESS;
}
