# FBNetwork

FBNetwork is a C++ network library that provides simple TCP client and server implementations with event queue integration. It is ideal as a foundation for your own network-based applications or to extend existing projects with network functionality.

---

## 🚀 Features

- Simple TCP client and server classes
- Event-driven communication via EventQueue
- Modular architecture
- Extendable with optional MySQL integration

---

## 📁 Project Structure

```bash
FBNetwork/
├── include/
│   ├── client.h           # TCP Client Class
│   ├── server.h           # TCP Server Class
│   ├── eventQueue.h       # Event Management
│   ├── extendedSystem.h   # Platform-dependent extensions
│   └── mySQL.h            # (Optional) MySQL Database Integration
├── src/
│   ├── client.cpp
│   ├── server.cpp
│   ├── eventQueue.cpp
│   ├── extendedSystem.cpp
│   └── mySQL.cpp
```

---

## 🛠️ Installation

```bash
git clone https://github.com/Felix-Brodmann/FBNetwork.git
cd FBNetwork
mkdir build && cd build
cmake ..
make
```

Note: For MySQL functionality, `libmysqlclient` is required.

---

## 📚 Example: TCP Server

```cpp
#include "server.hpp"

int main() {
    try
    {
        FBNetwork::Server server(Domain::IPV4_DOMAIN, 12345, 20);  // IPv4, Port 12345 and max 20 connections
        server.startServer();  // Start the server
        server.startListening();  // Start listening for incoming connections
        int clientID = server.acceptClient();  // Accept a client connection in a blocking manner
        std::cout << "Client connected with ID: " << clientID << " and IP: " << server.getClientIpAddress(clientID) << std::endl;
        server.readTillXData(clientID, "\r\n");  // Read data until a specific delimiter
        std::cout << "Received data from client: " << server.getData(clientID) << std::endl;
        server.sendData(clientID, "Hello from server!");  // Send data to the client
        server.closeClient(clientID);  // Close the client connection
        server.stopServer();  // Stop the server
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

---

## 🙌 Contribute

Pull requests and suggestions for improvement are always welcome!

---

## 📄 License

FBNetwork © 2025 by Felix Brodmann is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International 
