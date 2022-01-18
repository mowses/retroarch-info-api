
#include "OSystem.hxx"
#include "./scores/stella.h"
#include "/var/www/html/bettina/shared-lib/src/Resources/c++/unixsocket-server-client/Server.cxx"

bool on_bind(string message) { printf("on bind: %s\n", message.c_str()); return true; }
bool on_connect(string message) { printf("on connect: %s\n", message.c_str()); return true; }
bool on_error(string message) { printf("on error: %s\n", message.c_str()); return true; }
bool on_message(string message) { printf("on message: %s\n", message.c_str()); return true; }

class InfoLIBRETRO
{
  public:
    InfoLIBRETRO();
    
    json currentScore() {
      return current_score(*myOSystem);
    }

    void retroRun();
    void setOSystem(OSystem& system);

  private:
    void init()
    {
      server
        .setPath("/home/unknown/Downloads/server.sock")
        .unlink()
        .on("bind", &on_bind)
        .on("connect", &on_connect)
        .on("error", &on_error)
        .on("message", &on_message)
        .connect()
        .bind();
    };
    
    OSystem *myOSystem;
    UnixSocketServer server;
};