
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
    /**
     * @todo should read() until line break
     * otherwise will receive a unrecognizable command block
     * ex: current_score\ncurrent_score\ncurrent_score
     * will result in *unknown command*
     */
    message = server.read(client);
    if (message == "") continue;

    cout << "[INFO-API] Client " << client << " requested: " << message << endl;

    if (message == "current_score") {
      server.write(client, to_string(current_score(*myOSystem)));
    } else if (message == "retro_api_version") {
      server.write(client, to_string(retro_api_version()));
    }  else if (message == "retro_get_region") {
      server.write(client, to_string(retro_get_region()));
    } else {
      cout << "[INFO-API] Client " << client << " wrote unknown command: " << message << endl;
    }
  }
}