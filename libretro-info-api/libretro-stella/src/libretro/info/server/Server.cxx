// sources:
// https://www.linuxhowtos.org/C_C++/socket.htm
// https://www.ibm.com/docs/en/i/7.2?topic=designs-example-nonblocking-io-select

#include "Server.hxx"

using namespace std;

#define BACKLOG 10     /* how many pending connections queue will hold */

UnixSocketServer::UnixSocketServer(string path)
    : path{path}
{
}

UnixSocketServer::UnixSocketServer()
{
    path = string("/tmp/server-" + to_string(time(nullptr)));
}

string UnixSocketServer::getPath()
{
    return path;
}

UnixSocketServer& UnixSocketServer::unlink()
{
    remove(path.c_str());

    return *this;
}

UnixSocketServer& UnixSocketServer::setPath(string newpath)
{
    path = newpath;

    return *this;
}

/**
 * Available events:
 * accept
 * bind
 * close
 * connect
 * disconnect
 * error
 * message
 * 
 * Usage ex: sock.on('connect', function_name)
 *
 * ex: define this inside your main():
 * auto cbmes = [&](string message)  // lambda
    {
        ...  // can access main() variables
    };
 */
UnixSocketServer& UnixSocketServer::on(string event_name, std::function<bool(string message)> lambda)
{
    // @todo use structs
    events.push_back(event_name);
    callbacks.push_back(lambda);

    return *this;
}

UnixSocketServer& UnixSocketServer::connect()
{
    if (sock) return *this;  // already created
    memset(&sockaddr, 0, sizeof(struct sockaddr_un));

    /****************************************/
    /* Create a UNIX domain STREAM SOCKET   */
    /****************************************/
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        trigger_event("error", "SOCKET CONNECTION ERROR = " + to_string(sock_errno()));
        return *this;
    }

    /***************************************/
    /* Set up the UNIX sockaddr structure  */
    /* by using AF_UNIX for the family and */
    /* giving it a filepath to bind to.    */
    /***************************************/
    bzero((char *) &sockaddr, sizeof(sockaddr));
    sockaddr.sun_family = AF_UNIX;
    strcpy(sockaddr.sun_path, path.c_str());
    len = sizeof(sockaddr);

    /*******************************************/
    /* Allow socket descriptor to be reuseable */
    /*******************************************/
    int on = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

    /*************************************************/
    /* Set socket to be nonblocking.                 */
    /* Set the socket I/O mode: In this case FIONBIO */
    /* enables or disables the blocking mode for the */
    /* socket based on the numerical value of iMode. */
    /* If iMode = 0, blocking is enabled;            */
    /* If iMode != 0, non-blocking mode is enabled.  */
    /*************************************************/
    ioctl(sock, FIONBIO, (char *)&on);

    trigger_event("connect", "");

    return *this;
}

UnixSocketServer& UnixSocketServer::close()
{
    // disconnect all clients
    for (int i = 0, t = clients.size(); i < t; i++){
        disconnect(clients[i]);
    }

    ::close(sock);

    trigger_event("close", "");

    return *this;
}

UnixSocketServer& UnixSocketServer::disconnect(int client)
{
    ::close(client);
    clients.erase(remove(clients.begin(), clients.end(), client), clients.end());
    
    trigger_event("disconnect", to_string(client));

    return *this;
}

UnixSocketServer& UnixSocketServer::bind()
{
    int rc = ::bind(sock, (struct sockaddr *) &sockaddr, len);
    if (rc < 0) {
        trigger_event("error", "BIND ERROR = " + to_string(sock_errno()));
        close();
        return *this;
    }

    ::listen(sock, BACKLOG);

    trigger_event("bind", "");

    return *this;
}

UnixSocketServer& UnixSocketServer::accept()
{
    struct sockaddr_un client_addr;

    socklen_t clilen = sizeof(client_addr);
    int newsockfd = ::accept(sock, (struct sockaddr *) &client_addr, &clilen);
    
    if (newsockfd < 0) {
        if (sock_errno() == EAGAIN) return *this;

        trigger_event("error", "ACCEPT ERROR = " + to_string(sock_errno()));
        return *this;
    }

    clients.push_back(newsockfd);
    int on = 1;
    ioctl(newsockfd, FIONBIO, (char *)&on);

    trigger_event("accept", to_string(newsockfd));

    return *this;
}

string UnixSocketServer::read(int client)
{
    bzero(buffer, 256);
    int bytes = ::read(client, buffer, 255);
    
    if (bytes < 0) {
        if (sock_errno() == EAGAIN) return "";

        trigger_event("error", "READ ERROR = " + to_string(sock_errno()));
        return "";
    }

    return ::trim(string(buffer));
}

int UnixSocketServer::write(int client, string message)
{
    int bytes = ::write(client, message.c_str(), message.length());
    if (bytes < 0) {
        trigger_event("error", "WRITE ERROR = " + to_string(sock_errno()));
        return bytes;
    }

    return bytes;
}

UnixSocketServer& UnixSocketServer::prune()
{
    for (int i = 0, t = clients.size(); i < t; i++){
        if (isDisconnected(clients[i])) {
            disconnect(clients[i]);
        }
    }

    return *this;
}