
#include "OSystem.hxx"
#include "./scores/stella.h"
#include "./server/Server.cxx"

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
        //.setPath("/home/unknown/Downloads/server.sock")  // todo
        .unlink()
        .on("bind", &on_bind)
        .on("connect", &on_connect)
        .on("error", &on_error)
        .on("message", &on_message)
        .connect()
        .bind();

      cout << "INFO API is available to be connected at: " << server.getPath() << endl;
    };
    
    OSystem *myOSystem;
    UnixSocketServer server;
};