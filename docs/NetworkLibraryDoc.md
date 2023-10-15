# Network Library

The Network Library is a robust networking library based on Boost::Asio utilizing the UDP protocol.
It's designed for turn-key network implementation, supporting any protocol including Binary and Text.
The library features built-in algorithms for packet retransmission on loss and packet reordering.

## Usage

The Network Library is designed to facilitate both client and server-side networking.
Below are examples and explanations categorized based on the client-side, server-side, and common usage.

## Shared Usage

The core element shared across the client and server in the Network Library is the handling of messages. Messages are encapsulated in classes that inherit from the `IMessage` interface. Below is an example demonstrating how to create a custom message type by extending `AMessage`.
### Creating Custom Message Types


To create a custom message type, you can either extend `IMessage` and implement its methods, or extend `AMessage` which already provides a basic implementation of `IMessage`.

Here's an example of creating a custom message type by extending `AMessage`:



```c++
namespace Network {

    class Message : public AMessage {

    public:

        Message(args ...);
        Message(std::vector<std::uint8_t> &message);
        ~Message() override = default;

        // ... other methods and fields

    private:
        // ... implementation details
    };
}
```


In this example, a new class `Message` is created that extends `AMessage`.
The `Message` class constructor takes several parameters that are specific to this custom message type.
It provides additional methods and fields that allow for more specific message handling according to your custom protocol.


Once created, instances of the `Message` class will be transported within the library as `IMessage` instances, allowing for a consistent message handling mechanism while accommodating different message types tailored to your specific protocol needs.


This way, you can create custom message types tailored to your specific protocol needs, while utilizing the common message handling infrastructure provided by the Network Library.

### OwnedMessage

In the Network Library, `OwnedMessage` is a utility structure that associates a message with the identifier of the sender. This pairing is useful for tracking who sent a particular message, which can be crucial in client-server interactions.

The `OwnedMessage` structure contains two main elements:

- `remote`: A numeric identifier representing the sender of the message.
- `message`: A reference to the message itself, encapsulated as an `IMessage`.

Thus, when a message is received, it is placed into an `OwnedMessage` instance along with the identifier of the sender, allowing for further processing of the message in the context of who sent it. This structure facilitates the handling of incoming messages in a way that associates each message with its sender.


### Client-Side Usage

The `Client` class is designed as a singleton, ensuring that only one instance of the `Client` class is created throughout the lifespan of the application. Below are the steps and examples on how to instantiate and use the `Client` class.

   1. **Initialization:**
     - First, initialize the `Client` class using the `init` method. The `init` method takes two arguments:
     - `tick`: The tick rate in milliseconds.
     - `forwardQueue`: A reference to a thread-safe queue for forwarding messages.

      ```c++
      #include "Client.hpp"
      #include "TSQueue.hpp"
    
      Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
      Network::Client::init(128, queue);
      ```

   2. **Getting the Client Instance:**
   - The `Client` class is a singleton, so the instance can be retrieved using the `getInstance` method.
     ```c++
     #include "Client.hpp"
    
      Network::Client& client = Network::Client::getInstance();
     ```

   3. **Connecting to a Server:**
       - Use the connect method to connect to a server by specifying the host and port.
       ```c++
       #include "Endpoint.hpp"
       #include "Client.hpp"
        
       Network::Endpoint endpoint("127.0.0.1", 4444);
       Network::Client& client = Network::Client::getInstance();
       client.connect(endpoint);
       ```

   4. **Sending Messages:**

      - Use the send method to send [messages](#creating-custom-message-types) to the server.
      ```c++
       #include "Client.hpp"
       #include "Message.hpp"
        
           std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>(args ...);
           Network::Client& client = Network::Client::getInstance();
           client.send(message);
      ```
   5. **Receiving Messages:**
       - Use the `receive` method to receive messages from the server.
       ```c++
       #include "Client.hpp"
       #include "TSQueue.hpp"
       
       // Create a thread-safe queue to hold received messages
       Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> messageQueue;
    
       // Initialize the client
       Network::Client::init(10, messageQueue);
    
       // Get the singleton instance of the client
       Network::Client& client = Network::Client::getInstance();
      ```

      In this code:
    
      - A thread-safe queue named `messageQueue` is created to hold received messages.
      - The init method is called on Network::Client, passing in a `tick rate` of 10 and a reference to `messageQueue`.
      - The `getInstance` method is called on Network::Client to obtain the singleton instance of the client.      
    
      Now, whenever the client receives a message, the message is *automatically* unpacked and placed in `messageQueue` as an [OwnedMessage](#ownedmessage) object.
      You can then process the messages from the queue in your application code.
    
   ```c++
   // Example: Processing received messages
   while (!messageQueue.empty()) {
       auto ownedMessage = messageQueue.front();
       messageQueue.pop();
    
       // Process the ownedMessage...
   }
   ```
   This mechanism allows for efficient and automatic handling of incoming messages, making it easier to focus on the logic of processing the messages rather than the intricacies of message reception and unpacking.

       
### Server Usage

1. **Initialization:**  
   To initialize a server instance, use the static `init` method, specifying the port, maximum number of clients, tick rate, and a reference to a queue for forwarding messages.
    
    ```c++
    #include "Server.hpp"
    #include "TSQueue.hpp"
     
    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> forwardQueue;
    Network::Server::init(4444, 100, 1000, forwardQueue);
    Network::Server& server = Network::Server::getInstance();
    ```

2. **Getting the Server Instance:**

    The `Server` class is a singleton, so the instance can be retrieved using the `getInstance` method.

    ```c++
    #include "Server.hpp"
    
    Network::Server& server = Network::Server::getInstance();
    ```

3. **Starting and Stopping the Server:**

    Once initialized, you can start and stop the server using the start and stop methods respectively.

    ```c++
    #include "Server.hpp"
        
    Network::Server& server = Network::Server::getInstance();
    server.start();
    // ... server is now running
    server.stop();
    // ... server is now stopped
    ```
4. **Sending Messages:**

    You can send messages to clients using various methods provided by the `Network::Server` class:
       - `sendClient` sends a message to a specific client.
       - `sendAllClients` sends a message to all connected clients.
       - `sendAllClientsExcept` sends a message to all connected clients except for a specified client.
       - `sendClients` sends a message to a list of specified clients.

    ```c++
    #include "Server.hpp"
    #include "IMessage.hpp"
    
    Network::Server& server = Network::Server::getInstance();
   
    std::shared_ptr<Network::IMessage> message = ...;
    server.sendClient(1, message);  // send to client with ID 1
    server.sendAllClients(message);  // send to all clients
    server.sendAllClientsExcept(1, message);  // send to all except client with ID 1
    server.sendClients({1, 2, 3}, message);  // send to clients with IDs 1, 2, and 3
    ```

5. **Receiving Messages:**

    Messages received from clients will be placed into the forwardQueue specified during initialization. You can process these messages from the queue in your application code.
    
    ```c++
    // Example: Processing received messages
    while (!forwardQueue.empty()) {
        auto ownedMessage = forwardQueue.front();
        forwardQueue.pop();
       // Process the ownedMessage...
    }
    ```
    
    This mechanism allows for efficient and automatic handling of incoming messages, making it easier to focus on the logic of processing the messages rather than the intricacies of message reception and unpacking.

6. ** Managing Clients:** 

    The Network::Server class provides methods for disconnecting clients and retrieving lists of connected and disconnected clients.

    ```c++
    #include "Server.hpp"
    
    Network::Server& server = Network::Server::getInstance();
    server.disconnectClient(1);  // disconnect client with ID 1
    Network::TSQueue<unsigned int>& connectedClients = server.getConnectedClients();
    Network::TSQueue<unsigned int>& disconnectedClients = server.getDisconnectedClients();
    ```

## Acknowledgments

The author extends heartfelt gratitude towards the individuals and organizations who have played a pivotal role in the development and review of this protocol specification. Special acknowledgments are directed towards EPITECH, and all members of the THCB Company for their invaluable insights and unwavering support.

## Author's Address

Clément LAGASSE  
THCB Company  
Email: clement.lagasse@epitech.eu

