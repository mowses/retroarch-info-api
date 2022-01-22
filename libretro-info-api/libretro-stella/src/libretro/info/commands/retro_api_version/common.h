#include "OSystem.hxx"

json retro_api_version(OSystem& osystem)
{
  json response = json::object();
  
  response["version"] = ::retro_api_version();

  return response;
}