

#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <iostream>
#include <string>
#include <fstream>

class ResourceLoader
{
public:
  ResourceLoader(const char *);
  virtual ~ResourceLoader();

  void load();
  void unload();

private:
  const std::string file_path;
  std::ifstream file;
};

#endif