#include <unordered_map>

#include <InputStream.h>
#include <IFigure.h>


namespace
{
std::unordered_map<size_t, std::function<std::shared_ptr<IFigure>(const InputStream &)>> registeredTypes;
}


//------------------------------------------------------------------------------
/**
  \brief Читает данные из потока и на основе их создает фигуру
  \details Сначала метод пытается интерпретировать первые данные как хэш.
           После этого он ищет по данному хэшу зарегестрированный тип.
           Если тип зарегестрирован то вызывает его метод Read.
           В ином случае возвращает nullptr
*/
std::shared_ptr<IFigure> IFigure::Read(const InputStream& is)
{
  size_t hash;
  if (!is.Read(hash))
    return nullptr;

  auto it = registeredTypes.find(hash);

  if (it != registeredTypes.end())
  {
    return it->second(is);
  }

  return nullptr;

}

//------------------------------------------------------------------------------
/**
  Регистрирует тип фигуры по хэшу
*/
//---
bool IFigure::RegisterType(size_t hash, std::function<std::shared_ptr<IFigure>(const InputStream&)> read)
{
  auto result = registeredTypes.emplace(hash, read);

  return result.second;
}
