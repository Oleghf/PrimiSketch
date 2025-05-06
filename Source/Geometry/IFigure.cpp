#include <unordered_map>

#include <IFigure.h>

namespace
{
std::unordered_map<size_t, std::function<std::shared_ptr<IFigure>(const InputStream &)>> types;
}


//
std::shared_ptr<IFigure> IFigure::Read(size_t hash)
{
  auto it = types.find(hash);

  if (it != types.end())
  {
    return it->second()
  }
}

//
bool IFigure::RegisterType(size_t hash, std::function<std::shared_ptr<IFigure>(const InputStream&)> read)
{
  types.insert({hash, read});

  return true;
}
