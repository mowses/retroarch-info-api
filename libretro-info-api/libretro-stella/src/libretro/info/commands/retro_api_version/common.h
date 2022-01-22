
json info_retro_api_version()
{
  json response = json::object();
  
  response["version"] = retro_api_version();

  return response;
}