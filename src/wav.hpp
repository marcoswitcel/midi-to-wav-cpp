#pragma once


#include <string>
#include <fstream>

enum Audio_Format
{
  PCM = 1,
  IEEE_754_FLOAT = 3,
};

enum Bits_Per_Sample
{
  /**
   * @brief proporciona 48 dB de faixa dinâmica
   * @note ainda não suportado
   */
  BITS_PER_SAMPLE_8_BITS = 8,
  /**
   * @brief proporciona ~96 dB de faixa dinâmica
   */
  BITS_PER_SAMPLE_16_BITS = 16,
  /**
   * @brief proporciona ~144 dB de faixa dinâmica
   * @note provavelmente não suportado
   */
  BITS_PER_SAMPLE_24_BITS = 24,
  /**
   * @brief formato mais complexo usado em cenários onde precisa de mais qualidade, pode operar diferente dos demais
   * @note não suportado
   */
  BITS_PER_SAMPLE_32_BITS = 32,
};

#pragma pack(push, 1)
/**
 * @brief header padrão dos arquivos wav, configurado como RIFF.
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
  uint16_t bits_per_sample = BITS_PER_SAMPLE_16_BITS;

  // Sessão com os dados
  char data_block_ID[4] = {'d', 'a', 't', 'a'};
  // size em bytes
  uint32_t data_size;
};
#pragma pack(pop)

constexpr auto STANDARD_RIFF_WAV_SIZE_IN_BYTES = 44;
static_assert(sizeof(WAV_File_Header) == STANDARD_RIFF_WAV_SIZE_IN_BYTES, "Deve ter 44 bytes"); 

/**
 * @brief Representa o arquivo "wav" inteiro, header e dados. Geralmente usado
 * nas funções que fazem a leitura e a persistencia de dados.
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

/**
 * @brief inicializa os metadados do arquivo de acordo com as configurações providas
 * 
 * @param wav_file_header cabeçalho do arquivo WAV
 * @param sample_rate número de amostras (samples) de áudio coletados e armazenados por segundo
 * @param num_channels número de canais de áudio
 * @param data_size quantidade de bytes ocupados pelos samples
 */
inline void init_wav_file_header(WAV_File_Header &wav_file_header, uint32_t sample_rate, uint16_t num_channels, uint32_t data_size);

/**
 * @brief inicializa/configura o WAV_File com as informações providas
 * 
 * @param wav_file objeto a ser inicializado
 * @param sample_rate número de amostras (samples) de áudio coletados e armazenados por segundo desejadas
 * @param num_channels número de canais
 * @param data_sample ponteiro pra memória dos samples
 * @param data_size tamanho em bytes
 */
void init_wav_file(WAV_File &wav_file, uint32_t sample_rate, uint16_t num_channels, uint8_t* data_sample, uint32_t data_size);

/**
 * @brief persiste o arquivo em disco usando o nome provido
 * 
 * @param filename nome do arquivo a ser persistido no disco
 * @param wav_file wav file object que será persistido
 * @return true sucesso
 * @return false falha
 */
bool export_wav(const std::string &filename, WAV_File &wav_file);

