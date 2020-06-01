

#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <iostream> 
#include <fstream> 

class ResourceLoader
{
public:
  ResourceLoader(const char *);
  virtual ~ResourceLoader();

  void load();
  void unload();

private:
  std::ifstream file;
};


#endif