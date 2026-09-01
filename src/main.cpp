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

  return EXIT_SUCCESS;
}
