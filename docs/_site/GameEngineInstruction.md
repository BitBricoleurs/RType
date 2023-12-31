# GameEngine Documentation

## Table of Contents
- [GameEngine Documentation](#gameengine-documentation)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
 - [Usage](#usage)
    - [Registry](#registry)
    - [**Scenes**](#scenes)
    - [**Entities and Components**](#entities-and-components)
    - [**Systems**](#systems)
    - [Example Usage:](#example-usage)
  - [**Example 1: Creating a Simple Game Entity**](#example-1-creating-a-simple-game-entity)
  - [**Example 2: Implementing a Custom System**](#example-2-implementing-a-custom-system)
  - [**Example 3: Scene Management**](#example-3-scene-management)
- [Layers in Renderable Components](#layers-in-renderable-components)
  - [LayerType Class](#layertype-class)
    - [Public Methods:](#public-methods)
    - [Private Members:](#private-members)
  - [Example Usage:](#example-usage-1)
  - [Recommendation:](#recommendation)
    - [Entities and Components](#entities-and-components-1)
  - [Entities](#entities)
  - [Components](#components)
    - [Example Usage:](#example-usage-2)
      - [Defining Components:](#defining-components)
    - [Using Components:](#using-components)
    - [Systems](#systems-1)
- [Systems in GameEngine](#systems-in-gameengine)
  - [ISystem Interface](#isystem-interface)
    - [Attributes:](#attributes)
    - [Methods:](#methods)
      - [update:](#update)
    - [Example Usage:](#example-usage-3)
  - [Recommendations:](#recommendations)
  - [Advanced Usage](#advanced-usage)
  - [API Reference](#api-reference)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction

Welcome to the GameEngine documentation! This documentation provides comprehensive information on how to use our game engine to build interactive and engaging games.

## Usage

GameEngine provides a set of powerful features to help you develop games efficiently. Here's an overview of key concepts and components:

### Registry

The `Registry` class is the central component for managing entities, components, and systems in your game. It allows you to:

- **Manage Scenes**: 
  - Efficiently bind scenes to initialization functions and change scenes during game flow.

- **Handle Entities**: 
  - Create, delete, and retrieve entities, either individually or with attached components.

- **Bind Components**: 
  - Attach, detach, and fetch components to/from entities, providing flexibility in defining object behaviors and attributes.

- **Integrate Systems**: 
  - Seamlessly add, delete, or fetch game systems that implement the logic and interactions in your game.

### **Scenes**

Scenes help you organize different parts of your game. With the `Registry`, you can:

- **Bind Initialization Functions**: 
  - Associate a particular scene with its initialization function.

- **Change Active Scene**: 
  - Transition to a different scene at any point in the game.

### **Entities and Components**

Entities represent objects in your game, and components are the data associated with them. With the `Registry`, you can:

- **Create Entities**: 
  - Instantiate new entities, either empty or with a set of initial components.

- **Delete Entities**: 
  - Remove entities that are no longer needed.

- **Bind Components to Entities**: 
  - Attach specific components to an entity to define its properties and behaviors.

- **Fetch Components**: 
  - Retrieve specific components or sets of components attached to entities.
  
### **Systems**

Systems are responsible for game logic. With the `Registry`, you can:

- **Add Systems**: 
  - Register new game systems by name or by specifying their path.

- **Prioritize Systems**: 
  - Specify the execution priority of a system.

- **Delete Systems**: 
  - Remove a system when it's no longer required.

### Example Usage:

Here are some code examples to illustrate how to use GameEngine:

## **Example 1: Creating a Simple Game Entity**

```cpp
// Initializing the Registry
GameEngine::Registry registry;

// Creating a new entity
size_t entityID = registry.createEntity();

// Binding a component (e.g., Position) to the entity
registry.bindComponentToEntity(entityID, PositionComponentType, Position{5, 5});
```


## **Example 2: Implementing a Custom System**

```cpp
class RenderSystem : public ISystem {
    // Implement the system logic here
};

// Creating the system and adding to the registry
auto renderSystem = std::make_shared<RenderSystem>();
registry.addSystem("RenderSystem", renderSystem);
```

## **Example 3: Scene Management**

```cpp
// Binding a scene initialization function
registry.bindSceneInitiation("MainMenu", [](GameEngine::Registry& reg) {
    // Initialization logic for the main menu
});

// Changing to the main menu scene
registry.changeScene("MainMenu");
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

- Entities are unique identifiers for game objects in the game world, often represented as integers (like `size_t`). GameEngine's `Registry` provides methods to manage these entities.

- **createEntity**: Creates a new entity, optionally specifying its layer or initial components, and returns its ID.
  
- **deleteEntity**: Deletes an entity and its associated resources or components.

## Components

- In GameEngine, components derive from the `IComponent` interface and can be attached to entities. The `IComponent` interface has methods like:

- **getComponentType**: Provides a unique ID for the component type.
  
- **incrementBindedEntities**: Increases the count of entities a component is bound to.

- **decrementBindedEntities**: Decreases the entity count the component is bound to.

- **getBindedEntities**: Shows how many entities a component is bound to.

- For component type management, GameEngine offers the `ComponentsType` class to handle unique type IDs. The `Registry` class in GameEngine also includes methods to work with component-entity bindings:

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
GameEngine::Registry registry;

// Creating a spaceship entity
size_t spaceshipID = registry.createEntity();

// Binding the components
registry.bindComponentToEntity(spaceshipID, ComponentsType::getNewComponentType("Position"), Position{0, 0});
registry.bindComponentToEntity(spaceshipID, ComponentsType::getNewComponentType("Velocity"), Velocity{2, 2});
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

- **Description**: This method is called whenever the game developper specifies it or every frame by default and is intended for updating game entities based on their components. When creating a custom system, you should override this method to define the specific behavior of that system.
- **Parameters**:
    - `componentsContainer`: This parameter is an unordered map where each key represents an entity's unique ID, and the associated value is a vector of optional components. The optional `std::any` type allows for flexibility, meaning that systems can process different types of components without knowing their exact type at compile time. This design choice promotes a decoupled and extensible architecture.
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

---

Thank you for choosing GameEngine! If you have any questions or need assistance, please [contact us](mailto:your@email.com).


