
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
    message = server.read(client);
    if (message == "") continue;

    // server.write(server.clients[i], "\nThanks for your feedback. It was " + to_string(message.size()) + " chars in length.\n");
    
    if (message == "current_score") {
        server.write(client, to_string(currentScore()));
      } else {
        cout << "Client " << client << " wrote unknown command: " << message << endl;
      }
  }
}