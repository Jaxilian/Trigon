#include "pipeline.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////

std::vector<char> readFile(const std::string& filename) 
{
  std::ifstream file{filename, std::ios::ate | std::ios::binary};

  if (!file.is_open()) 
  {
    throw std::runtime_error("failed to open file: " + filename);
  }
  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return buffer;
}

////////////////////////////////////////////////////////////////////

void vkpipe::createPipe(const char* vertPath, const char* fragPath)
{

    auto vertCode = readFile(std::string(vertPath));
    auto fragCode = readFile( std::string(fragPath));

    #ifdef _DEBUG
    std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
    std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
    #endif
    
}