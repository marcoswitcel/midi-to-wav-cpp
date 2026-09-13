
#include <string>
#include <fstream>

#include "./wav.hpp"


inline void patch_wav_file_header_size(WAV_File_Header &wav_file_header, uint32_t data_size)
{
  // ajusta tamanho do arquivo
  wav_file_header.file_size = (STANDARD_RIFF_WAV_SIZE_IN_BYTES - 8) + data_size; 
  // define quantidade de samples (em bytes)
  wav_file_header.data_size = data_size;
}

inline void init_wav_file_header(WAV_File_Header &wav_file_header, uint32_t sample_rate, uint16_t num_channels, uint32_t data_size)
{
  wav_file_header.bits_per_sample = 16;

  wav_file_header.num_channels = num_channels;
  wav_file_header.sample_rate = sample_rate;
  
  wav_file_header.bytes_per_block = (num_channels * wav_file_header.bits_per_sample / 8);
  wav_file_header.byte_per_sec = sample_rate * wav_file_header.bytes_per_block;

  patch_wav_file_header_size(wav_file_header, data_size);
}

void init_wav_file(WAV_File &wav_file, uint32_t sample_rate, uint16_t num_channels, uint8_t* data_sample, uint32_t data_size)
{
  init_wav_file_header(wav_file.header, sample_rate, num_channels, data_size);

  wav_file.data_sample = data_sample;
}

bool export_wav(const std::string &filename, WAV_File &wav_file)
{
  std::ofstream file(filename, std::ios::binary);
  
  // @note por hora sem log do motivo do erro...
  if (!file) return false;

  file.write(reinterpret_cast<const char *>(&wav_file.header), sizeof(WAV_File_Header));
  file.write(reinterpret_cast<const char *>(wav_file.data_sample), wav_file.header.data_size);

  // força o fechamento
  file.close();

  // responde ocorreu tudo bem, inclusive com o fechamento
  return !file.fail();
}

