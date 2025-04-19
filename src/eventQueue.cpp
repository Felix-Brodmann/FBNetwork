#include "../include/eventQueue.hpp"

void FBNetwork::EventQueue::setEventQueueFileDescriptor(const FBNetwork::fileDescriptor t_kqueueFileDescriptor)
{
    m_eventQueueFileDescriptor = t_kqueueFileDescriptor;
}

void FBNetwork::EventQueue::setServerFileDescriptor(const FBNetwork::fileDescriptor t_serverFileDescriptor)
{
    if (t_serverFileDescriptor < 0)
    {
        throw InvalidArgumentException("The server file descriptor is invalid.");
    }
    m_serverFileDescriptor = t_serverFileDescriptor;
}

const FBNetwork::fileDescriptor FBNetwork::EventQueue::getEventQueueFileDescriptor() const
{
    std::shared_lock<std::shared_mutex> lock(m_eventQueueFileDescriptorMutex);
    return m_eventQueueFileDescriptor;
}

const FBNetwork::fileDescriptor FBNetwork::EventQueue::getServerFileDescriptor() const
{
    std::shared_lock<std::shared_mutex> lock(m_serverFileDescriptorMutex);
    return m_serverFileDescriptor;
}

#ifdef __APPLE__

FBNetwork::EventQueue::EventQueue()
{
    fileDescriptor eventQueueFileDescriptor = kqueue();
    if (eventQueueFileDescriptor < 0)
    {
        throw ServerRuntimeException("Creating the event queue file descriptor failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    setEventQueueFileDescriptor(eventQueueFileDescriptor);
}

FBNetwork::EventQueue::~EventQueue()
{
    close(getEventQueueFileDescriptor());
}

void FBNetwork::EventQueue::setServer(const FBNetwork::fileDescriptor t_serverFileDescriptor)
{
    try
    {
        setServerFileDescriptor(t_serverFileDescriptor);
    }
    catch (InvalidArgumentException &e)
    {
        throw e;
    }
    event event;
    EV_SET(&event, getServerFileDescriptor(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(getEventQueueFileDescriptor(), &event, 1, NULL, 0, NULL) == -1)
    {
        throw ServerRuntimeException("Adding the event to the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::EventQueue::addClient(const FBNetwork::fileDescriptor t_clientFileDescriptor)
{
    event event;
    EV_SET(&event, t_clientFileDescriptor, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(getEventQueueFileDescriptor(), &event, 1, NULL, 0, NULL) == -1)
    {
        throw ServerRuntimeException("Adding the event to the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::EventQueue::removeClient(const FBNetwork::fileDescriptor t_clientFileDescriptor)
{
    event event;
    EV_SET(&event, t_clientFileDescriptor, EVFILT_READ, EV_DELETE, 0, 0, NULL);

    if (kevent(getEventQueueFileDescriptor(), &event, 1, NULL, 0, NULL) == -1 && errno != ENOENT)
    {
        throw ServerRuntimeException("Removing the event from the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

FBNetwork::eventList FBNetwork::EventQueue::pollEvents()
{
    std::vector<event> events(Constants::MAX_EVENTS);
    int                count = kevent(getEventQueueFileDescriptor(), NULL, 0, events.data(), Constants::MAX_EVENTS, NULL);
    if (count == Constants::EVENT_ERROR)
    {
        throw ServerRuntimeException("Retrieving the events from the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    events.resize(count);
    std::vector<event> filteredEvents;
    for (const auto &ev : events)
    {
        if (ev.ident > 2)
        {
            filteredEvents.push_back(ev);
        }
        else
        {
            event removedEvent;
            removedEvent.ident  = ev.ident;
            removedEvent.filter = 0;
            if (kevent(getEventQueueFileDescriptor(), &removedEvent, 1, NULL, 0, NULL) == -1)
            {
                if (errno != ENOENT)
                {
                    throw ServerRuntimeException("Removing the event from the event queue failed. Error: " +
                                                 ExtendedSystem::getCurrentErrnoError());
                }
            }
        }
    }
    return filteredEvents;
}

FBNetwork::eventList FBNetwork::EventQueue::pollEvents(const int t_timeout)
{
    struct timespec timeout;
    timeout.tv_sec  = t_timeout / 1000;
    timeout.tv_nsec = (t_timeout % 1000) * 1000000;
    std::vector<event> events;
    events.reserve(Constants::MAX_EVENTS);
    int count = kevent(getEventQueueFileDescriptor(), NULL, 0, events.data(), Constants::MAX_EVENTS, &timeout);
    if (count == Constants::EVENT_ERROR)
    {
        throw ServerRuntimeException("Retrieving the events from the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    else if (count == 0)
    {
        throw ServerTimeoutException("Timeout reached while polling the events.");
    }
    events.resize(count);
    std::vector<event> filteredEvents;
    for (const auto &ev : events)
    {
        if (ev.ident > 2)
        {
            filteredEvents.push_back(ev);
        }
        else
        {
            event removedEvent;
            removedEvent.ident  = ev.ident;
            removedEvent.filter = 0;
            if (kevent(getEventQueueFileDescriptor(), &removedEvent, 1, NULL, 0, NULL) == -1)
            {
                if (errno != ENOENT)
                {
                    throw ServerRuntimeException("Removing the event from the event queue failed. Error: " +
                                                 ExtendedSystem::getCurrentErrnoError());
                }
            }
        }
    }
    return filteredEvents;
}

bool FBNetwork::EventQueue::hasAnError(event *t_event) const
{
    return (t_event->flags & EV_ERROR) != 0;
}

bool FBNetwork::EventQueue::isServerEvent(event *t_event) const
{
    return t_event->ident == getServerFileDescriptor();
}

bool FBNetwork::EventQueue::isClientEvent(event *t_event) const
{
    return t_event->ident != getServerFileDescriptor();
}

FBNetwork::fileDescriptor FBNetwork::EventQueue::getClientFileDescriptor(const event *t_event) const
{
    return t_event->ident;
}

#else

FBNetwork::EventQueue::EventQueue()
{
    fileDescriptor eventQueueFileDescriptor = epoll_create1(0);
    if (eventQueueFileDescriptor < 0)
    {
        throw ServerRuntimeException("Creating the event queue file descriptor failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
    setEventQueueFileDescriptor(eventQueueFileDescriptor);
}

FBNetwork::EventQueue::~EventQueue()
{
    close(getEventQueueFileDescriptor());
}

void FBNetwork::EventQueue::setServer(const FBNetwork::fileDescriptor t_serverFileDescriptor)
{
    try
    {
        setServerFileDescriptor(t_serverFileDescriptor);
    }
    catch (InvalidArgumentException &e)
    {
        throw e;
    }
    event event;
    event.events  = EPOLLIN;
    event.data.fd = getServerFileDescriptor();
    if (epoll_ctl(getEventQueueFileDescriptor(), EPOLL_CTL_ADD, getServerFileDescriptor(), &event) == -1)
    {
        throw ServerRuntimeException("Adding the event to the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::EventQueue::addClient(const FBNetwork::fileDescriptor t_clientFileDescriptor)
{
    event event;
    event.events  = EPOLLIN;
    event.data.fd = t_clientFileDescriptor;
    if (epoll_ctl(getEventQueueFileDescriptor(), EPOLL_CTL_ADD, t_clientFileDescriptor, &event) == -1)
    {
        throw ServerRuntimeException("Adding the event to the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

void FBNetwork::EventQueue::removeClient(const FBNetwork::fileDescriptor t_clientFileDescriptor)
{
    if (epoll_ctl(getEventQueueFileDescriptor(), EPOLL_CTL_DEL, t_clientFileDescriptor, NULL) == -1 && errno != ENOENT)
    {
        throw ServerRuntimeException("Removing the event from the event queue failed. Error: " + ExtendedSystem::getCurrentErrnoError());
    }
}

FBNetwork::eventList FBNetwork::EventQueue::pollEvents()
{
    while (true)
    {
        std::vector<event> events(Constants::MAX_EVENTS);
        int                count = epoll_wait(getEventQueueFileDescriptor(), events.data(), Constants::MAX_EVENTS, -1);
        events.resize(count);
        if (count == Constants::EVENT_ERROR)
        {
            throw ServerRuntimeException("Retrieving the events from the event queue failed. Error: " +
                                         ExtendedSystem::getCurrentErrnoError());
        }
        std::vector<event> filteredEvents;
        for (const auto &ev : events)
        {
            if (ev.data.fd > 2)
            {
                filteredEvents.push_back(ev);
            }
            else
            {
                event removedEvent;
                removedEvent.data.fd = ev.data.fd;
                removedEvent.events  = 0;
                if (epoll_ctl(getEventQueueFileDescriptor(), EPOLL_CTL_DEL, ev.data.fd, &removedEvent) == -1)
                {
                    if (errno != ENOENT)
                    {
                        throw ServerRuntimeException("Removing the event from the event queue failed. Error: " +
                                                     ExtendedSystem::getCurrentErrnoError());
                    }
                }
            }
        }
        if (!filteredEvents.empty())
        {
            return filteredEvents;
        }
    }
}

FBNetwork::eventList FBNetwork::EventQueue::pollEvents(const int t_timeout)
{
    auto               now     = std::chrono::steady_clock::now();
    auto               timeout = now + std::chrono::milliseconds(t_timeout);
    std::vector<event> filteredEvents;
    while (now < timeout)
    {
        std::vector<event> events(Constants::MAX_EVENTS);
        int                remainingTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeout - now).count();
        int                count         = epoll_wait(getEventQueueFileDescriptor(), events.data(), Constants::MAX_EVENTS, remainingTime);
        events.resize(count);
        if (count == Constants::EVENT_ERROR)
        {
            throw ServerRuntimeException("Retrieving the events from the event queue failed. Error: " +
                                         ExtendedSystem::getCurrentErrnoError());
        }
        else if (remainingTime <= 0)
        {
            return events;
        }
        filteredEvents.clear();
        filteredEvents.reserve(count);
        for (const auto &ev : events)
        {
            if (ev.data.fd > 2)
            {
                filteredEvents.push_back(ev);
            }
        }
        now = std::chrono::steady_clock::now();
    }
    return filteredEvents;
}

bool FBNetwork::EventQueue::hasAnError(event *t_event) const
{
    return (t_event->events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) != 0;
}

bool FBNetwork::EventQueue::isServerEvent(event *t_event) const
{
    return t_event->data.fd == m_serverFileDescriptor;
}

bool FBNetwork::EventQueue::isClientEvent(event *t_event) const
{
    return t_event->data.fd != m_serverFileDescriptor;
}

FBNetwork::fileDescriptor FBNetwork::EventQueue::getClientFileDescriptor(const event *t_event) const
{
    return t_event->data.fd;
}

#endif