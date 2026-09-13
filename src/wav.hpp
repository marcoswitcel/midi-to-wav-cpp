#pragma once


#include <string>
#include <fstream>

enum Audio_Format
{
  PCM = 1,
  IEEE_754_FLOAT = 3,
};

#pragma pack(push, 1)
/**
 * @brief 
 * @url https://en.wikipedia.org/wiki/WAV#WAV_file_header
 */
struct WAV_File_Header
{
  // Master RIFF
  char file_type_block_ID[4] = {'R', 'I', 'F', 'F'};
  uint32_t file_size;
  char file_format_ID[4]     = {'W', 'A', 'V', 'E'};
  
  // Metadados sobre o formato
  char format_block_ID[4]  = {'f', 'm', 't', ' '};
  uint32_t block_size      = 16; // PCM format
  uint16_t audio_format    = 1;  // (1: PCM integer, 3: IEEE 754 float) Uncompressed PCM
  uint16_t num_channels    = 1;  // Mono; 1 = Mono, 2 = Stereo
  uint32_t sample_rate     = 44100; // in hertz
  uint32_t byte_per_sec    = 44100 * 2;
  uint16_t bytes_per_block = 2;
  uint16_t bits_per_sample = 16;

  // Sessão com os dados
  char data_block_ID[4] = {'d', 'a', 't', 'a'};
  uint32_t data_size;
};
#pragma pack(pop)

constexpr auto STANDARD_RIFF_WAV_SIZE_IN_BYTES = 44;
static_assert(sizeof(WAV_File_Header) == STANDARD_RIFF_WAV_SIZE_IN_BYTES, "Deve ter 44 bytes"); 

/**
 * @brief Representa o arquivo na integra
 * 
 */
struct WAV_File
{
  WAV_File_Header header;
  uint8_t *data_sample;
};

/**
 * @brief realiza o processo de update dos campos apropriados para definir o tamanho do arquivo que deve ser escrito
 * 
 * @param wav_file_header 
 * @param data_size 
 */
inline void patch_wav_file_header_size(WAV_File_Header &wav_file_header, uint32_t data_size);

inline void init_wav_file_header(WAV_File_Header &wav_file_header, uint32_t sample_rate, uint16_t num_channels, uint32_t data_size);

void init_wav_file(WAV_File &wav_file, uint32_t sample_rate, uint16_t num_channels, uint8_t* data_sample, uint32_t data_size);

bool export_wav(const std::string &filename, WAV_File &wav_file);

