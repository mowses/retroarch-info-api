
#include "InfoLIBRETRO.hxx"

InfoLIBRETRO::InfoLIBRETRO()
{
  init();
}

void InfoLIBRETRO::setOSystem(OSystem& system)
{
  myOSystem = &system;
}

void InfoLIBRETRO::retroRun()
{
  string request;
  json response;
  int client;

  server.accept();
  // server.prune();
  
  // cout << server.getPath() << " has " << server.clients.size() << " clients." << endl;

  for (int i = 0, t = server.clients.size(); i < t; i++) {
    client = server.clients[i];

    std::istringstream command(server.read(client));
    
    while(std::getline(command, request, '\n')) {
      if (request == "") continue;
      response = nullptr;

      cout << "[INFO-API] Client " << client << " requested: " << request << endl;

      if (request == "current_score") {
        response = info_current_score(*myOSystem);
      } else if (request == "retro_api_version") {
        response = info_retro_api_version();
      } else {
        cout << "[INFO-API] Client " << client << " wrote unknown command: " << request << endl;
        continue;
      }

      server.write(client, request + ":" + to_string(response) + '\0' + "\n");
    }
  }
}