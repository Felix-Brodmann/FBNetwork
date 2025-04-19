#include "../include/client.hpp"

void FBNetwork::Client::setServerFileDescriptor(const fileDescriptor t_serverFileDescriptor)
{
    if (t_serverFileDescriptor == -1)
    {
        throw InvalidArgumentException("Invalid server file descriptor.");
    }
    m_serverFileDescriptor = t_serverFileDescriptor;
}

void FBNetwork::Client::setServerDomain(const domain t_domain)
{
    if (t_domain != Domain::IPV4_DOMAIN && t_domain != Domain::IPV6_DOMAIN && t_domain != Domain::LOCAL_DOMAIN)
    {
        throw InvalidDomainException("Must be either IPV4_DOMAIN, IPV6_DOMAIN or LOCAL_DOMAIN.");
    }
    m_serverDomain = t_domain;
}

void FBNetwork::Client::setServerPort(const port t_port)
{
    if (t_port < 0 || t_port > 65535)
    {
        throw InvalidArgumentException("Invalid port.");
    }
    m_serverPort = t_port;
}

void FBNetwork::Client::setServerIpAddress(const std::string &t_ipAddress)
{
    if (t_ipAddress.empty())
    {
        throw InvalidArgumentException("Invalid IP address.");
    }
    m_serverIpAddress = t_ipAddress;
}

void FBNetwork::Client::setServerSocketPath(const std::string &t_socketPath)
{
    if (t_socketPath.empty())
    {
        throw InvalidArgumentException("Invalid socket path.");
    }
    m_serverSocketPath = t_socketPath;
}

void FBNetwork::Client::setUsesIpv4Domain(const bool t_usesIpv4Domain)
{
    m_usesIpv4Domain = t_usesIpv4Domain;
}

void FBNetwork::Client::setUsesIpv6Domain(const bool t_usesIpv6Domain)
{
    m_usesIpv6Domain = t_usesIpv6Domain;
}

void FBNetwork::Client::setUsesLocalDomain(const bool t_usesLocalDomain)
{
    m_usesLocalDomain = t_usesLocalDomain;
}

void FBNetwork::Client::setServerAddressIpv4(std::shared_ptr<sockaddr_in> t_serverAddressIpv4)
{
    if (t_serverAddressIpv4 == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressIpv4 = t_serverAddressIpv4;
}

void FBNetwork::Client::setServerAddressIpv6(std::shared_ptr<sockaddr_in6> t_serverAddressIpv6)
{
    if (t_serverAddressIpv6 == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressIpv6 = t_serverAddressIpv6;
}

void FBNetwork::Client::setServerAddressLocal(std::shared_ptr<sockaddr_un> t_serverAddressLocal)
{
    if (t_serverAddressLocal == nullptr)
    {
        throw InvalidArgumentException("Invalid server address.");
    }
    m_serverAddressLocal = t_serverAddressLocal;
}

void FBNetwork::Client::setData(const std::string &t_data)
{
    m_data = t_data;
}

FBNetwork::fileDescriptor FBNetwork::Client::getServerFileDescriptor() const
{
    return m_serverFileDescriptor;
}

FBNetwork::domain FBNetwork::Client::getServerDomain() const
{
    return m_serverDomain;
}

FBNetwork::port FBNetwork::Client::getServerPort() const
{
    return m_serverPort;
}

std::string FBNetwork::Client::getServerIpAddress() const
{
    return m_serverIpAddress;
}

std::string FBNetwork::Client::getServerSocketPath() const
{
    return m_serverSocketPath;
}

bool FBNetwork::Client::usesIpv4Domain() const
{
    return m_usesIpv4Domain;
}

bool FBNetwork::Client::usesIpv6Domain() const
{
    return m_usesIpv6Domain;
}

bool FBNetwork::Client::usesLocalDomain() const
{
    return m_usesLocalDomain;
}

std::shared_ptr<sockaddr_in> FBNetwork::Client::getServerAddressIpv4()
{
    return m_serverAddressIpv4;
}

std::shared_ptr<sockaddr_in6> FBNetwork::Client::getServerAddressIpv6()
{
    return m_serverAddressIpv6;
}

std::shared_ptr<sockaddr_un> FBNetwork::Client::getServerAddressLocal()
{
    return m_serverAddressLocal;
}

timeval FBNetwork::Client::getTimeout()
{
    return m_timeout;
}

std::string FBNetwork::Client::getData() const
{
    return m_data;
}

FBNetwork::Client::Client(const domain t_domain, const std::string &t_ipAddress, const port t_port)
{
    try
    {
        setServerDomain(t_domain);
        setServerIpAddress(t_ipAddress);
        setServerPort(t_port);
    }
    catch (const InvalidDomainException &e)
    {
        throw e;
    }
    if (getServerDomain() == Domain::IPV4_DOMAIN)
    {
        setUsesIpv4Domain(true);
        setUsesIpv6Domain(false);
        setUsesLocalDomain(false);
    }
    else if (getServerDomain() == Domain::IPV6_DOMAIN)
    {
        setUsesIpv4Domain(false);
        setUsesIpv6Domain(true);
        setUsesLocalDomain(false);
    }
    else
    {
        throw InvalidDomainException("Please use either IPv4 or IPv6.");
    }
    setTimeout(Constants::DEFAULT_TIMEOUT);
}

FBNetwork::Client::Client(const std::string &t_socketPath, const port t_port)
{
    try
    {
        setServerDomain(Domain::LOCAL_DOMAIN);
        setServerSocketPath(t_socketPath);
        setServerPort(t_port);
    }
    catch (const InvalidArgumentException &e)
    {
        throw e;
    }
    setUsesIpv4Domain(false);
    setUsesIpv6Domain(false);
    setUsesLocalDomain(true);
    setTimeout(Constants::DEFAULT_TIMEOUT);
}

FBNetwork::Client::~Client()
{
    try
    {
        disconnectFromServer();
    }
    catch (const ClientRuntimeException &e)
    {

        // just do nothing
        // if disconnecting from the server fails, there is nothing we can do
    }
}

void FBNetwork::Client::connectToServer()
{
    if (usesIpv4Domain())
    {
        std::shared_ptr<sockaddr_in> serverAddressIpv4    = std::make_shared<sockaddr_in>();
        fileDescriptor               serverFileDescriptor = -1;
        *serverAddressIpv4                                = {};
        serverAddressIpv4->sin_family                     = Domain::IPV4_DOMAIN;
        if (inet_pton(Domain::IPV4_DOMAIN, getServerIpAddress().c_str(), &(serverAddressIpv4->sin_addr)) != 1)
        {
            throw ClientCreationException("Invalid IP address.");
        }
        serverAddressIpv4->sin_port = htons(getServerPort());
        try
        {
            serverFileDescriptor = socket(Domain::IPV4_DOMAIN, SOCK_STREAM, 0);
            setServerFileDescriptor(serverFileDescriptor);
        }
        catch (const InvalidArgumentException &e)
        {
            throw ClientCreationException("Creating the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        if (connect(serverFileDescriptor, reinterpret_cast<sockaddr *>(serverAddressIpv4.get()), sizeof(sockaddr_in)) == -1)
        {
            throw ClientCreationException("Connecting the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        setServerAddressIpv4(serverAddressIpv4);
    }
    else if (usesIpv6Domain())
    {
        std::shared_ptr<sockaddr_in6> serverAddressIpv6    = std::make_shared<sockaddr_in6>();
        fileDescriptor                serverFileDescriptor = -1;
        *serverAddressIpv6                                 = {};
        serverAddressIpv6->sin6_family                     = Domain::IPV6_DOMAIN;
        if (inet_pton(Domain::IPV6_DOMAIN, getServerIpAddress().c_str(), &serverAddressIpv6->sin6_addr) != 1)
        {
            throw ClientCreationException("Invalid IP address.");
        }
        serverAddressIpv6->sin6_port = htons(getServerPort());
        try
        {
            serverFileDescriptor = socket(Domain::IPV6_DOMAIN, SOCK_STREAM, 0);
            setServerFileDescriptor(serverFileDescriptor);
        }
        catch (const InvalidArgumentException &e)
        {
            throw ClientCreationException("Creating the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        if (connect(serverFileDescriptor, reinterpret_cast<sockaddr *>(serverAddressIpv6.get()), sizeof(*serverAddressIpv6)) == -1)
        {
            throw ClientCreationException("Connecting the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        setServerAddressIpv6(serverAddressIpv6);
    }
    else if (usesLocalDomain())
    {
        std::shared_ptr<sockaddr_un> serverAddressLocal   = std::make_shared<sockaddr_un>();
        fileDescriptor               serverFileDescriptor = -1;
        *serverAddressLocal                               = {};
        serverAddressLocal->sun_family                    = Domain::LOCAL_DOMAIN;
        strncpy(serverAddressLocal->sun_path, getServerSocketPath().c_str(), sizeof(getServerSocketPath()));
        try
        {
            serverFileDescriptor = socket(Domain::LOCAL_DOMAIN, SOCK_STREAM, 0);
            setServerFileDescriptor(serverFileDescriptor);
        }
        catch (const InvalidArgumentException &e)
        {
            throw ClientCreationException("Creating the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        if (connect(serverFileDescriptor, reinterpret_cast<sockaddr *>(serverAddressLocal.get()), sizeof(*serverAddressLocal)) == -1)
        {
            throw ClientCreationException("Connecting the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
        }
        setServerAddressLocal(serverAddressLocal);
    }
}

void FBNetwork::Client::disconnectFromServer()
{
    if (close(getServerFileDescriptor()) == -1)
    {
        throw ClientRuntimeException("Closing the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::Client::sendData(const std::string t_data)
{
    if (t_data.empty())
    {
        throw InvalidArgumentException("Invalid data.");
    }
    fileDescriptor serverFileDescriptor = getServerFileDescriptor();
    int            activity             = 0;
    timeval        timeout              = getTimeout();
    time_t         timeoutSeconds       = timeout.tv_sec;
    suseconds_t    timeoutMicroseconds  = timeout.tv_usec;
    fd_set         writeSet;
    FD_ZERO(&writeSet);
    FD_SET(serverFileDescriptor, &writeSet);

    // Wait for the socket to be ready for writing with the specified timeout

    activity = select(serverFileDescriptor + 1, NULL, &writeSet, NULL, &timeout);

    int       error = 0;
    socklen_t len   = sizeof(error);
    if (getsockopt(serverFileDescriptor, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
    {
        throw ClientRuntimeException("Error getting socket options: " + ExtendedSystem::getCurrentErrnoError());
    }
    if (activity < 0 && errno != EINTR)
    {
        throw ClientRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
    }
    else if (activity == 0)
    {

        // Timeout reached

        throw ClientTimeoutException("Timeout reached while sending data.");
    }
    if (FD_ISSET(serverFileDescriptor, &writeSet))
    {
        while (send(serverFileDescriptor, t_data.c_str(), t_data.size(), MSG_NOSIGNAL) == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                throw ClientRuntimeException("Sending the data failed. Error: " + ExtendedSystem::getCurrentErrnoError());
            }
        }
    }
    return;
}

void FBNetwork::Client::readXData(const ssize_t t_x)
{
    fd_set         readFds;
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        totalBytesRead                 = 0;
    ssize_t        bytesRead                      = 0;
    ssize_t        bytesToAdd                     = 0;
    std::string    dataBuffer                     = "";
    int            activity                       = 0;
    timeval        timeout                        = getTimeout();
    time_t         timeoutSeconds                 = timeout.tv_sec;
    suseconds_t    timeoutMicroseconds            = timeout.tv_usec;
    fileDescriptor serverFileDescriptor           = getServerFileDescriptor();
    if (serverFileDescriptor == -1)
    {
        throw ClientRuntimeException("Invalid server file descriptor.");
    }
    setData(std::string(""));
    if (t_x <= 0)
    {
        throw InvalidArgumentException("Invalid number of bytes to read.");
    }
    while (true)
    {
        FD_ZERO(&readFds);
        FD_SET(serverFileDescriptor, &readFds);

        // Wait for data to be available with the specified timeout

        activity = select(serverFileDescriptor + 1, &readFds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ClientRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ClientTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(serverFileDescriptor, &readFds))
        {
            bytesRead = recv(serverFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ClientRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ClientRuntimeException("Connection closed by client.");
            }
            bytesToAdd = std::min(bytesRead, t_x - totalBytesRead);
            dataBuffer.append(buffer, bytesToAdd);
            totalBytesRead += bytesToAdd;
            memset(buffer, 0, Constants::BUFFER_SIZE);
            if (totalBytesRead == t_x)
            {
                setData(dataBuffer);
                return;
            }

            // Reset the timeout

            timeout.tv_sec  = timeoutSeconds;
            timeout.tv_usec = timeoutMicroseconds;
        }
    }
}

void FBNetwork::Client::readTillXData(const std::string t_x)
{
    fd_set         readFds;
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        bytesRead                      = 0;
    std::string    dataBuffer                     = "";
    size_t         pos                            = 0;
    int            activity                       = 0;
    timeval        timeout                        = getTimeout();
    time_t         timeoutSeconds                 = timeout.tv_sec;
    suseconds_t    timeoutMicroseconds            = timeout.tv_usec;
    fileDescriptor serverFileDescriptor           = getServerFileDescriptor();
    if (serverFileDescriptor == -1)
    {
        throw ClientRuntimeException("Invalid server file descriptor.");
    }
    setData("");
    if (t_x.empty())
    {
        throw InvalidArgumentException("Invalid string to read.");
    }
    while (true)
    {
        FD_ZERO(&readFds);
        FD_SET(serverFileDescriptor, &readFds);

        // Wait for data to be available with the specified timeout

        activity = select(serverFileDescriptor + 1, &readFds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ClientRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ClientTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(serverFileDescriptor, &readFds))
        {
            bytesRead = recv(serverFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ClientRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ClientRuntimeException("Connection closed by client.");
            }
            dataBuffer.append(buffer, bytesRead);
            pos = dataBuffer.find(t_x);
            if (pos != std::string::npos)
            {
                setData(dataBuffer.substr(0, pos + t_x.length()));
                return;
            }
            memset(buffer, 0, Constants::BUFFER_SIZE);

            // Reset the timeout

            timeout.tv_sec  = timeoutSeconds;
            timeout.tv_usec = timeoutMicroseconds;
        }
    }
}

void FBNetwork::Client::readTillXComesYTimesData(const std::string t_x, const int t_y)
{
    fd_set         readFds;
    char           buffer[Constants::BUFFER_SIZE] = {0};
    ssize_t        bytesRead                      = 0;
    std::string    dataBuffer                     = "";
    size_t         pos                            = 0;
    size_t         bufferPos                      = 0;
    int            count                          = 0;
    int            activity                       = 0;
    timeval        timeout                        = getTimeout();
    time_t         timeoutSeconds                 = timeout.tv_sec;
    suseconds_t    timeoutMicroseconds            = timeout.tv_usec;
    fileDescriptor serverFileDescriptor           = getServerFileDescriptor();
    if (serverFileDescriptor == -1)
    {
        throw ClientRuntimeException("Invalid server file descriptor.");
    }
    setData("");
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
        FD_ZERO(&readFds);
        FD_SET(serverFileDescriptor, &readFds);

        // Wait for data to be available with the specified timeout

        activity = select(serverFileDescriptor + 1, &readFds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            throw ClientRuntimeException("Error during select: " + ExtendedSystem::getCurrentErrnoError());
        }
        else if (activity == 0)
        {

            // Timeout reached

            throw ClientTimeoutException("Timeout reached while reading data.");
        }

        // Check if data is ready to be read

        if (FD_ISSET(serverFileDescriptor, &readFds))
        {
            bytesRead = recv(serverFileDescriptor, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    throw ClientRuntimeException("Error reading data: " + ExtendedSystem::getCurrentErrnoError());
                }
            }
            else if (bytesRead == 0)
            {
                throw ClientRuntimeException("Connection closed by client.");
            }
            dataBuffer.append(buffer, bytesRead);
            while ((pos = dataBuffer.find(t_x, bufferPos)) != std::string::npos)
            {
                count++;
                bufferPos = pos + t_x.length();
                if (count == t_y)
                {
                    setData(dataBuffer.substr(0, bufferPos));
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

bool FBNetwork::Client::isDataAvailable(const std::shared_ptr<timeval> t_timeout)
{
    int    result = -1;
    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(getServerFileDescriptor(), &readFds);
    timeval timeout = *t_timeout;
    result          = select(getServerFileDescriptor() + 1, &readFds, NULL, NULL, &timeout);
    if (result == -1)
    {
        throw ClientRuntimeException("Selecting the socket failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    else if (result == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FBNetwork::Client::setTimeout(const timeval t_timeout)
{
    if (t_timeout.tv_sec < 0 || t_timeout.tv_usec < 0 || t_timeout.tv_usec > 999999)
    {
        throw InvalidArgumentException("Invalid timeout.");
    }
    m_timeout = t_timeout;
}