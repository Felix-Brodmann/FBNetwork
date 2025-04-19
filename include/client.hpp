#ifndef FBNETWORK_CLIENT_HPP
#define FBNETWORK_CLIENT_HPP

#include "constants.hpp"
#include "exceptions.hpp"
#include "extendedSystem.hpp"
#include <arpa/inet.h>
#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

namespace FBNetwork
{
    /**
     * @class Client
     * @brief Represents a client object.
     * @details The `Client` class encapsulates the functionality and properties of a client. It provides methods to set and retrieve
     * various client attributes and to interact with a server.
     * @version 1.0.0
     */
    class Client
    {
    private:
        fileDescriptor                       m_serverFileDescriptor = -1;
        int                                  m_serverDomain         = -1;
        port                                 m_serverPort           = -1;
        std::string                          m_serverIpAddress      = "";
        std::string                          m_serverSocketPath     = "";
        std::string                          m_data                 = "";
        bool                                 m_usesIpv4Domain       = false;
        bool                                 m_usesIpv6Domain       = false;
        bool                                 m_usesLocalDomain      = false;
        timeval                              m_timeout              = FBNetwork::Constants::DEFAULT_TIMEOUT;
        std::shared_ptr<struct sockaddr_in>  m_serverAddressIpv4    = nullptr;
        std::shared_ptr<struct sockaddr_in6> m_serverAddressIpv6    = nullptr;
        std::shared_ptr<struct sockaddr_un>  m_serverAddressLocal   = nullptr;

        /**
         * @brief Sets the server file descriptor.
         * @details This function sets the file descriptor for the server connection.
         * @param t_serverFileDescriptor The file descriptor for the server connection.
         * @throws `InvalidArgumentException` if the file descriptor is -1.
         * @version 1.0.0
         */
        void setServerFileDescriptor(const fileDescriptor t_serverFileDescriptor);

        /**
         * @brief Sets the domain of the server.
         * @details This function sets the domain of the server.
         * @param t_domain The domain of the server.
         * @throws `InvalidDomainException` if `t_domain` is not a valid domain.
         * @version 1.0.0
         */
        void setServerDomain(const domain t_domain);

        /**
         * @brief Sets the port of the server.
         * @details This function sets the port of the server.
         * @param t_port The port of the server.
         * @throws `InvalidArgumentException` if the port is less then 0 or greater than 65535.
         * @version 1.0.0
         */
        void setServerPort(const port t_port);

        /**
         * @brief Sets the IP address of the server.
         * @details This function sets the IP address of the server.
         * @param t_ipAddress The IP address of the server.
         * @throws `InvalidArgumentException` if the IP address is empty.
         * @version 1.0.0
         */
        void setServerIpAddress(const std::string &t_ipAddress);

        /**
         * @brief Sets the server socket path.
         * @details This function sets the server socket path.
         * @param t_socketPath The server socket path.
         * @throws `InvalidArgumentException` if the socket path is empty.
         * @version 1.0.0
         */
        void setServerSocketPath(const std::string &t_socketPath);

        /**
         * @brief Sets the data.
         * @details This function sets the data.
         * @param t_data The data.
         * @version 1.0.0
         */
        void setData(const std::string &t_data);

        /**
         * @brief Sets whether the client uses the IPv4 domain.
         * @details This function sets whether the client uses the IPv4 domain.
         * @param t_usesIpv4Domain Whether the client uses the IPv4 domain.
         * @version 1.0.0
         */
        void setUsesIpv4Domain(const bool t_usesIpv4Domain);

        /**
         * @brief Sets whether the client uses the IPv6 domain.
         * @details This function sets whether the client uses the IPv6 domain.
         * @param t_usesIpv6Domain Whether the client uses the IPv6 domain.
         * @version 1.0.0
         */
        void setUsesIpv6Domain(const bool t_usesIpv6Domain);

        /**
         * @brief Sets whether the client uses the local domain.
         * @details This function sets whether the client uses the local domain.
         * @param t_usesLocalDomain Whether the client uses the local domain.
         * @version 1.0.0
         */
        void setUsesLocalDomain(const bool t_usesLocalDomain);

        /**
         * @brief Sets the server address for the IPv4 domain.
         * @details This function sets the server address for the IPv4 domain.
         * @param t_servAddrIpv4 The server address for the IPv4 domain.
         * @throws `InvalidArgumentException` if the server address is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressIpv4(std::shared_ptr<sockaddr_in> t_servAddrIpv4);

        /**
         * @brief Sets the server address for the IPv6 domain.
         * @details This function sets the server address for the IPv6 domain.
         * @param t_servAddrIpv6 The server address for the IPv6 domain.
         * @throws `InvalidArgumentException` if the server address is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressIpv6(std::shared_ptr<sockaddr_in6> t_servAddrIpv6);

        /**
         * @brief Sets the server address for the local domain.
         * @details This function sets the server address for the local domain.
         * @param t_servAddrLocal The server address for the local domain.
         * @throws `InvalidArgumentException` if the server address is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressLocal(std::shared_ptr<sockaddr_un> t_servAddrLocal);

        /**
         * @brief Gets the server file descriptor.
         * @details This function gets the server file descriptor.
         * @return The server file descriptor.
         * @version 1.0.0
         */
        fileDescriptor getServerFileDescriptor() const;

        /**
         * @brief Gets the domain of the server.
         * @details This function gets the domain of the server.
         * @return The domain of the server.
         * @version 1.0.0
         */
        domain getServerDomain() const;

        /**
         * @brief Gets the port of the server.
         * @details This function gets the port of the server.
         * @return The port of the server.
         * @version 1.0.0
         */
        port getServerPort() const;

        /**
         * @brief Gets the IP address of the server.
         * @details This function gets the IP address of the server.
         * @return The IP address of the server.
         * @version 1.0.0
         */
        std::string getServerIpAddress() const;

        /**
         * @brief Gets the server socket path.
         * @details This function gets the server socket path.
         * @return The server socket path.
         * @version 1.0.0
         */
        std::string getServerSocketPath() const;

        /**
         * @brief Checks if the client uses the IPv4 domain.
         * @details This function returns true if the client uses the IPv4 domain, and false otherwise.
         * @return true if the client uses the IPv4 domain, false otherwise.
         * @version 1.0.0
         */
        bool usesIpv4Domain() const;

        /**
         * @brief Checks if the client uses the IPv6 domain.
         * @details This function returns true if the client uses the IPv6 domain, and false otherwise.
         * @return true if the client uses the IPv6 domain, false otherwise.
         * @version 1.0.0
         */
        bool usesIpv6Domain() const;

        /**
         * @brief Checks if the client uses the local domain.
         * @details This function returns true if the client uses the local domain, and false otherwise.
         * @return true if the client uses the local domain, false otherwise.
         * @version 1.0.0
         */
        bool usesLocalDomain() const;

        /**
         * @brief Gets the timeout for waiting for the server.
         * @details This function gets the timeout for waiting for the server.
         * @return The timeout for waiting for the server.
         * @version 1.0.0
         */
        timeval getTimeout();

        /**
         * @brief Gets the server address for the IPv4 domain.
         * @details This function gets the server address for the IPv4 domain.
         * @return The server address for the IPv4 domain.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in> getServerAddressIpv4();

        /**
         * @brief Gets the server address for the IPv6 domain.
         * @details This function gets the server address for the IPv6 domain.
         * @return The server address for the IPv6 domain.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in6> getServerAddressIpv6();

        /**
         * @brief Gets the server address for the local domain.
         * @details This function gets the server address for the local domain.
         * @return The server address for the local domain.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_un> getServerAddressLocal();

    public:
        /**
         * @brief Constructs a IP Client object.
         * @param t_domain The domain of the server.
         * @param t_ipAddress The IP address of the server.
         * @param t_port The port of the server.
         * @throws `InvalidDomainException` if the domain is not IPV4_DOMAIN or IPV6_DOMAIN.
         * @throws `InvalidArgumentException` if the IP address is empty or the port is less than 0 or greater than 65535.
         * @note The domain can only be one of the following: `FBNetwork::Domain::IPV4_DOMAIN` (for IPv4 domain) and
         * `FBNetwork::Domain::IPV6_DOMAIN` (for IPv6 domain). If you want to use the local domain, use the constructor thatm takes a socket
         * path as an argument.
         * @version 1.0.0
         */
        Client(const domain t_domain, const std::string &t_ipAddress, const port t_port);

        /**
         * @brief Constructs a UNIX Domain Client object.
         * @param t_socketPath The socket path of the server.
         * @param t_port The port of the server.
         * @throws `InvalidArgumentException` if the socket path is empty or the port is less than 0 or greater than 65535.
         * @note The domain is set to FBNetwork::Domain::LOCAL_DOMAIN.
         * @version 1.0.0
         */
        Client(const std::string &t_socketPath, const port t_port);

        /**
         * @brief Destructs a Client object.
         * @details This calls the disconnectFromServer function to disconnect from the server.
         * @version 1.0.0
         */
        ~Client();

        /**
         * @brief Sets the timeout for waiting for the server.
         * @details This function sets the timeout for waiting for the server.
         * @param t_timeout The timeout for waiting for the server.
         * @version 1.0.0
         */
        void setTimeout(const timeval t_timeout);

        /**
         * @brief Gets the data.
         * @details This function gets the data.
         * @return The data.
         * @version 1.0.0
         */
        std::string getData() const;

        /**
         * @brief Connects to the server.
         * @details This function connects to the server.
         * @throws `ClientCreationException` if the connection fails.
         * @version 1.0.0
         */
        void connectToServer();

        /**
         * @brief Disconnects from the server.
         * @details This function disconnects from the server.
         * @throws `ClientRuntimeException` if the disconnection fails.
         * @version 1.0.0
         */
        void disconnectFromServer();

        /**
         * @brief Sends data to the server.
         * @details This function sends data to the server.
         * @param t_data The data to send.
         * @throws `InvalidArgumentException` if the data is empty.
         * @throws `ClientRuntimeException` if the data cannot be sent.
         * @version 1.0.0
         */
        void sendData(const std::string t_data);

        /**
         * @brief Reads data from the server.
         * @details This function reads data from the server.
         * @param t_x The size of the data to read.
         * @throws `InvalidArgumentException` if the size is less or equal to 0.
         * @throws `ClientRuntimeException` if the data cannot be read.
         * @version 1.0.0
         */
        void readXData(const ssize_t t_x);

        /**
         * @brief Reads data from the server until a specific character is encountered.
         * @details This function reads data from the server until a specific character is encountered.
         * @param t_x The character to read until.
         * @throws `InvalidArgumentException` if the character is empty.
         * @throws `ClientRuntimeException` if the data cannot be read.
         * @version 1.0.0
         */
        void readTillXData(const std::string t_x);

        /**
         * @brief Reads data from the server until a specific character is encountered a specific number of times.
         * @details This function reads data from the server until a specific character is encountered a specific number of times.
         * @param t_x The character to read until.
         * @param t_y The number of times to read the character.
         * @throws `InvalidArgumentException` if the delimiter is empty or the number of times is less than 0.
         * @throws `ClientRuntimeException` if the data cannot be read.
         * @version 1.0.0
         */
        void readTillXComesYTimesData(const std::string t_x, const int t_y);

        /**
         * @brief Checks if data is available in the given timeout.
         * @details This function checks if data is available in the given timeout.
         * @param t_timeout The timeout.
         * @return true if data is available, false otherwise.
         * @throws `ClientRuntimeException` if the data availability cannot be checked.
         * @version 1.0.0
         */
        bool isDataAvailable(const std::shared_ptr<timeval> t_timeout);
    };
}  // namespace FBNetwork

#endif