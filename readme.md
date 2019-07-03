# Codename TE

The purpose of this project is **NOT** to develop a game but instead to develop an **Engine** in SFML while learning to make games. 

With each additional Iteration/Phase of the Game/Project newer systems/managers will be added to the engine till we have a decent engine that can be robustly be used to develop games both simple and complex.

# Overall System Goal
    
    The below given goals are likely to change over the course of its development.  
    Currently it is just a rough outline of what comes to my mind.

- Game Manager
- State Manager
- Resource Manager
- Input Manager
- Scene Manager
- Entity Manager
- Component Manager
- Animation System

# **Phase 1**
- [x] Goal is to create a character that can be controlled by input.

### REQUIREMENTS
- [x] Game System
- [x] Resource Manager
  - [x] Textures
- [x] Input Manager
  - [x] Multiple keys to same action
  - [x] Action to callback with Entity state
### NOTES
  - The **Game System** loads a ***Game window***, ***Texture manager***, ***Action mapper***, and ***Input manager***.
    - It contains a few utility function to modify the window and game option.
    - It contains a game loop with *fixed time step* and a max loop counter for panic handle.
    - It also default initializes an *Input manager*.
    - The Game class needs to be inherited and init, update, and draw function needed to be overriden in the new *game class*.
    - These overriden funtions will be called by the base Game class from the game loop.
  - The *Input manager* is used to bind keys to action and bind action to callback fucntion of entities.
    - It contains an ***Action mapper*** which is used to store the mapping of keys to action.
    - And a ***Reaction manager*** stack to hold the list of entities reacting to actions.
    - The Reaction manager is initailised in the entity objects.
    - One instance of an input manager is assumed for every game although more may be created manually.
    - It requires a base object for mapping which is usually the game object itself, It is so that the it has the least priority.
    - More object which are instances of/or (usually)inherited from InputHandler object can be pushed in to a stack of object in order of priority which try to execute callback for the action in order.
    - Usually the number of InputHandlers that will be pushed is minimum as the number of InputHandlers that react to input may not be many.
    - Thus mapping and traversal of the stack will be fast due to the low count.
  - The *Resource manager* can load textures and returns a handle.
    - The obtained handle can be passed to a function in resource manager to obtain the mapped texture.
### ISSUES
  - ~~Using multiple resource manager/texture manager objects makes no sense to me, therefore we just use a single instance. Using one instance to access functions seems very redunctant, as we will have to pass the object around to load and retrieve resources/textures.~~
    - >~~Thus we can have the function of the resource manager be static so as to able to use it without a instance of the class. This will allow us to load and query for resources from anywhere in the game. All we will have to pass around are the handles ,***IFF*** the need arises to load a resource in one entity and access it in another.~~
  - ~~Currently Resource manger does have an unload function to unload loaded resources.~~
    - >~~Add an unload function for resources, to be able to unload resources when not needed anymore and reduce memory used.~~
  - Action Mapper currently does not load mappings from a file instead have to be coded.
    - >Change Action mapper to load from a file of action = input mapping.
  - ~~Change Action mapper from map to unordered_map as the insertion/binding only occurs at the beginning and the rest is all access calls.~~
    - >~~Change map to unorderd_map for Action mapper.~~
  - ~~Action mapper maps action like mouse move and mouce scroll which have no mouse buttons by giving them a button value which will not be used otherwise. Currently the given values are hardcoded.~~
    - >~~Change the hardcoded values into Defines so as to not deal with magic numbers.~~
  - ~~Input manager realtime check of actions is currently declared but not defined.~~
    - >~~Define realtime check for input actions.~~
    - >~~Or do we actually need realtime check, is event based system enough.~~
  - ~~Reaction mapper uses a map to store mappings.~~
    - >~~Change it to unordered_map~~
  - ***DOCUMENTATION***




