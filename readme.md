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
- Physics System

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
  - Action Mapper currently does not load mappings from a file instead have to be coded manually.
    - >Change Action mapper to load from a file of action = input mapping.
    - >Add function to allow editing of file and reloading of controls.
    - >make current function to map keys to action private.
  - ~~Mapping two or more keys to an action will and activating those keys will trigger it multiple times.~~
    - >~~Make it so that multiple presses to same action is triggered only once~~
    - >~~Should it be handled within the game instead?~~
    - >~~Leaving it as is for now since it doesnt make sense, if needed by dev, let them handle it.~~
  - ~~Using multiple resource manager/texture manager objects makes no sense to me, therefore we just use a single instance. Using one instance to access functions seems very redunctant, as we will have to pass the object around to load and retrieve resources/textures.~~
    - >~~Thus we can have the function of the resource manager be static so as to able to use it without a instance of the class. This will allow us to load and query for resources from anywhere in the game. All we will have to pass around are the handles ,***IFF*** the need arises to load a resource in one entity and access it in another.~~
  - ~~Currently Resource manger does have an unload function to unload loaded resources.~~
    - >~~Add an unload function for resources, to be able to unload resources when not needed anymore and reduce memory used.~~
  - ~~Change Action mapper from map to unordered_map as the insertion/binding only occurs at the beginning and the rest is all access calls.~~
    - >~~Change map to unorderd_map for Action mapper.~~
  - ~~Action mapper maps action like mouse move and mouce scroll which have no mouse buttons by giving them a button value which will not be used otherwise. Currently the given values are hardcoded.~~
    - >~~Change the hardcoded values into Defines so as to not deal with magic numbers.~~
  - ~~Input manager realtime check of actions is currently declared but not defined.~~
    - >~~Define realtime check for input actions.~~
    - >~~Or do we actually need realtime check, is event based system enough.~~
  - ~~Reaction mapper uses a map to store mappings.~~
    - >~~Change it to unordered_map~~
  - ~~*** "Self" DOCUMENTATION***~~

#### Example game
  - It needs to use all the features defined in this phase extensively for testing puposes.
  - [Asteroids](https://github.com/bitDaft/Asteroids).
  - **TODO** - Postmortem of asteroids to understand difficulty in using this engine.

# **Phase 2**
- [x] Goal is to allow custom events.

### REQUIREMENTS
- [x] Custom Events and Event Handler

### NOTES
  - This Custom Event Handler will be able to directly integrate into the built-in event queue of SFML
  - This will allow us to not having to manage events and simply define them, trigger them, and process them without worrying about
    underlying queue mechanics.
  - There should be a ***Custom event class*** which is extended from ***SFML Event*** which will allow these events to interface with SFML
  event queue.
  - A method to inject these custom events into the SFML event queue. Learn the current method used by SFML to push events into queue
  and see if the API is public; if not, extend the event handler to allow adding to the queue.
  - These events will be available for processing in the normal event queue for SFML events and can be redirected to custom user handling function.

  - After checking the built in Event System used by SFML, can conclude we are unable to push events manually.
  - Thus a custom event queue will have to be made.
  - The Custom Event System should allow defining of custom events, triggering of custom events and polling of custom events for processing.
  - Our Custom Events will inherit from sf::Event so that we can hold both types of events in a single queue.
  - Our Custom window will inherit from sf::RenderWindow so we can use it same as existing window with new polling functionality.
  - Custom window will allow the triggering of custom inputs.
  - Custom window will be responsible for managing Event queue.
  - When a custom event is triggered, empty out SFML queue into custom queue and push custom event to it to preserve order of triggered events. 
  - **TODO** - complete the notes with the new changes to event system.

#### Example Game 
  - Need to make game with extensive use of custom event which will and will not send additional data.
  - **TODO** - Design a game given the above criteria.

# **Phase 3**
  - [ ] To be able to transition between state for both game and entities
  
### REQUIREMENTS
  - [ ] Make a finite state machine which can be used to control the behaviour of entities and game via states
    - [ ] Add Push down automata to it to allow for state transition preservation

### NOTES
  
