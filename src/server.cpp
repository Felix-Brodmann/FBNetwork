#include "../include/server.hpp"

void FBNetwork::Server::setServerFileDescriptor(const fileDescriptor t_serverFileDescriptor)
{
    std::unique_lock<std::shared_mutex> lock(m_serverFileDescriptorMutex);
    if (t_serverFileDescriptor == -1)
    {
        throw InvalidArgumentException("Server File descriptor can not be -1.");
    }
    m_serverFileDescriptor = t_serverFileDescriptor;
}

void FBNetwork::Server::setUsesIpv4Domain(const bool t_usesIpv4Domain)
{
    std::unique_lock<std::shared_mutex> lock(m_usesIpv4DomainMutex);
    m_usesIpv4Domain = t_usesIpv4Domain;
}

void FBNetwork::Server::setUsesIpv6Domain(const bool t_usesIpv6Domain)
{
    std::unique_lock<std::shared_mutex> lock(m_usesIpv6DomainMutex);
    m_usesIpv6Domain = t_usesIpv6Domain;
}

void FBNetwork::Server::setUsesLocalDomain(const bool t_usesLocalDomain)
{
    std::unique_lock<std::shared_mutex> lock(m_usesLocalDomainMutex);
    m_usesLocalDomain = t_usesLocalDomain;
}

void FBNetwork::Server::setIsServerOnline(const bool t_isServerOnline)
{
    std::unique_lock<std::shared_mutex> lock(m_isServerOnlineMutex);
    m_isServerOnline = t_isServerOnline;
}

void FBNetwork::Server::setLocalServerSocketPath(const std::string &t_localServerSocketPath)
{
    std::unique_lock<std::shared_mutex> lock(m_localServerSocketPathMutex);
    if (t_localServerSocketPath.empty())
    {
        throw InvalidArgumentException("Invalid local server socket path.");
    }
    if (t_localServerSocketPath.size() > 104)
    {
        throw InvalidArgumentException("Local server socket path is too long.");
    }
    m_localServerSocketPath = t_localServerSocketPath;
}

void FBNetwork::Server::setDomain(const domain t_domain)
{
    std::unique_lock<std::shared_mutex> lock(m_domainMutex);
    if (t_domain != Domain::IPV4_DOMAIN && t_domain != Domain::IPV6_DOMAIN && t_domain != Domain::LOCAL_DOMAIN)
    {
        throw InvalidDomainException("Must be either IPV4_DOMAIN, IPV6_DOMAIN or LOCAL_DOMAIN.");
    }
    m_domain = t_domain;
}

void FBNetwork::Server::setPort(const port t_port)
{
    std::unique_lock<std::shared_mutex> lock(m_portMutex);
    if (t_port < 0 || t_port > 65535)
    {
        throw InvalidArgumentException("Invalid port.");
    }
    m_port = t_port;
}

void FBNetwork::Server::setMaximumCurrentConnections(const int t_maximumCurrentConnections)
{
    std::unique_lock<std::shared_mutex> lock(m_maximumCurrentConnectionsMutex);
    if (t_maximumCurrentConnections <= 0)
    {
        throw InvalidArgumentException("Maximum current connections must be greater than 0.");
    }
    m_maximumCurrentConnections = t_maximumCurrentConnections;
}

void FBNetwork::Server::setStartTime(const time_t t_startTime)
{
    std::unique_lock<std::shared_mutex> lock(m_startTimeMutex);
    if (t_startTime < 0)
    {
        throw InvalidArgumentException("Start time cannot be negative.");
    }
    m_startTime = t_startTime;
}

void FBNetwork::Server::setServerAddressIpv4(std::shared_ptr<sockaddr_in> t_serverAddressIpv4)
{
    std::unique_lock<std::shared_mutex> lock(m_serverAddressIpv4Mutex);
    if (t_serverAddressIpv4 == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressIpv4 = t_serverAddressIpv4;
}

void FBNetwork::Server::setServerAddressIpv6(std::shared_ptr<sockaddr_in6> t_serverAddressIpv6)
{
    std::unique_lock<std::shared_mutex> lock(m_serverAddressIpv6Mutex);
    if (t_serverAddressIpv6 == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressIpv6 = t_serverAddressIpv6;
}

void FBNetwork::Server::setServerAddressLocal(std::shared_ptr<sockaddr_un> t_serverAddressLocal)
{
    std::unique_lock<std::shared_mutex> lock(m_serverAddressLocalMutex);
    if (t_serverAddressLocal == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressLocal = t_serverAddressLocal;
}

void FBNetwork::Server::setEventQueue(std::shared_ptr<EventQueue> t_eventQueue)
{
    std::unique_lock<std::shared_mutex> lock(m_eventQueueMutex);
    if (t_eventQueue == nullptr)
    {
        throw InvalidArgumentException("Event queue cannot be nullptr.");
    }
    m_eventQueue = t_eventQueue;
}

void FBNetwork::Server::setData(const int t_clientID, const std::string &t_data)
{
    std::unique_lock<std::shared_mutex> lock(m_dataMutex);
    m_data[t_clientID] = t_data;
}

void FBNetwork::Server::setStartDate(const std::string &t_startDate)
{
    std::unique_lock<std::shared_mutex> lock(m_startDateMutex);
    if (t_startDate.empty())
    {
        throw InvalidArgumentException("Start date cannot be empty.");
    }
    m_startDate = t_startDate;
}

void FBNetwork::Server::setClientFileDescriptor(const int t_clientID, const fileDescriptor t_clientFileDescriptor)
{
    std::unique_lock<std::shared_mutex> lock(m_clientFileDescriptorMutex);
    m_clientFileDescriptor[t_clientID] = t_clientFileDescriptor;
}

void FBNetwork::Server::setClientAddressIpv4(const int t_clientID, std::shared_ptr<sockaddr_in> t_clientAddressIpv4)
{
    std::unique_lock<std::shared_mutex> lock(m_clientAddressIpv4Mutex);
    if (t_clientAddressIpv4 == nullptr)
    {
        throw InvalidArgumentException("Invalid client address.");
    }
    m_clientAddressIpv4[t_clientID] = t_clientAddressIpv4;
}

void FBNetwork::Server::setClientAddressIpv6(const int t_clientID, std::shared_ptr<sockaddr_in6> t_clientAddressIpv6)
{
    std::unique_lock<std::shared_mutex> lock(m_clientAddressIpv6Mutex);
    if (t_clientAddressIpv6 == nullptr)
    {
        throw InvalidArgumentException("Invalid client address.");
    }
    m_clientAddressIpv6[t_clientID] = t_clientAddressIpv6;
}

void FBNetwork::Server::setClientAddressLocal(const int t_clientID, std::shared_ptr<sockaddr_un> t_clientAddressLocal)
{
    std::unique_lock<std::shared_mutex> lock(m_clientAddressLocalMutex);
    if (t_clientAddressLocal == nullptr)
    {
        throw InvalidArgumentException("Invalid client address.");
    }
    m_clientAddressLocal[t_clientID] = t_clientAddressLocal;
}

void FBNetwork::Server::setCurrentClientID(const int t_currentClientID)
{
    std::unique_lock<std::shared_mutex> lock(m_currentClientIDMutex);
    if (t_currentClientID < 0)
    {
        throw InvalidArgumentException("Current client ID cannot be negative.");
    }
    m_currentClientID = t_currentClientID;
}

FBNetwork::fileDescriptor FBNetwork::Server::getServerFileDescriptor() const
{
    std::shared_lock<std::shared_mutex> lock(m_serverFileDescriptorMutex);
    return m_serverFileDescriptor;
}

bool FBNetwork::Server::usesIpv4Domain() const
{
    std::shared_lock<std::shared_mutex> lock(m_usesIpv4DomainMutex);
    return m_usesIpv4Domain;
}

bool FBNetwork::Server::usesIpv6Domain() const
{
    std::shared_lock<std::shared_mutex> lock(m_usesIpv6DomainMutex);
    return m_usesIpv6Domain;
}

bool FBNetwork::Server::usesLocalDomain() const
{
    std::shared_lock<std::shared_mutex> lock(m_usesLocalDomainMutex);
    return m_usesLocalDomain;
}

std::string FBNetwork::Server::getLocalServerSocketPath() const
{
    std::shared_lock<std::shared_mutex> lock(m_localServerSocketPathMutex);
    return m_localServerSocketPath;
}

FBNetwork::domain FBNetwork::Server::getDomain() const
{
    std::shared_lock<std::shared_mutex> lock(m_domainMutex);
    return m_domain;
}

int FBNetwork::Server::getMaximumCurrentConnections() const
{
    std::shared_lock<std::shared_mutex> lock(m_maximumCurrentConnectionsMutex);
    return m_maximumCurrentConnections;
}

time_t FBNetwork::Server::getStartTime() const
{
    std::shared_lock<std::shared_mutex> lock(m_startTimeMutex);
    return m_startTime;
}

std::shared_ptr<sockaddr_in> FBNetwork::Server::getServerAddressIpv4()
{
    std::shared_lock<std::shared_mutex> lock(m_serverAddressIpv4Mutex);
    return m_serverAddressIpv4;
}

std::shared_ptr<sockaddr_in6> FBNetwork::Server::getServerAddressIpv6()
{
    std::shared_lock<std::shared_mutex> lock(m_serverAddressIpv6Mutex);
    return m_serverAddressIpv6;
}

std::shared_ptr<sockaddr_un> FBNetwork::Server::getServerAddressLocal()
{
    std::shared_lock<std::shared_mutex> lock(m_serverAddressLocalMutex);
    return m_serverAddressLocal;
}

std::shared_ptr<FBNetwork::EventQueue> FBNetwork::Server::getEventQueue()
{
    std::shared_lock<std::shared_mutex> lock(m_eventQueueMutex);
    return m_eventQueue;
}

FBNetwork::fileDescriptor FBNetwork::Server::getClientFileDescriptor(const int t_clientID) const
{
    std::shared_lock<std::shared_mutex> lock(m_clientFileDescriptorMutex);
    if (thisClientDoesNotExist(t_clientID))
    {
        throw std::out_of_range("Client ID not found.");
    }
    return m_clientFileDescriptor.at(t_clientID);
}

int FBNetwork::Server::getClientID(const fileDescriptor t_clientFileDescriptor)
{
    if (t_clientFileDescriptor < 0)
    {
        throw InvalidArgumentException("Invalid client file descriptor.");
    }
    std::shared_lock<std::shared_mutex> lock(m_clientFileDescriptorMutex);
    for (auto const &client : m_clientFileDescriptor)
    {
        if (client.second == t_clientFileDescriptor)
        {
            return client.first;
        }
    }
    throw std::out_of_range("Client file descriptor not found.");
}

std::shared_ptr<sockaddr_in> FBNetwork::Server::getClientAddressIpv4(const int t_clientID)
{
    std::shared_lock<std::shared_mutex> lock(m_clientAddressIpv4Mutex);
    if (thisClientDoesNotExist(t_clientID))
    {
        throw std::out_of_range("Client ID not found.");
    }
    return m_clientAddressIpv4.at(t_clientID);
}

std::shared_ptr<sockaddr_in6> FBNetwork::Server::getClientAddressIpv6(const int t_clientID)
{
    std::shared_lock<std::shared_mutex> lock(m_clientAddressIpv6Mutex);
    if (thisClientDoesNotExist(t_clientID))
    {
        throw std::out_of_range("Client ID not found.");
    }
    return m_clientAddressIpv6.at(t_clientID);
}

std::shared_ptr<sockaddr_un> FBNetwork::Server::getClientAddressLocal(const int t_clientID)
{
    std::shared_lock<std::shared_mutex> lock(m_clientAddressLocalMutex);
    if (thisClientDoesNotExist(t_clientID))
    {
        throw std::out_of_range("Client ID not found.");
    }
    return m_clientAddressLocal.at(t_clientID);
}

int FBNetwork::Server::getCurrentClientID() const
{
    std::shared_lock<std::shared_mutex> lock(m_currentClientIDMutex);
    return m_currentClientID;
}

timeval FBNetwork::Server::getTimeout()
{
    return m_timeout;
}

void FBNetwork::Server::rearrangeClientIDs()
{
    closeDisconnectedClients();
    int nextFreeIndex = 0;
    for (int i = 0; i < getCurrentClientID(); i++)
    {
        if (getClientFileDescriptor(i) != -1)
        {
            if (i != nextFreeIndex)
            {
                setClientFileDescriptor(nextFreeIndex, getClientFileDescriptor(i));
                if (usesIpv4Domain())
                {
                    setClientAddressIpv4(nextFreeIndex, getClientAddressIpv4(i));
                }
                else if (usesIpv6Domain())
                {
                    setClientAddressIpv6(nextFreeIndex, getClientAddressIpv6(i));
                }
                else if (usesLocalDomain())
                {
                    setClientAddressLocal(nextFreeIndex, getClientAddressLocal(i));
                }
            }
            nextFreeIndex++;
        }
    }
    setCurrentClientID(nextFreeIndex);
}

bool FBNetwork::Server::thisClientDoesNotExist(const int t_clientID) const
{
    return t_clientID > getCurrentClientID();
}

bool FBNetwork::Server::isServerOnline()
{
    std::shared_lock<std::shared_mutex> lock(m_isServerOnlineMutex);
    return m_isServerOnline;
}

FBNetwork::port FBNetwork::Server::getPort()
{
    std::shared_lock<std::shared_mutex> lock(m_portMutex);
    return m_port;
}

std::string FBNetwork::Server::getData(const int t_clientID)
{
    std::shared_lock<std::shared_mutex> lock(m_dataMutex);

    return m_data.at(t_clientID);
}

std::string FBNetwork::Server::getStartDate()
{
    std::shared_lock<std::shared_mutex> lock(m_startDateMutex);
    return m_startDate;
}

time_t FBNetwork::Server::getLifeTime()
{
    std::shared_lock<std::shared_mutex> lock(m_lifeTimeMutex);
    return time(0) - getStartTime();
}

std::string FBNetwork::Server::getClientIpAddress(const int t_clientID)
{
    std::shared_lock<std::shared_mutex> lock(m_clientIpAddressMutex);
    char                                ip[INET_ADDRSTRLEN];
    char                                ip6[INET6_ADDRSTRLEN];
    if (usesIpv4Domain() == true)
    {
        if (inet_ntop(AF_INET, &getClientAddressIpv4(t_clientID)->sin_addr, ip, sizeof(ip)) == nullptr)
        {
            throw ServerRuntimeException("Failed to convert IPv4 address to string. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        return std::string(ip);
    }
    else if (usesIpv6Domain() == true)
    {
        if (inet_ntop(AF_INET6, &getClientAddressIpv6(t_clientID)->sin6_addr, ip6, sizeof(ip6)) == nullptr)
        {
            throw ServerRuntimeException("Failed to convert IPv6 address to string. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        return std::string(ip6);
    }
    else if (usesLocalDomain() == true)
    {
        return "localhost";
    }
    else
    {
        throw InvalidDomainException("You try to get the IP address of an invalid domain.");
    }
}

int FBNetwork::Server::getCurrentlyConnectedClientsCount()
{
    std::shared_lock<std::shared_mutex> lock(m_clientsCountMutex);
    int                                 count = 0;
    for (int i = 0; i < getCurrentClientID(); i++)
    {
        if (!isDisconnected(i))
        {
            count++;
        }
    }
    return count;
}

FBNetwork::Server::Server(const int t_domain, const port t_port, const int t_maximumCurrentConnections)
{
    try
    {
        setDomain(t_domain);
        setPort(t_port);
        setMaximumCurrentConnections(t_maximumCurrentConnections);
    }
    catch (InvalidArgumentException &e)
    {
        throw e;
    }
    if (getDomain() == Domain::IPV4_DOMAIN)
    {
        setUsesIpv4Domain(true);
        setUsesIpv6Domain(false);
        setUsesLocalDomain(false);
    }
    else if (getDomain() == Domain::IPV6_DOMAIN)
    {
        setUsesIpv4Domain(false);
        setUsesIpv6Domain(true);
        setUsesLocalDomain(false);
    }
    else
    {
        throw InvalidDomainException("Please use either IPv4 or IPv6.");
    }
    setTimeout(FBNetwork::Constants::DEFAULT_TIMEOUT);
}

FBNetwork::Server::Server(std::string &t_socketPath, const port t_port, const int t_maximumCurrentConnections)
{
    setDomain(Domain::LOCAL_DOMAIN);
    try
    {
        setLocalServerSocketPath(t_socketPath);
        setPort(t_port);
        setMaximumCurrentConnections(t_maximumCurrentConnections);
    }
    catch (InvalidArgumentException &e)
    {
        throw e;
    }
    setUsesIpv4Domain(false);
    setUsesIpv6Domain(false);
    setUsesLocalDomain(true);
    setTimeout(FBNetwork::Constants::DEFAULT_TIMEOUT);
}

FBNetwork::Server::~Server()
{
    stopServer();
}

void FBNetwork::Server::startServer()
{
    try
    {
        setServerFileDescriptor(socket(getDomain(), SOCK_STREAM, 0));
    }
    catch (InvalidArgumentException &e)
    {
        throw ServerCreationException("Creating the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }

    int opt = 1;
    if (setsockopt(getServerFileDescriptor(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        close(getServerFileDescriptor());
        throw ServerCreationException("Setting socket options failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    if (usesIpv4Domain())
    {
        std::shared_ptr<sockaddr_in> serverAddressIpv4 = std::make_shared<sockaddr_in>();
        *serverAddressIpv4                             = {};
        serverAddressIpv4->sin_family                  = getDomain();
        serverAddressIpv4->sin_addr.s_addr             = INADDR_ANY;
        serverAddressIpv4->sin_port                    = htons(getPort());
        if (bind(getServerFileDescriptor(), reinterpret_cast<sockaddr *>(serverAddressIpv4.get()), sizeof(sockaddr_in)) == -1)
        {
            close(getServerFileDescriptor());
            throw ServerCreationException("Binding the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }

        // Do not catch InvalidArgumentException here, because it is not possible to throw it. See that we have already checked if
        // serverAddressIpv4 is nullptr.

        setServerAddressIpv4(serverAddressIpv4);
    }
    else if (usesIpv6Domain())
    {
        std::shared_ptr<sockaddr_in6> serverAddressIpv6 = std::make_shared<sockaddr_in6>();
        *serverAddressIpv6                              = {};
        serverAddressIpv6->sin6_family                  = getDomain();
        serverAddressIpv6->sin6_addr                    = in6addr_any;
        serverAddressIpv6->sin6_port                    = htons(getPort());
        if (bind(getServerFileDescriptor(), reinterpret_cast<sockaddr *>(serverAddressIpv6.get()), sizeof(sockaddr_in6)) == -1)
        {
            close(getServerFileDescriptor());
            throw ServerCreationException("Binding the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }

        // Do not catch InvalidArgumentException here, because it is not possible to throw it. See that we have already checked if
        // serverAddressIpv6 is nullptr.

        setServerAddressIpv6(serverAddressIpv6);
    }
    else if (usesLocalDomain())
    {
        std::shared_ptr<sockaddr_un> serverAddressLocal = std::make_shared<sockaddr_un>();
        *serverAddressLocal                             = {};
        serverAddressLocal->sun_family                  = getDomain();
        strncpy(serverAddressLocal->sun_path, getLocalServerSocketPath().c_str(), sizeof(getLocalServerSocketPath()));
        if (unlink(getLocalServerSocketPath().c_str()) == -1 && errno != ENOENT)
        {
            throw ServerCreationException("Removing the existing socket file failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        if (bind(getServerFileDescriptor(), reinterpret_cast<sockaddr *>(serverAddressLocal.get()), sizeof(sockaddr_un)) == -1)
        {
            throw ServerCreationException("Binding the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }

        // Do not catch InvalidArgumentException here, because it is not possible to throw it. See that we have already checked if
        // serverAddressLocal is nullptr.

        setServerAddressLocal(serverAddressLocal);
    }
    try
    {
        std::shared_ptr<EventQueue> eventQueue = std::make_shared<EventQueue>();
        eventQueue->setServer(getServerFileDescriptor());
        setEventQueue(eventQueue);
    }
    catch (ServerRuntimeException &e)
    {
        throw ServerCreationException(e.what());
    }

    setIsServerOnline(true);
    setStartTime(time(0));
    setStartDate(ExtendedSystem::getCurrentDate() + " " + ExtendedSystem::getCurrentTime());
}

void FBNetwork::Server::startListening()
{
    if (listen(getServerFileDescriptor(), getMaximumCurrentConnections()) == -1)
    {
        throw ServerRuntimeException("Listening on the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::Server::stopServer()
{
    try
    {
        for (int i = 0; i < getCurrentClientID(); i++)
        {
            if (!isDisconnected(i))
            {
                close(getClientFileDescriptor(i));
            }
        }
    }
    catch (ServerRuntimeException &e)
    {
        throw e;
    }
    if (close(getServerFileDescriptor()) == -1)
    {
        throw ServerRuntimeException("Closing the server socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    setIsServerOnline(false);
    setStartTime(0);
}

void FBNetwork::Server::setServerKeepAlive(const bool t_keepAlive)
{
    int keepAlive = t_keepAlive ? 1 : 0;
    if (setsockopt(getServerFileDescriptor(), SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(keepAlive)) == -1)
    {
        throw ServerRuntimeException("Setting the keep alive option failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

int FBNetwork::Server::acceptClient()
{
    rearrangeClientIDs();
    int currentClientID = getCurrentClientID();
    if (currentClientID >= getMaximumCurrentConnections())
    {
        throw ServerRuntimeException("Maximum number of current connections reached.");
    }
    int serverFileDescriptor = getServerFileDescriptor();
    if (usesIpv4Domain() == true)
    {
        try
        {
            socklen_t                    clientAddressLength = sizeof(sockaddr_in);
            std::shared_ptr<sockaddr_in> clientAddressIpv4   = std::make_shared<sockaddr_in>();
            *clientAddressIpv4                               = {};
            int clientFileDescriptor =
                accept(serverFileDescriptor, reinterpret_cast<sockaddr *>(clientAddressIpv4.get()), &clientAddressLength);
            setClientFileDescriptor(currentClientID, clientFileDescriptor);
            setClientAddressIpv4(currentClientID, clientAddressIpv4);
        }
        catch (InvalidArgumentException &e)
        {

            // The accept function failed.

            throw ServerRuntimeException("Accepting the client failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
    }
    else if (usesIpv6Domain() == true)
    {
        try
        {
            socklen_t                     clientAddressLength = sizeof(sockaddr_in6);
            std::shared_ptr<sockaddr_in6> clientAddressIpv6   = std::make_shared<sockaddr_in6>();
            *clientAddressIpv6                                = {};
            int clientFileDescriptor =
                accept(serverFileDescriptor, reinterpret_cast<sockaddr *>(clientAddressIpv6.get()), &clientAddressLength);
            setClientFileDescriptor(currentClientID, clientFileDescriptor);
            setClientAddressIpv6(currentClientID, clientAddressIpv6);
        }
        catch (InvalidArgumentException &e)
        {

            // The accept function failed.

            throw ServerRuntimeException("Accepting the client failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
    }
    else if (usesLocalDomain() == true)
    {
        try
        {
            socklen_t                    clientAddressLength = sizeof(sockaddr_un);
            std::shared_ptr<sockaddr_un> clientAddressLocal  = std::make_shared<sockaddr_un>();
            *clientAddressLocal                              = {};
            int clientFileDescriptor =
                accept(serverFileDescriptor, reinterpret_cast<sockaddr *>(clientAddressLocal.get()), &clientAddressLength);
            setClientFileDescriptor(currentClientID, clientFileDescriptor);
            setClientAddressLocal(currentClientID, clientAddressLocal);
        }
        catch (InvalidArgumentException &e)
        {

            // The accept function failed.

            throw ServerRuntimeException("Accepting the client failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
    }
    try
    {
        getEventQueue()->addClient(getClientFileDescriptor(currentClientID));
    }
    catch (ServerRuntimeException &e)
    {
        throw ServerRuntimeException("Setting the server file descriptor for the event queue failed.");
    }
    setCurrentClientID(currentClientID + 1);
    return currentClientID;
}

void FBNetwork::Server::closeDisconnectedClients()
{
    for (int i = 0; i < getCurrentClientID(); i++)
    {
        if (isDisconnected(i))
        {
            try
            {
                getEventQueue()->removeClient(getClientFileDescriptor(i));
            }
            catch (InvalidArgumentException &e)
            {
            }
            catch (ServerRuntimeException &e)
            {
            }
            int result = close(getClientFileDescriptor(i));
            setClientFileDescriptor(i, -1);
        }
    }
}

void FBNetwork::Server::sendData(const int t_clientID, const std::string &t_data)
{
    if (t_data.empty())
    {
        throw InvalidArgumentException("Data to send cannot be empty.");
    }
    if (write(getClientFileDescriptor(t_clientID), t_data.c_str(), t_data.length()) == -1)
    {
        throw ServerRuntimeException("Writing the data failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::Server::readXData(const int t_clientID, const ssize_t t_x)
{
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        totalBytesRead                 = 0;
    ssize_t        bytesRead                      = 0;
    ssize_t        bytesToAdd                     = 0;
    std::string    dataBuffer                     = "";
    fileDescriptor clientFileDescriptor           = getClientFileDescriptor(t_clientID);
    if (clientFileDescriptor == -1)
    {
        throw InvalidArgumentException("Invalid client ID.");
    }
    int         activity = 0;
    fd_set      readfds;
    timeval     timeout             = getTimeout();
    time_t      timeoutSeconds      = timeout.tv_sec;
    suseconds_t timeoutMicroseconds = timeout.tv_usec;
    setData(t_clientID, std::string(""));
    if (t_x <= 0)
    {
        throw InvalidArgumentException("Invalid number of bytes to read.");
    }
    while (true)
    {
        FD_ZERO(&readfds);
        FD_SET(clientFileDescriptor, &readfds);

        // Wait for data to be available with the specified timeout

        activity = select(clientFileDescriptor + 1, &readfds, nullptr, nullptr, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ServerRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ServerTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(clientFileDescriptor, &readfds))
        {
            bytesRead = recv(clientFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ServerRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ServerRuntimeException("Connection closed by client.");
            }
            bytesToAdd = std::min(bytesRead, t_x - totalBytesRead);
            dataBuffer.append(buffer, bytesToAdd);
            totalBytesRead += bytesToAdd;
            memset(buffer, 0, Constants::BUFFER_SIZE);
            if (totalBytesRead == t_x)
            {
                setData(t_clientID, dataBuffer);
                return;
            }

            // Reset the timeout

            timeout.tv_sec  = timeoutSeconds;
            timeout.tv_usec = timeoutMicroseconds;
        }
    }
}

void FBNetwork::Server::readTillXData(const int t_clientID, const std::string &t_x)
{
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        bytesRead                      = 0;
    std::string    dataBuffer                     = "";
    size_t         pos                            = 0;
    fileDescriptor clientFileDescriptor           = getClientFileDescriptor(t_clientID);
    if (clientFileDescriptor == -1)
    {
        throw InvalidArgumentException("Invalid client ID.");
    }
    int         activity = 0;
    fd_set      readfds;
    timeval     timeout             = getTimeout();
    time_t      timeoutSeconds      = timeout.tv_sec;
    suseconds_t timeoutMicroseconds = timeout.tv_usec;
    setData(t_clientID, std::string(""));
    if (t_x.empty())
    {
        throw InvalidArgumentException("Invalid string to read.");
    }
    while (true)
    {
        FD_ZERO(&readfds);
        FD_SET(clientFileDescriptor, &readfds);

        // Wait for data to be available with the specified timeout

        int activity = select(clientFileDescriptor + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ServerRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ServerTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(clientFileDescriptor, &readfds))
        {
            bytesRead = recv(clientFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ServerRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ServerRuntimeException("Connection closed by client.");
            }

            dataBuffer.append(buffer, bytesRead);
            pos = dataBuffer.find(t_x);
            if (pos != std::string::npos)
            {
                setData(t_clientID, dataBuffer.substr(0, pos + t_x.length()));
                return;
            }
            memset(buffer, 0, Constants::BUFFER_SIZE);

            // Reset the timeout

            timeout.tv_sec  = timeoutSeconds;
            timeout.tv_usec = timeoutMicroseconds;
        }
    }
}

void FBNetwork::Server::readTillXComesYTimesData(const int t_clientID, const std::string &t_x, const int t_y)
{
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        bytesRead                      = 0;
    std::string    dataBuffer                     = "";
    size_t         pos                            = 0;
    size_t         bufferPos                      = 0;
    int            count                          = 0;
    fileDescriptor clientFileDescriptor           = getClientFileDescriptor(t_clientID);
    if (clientFileDescriptor == -1)
    {
        throw InvalidArgumentException("Invalid client ID.");
    }
    int         activity = 0;
    fd_set      readfds;
    timeval     timeout             = getTimeout();
    time_t      timeoutSeconds      = timeout.tv_sec;
    suseconds_t timeoutMicroseconds = timeout.tv_usec;
    setData(t_clientID, std::string(""));
    if (t_x.empty())
    {
        throw InvalidArgumentException("Invalid string to read.");
    }
    if (t_y <= 0)
    {
        throw InvalidArgumentException("Invalid number of times to read.");
    }
    while (true)
    {
        FD_ZERO(&readfds);
        FD_SET(clientFileDescriptor, &readfds);

        // Wait for data to be available with the specified timeout

        int activity = select(clientFileDescriptor + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ServerRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ServerTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(clientFileDescriptor, &readfds))
        {
            bytesRead = recv(clientFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ServerRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ServerRuntimeException("Connection closed by client.");
            }
            dataBuffer.append(buffer, bytesRead);
            while ((pos = dataBuffer.find(t_x, bufferPos)) != std::string::npos)
            {
                count++;
                bufferPos = pos + t_x.length();
                if (count == t_y)
                {
                    setData(t_clientID, dataBuffer.substr(0, bufferPos));
                    return;
                }
            }
            memset(buffer, 0, Constants::BUFFER_SIZE);

            // Reset the timeout

            timeout.tv_sec  = timeoutSeconds;
            timeout.tv_usec = timeoutMicroseconds;
        }
    }
}

std::vector<FBNetwork::eventTuple> FBNetwork::Server::getPendingEvents()
{
    FBNetwork::eventList               pendingEvents = getEventQueue()->pollEvents();
    std::vector<FBNetwork::eventTuple> returnEvents;
    for (event e : pendingEvents)
    {
        if (getEventQueue()->hasAnError(&e))
        {
            returnEvents.push_back(std::make_tuple(EventType::ERROR, -1));
        }
        else if (getEventQueue()->isServerEvent(&e))
        {
            returnEvents.push_back(std::make_tuple(EventType::CLIENT_WANTS_TO_CONNECT, -1));
        }
        else
        {
            returnEvents.push_back(
                std::make_tuple(EventType::CLIENT_WANTS_TO_SEND_DATA, getClientID(getEventQueue()->getClientFileDescriptor(&e))));
        }
    }
    return returnEvents;
}

bool FBNetwork::Server::isDataAvailable(const timeval *t_timeout)
{
    int    result               = -1;
    int    serverFileDescriptor = getServerFileDescriptor();
    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(serverFileDescriptor, &readFds);
    timeval timeout = *t_timeout;
    result          = select(serverFileDescriptor + 1, &readFds, nullptr, nullptr, &timeout);
    if (result == -1)
    {
        throw ServerRuntimeException("Selecting the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    if (result > 0 && FD_ISSET(serverFileDescriptor, &readFds))
    {
        return true;
    }
    return false;
}

bool FBNetwork::Server::isDisconnected(const int t_clientID)
{
    char buffer[1];
    while (true)
    {
        int bytesRead = recv(getClientFileDescriptor(t_clientID), buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT);
        if (bytesRead == 0)
        {
            return true;
        }
        if (bytesRead == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
}

void FBNetwork::Server::closeClient(const int t_clientID)
{
    if (close(getClientFileDescriptor(t_clientID)) == -1)
    {
        if (errno != EBADF)
        {
            throw ServerRuntimeException("Closing the client failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
    }
}

void FBNetwork::Server::setTimeout(const timeval t_timeout)
{
    if (t_timeout.tv_sec < 0 || t_timeout.tv_usec < 0 || t_timeout.tv_usec > 999999)
    {
        throw InvalidArgumentException("Invalid timeout.");
    }
    m_timeout = t_timeout;
}