# GameEngine Documentation

## Table of Contents
- [GameEngine Documentation](#gameengine-documentation)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Usage](#usage)
    - [GameEngine](#gameengine-1)
    - [Scenes](#scenes-1)
    - [Entities and Components](#entities-and-components-1)
    - [Systems](#systems-1)
    - [Example 1: Creating a Simple Game Entity](#example-1-creating-a-simple-game-entity)
    - [Example 2: Implementing a Custom System](#example-2-implementing-a-custom-system)
    - [Example 3: Scene Management](#example-3-scene-management)
- [Layers in Renderable Components](#layers-in-renderable-components)
  - [LayerType Class](#layertype-class)
    - [Public Methods](#public-methods)
    - [Private Members](#private-members)
  - [Example Usage](#example-usage)
  - [Recommendation](#recommendation)
    - [Entities and Components](#entities-and-components-2)
  - [Entities](#entities-1)
  - [Components](#components-1)
    - [Example Usage](#example-usage-1)
      - [Defining Components](#defining-components)
    - [Using Components](#using-components)
    - [Systems](#systems-2)
- [Systems in GameEngine](#systems-in-gameengine)
  - [ISystem Interface](#isystem-interface)
    - [Attributes](#attributes)
    - [Methods](#methods)
      - [update](#update)
    - [Example Usage](#example-usage-2)
  - [Recommendations:](#recommendations)
  - [Advanced Usage](#advanced-usage)
- [EventHandler](#eventhandler)

## Introduction

Welcome to the GameEngine documentation! This documentation provides comprehensive information on how to use our game engine to build interactive and engaging games.

## Usage

GameEngine provides a set of powerful features to help you develop games efficiently. Here's an overview of key concepts and components:

### GameEngine

The `GameEngine` class is the central component for managing entities, components, and systems in your game. It allows you to:

- **Manage Scenes**: 
  - Efficiently bind scenes to initialization functions and change scenes during game flow.

- **Handle Entities**: 
  - Create, delete, and retrieve entities, either individually or with attached components.

- **Bind Components**: 
  - Attach, detach, and fetch components to/from entities, providing flexibility in defining object behaviors and attributes.

- **Integrate Systems**: 
  - Seamlessly add, delete, or fetch game systems that implement the logic and interactions in your game.

### **Scenes**

Scenes help you organize different parts of your game. With the `GameEngine`, you can:

- **Bind Initialization Functions**: 
  - Associate a particular scene with its initialization function.

- **Change Active Scene**: 
  - Transition to a different scene at any point in the game.

### **Entities and Components**

Entities represent objects in your game, and components are the data associated with them. With the `ComponentsContainer`, you can:

- **Create Entities**: 
  - Instantiate new entities, either empty or with a set of initial components.

- **Delete Entities**: 
  - Remove entities that are no longer needed.

- **Bind Components to Entities**: 
  - Attach specific components to an entity to define its properties and behaviors.

- **Fetch Components**: 
  - Retrieve specific components or sets of components attached to entities.
  
### **Systems**

Systems are responsible for game logic. With the `GameEngine` and the `EventHandler`, you can:

- **Add Systems**: 
  - Register new game systems by name or by specifying their path.

- **Prioritize Systems**: 
  - Specify the execution priority of a system.

- **Delete Systems**: 
  - Remove a system when it's no longer required.
  - 
- **Bind to events**:
  - Bind a system to an event, so that it can react to it.

### Example Usage:

Here are some code examples to illustrate how to use GameEngine:

## **Example 1: Creating a Simple Game Entity**

```cpp
// Initializing the GameEngine
GameEngine::GameEngine engine;

// Creating a new entity
size_t entityID = engine.createEntity();

// Binding a component (e.g., Position) to the entity
engine.bindComponentToEntity(entityID, PositionComponentType, Position{5, 5});
```


## **Example 2: Implementing a Custom System**

```cpp
class RenderSystem : public ISystem {
    // Implement the system logic here
};

// Creating the system and adding to the engine
auto renderSystem = std::make_shared<RenderSystem>();
engine.addSystem("RenderSystem", renderSystem);
```

## **Example 3: Scene Management**

```cpp
// Binding a scene initialization function
engine.bindSceneInitiation("MainMenu", [](GameEngine::GameEngine& engine) {
    // Initialization logic for the main menu
});

// Changing to the main menu scene
engine.changeScene("MainMenu");
```

# Layers in Renderable Components

In graphical applications, managing the rendering order of visual elements is paramount. The concept of layers provides an efficient way to determine the sequence in which different elements, specifically renderable components like Text, Sprites, etc., are drawn on the screen. By associating these components with distinct layers, developers can dictate the z-order or sequence in which they are rendered.

The `LayerType` class facilitates this by generating and managing unique identifiers (IDs) for layers associated with these renderable components.

## LayerType Class

### Public Methods:

- **Constructor (`LayerType()`) and Destructor (`~LayerType()`):**
  - Responsible for the initialization and cleanup of resources tied to the `LayerType` class.

- **getNewLayerType():**
  - Produces and returns a new unique layer identifier for an unnamed renderable component.

- **getNewLayerType(std::string componentName):**
  - Creates and returns a unique layer ID tailored to the specified renderable component name (`componentName`).

- **getLayerType(std::string componentName):**
  - Retrieves the unique layer ID associated with a named renderable component.

### Private Members:

- **layerTypeCounter:**
  - A static counter ensuring that each layer ID remains distinct.

- **layerTypeMap:**
  - An unordered_map linking the names of renderable components to their individual layer IDs, enabling easy retrieval of named layers.

## Example Usage:

```cpp
// Assign a new layer for a Sprite component named "BackgroundSprite"
size_t backgroundSpriteLayer = GameEngine::LayerType::getNewLayerType("BackgroundSprite");

// Sprite component with a layer value
backgroundSprite.layer = backgroundSpriteLayer;

// Retrieve the layer ID for the named Sprite component
size_t fetchedLayer = GameEngine::LayerType::getLayerType("BackgroundSprite");

// Verify if the two IDs are identical (they should be)
if (backgroundSpriteLayer == fetchedLayer) {
    std::cout << "Layer IDs are consistent!" << std::endl;
}
```

With the LayerType class, it becomes straightforward to manage the rendering hierarchy of components like Text, Sprites, and other visual elements that can be layered.

## Recommendation:

- Layers can be utilized to manage game objects' rendering order and update priority. For instance, background elements can be placed on a background layer (drawn first), gameplay elements on a gameplay layer, and UI elements on a UI layer (drawn last). This way, the game's visual elements stack correctly on the screen.

### Entities and Components

- Entities and Components form the core of GameEngine's ECS architecture. The principle is to have entities represent game objects or actors, and components represent their data or behaviors. Systems then use these to define game logic.

## Entities

- Entities are unique identifiers for game objects in the game world, often represented as integers (like `size_t`). GameEngine's `ComponentContainer` provides methods to manage these entities.

- **createEntity**: Creates a new entity, optionally specifying its layer or initial components, and returns its ID.
  
- **deleteEntity**: Deletes an entity and its associated resources or components.

## Components

- In GameEngine, components derive from the `IComponent` interface and can be attached to entities. The `IComponent` interface has methods like:

- **getComponentType**: Provides a unique ID for the component type.

- For component type management, GameEngine offers the `ComponentsType` class to handle unique type IDs. The `ComponentsContainer` class in GameEngine also includes methods to work with component-entity bindings:

- **bindComponentToEntity**: Binds a component to an entity.
  
- **unbindComponentFromEntity**: Unbinds a component from an entity.

- **getComponents**: Fetches components of a specified type across entities.

- **getComponent**: Retrieves a specific component type from an entity.

- **getEntitiesWithComponent**: Lists entity IDs with a particular component type.

- **getComponentsFromEntity**: Gets all components bound to a given entity.

### Example Usage:

- Consider a game with spaceships that have "Position" and "Velocity" components.

#### Defining Components:

```cpp
namespace GameEngine {

class Position : public IComponent {
    float x, y;
    componentType = ComponentsType::getNewComponentType("Position");
    // Other methods...
    // Remaining implementation
};

class Velocity : public IComponent {
    float dx, dy;
    componentType = ComponentsType::getNewComponentType("Velocity");
    // Other methods...
    // Remaining implementation
};
} // namespace GameEngine
```

### Using Components:

```cpp
GameEngine::GameEngine engine;

// Creating a spaceship entity
size_t spaceshipID = engine.createEntity();

// Binding the components
engine.bindComponentToEntity(spaceshipID, ComponentsType::getNewComponentType("Position"), Position{0, 0});
engine.bindComponentToEntity(spaceshipID, ComponentsType::getNewComponentType("Velocity"), Velocity{2, 2});
```

- This structure allows for efficient management, scalability, and customization in GameEngine.

### Systems

- Systems are responsible for game logic. You can:

# Systems in GameEngine

- In the GameEngine, **systems** are responsible for processing game logic, especially the behavior of entities based on their associated components. The primary way to define a system's logic is through implementing the `ISystem` interface.

## ISystem Interface

- The `ISystem` interface serves as a blueprint for all the game systems within the GameEngine. Each system is expected to provide an implementation for the update method, which defines how the system processes and manipulates game entities.

### Attributes:

- There are no attributes or member variables explicitly defined in the `ISystem` interface. Systems are free to have their internal state if required, but it should be added in the derived classes.

### Methods:

#### update:

- **Description**: This method is called whenever the game developper specifies it or every frame if he added it using the 'addSystem' method from the GameEngine and is intended for updating game entities based on their components. When creating a custom system, you should override this method to define the specific behavior of that system.
- **Parameters**:
    - `componentsContainer`: This parameter is a class that allows you to interact with every entity actually present in the game, as well as the components attached to them. It is a map that associates each entity ID with a vector of optional components.
    - `eventHandler`: A shared pointer to the `EventHandler` class, allowing systems to react to or dispatch specific game events.
- **Return Type**: None. The update function alters the state of the game world and entities based on the system's logic but doesn't return any value.

### Example Usage:

If you want to create a movement system that updates the position of entities based on their velocity, your implementation might look like this:

```cpp
namespace GameEngine {
    class MovementSystem : public ISystem {
    public:
        void update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer, std::shared_ptr<EventHandler> eventHandler) override {
            // Iterate over all entities and update their positions based on velocity
            for (auto& [entityID, components] : componentsContainer) {
                // Retrieve the Position and Velocity components for each entity (assuming you have such components defined)
                // Modify them as needed
            }
        }
    };
} // namespace GameEngine
```

## Recommendations:

1. It's advisable to have a proper type-checking mechanism or a way to safely cast the `std::any` type to the expected component type within systems to avoid runtime errors.
  
2. Systems can also communicate or interact with other systems if needed. However, make sure to manage dependencies between systems carefully to avoid tight coupling and circular dependencies.

With this information, users of the GameEngine can better understand how to implement custom game systems and how they interact with entities and components.

## EventHandler

The `EventHandler` class is responsible for managing and processing events within the GameEngine namespace. It provides capabilities to register, queue, process, schedule, and trigger events.

### Public Member Functions

- **EventHandler()**: Default constructor for initializing the event handler.

- **~EventHandler()**: Destructor to handle necessary cleanup.

- **addEvent(const std::string& eventName, std::shared_ptr<ISystem> system)**: Register a system to respond to a particular event.

- **addEvent(const std::string& eventName, std::function<void()> function)**: Register a function callback to respond to a particular event.

- **addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems)**: Register multiple systems to respond to a particular event.

- **queueEvent(const std::string& eventName, const std::any& eventData = {})**: Queue an event for later processing, with optional data.

- **processEventQueue(ComponentsContainer& componentsContainer)**: Process the events queued up.

- **triggerEvent(const std::string& eventName, ComponentsContainer& componentsContainer)**: Immediately trigger and process an event.

- **deleteEvent(const std::string& eventName)**: Remove an event from the registry.

- **scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData = {}, size_t repeat = 0)**: Schedule an event to occur at a specified interval with optional data and repetitions.

- **unscheduleEvent(const std::string& eventName, const std::any& eventData = {})**: Remove a previously scheduled event.

- **updateScheduledEvents()**: Update the state of scheduled events.

- **getTriggeredEvent() const**: Retrieve the front-most event in the queue.

- **setContinuousEvent(const std::string& eventName, const std::string& continuousEventName, const std::any& eventData = {})**: Set an event as continuous, linking it with another event and its data.

- **removeContinuousEvent(const std::string& eventName)**: Remove a continuous event linkage.

### Example Usage

```cpp
// Create a system to handle the event
auto system = std::make_shared<GameEngine::MovementSystem>();

// Register the system to handle the event
eventHandler->addEvent("Move", system);

// Queue the event
eventHandler->queueEvent("Move");

// Schedule the event to occur every 5 ticks
eventHandler->scheduleEvent("Move", 5);

// Schedule the event to occur every 5 ticks, 3 times

eventHandler->scheduleEvent("Move", 5, {}, 3);

// Send data with the event
eventHandler->queueEvent("Move", 5, {1, 2, 3});

// Get the event that was triggered (Works only in a system called by the event handler)
auto [eventName, eventData] = eventHandler->getTriggeredEvent();
-> eventName = "Move"
-> eventData = {1, 2, 3}

// The system will now be called when the event is processed
```

In summary, the `EventHandler` class provides a robust mechanism for managing events in the GameEngine.

---

Thank you for choosing GameEngine! If you have any questions or need assistance, please [contact us](mailto:theophilus.homawoo@epitech.eu).


