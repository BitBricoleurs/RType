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
- [RenderEngine Documentation](#renderengine-documentation)
- [PhysicsEngine Documentation](#physicsengine-documentation)
- [LuaScriptingEngine Documentation](#luascriptingengine-documentation)



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

# LuaScriptingEngine Documentation
## Overview

The LuaScriptingEngine is an integral part of the game engine, designed to facilitate scripting capabilities within the game. It provides the ability to run Lua scripts, allowing for dynamic and flexible game behavior. Integration with Lua is achieved through LuaBridge, a library that connects C++ code with Lua without the need for external dependencies.
Scripting Engine Essentials

The engine initializes and manages the Lua state, enabling the execution of Lua scripts and providing an interface for C++ functions to be called from Lua.
Exposing Game Systems to Lua

For game systems, such as the RenderEngineCinematicSystem, to be controlled via Lua, they must be registered within the Lua environment. This is done succinctly through LuaBridge with minimal code. For example:

```cpp 

void registerCinematicSystemWithLua(lua_State* L) {
// LuaBridge namespace and class registration omitted for brevity
}
```
The details of class methods and their usage in Lua are streamlined in the documentation, providing just enough information for developers to understand how to implement and use the exposed classes.
Using the LuaScriptingEngine

With the LuaScriptingEngine, Lua scripts can instantiate and interact with C++ systems, such as initiating and ending cinematic sequences through the RenderEngineCinematicSystem:

```lua

local cinematicSystem = RenderEngine.RenderEngineCinematicSystem()
cinematicSystem:loadJSON('path/to/cinematic.json')
cinematicSystem:playCinematic()
-- ... Other interactions ...
```
# Conclusion

By leveraging the LuaScriptingEngine, developers can script complex game behaviors and interactions, such as cinematic sequences, enriching the gaming experience with ease and flexibility. The engine's integration with LuaBridge ensures a seamless bridge between C++ and Lua, simplifying the scripting process within the game's architecture.

# PhysicsEngine Documentation

## Table of Contents
- [PhysicsEngine Documentation](#physicsengine-documentation)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [PhysicsEngineMovementSystem2D](#physicsenginemovementsystem2d)
    - [Initialization](#initialization)
    - [Update Method](#update-method)
  - [PhysicsEngine](#physicsengine)
    - [Broad Phase Collision Detection](#broad-phase-collision-detection)
    - [Narrow Phase Collision Detection](#narrow-phase-collision-detection)
    - [Object Movement](#object-movement)
    - [Gravity Application](#gravity-application)
    - [Jump Force Application](#jump-force-application)
  - [Examples](#examples)
    - [Applying Gravity](#applying-gravity)
    - [Executing a Jump](#executing-a-jump)

## Introduction
The `PhysicsEngine` is an entity-component system (ECS)-based module designed to handle physics simulation for 2D games. It manages movement, collision detection, and other physics-related functionalities for game entities.

## Features
- Efficient collision detection system that distinguishes between broad and narrow phase checks.
- Support for Axis-Aligned Bounding Box (AABB) components for spatial queries and collision responses.
- Movement system that updates entity positions based on velocity and applies constraints based on movement limits.
- Gravity and jump mechanics that affect the velocity of entities with respective components.

## PhysicsEngineMovementSystem2D

### Initialization
When the `PhysicsEngineMovementSystem2D` is initialized, it creates a new instance of the `PhysicsEngine`.

### Update Method
This method processes entities that have a `MovementComponent2D` and updates their positions. It also handles movement constraints and updates AABBs for collision detection.

## PhysicsEngine

### Broad Phase Collision Detection
The `broadPhase` method is a quick check to determine if two entities could potentially collide, using their AABB components.

### Narrow Phase Collision Detection
The `narrowPhase` method performs a detailed check between two colliders to determine if a collision has occurred.

### Object Movement
The `moveObject` method updates the position of an entity based on its velocity.

### Gravity Application
The `applyGravity` method applies a gravity force to the velocity component of an entity, influenced by its weight and the time elapsed.

### Jump Force Application
The `applyJumpForce` method sets the upward velocity for an entity, simulating a jump.

## Examples

### Applying Gravity
```cpp
VelocityComponent velocityComponent;
Utils::Vect2 gravity(0, -9.81);
float weight = 1.0f;
float fallTime = 1.0f;

// Applying gravity to the velocity component
physicsEngine.applyGravity(velocityComponent, gravity, weight, fallTime);
```
Executing a Jump

```cpp

VelocityComponent velocityComponent;
float jumpSpeed = 5.0f;

// Applying jump force to the velocity component
physicsEngine.applyJumpForce(velocityComponent, jumpSpeed);
```
This documentation serves as a developer's guide for utilizing the Physics Engine's capabilities in a 2D game environment. It provides an overview of the system, outlines its key features, and gives examples of how to use the main functionalities provided by the engine.

vbnet


This documentation serves as a concise guide to the Physics Engine, providing developers with the necessary information to understand and utilize the engine's capabilities within their games.

# Physics Engine Documentation

## Introduction
The Physics Engine provides a comprehensive suite of components and systems to simulate 2D physics in a game environment. It utilizes an Entity Component System (ECS) architecture for modularity and flexibility.

## Components

### AABBComponent2D
Defines the axis-aligned bounding box for an entity, used in broad-phase collision detection.

### Collider Components
- `CircleColliderComponent2D`: Defines a circular area for collision detection.
- `RectangleColliderComponent2D`: Defines a rectangular area for collision detection.
- `PolygonColliderComponent2D`: Defines a polygonal area for collision detection.

### GravityComponent
Specifies the gravitational force applied to an entity.

### JumpComponent
Enables an entity to perform jump actions with specified force.

### Movement Components
- `MovementComponent2D`: Handles the 2D movement logic for an entity.
- `MovementLimits`: Sets boundaries for an entity's movement.

### VelocityComponent
Stores the current velocity of an entity, used for movement and collision response.

## Systems

### Collision System
Determines if entities collide with each other using the `PhysicsEngineCollisionSystem2D`.

### Gravity System
Applies gravity to entities with `GravityComponent` using the `PhysicsEngineGravitySystem`.

### Jump System
Manages the jump actions for entities with `JumpComponent` using the `PhysicsEngineJumpSystem`.

### Movement System
Updates the positions of entities based on their velocities and movement constraints in the `PhysicsEngineMovementSystem2D`.

### Update Hitboxes System
Updates the hitbox dimensions for entities based on their collider components using the `PhysicsEngineUpdateHitboxes`.

## PhysicsEngine Class
The `PhysicsEngine` class is the core of the physics simulation, providing methods for object movement, collision checks, gravity application, and jump force application.

# Render Engine Documentation

## Introduction
The Render Engine is responsible for drawing all visual components on the screen and handling user input events. It uses `raylib` for rendering and supports different types of drawable components.

## Components

### AnimationComponent
Defines animation states and frames for entities that have animated graphics.

### ButtonComponent
Represents a clickable button, handling its state and appearance.

### CinematicComponent
Manages cinematic sequences, including transitions and timed events.

### TextComponent
Handles the rendering of text elements on the screen, with support for different fonts and styles.

### SpriteComponent
Controls the rendering of static and animated sprites.

## Systems

### Animation System
Updates and plays entity animations based on the current state and animation frames.

### Cinematic System
Controls the flow and display of cinematic sequences.

## RenderEngine Class

### Initialization
`Initialize`: Sets up the rendering window and initializes necessary properties.

### Drawing Components
`Draw`: Overloaded functions for drawing text, sprites, and buttons.

### Polling Events
`PollEvents`: Checks for user input and updates the event handler accordingly.

### Shutdown
`Shutdown`: Cleans up resources and closes the rendering window.

## Resource Management

### ResourceManager
Handles the loading and management of assets such as textures, fonts, and sounds.

## Key Mapping and Events

### KeyMapping
Maps keyboard inputs to specific events in the game, facilitating input handling.

## Initialization and Shutdown

### Initialize
Sets up the window, context, and any initial settings required for rendering.

### Shutdown
Properly closes and cleans up the rendering context and any allocated resources.

## Drawing Components

### Draw Methods
Each component type has a specific `Draw` method tailored to render it according to its properties.

## Polling Events

### PollEvents
Processes user input, updating the state based on key presses and translating them into game events.

## Utility Functions

### Screen Dimensions
`getScreenWidth` and `getScreenHeight` provide access to the current window dimensions.




