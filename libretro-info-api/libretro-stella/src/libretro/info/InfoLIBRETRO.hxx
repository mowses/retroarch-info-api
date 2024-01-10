
#include <cstdlib>
#include <sstream>
#include "OSystem.hxx"
#include "./commands/current_score/stella.h"
#include "./commands/retro_api_version/common.h"
#include "./commands/unknown_command/common.h"
#include "./server/Server.cxx"

bool on_bind(string message) { printf("[INFO-API] socket bound\n"); return true; }
bool on_connect(string message) { printf("[INFO-API] socket connected\n"); return true; }
bool on_error(string message) { printf("[INFO-API] socket error: %s\n", message.c_str()); return true; }
bool on_message(string message) { printf("[INFO-API] socket message: %s\n", message.c_str()); return true; }

class InfoLIBRETRO
{
  public:
    InfoLIBRETRO();
    
    void retroRun();
    void setOSystem(OSystem& system);

  private:
    void init()
    {
      char const* unixfile = getenv("INFO_API_UNIX_FILE");
      
      if (unixfile != NULL) {
        server.setPath((string)unixfile);
      }
      
      server
        .unlink()
        .on("bind", &on_bind)
        .on("connect", &on_connect)
        .on("error", &on_error)
        .on("message", &on_message)
        .connect()
        .bind();

      cout << "[INFO-API] INFO API is available to be connected at: " << server.getPath() << endl;
    };
    
    OSystem *myOSystem;
    UnixSocketServer server;
};