
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
  string message;
  int client;

  server.accept();
  // server.prune();
  
  // cout << server.getPath() << " has " << server.clients.size() << " clients." << endl;

  for (int i = 0, t = server.clients.size(); i < t; i++) {
    client = server.clients[i];

    std::istringstream command(server.read(client));
    
    while(std::getline(command, message, '\n')) {
      if (message == "") continue;

      cout << "[INFO-API] Client " << client << " requested: " << message << endl;

      if (message == "current_score") {
        server.write(client, to_string(info_current_score(*myOSystem)));
      } else if (message == "retro_api_version") {
        server.write(client, to_string(info_retro_api_version()));
      } else {
        cout << "[INFO-API] Client " << client << " wrote unknown command: " << message << endl;
      }
    }
  }
}