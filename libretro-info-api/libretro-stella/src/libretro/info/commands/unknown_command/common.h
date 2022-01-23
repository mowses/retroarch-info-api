
json info_unknown_command()
{
  json response = json::object();
  
  response["message"] = "Unknown command.";

  return response;
}