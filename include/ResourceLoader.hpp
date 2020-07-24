

#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <vector>

#include <TELDR/Loader.hpp>

#include "LoaderModels.hpp"

class ResourceLoader
{
public:
  ResourceLoader();
  ResourceLoader(const char *);
  virtual ~ResourceLoader();

  bool loadFile(const char *);

  void load();
  void unload();

private:
  Loader *ldr;
};

#endif