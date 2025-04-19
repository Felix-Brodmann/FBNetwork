#ifndef FBNETWORK_SERVER_HPP
#define FBNETWORK_SERVER_HPP

#include "constants.hpp"
#include "eventQueue.hpp"
#include "exceptions.hpp"
#include "extendedSystem.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <errno.h>
#include <map>
#include <mutex>
#include <netinet/in.h>
#include <shared_mutex>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>

namespace FBNetwork
{
    /**
     * @brief Represents a server object.
     * @details The `Server` class encapsulates the functionality and properties of a server. It provides methods to set and retrieve
     * various server attributes and to interact with clients.
     * @note The `Server` class uses shared mutexes to ensure thread-safe access to its member variables. It also provides private setter
     * methods to enforce proper validation and error handling when setting the values of its attributes.
     * @version 1.0.0
     */
    class Server
    {
    private:
        mutable std::shared_mutex m_serverFileDescriptorMutex;
        mutable std::shared_mutex m_clientsCountMutex;
        mutable std::shared_mutex m_usesIpv4DomainMutex;
        mutable std::shared_mutex m_usesIpv6DomainMutex;
        mutable std::shared_mutex m_usesLocalDomainMutex;
        mutable std::shared_mutex m_isServerOnlineMutex;
        mutable std::shared_mutex m_localServerSocketPathMutex;
        mutable std::shared_mutex m_domainMutex;
        mutable std::shared_mutex m_portMutex;
        mutable std::shared_mutex m_maximumCurrentConnectionsMutex;
        mutable std::shared_mutex m_startTimeMutex;
        mutable std::shared_mutex m_serverAddressIpv4Mutex;
        mutable std::shared_mutex m_serverAddressIpv6Mutex;
        mutable std::shared_mutex m_serverAddressLocalMutex;
        mutable std::shared_mutex m_clientAddressLengthMutex;
        mutable std::shared_mutex m_dataMutex;
        mutable std::shared_mutex m_eventQueueMutex;
        mutable std::shared_mutex m_startDateMutex;
        mutable std::shared_mutex m_clientFileDescriptorMutex;
        mutable std::shared_mutex m_clientAddressIpv4Mutex;
        mutable std::shared_mutex m_clientAddressIpv6Mutex;
        mutable std::shared_mutex m_clientAddressLocalMutex;
        mutable std::shared_mutex m_lifeTimeMutex;
        mutable std::shared_mutex m_clientIpAddressMutex;
        mutable std::shared_mutex m_currentClientIDMutex;

        fileDescriptor                                 m_serverFileDescriptor      = -1;
        port                                           m_port                      = 0;
        int                                            m_domain                    = 0;
        int                                            m_maximumCurrentConnections = 0;
        int                                            m_currentClientID           = 0;
        time_t                                         m_startTime                 = 0;
        std::string                                    m_localServerSocketPath     = "";
        std::string                                    m_startDate                 = "";
        bool                                           m_usesIpv4Domain            = false;
        bool                                           m_usesIpv6Domain            = false;
        bool                                           m_usesLocalDomain           = false;
        bool                                           m_isServerOnline            = false;
        std::shared_ptr<struct sockaddr_in> m_serverAddressIpv4         = nullptr;
        std::shared_ptr<struct sockaddr_in6> m_serverAddressIpv6         = nullptr;
        std::shared_ptr<struct sockaddr_un> m_serverAddressLocal        = nullptr;
        std::shared_ptr<EventQueue> m_eventQueue                = nullptr;
        timeval                                        m_timeout;
        std::unordered_map<int, std::string>           m_data;
        std::unordered_map<int, int>                   m_clientFileDescriptor;
        std::unordered_map<int, std::shared_ptr<struct sockaddr_in>>  m_clientAddressIpv4;
        std::unordered_map<int, std::shared_ptr<struct sockaddr_in6>> m_clientAddressIpv6;
        std::unordered_map<int, std::shared_ptr<struct sockaddr_un>>  m_clientAddressLocal;

    private:
        /**
         * @brief Sets the server file descriptor.
         * @details This function sets the file descriptor for the server.
         * @param t_serverFileDescriptor The file descriptor to set.
         * @throws `InvalidArgumentException` If `t_serverFileDescriptor` is -1.
         * @version 1.0.0
         */
        void setServerFileDescriptor(const fileDescriptor t_serverFileDescriptor);

        /**
         * @brief Sets the domain value for the server.
         * @details This function sets the domain value for the server. The domain value determines the network domain in which the server
         * operates.
         * @param t_domain The domain value to set.
         * @throws `InvalidDomainException` If `t_domain` is not a valid domain.
         * @version 1.0.0
         */
        void setDomain(const domain t_domain);

        /**
         * @brief Sets the port number for the server.
         * @details This function allows you to set the port number that the server will listen on.
         * @param t_port The port number to set.
         * @throws `InvalidArgumentException` If `t_port` is less than 0 or greater than 65535.
         * @version 1.0.0
         */
        void setPort(const port t_port);

        /**
         * @brief Sets the maximum number of connections.
         * @details This function sets the maximum number of current connections that the server can handle.
         * @param t_maximumCurrentConnections The maximum number of current connections.
         * @throws `InvalidArgumentException` If `t_maximumCurrentConnections` is less or equal to 0.
         * @version 1.0.0
         */
        void setMaximumCurrentConnections(const int t_maximumCurrentConnections);

        /**
         * @brief Sets the current client ID.
         * @details This function sets the current client ID.
         * @param t_currentClientID The current client ID.
         * @throws `InvalidArgumentException` If `t_currentClientID` is negative.
         * @version 1.0.0
         */
        void setCurrentClientID(const int t_currentClientID);

        /**
         * @brief Sets the start time of the server.
         * @details This function sets the start time of the server to the specified time.
         * @param t_startTime The start time to set.
         * @throws `InvalidArgumentException` If `t_startTime` is negative.
         * @version 1.0.0
         */
        void setStartTime(const time_t t_startTime);

        /**
         * @brief Sets the local server socket path.
         * @details This function sets the path of the local server socket to be used for communication.
         * @param t_localServerSocketPath The path of the local server socket.
         * @throws `InvalidArgumentException` If `t_localServerSocketPath` is empty or exceeds the maximum length of 104 characters.
         * @version 1.0.0
         */
        void setLocalServerSocketPath(const std::string &t_localServerSocketPath);

        /**
         * @brief Sets the start date of the server.
         * @details This function sets the start date of the server to the specified value.
         * @param t_startDate The start date to be set.
         * @throws `InvalidArgumentException` If `t_startDate` is empty.
         * @version 1.0.0
         */
        void setStartDate(const std::string &t_startDate);

        /**
         * @brief Sets whether the server uses the IPv4 domain.
         * @details This function sets the flag indicating whether the server uses an IPv4 domain. If `t_usesIpv4Domain` is `true`, it means
         * the server uses an IPv4 domain.
         * @param t_usesIpv4Domain A boolean value indicating whether the server uses the IPv4 domain.
         * @version 1.0.0
         */
        void setUsesIpv4Domain(const bool t_usesIpv4Domain);

        /**
         * @brief Sets whether the server uses an IPv6 domain.
         * @details This function sets the flag indicating whether the server uses an IPv6 domain. If `t_usesIpv6Domain` is `true`, it means
         * the server uses an IPv6 domain.
         * @param t_usesIpv6Domain A boolean value indicating whether the server uses an IPv6 domain.
         * @version 1.0.0
         */
        void setUsesIpv6Domain(const bool t_usesIpv6Domain);

        /**
         * @brief Sets whether the server uses the local domain.
         * @details This function sets the flag indicating whether the server uses the local domain. If the server uses the local domain, it
         * will bind to the local IP address. If the server does not use the local domain, it will bind to the specified IP address.
         * @param t_usesLocalDomain A boolean value indicating whether the server uses the local domain.
         * @version 1.0.0
         */
        void setUsesLocalDomain(const bool t_usesLocalDomain);

        /**
         * @brief Sets the status of the server.
         * @details This function sets the status of the server to either online or offline.
         * @param t_isServerOnline A boolean value indicating whether the server is online or offline.
         * @version 1.0.0
         */
        void setIsServerOnline(const bool t_isServerOnline);

        /**
         * @brief Sets the IPv4 server address.
         * @details This function sets the IPv4 server address to be used by the server.
         * @param t_serverAddressIpv4 The IPv4 server address to be set.
         * @throws `InvalidArgumentException` If `t_serverAddressIpv4` is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressIpv4(std::shared_ptr<sockaddr_in> t_serverAddressIpv4);

        /**
         * @brief Sets the IPv6 server address.
         * @details This function sets the IPv6 server address to be used by the server.
         * @param t_serverAddressIpv6 The IPv6 server address to be set.
         * @throws `InvalidArgumentException` If `t_serverAddressIpv6` is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressIpv6(std::shared_ptr<sockaddr_in6> t_serverAddressIpv6);

        /**
         * @brief Sets the local server address.
         * @details This function sets the local server address to the specified value.
         * @param t_serverAddressLocal The local server address to set.
         * @throws `InvalidArgumentException` If `t_serverAddressLocal` is `nullptr`.
         * @version 1.0.0
         */
        void setServerAddressLocal(std::shared_ptr<sockaddr_un>t_serverAddressLocal);

        /**
         * @brief Sets the event queue for the server.
         * @details This function sets the event queue for the server. The event queue is used to manage events such as client connections
         * and disconnections.
         * @param t_eventQueue The event queue to set.
         * @version 1.0.0
         */
        void setEventQueue(std::shared_ptr<EventQueue> t_eventQueue);

        /**
         * @brief Sets the data for the server.
         * @details This function sets the data for the server. The data is passed as a std::string parameter.
         * @param t_clientID The ID of the client.
         * @param t_data The data to be set for the server.
         * @version 1.0.0
         */
        void setData(const int t_clientID, const std::string &t_data);

        /**
         * @brief Sets the client file descriptor.
         * @details This function is used to set the client file descriptor.
         * @param t_clientID The ID of the client.
         * @param t_clientFileDescriptor The file descriptor of the client.
         * @version 1.0.0
         */
        void setClientFileDescriptor(const int t_clientID, const fileDescriptor t_clientFileDescriptor);

        /**
         * @brief Sets the IPv4 address of a client.
         * @details This function is used to set the IPv4 address of a client.
         * @param t_clientID The ID of the client.
         * @param t_clientAddressIpv4 The IPv4 address of the client to set.
         * @throws `InvalidArgumentException` If `t_clientAddressIpv4` is `nullptr`.
         * @version 1.0.0
         */
        void setClientAddressIpv4(const int t_clientID, std::shared_ptr<sockaddr_in> t_clientAddressIpv4);

        /**
         * @brief Sets the IPv6 client address.
         * @details This function sets the IPv6 client address  in the server.
         * @param t_clientID The ID of the client.
         * @param t_clientAddressIpv6 The IPv6 client address to set.
         * @throws `InvalidArgumentException` If `t_clientAddressIpv6` is `nullptr`.
         * @version 1.0.0
         */
        void setClientAddressIpv6(const int t_clientID, std::shared_ptr<sockaddr_in6>t_clientAddressIpv6);

        /**
         * @brief Sets the local client address.
         * @details This function is used to set the local client address in the server.
         * @param t_clientID The ID of the client.
         * @param t_clientAddressLocal The local client address to set.
         * @throws `InvalidArgumentException` If `t_clientAddressLocal` is `nullptr`.
         * @version 1.0.0
         */
        void setClientAddressLocal(const int t_clientID, std::shared_ptr<sockaddr_un> t_clientAddressLocal);

        /**
         * @brief Retrieves the file descriptor of the server.
         * @details This function returns the file descriptor associated with the server. The file descriptor can be used for various
         * operations, such as reading from or writing to the server.
         * @return The file descriptor of the server.
         * @version 1.0.0
         */
        fileDescriptor getServerFileDescriptor() const;

        /**
         * @brief Retrieves the domain of the server.
         * @details This function returns the domain of the server as an integer value.
         * @return The domain of the server.
         * @version 1.0.0
         */
        domain getDomain() const;

        /**
         * @brief Retrieves the maximum number of current connections allowed.
         * @details This function returns the maximum number of current connections allowed by the server.
         * @return The maximum number of current connections allowed.
         * @version 1.0.0
         */
        int getMaximumCurrentConnections() const;

        /**
         * @brief Retrieves the next free ID for a client.
         * @details This function returns the next free ID for a client. It is used to assign unique IDs to clients.
         * @return The next free client ID.
         * @version 1.0.0
         */
        int getCurrentClientID() const;

        /**
         * @brief Retrieves the start time of the server.
         * @details This function returns the start time of the server as a time_t value.
         * @return The start time of the server as a time_t value.
         * @version 1.0.0
         */
        time_t getStartTime() const;

        /**
         * @brief Get the local server socket path.
         * @details This function returns the path of the local server socket.
         * @return The local server socket path.
         * @version 1.0.0
         */
        std::string getLocalServerSocketPath() const;

        /**
         * @brief Checks if the server uses the IPv4 domain.
         * @details This function returns true if the server uses the IPv4 domain, and false otherwise.
         * @return true if the server uses the IPv4 domain, false otherwise.
         * @version 1.0.0
         */
        bool usesIpv4Domain() const;

        /**
         * @brief Checks if the server uses IPv6 domain.
         * @details This function returns a boolean value indicating whether the server uses the IPv6 domain.
         * @return true if the server uses IPv6 domain, false otherwise.
         * @version 1.0.0
         */
        bool usesIpv6Domain() const;

        /**
         * @brief Checks whether the server uses the local domain.
         * @details This function returns a boolean value indicating whether the server uses the local domain.
         * @return true if the server uses the local domain, false otherwise.
         * @version 1.0.0
         */
        bool usesLocalDomain() const;

        /**
         * @brief Retrieves the timeout.
         * @details This function returns the timeout value used by the server.
         * @return The timeout value.
         * @version 1.0.0
         */
        timeval getTimeout();

        /**
         * @brief Retrieves the IPv4 server address.
         * @details This function returns a pointer to a sockaddr_in structure that represents the IPv4 address of the server.
         * @return A pointer to a sockaddr_in structure representing the IPv4 server address.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in> getServerAddressIpv4();

        /**
         * @brief Retrieves the IPv6 server address.
         * @details This function returns a pointer to a sockaddr_in6 structure that represents the server address.
         * @return A pointer to the sockaddr_in6 structure representing the server address.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in6> getServerAddressIpv6();

        /**
         * @brief Retrieves the local server address.
         * @details This function returns a pointer to a sockaddr_un structure that represents the local server address.
         * @return A pointer to a sockaddr_un structure representing the local server address.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_un> getServerAddressLocal();

        /**
         * @brief Retrieves the event queue.
         * @details This function returns a pointer to the event queue used by the server.
         * @return A pointer to the event queue.
         * @throws `InvalidArgumentException` If the event queue is `nullptr`.
         * @version 1.0.0
         */
        std::shared_ptr<EventQueue> getEventQueue();

        /**
         * @brief Retrieves the file descriptor of the client.
         * @details This function returns the file descriptor of the client.
         * @param t_clientID The ID of the client.
         * @return The file descriptor of the client.
         * @throws `std::out_of_range` If the client ID is not found.
         * @version 1.0.0
         */
        fileDescriptor getClientFileDescriptor(const int t_clientID) const;

        /**
         * @brief Retrieves the ID of the client.
         * @details This function returns the ID of the client associated with the specified file descriptor.
         * @param t_clientFileDescriptor The file descriptor of the client.
         * @return The ID of the client.
         * @throws `std::out_of_range` If the client file descriptor is not found.
         * @version 1.0.0
         */
        int getClientID(const fileDescriptor t_clientFileDescriptor);

        /**
         * @brief Retrieves the IPv4 address of the client.
         * @details This function returns a pointer to a sockaddr_in structure that contains the IPv4 address of the client.
         * @param t_clientID The ID of the client.
         * @return A pointer to a sockaddr_in structure representing the IPv4 address of the client.
         * @throws `std::out_of_range` If the client ID is not found.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in> getClientAddressIpv4(const int t_clientID);

        /**
         * @brief Retrieves the IPv6 address of the client.
         * @details This function returns a pointer to the `sockaddr_in6` structure representing the IPv6 address of the client.
         * @param t_clientID The ID of the client.
         * @return A pointer to the `sockaddr_in6` structure representing the IPv6 address of the client.
         * @throws `std::out_of_range` If the client ID is not found.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_in6> getClientAddressIpv6(const int t_clientID);

        /**
         * @brief Retrieves the local client address.
         * @details This function returns a pointer to the sockaddr_un structure representing the local client address.
         * @param t_clientID The ID of the client.
         * @return A pointer to the sockaddr_un structure representing the client's address.
         * @throws `std::out_of_range` If the client ID is not found.
         * @version 1.0.0
         */
        std::shared_ptr<sockaddr_un> getClientAddressLocal(const int t_clientID);

        /**
         * @brief Rearanges the client IDs.
         * @details This function rearranges the client IDs to ensure that they are contiguous.
         * @version 1.0.0
         */
        void rearrangeClientIDs();

        /**
         * @brief Checks if a clientID does not exist.
         * @details This function checks if a client with the specified ID does not exist.
         * @version 1.0.0
         */
        bool thisClientDoesNotExist(const int t_clientID) const;

        /**
         * @brief Checks if the client is disconnected.
         * @details This function checks if the client is disconnected by checking if there is no more data to read from the client.
         * @return True if the client is disconnected, false otherwise.
         * @version 1.0.0
         */
        bool isDisconnected(const int t_clientID);

    public:
        /**
         * @brief Returns the port number used by the server.
         * @details This function returns the port number used by the server as a 16-bit unsigned integer.
         * @return The port number as a 16-bit unsigned integer.
         * @version 1.0.0
         */
        port getPort();

        /**
         * @brief Retrieves the start date of the server.
         * @details This function returns the start date of the server as a string.
         * @return The start date of the server as a string.
         * @version 1.0.0
         */
        std::string getStartDate();

        /**
         * @brief Checks if the server is currently online.
         * @details This function returns true if the server is online, and false otherwise.
         * @return true if the server is online, false otherwise.
         * @version 1.0.0
         */
        bool isServerOnline();

        /**
         * @brief Retrieves the data.
         * @details This function returns the data stored in the server as a string.
         * @param t_clientID The ID of the client.
         * @return The data as a string.
         * @version 1.0.0
         */
        std::string getData(const int t_clientID);

        /**
         * @brief Gets the lifetime of an object.
         * @details This function returns the lifetime of the object as a time_t value.
         * @return The lifetime of the object as a time_t value.
         * @version 1.0.0
         */
        time_t getLifeTime();

        /**
         * @brief Retrieves the IP address of the client.
         * @details This function returns the IP address of the client as a string.
         * @return The IP address of the client as a string.
         * @throws `ServerRuntimeException` If something goes wrong while retrieving the IP address.
         * @throws `InvalidDomainException` If the server domain is invalid
         * @version 1.0.0
         */
        std::string getClientIpAddress(const int t_clientID);

        /**
         * @brief Gets the count of currently connected clients.
         * @details This function returns the count of currently connected clients to the server.
         * @return The count of currently connected clients.
         * @version 1.0.0
         */
        int getCurrentlyConnectedClientsCount();

        /**
         * @brief Constructs a IP Domain Server object.
         * @param t_domain The domain of the server.
         * @param t_port The port number of the server.
         * @param t_maximumCurrentConnections The maximum number of current connections allowed by the server.
         * @throws `InvalidArgumentException` If `t_port` is less than 0 or greater than 65535, or `t_maximumCurrentConnections` is less
         * than or equal to 0.
         * @throws `InvalidDomainException` If `t_domain` is invalid.
         * @note The domain can only be one of the following: `FBNetwork::Domain::IPV4_DOMAIN` (for IPv4 domain) and
         * `FBNetwork::Domain::IPV6_DOMAIN` (for IPv6 domain). If you want to use the local domain, use the constructor that takes a socket
         * path as an argument.
         * @version 1.0.0
         */
        Server(const int t_domain, const port t_port, const int t_maximumCurrentConnections);

        /**
         * @brief Constructs a Unix Domain Server object.
         * @param t_socketPath The path to the socket.
         * @param t_port The port number.
         * @param t_maximumCurrentConnections The maximum number of current connections.
         * @throws `InvalidArgumentException` If `t_socketPath` is empty, `t_port` is less than 0 or greater than 65535, or
         * `t_maximumCurrentConnections` is less than or equal to 0.
         * @note The domain is set to FBNetwork::Domain::LOCAL_DOMAIN.
         * @version 1.0.0
         */
        Server(std::string &t_socketPath, const port t_port, const int t_maximumCurrentConnections);

        /**
         * @brief Destructor for the Server class.
         * @details This destructor is responsible for cleaning up any resources used by the Server class. It is automatically called when
         * an instance of the Server class is destroyed.
         * @throws `ServerRuntimeException` If an error occurs while stopping the server.
         * @note This destructor calls the `stopServer()` function.
         * @version 1.0.0
         */
        ~Server();

        /**
         * @brief Starts the server.
         * @details This function initializes and starts the server.
         * @throws `ServerCreationException` If an error occurs while creating the server.
         * @note This function should be called after creating an instance of the Server class.
         * @version 1.0.0
         */
        void startServer();

        /**
         * @brief Starts listening for incoming connections.
         * @details This function initiates the server to start listening for incoming connections from clients. Once a connection is
         * established, the server can receive and process client requests.
         * @throws `ServerRuntimeException` if an error occurs while listening for incoming connections.
         * @version 1.0.0
         */
        void startListening();

        /**
         * @brief Stops the server.
         * @details This function is responsible for stopping the server and terminating any active connections. It should be called when
         * the server needs to be shut down.
         * @throws `ServerRuntimeException` if an error occurs while disconnecting the clients or stopping the server.
         * @version 1.0.0
         */
        void stopServer();

        /**
         * @brief Sets the server to the provided keepAlive value.
         * @details This function sets the server to keep alive. If `t_keepAlive` is `true`, the server will keep the connection alive.
         * @param t_keepAlive A boolean value indicating whether the server should keep the connection alive or not.
         * @throws `ServerRuntimeException` If an error occurred while setting the server option.
         * @version 1.0.0
         */
        void setServerKeepAlive(const bool t_keepAlive);

        /**
         * @brief Accepts a client connection. It automatically assigns an ID to the client and and prepares the ID for the next client.
         * @details This function accepts a client connection. It blocks until a client connection is established.
         * @throws `ServerRuntimeException` If an error occurred while accepting the client connection.
         * @return The ID of the client.
         * @version 1.0.0
         */
        int acceptClient();

        /**
         * @brief Closes client connections of disconnected clients. (If clients do not have any data to send)
         * @details This function closes the client connection if the client is disconnected. It checks if the client is disconnected by
         * checking if there is no more data to read from the client.
         * @throws `ServerRuntimeException` if an error occurred while closing the client connection.
         * @version 1.0.0
         */
        void closeDisconnectedClients();

        /**
         * @brief Sends data to a specific client.
         * @details This function sends data to a specific client.
         * @param t_clientID The ID of the client.
         * @param t_data The data to be sent.
         * @throws `InvalidArgumentException` If `t_data` is empty.
         * @throws `ServerRuntimeException` If an error occurred while sending the data.
         * @version 1.0.0
         */
        void sendData(const int t_clientID, const std::string &t_data);

        /**
         * @brief Reads x data from the client.
         * @details This function reads x data from the client. The data is read up to the specified size (in bytes).
         * @param t_clientID The ID of the client.
         * @param t_x The size of the data to read.
         * @throws `InvalidArgumentException` If `t_x` is less than or equal to 0.
         * @throws `ServerRuntimeException` If an error occurred while reading the data.
         * @throws `ServerTimeoutException` If the read operation timed out. The timeout is set via the `setSocketTimeout()` function. If
         * the timeout is not set, it will be the default FBNetwork::Constants::DEFAULT_TIMEOUT.
         * @version 1.0.0
         */
        void readXData(const int t_clientID, const ssize_t t_x);

        /**
         * @brief Reads data from the client until the specified 'x' is encountered.
         * @details This function reads data from the client until the specified character 'x' is encountered.
         * @param t_clientID The ID of the client.
         * @param t_x The string to search for.
         * @throws `InvalidArgumentException` If `t_x` is empty.
         * @throws `ServerRuntimeException` If an error occurred while reading the data.
         * @version 1.0.0
         */
        void readTillXData(const int t_clientID, const std::string &t_x);

        /**
         * @brief Reads data from the client until the specified string 'x' appears 'y' times.
         * @details This function reads data from the client until the specified string 'x' appears 'y' times.
         * @param t_clientID The ID of the client.
         * @param t_x The string to search for.
         * @param t_y The number of times the character 'x' should appear.
         * @throws `InvalidArgumentException` if `t_x` is empty or `t_y` is less than or equal to 0.
         * @throws `ServerRuntimeException` if an error occurred while reading the data.
         * @version 1.0.0
         */
        void readTillXComesYTimesData(const int t_clientID, const std::string &t_x, const int t_y);

        /**
         * @brief Gets the pending events. Waits indefinitely until an event is available.
         * @details This function returns the pending events in the event queue as a vector of event tuples, where the first element is the
         * event type and the second element is the client ID, if applicable.
         * @return The pending events in the event queue.
         * @version 1.0.0
         */
        std::vector<eventTuple> getPendingEvents();

        /**
         * @brief Checks if data is available to be read from the specified client within the given timeout.
         * @details This function checks if there is data available to be read from the client within the given timeout.
         * @param t_timeout The timeout value in seconds and microseconds.
         * @return true if data is available within the timeout, false otherwise.
         * @throws `ServerRuntimeException` If an error occurred while checking for data availability.
         * @version 1.0.0
         */
        bool isDataAvailable(const timeval *t_timeout);

        /**
         * @brief Closes the client connection.
         * @details This function closes the connection with the client to make the server available for other clients.
         * @param t_clientID The ID of the client.
         * @throws `ServerRuntimeException` If an error occurred while closing the client connection.
         * @version 1.0.0
         */
        void closeClient(const int t_clientID);

        /**
         * @brief Sets the socket timeout.
         * @details This function sets the timeout for reading from a client.
         * @param t_timeout The timeout value in seconds and microseconds.
         * @throws `InvalidArgumentException` If tv_sec is negative,tv_usec is negative or tv_usec is greater than 999999.
         * @version 1.0.0
         */
        void setTimeout(const timeval t_timeout);
    };
}  // namespace FBNetwork

#endif