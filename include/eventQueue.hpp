#ifndef FBNETWORK_EVENT_HPP
#define FBNETWORK_EVENT_HPP

#include <mutex>
#include <shared_mutex>
#include <tuple>
#include <unistd.h>
#include <vector>
#ifdef __APPLE__
#include <sys/event.h>
#else
#include <sys/epoll.h>
#endif
#include "constants.hpp"
#include "exceptions.hpp"
#include "extendedSystem.hpp"

namespace FBNetwork
{
    /**
     * @brief Represents a event queue.
     * @details The `EventQueue` class encapsulates the functionality and properties of a event queue. It provides methods to add and remove
     * events from the queue and to retrieve events in the queue.
     * @version 1.0.0
     */
    class EventQueue
    {
    private:
        mutable std::shared_mutex m_eventQueueFileDescriptorMutex;
        mutable std::shared_mutex m_serverFileDescriptorMutex;
        FBNetwork::fileDescriptor m_eventQueueFileDescriptor = -1;
        FBNetwork::fileDescriptor m_serverFileDescriptor     = -1;

    private:
        /**
         * @brief Sets the event queue file descriptor.
         * @details This function sets the event queue file descriptor to be used by the server.
         * @param t_eventQueueFileDescriptor The event queue file descriptor to be set.
         * @version 1.0.0
         */
        void setEventQueueFileDescriptor(const FBNetwork::fileDescriptor t_eventQueueFileDescriptor);

        /**
         * @brief Sets the server file descriptor.
         * @details This function sets the server file descriptor to be used by the server.
         * @param t_serverFileDescriptor The server file descriptor to be set.
         * @throws `InvalidArgumentException` If `t_serverFileDescriptor` is less than 0.
         * @version 1.0.0
         */
        void setServerFileDescriptor(const FBNetwork::fileDescriptor t_serverFileDescriptor);

        /**
         * @brief Retrieves the event queue file descriptor.
         * @details This function returns the event queue file descriptor used by the server.
         * @return The event queue file descriptor used by the server.
         * @version 1.0.0
         */
        const FBNetwork::fileDescriptor getEventQueueFileDescriptor() const;

        /**
         * @brief Retrieves the server file descriptor.
         * @details This function returns the server file descriptor used by the server.
         * @return The server file descriptor used by the server.
         * @version 1.0.0
         */
        const FBNetwork::fileDescriptor getServerFileDescriptor() const;

    public:
        /**
         * @brief Constructs a new `EventQueue` object.
         * @details This constructor creates a new `EventQueue` object and initializes the event queue file descriptor.
         * @throws `ServerRuntimeException` If creating the event queue file descriptor fails.
         * @version 1.0.0
         */
        EventQueue();

        /**
         * @brief Destroys the `EventQueue` object.
         * @details This destructor closes the event queue file descriptor.
         * @version 1.0.0
         */
        ~EventQueue();

        /**
         * @brief Sets the server file descriptor.
         * @details This function is used to set the server file descriptor.
         * @param t_serverFileDescriptor The server file descriptor to set.
         * @throws `InvalidArgumentException` If `t_serverFileDescriptor` is -1.
         * @throws `ServerRuntimeException` If adding the event to the event queue fails.
         * @version 1.0.0
         */
        void setServer(const FBNetwork::fileDescriptor t_serverFileDescriptor);

        /**
         * @brief Adds a client to the event queue.
         * @details This function adds a client to the event queue.
         * @param t_clientFileDescriptor The file descriptor of the client to add.
         * @throws `InvalidArgumentException` If `t_clientFileDescriptor` is -1.
         * @throws `ServerRuntimeException` If adding the event to the event queue fails.
         * @version 1.0.0
         */
        void addClient(const FBNetwork::fileDescriptor t_clientFileDescriptor);

        /**
         * @brief Removes a client from the event queue.
         * @details This function removes a client from the event queue.
         * @param t_clientFileDescriptor The file descriptor of the client to remove.
         * @throws `InvalidArgumentException` If `t_clientFileDescriptor` is -1.
         * @throws `ServerRuntimeException` If removing the event from the event queue fails.
         * @version 1.0.0
         */
        void removeClient(const FBNetwork::fileDescriptor t_clientFileDescriptor);

        /**
         * @brief Polls the events in the event queue.
         * @details This function polls the events in the event queue. It waits for events to occur and returns the events in the event
         * queue.
         * @return A vector of `event` structures representing the events in the event queue.
         * @version 1.0.0
         */
        eventList pollEvents();

        /**
         * @brief Polls the events in the event queue.
         * @details This function polls the events in the event queue. It waits for events to occur or until the timeout is reached and
         * returns the events in the event queue.
         * @param t_timeout The timeout value in milliseconds.
         * @return A vector of `event` structures representing the events in the event queue.
         * @throws `ServerTimeoutException` If the timeout is reached while polling the events.
         * @version 1.0.0
         */
        eventList pollEvents(const int t_timeout);

        /**
         * @brief Checks if the given event has an error.
         * @details This function checks if the given event has an error.
         * @param t_event The event to check.
         * @return `true` if the event has an error, `false` otherwise.
         * @version 1.0.0
         */
        bool hasAnError(event *t_event) const;

        /**
         * @brief Checks if the given event is a server event.
         * @details This function checks if the given event is a server event.
         * @param t_event The event to check.
         * @return `true` if the event is a server event, `false` otherwise.
         * @version 1.0.0
         */
        bool isServerEvent(event *t_event) const;

        /**
         * @brief Checks if the given event is a client event.
         * @details This function checks if the given event is a client event.
         * @param t_event The event to check.
         * @return `true` if the event is a client event, `false` otherwise.
         * @version 1.0.0
         */
        bool isClientEvent(event *t_event) const;

        /**
         * @brief Retrieves the file descriptor of the client from the given event.
         * @details This function retrieves the file descriptor of the client from the given event.
         * @param t_event The event to retrieve the client file descriptor from.
         * @return The file descriptor of the client.
         * @version 1.0.0
         */
        fileDescriptor getClientFileDescriptor(const event *t_event) const;
    };
}  // namespace FBNetwork

#endif