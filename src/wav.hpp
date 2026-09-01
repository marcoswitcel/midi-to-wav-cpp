#pragma once


#pragma pack(push, 1)
/**
 * @brief 
 * @url https://en.wikipedia.org/wiki/WAV#WAV_file_header
 */
struct WAV_File_Header
{
  // Master RIFF chunk
  char riff[4] = {'R', 'I', 'F', 'F'};
  uint32_t chunkSize;
  char wave[4] = {'W', 'A', 'V', 'E'};
  // Chunk describing the data format
  char fmt[4]  = {'f', 'm', 't', ' '};
  // @todo João, implementar
};
#pragma pack(pop)
