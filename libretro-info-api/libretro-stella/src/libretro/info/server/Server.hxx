// sources:
// https://www.linuxhowtos.org/C_C++/socket.htm
// https://www.ibm.com/docs/en/i/7.2?topic=designs-example-nonblocking-io-select

#include <algorithm>
#include <ctime>
#include <errno.h>
#include <functional>
#include <iostream>
#include <sstream>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>

using namespace std;

inline int sock_errno()  { return errno; }

inline string trim(const string &s)
{
    auto wsfront = std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
    auto wsback = std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
    return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

class UnixSocketServer
{
    public:
        int write(int client, string message);
        string getPath();
        string read(int client);
        UnixSocketServer& accept();
        UnixSocketServer& bind();
        UnixSocketServer& close();
        UnixSocketServer& disconnect(int client);
        UnixSocketServer& connect();
        UnixSocketServer& on(string event_name, std::function<bool(string message)> lambda);
        UnixSocketServer& prune();
        UnixSocketServer& setPath(string newpath);
        UnixSocketServer& unlink();
        UnixSocketServer();
        UnixSocketServer(string path);
        vector<int> clients;

        bool isDisconnected(int client)
        {
            char buffer[1];
            int rc = ::recv(client, buffer, 1, MSG_PEEK);
            return rc == 0;
        }

    private:
        string path;
        vector<std::function<bool(string message)>> callbacks;
        vector<string> events;
        struct sockaddr_un sockaddr;

        int sock = 0;
        uint len;
        char buffer[256];
        
        void trigger_event(string event, string message) {
            for(std::size_t i = 0; i < events.size(); ++i) {
                if (events[i] != event) continue;
                bool ret = callbacks[i](message);
                
                if (ret == false) break;
            }
        };
};