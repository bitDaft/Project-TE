Random thoughts and musings

```
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
  - [x] To be able to automatically manage updation of required entities
  
### REQUIREMENTS
  - [x] Create a global updation system which will handle the updation of entities 
    - [x] Automatically add updation required entities to the system
    - [x] Automatically remove entities from updation upon entity deletion
    - [x] Automatically calculate updates of entities each game loop

### NOTES
  - An updation class which contains a queue. 
  - It should be initialised at the start.
  - The number of queues needed can be set for priority stuff.
  - At every game loop the updation of this is called.
  - It will go through each queue in order and call each objects update function.
  - Two functions toggle whether to allow or prevent updation.
  - The game is in no updation mode at the start and will have to call function to allow updation.
  - An interface updatable exist to allow objects to be updated which will be stored in the queue.
  - Can the execution of specific queue be disabled. yes i think this is needed. so partial queues can run.
   
# **Phase 4**
  - [x] To be able to have animation for sprites
  
### REQUIREMENTS
  - [x] Make an animation system that will allow animation for sprites
    - [x] Implement an animated sprite object to work with the animation system
    - [x] Implement an animation class to hold the required animation.

### NOTES
  - Contains 2 classes which are responsible for animation.
  - Animation class holds the texture and the rects for each frame.
  - Animated sprite holds the reference to this animation and updates the currently shown animation rect depending on time passed.
  - Animation is independant of the Animated sprite which allows it to be reused by many animated sprite objects.
  - Animated sprite contains the actual logic of transition and holds other relevant data for the animation such as the current frame and the amount of time passed.
  - Improvements to this class are needed to allow for almost same interface as sf::sprite and additional functions which will allow us to integrate with the drawing system for efficient drawing. 
  
# **Phase 5**
  - [ ] Create actual resource manager class to allow for easier handling of resource handles
  
### REQUIREMENTS
  - [ ] Resource manager will allow storage and retrieval of handles based on users desired constants(namely enums or unsigned ints)
    - [ ] Create resource loaders for other resource types for fonts, music, sfx etc
    - [ ] Integrate Animation system into this resource management system to allow it to be also queries with ease
    - [ ] Automatically add any loaded resource with other resource loader class like textures and fonts to the resource manager map with the users desired key

### NOTES

# **Phase 6**
  - [ ] To be able to transition between state for both game and entities
  
### REQUIREMENTS
  - [ ] Make a finite state machine which can be used to control the behaviour of entities and game via states
    - [ ] Add Push down automata to it to allow for state transition preservation

### NOTES
  
```

## Other Notes

- current entity update system is managed manually. change it to some queue based system for auto updation.
- animation system
- dynamics sytem
- spriting system
- physics system

## state sytsem notes

- want to able to simply define states in a fsm without state objects.
- single state object callback functions for all states of fsm
- fsm state update callback binding
- kind of like the visitor pattern
- eg:-

  ```c++
  // IS THIS EVEN FEASABLE ???
  // DRAWBACKS ???
  class FSM{
    ...
  };
  class CallbackObj{
    void callback1(...){...}
    void callback2(...){...}
    void callback3(...){...}
  };

  FSM fsm;
  CallbackObj cObj;

  fsm.addState("state1"); // add states
  fsm.addState("state2");
  fsm.addState("state3");
  fsm.setStartState("state1"); // set start state
  fsm.bind("state1","state2",trigger1); // unidirectional binding
  fsm.bind("state2","state3",trigger2);
  fsm.bind("state3","state2",trigger3);
  fsm.bindc<callback1>("state1",cObj); // callback binding
  fsm.bindc<callback2>("state2",cObj);
  fsm.bindc<callback3>("state3",cObj);
  fsm.finalize(); // finish setting up fsm
  ```

**_WHAT ARE TRIGGERS!?!111!???_**  
 hmmmmmm.. let me see

physics system
animation system

## new insights into state system

- after research and thought new ideas of state system has sent the project into haitus.
- have to redesign the entire state system involving new ideas
- the new features / ideas etc will be outline below and the changes required of the state system

## the epiphany of state system

- the state system can also be used to draw the state of something and have the update function too
- consider drawing for now
- if we need screens that need to be drawn on top of another due to state change we can simply loop through the state and execute draw for each screen
- similarly for their execution
- we can have simple flags dictating whether to be drawable and updatable
- this allows to control drawing and updation of each screen. so states becomes screens for all
- each of these draw functions can simple return an image which will be rendered once for efficiency.
- it also allows us to do postfx and shader stuff later on.
- the issue lies in the design of this system and how to merge it with current system in place.
- Game will have a state machine, basically screens, each screen transitions to different state.
- we can use a stack. but we need to traverse from bottom to top for all of it
- Game generates an sf::Image. goes through state stack, checks drawable flag, if true draws onto image and return image.
- This image is then sent to the next state till top. drawing all drawable states.
- Then a queue of all drawable objects is traversed. for each object through its state stack from bottom to top drawing each state that is valid
- this final image is then rendered to the screen . so only one render call occurs and postfx can be done on image before render.
- same goes for update queue and updation of game and entities.

## implementing state system

- we need new queue system for updation and drawing.
- seems almost same system. just change in whether drawing or updating.
- each drawing or updating queue will have list of objects which will be traversed to do respective function.
- it will loop through each object and run its respective function
- each of these stored objects will inherit from an interface representing drawable and/or updatable.
- should there be multiple queues for different layers of drawing / different priority for updation? probably. lets make it adjustable.
- eg drawable layers background, main, and foreground layer for drawing.
- eg updation layers static background, particles, main entities etc.
- once these objects are created push them onto stack and then each loop go through these objects and run its function
- for drawable the order is important as to what gets drawn first. which led to the multiple queue idea.
- what about using priority queue to arrange entities so painters algorithm takes place for proper drawing
- eg for drawing lets have 3 layer. background, main, foreground. each has a priority from 1-5.
- i think that can work. the programmer can decide the number of layers and the priority of each object.
- almost follows similar structure to drawing on browser for each z index and priority depending on html structure for same z index
- lower the priority number the farther it is drawn.
- 0 be the default priority and the limit of priority can be self imposed by dev.
- how will this system work with states?
- if state is drawing should the state inherit drawable? but we dont want all states to have draw and update if they are not needed
- what if the entity is inheriting drawable but also has a state system to draw? should the user manually call the states draw?
- since there is a state stack of drawing but the drawing priority of each state and may be different and may be interleaved with other entities states?
- this is giving me a headache...
- back to basics... state system is used for updations. should rendering be done by state?
- let the object do the rendering?
- if the object does the rendering how does an overlay pause menu with transparency work?
- we can use scene graphs for this. each screen may have a scene graph
- but changing to pause state is a game state and not another object.
- but if we wanted the game to be rendered below the pause screen both the gameplay state and the pause state will need to be rendered
- this is basically rendering of two states over one each other at the same time.
- if only one state of each object need to be rendered then no issue arises.
- but here we need to render two different states with objects that are specific to each state
- so if a state goes out of the render pipeline then any objects under it also should not be rendered.
- like the gameplay state which causes the player to be render. but if not gameplay dont render the player either.
- but if in pause and i need the last game screen which will lead to the player also needing to be rendered and then render the pause screen on top of it
- so each of these screens may have its own rendered queue
- the reason for separate render queue is dont want to loop through the queue if that screen os not being rendered.
- if the screen is not rendered each of the object will need to be updated to not render every time. unnecessary.
- the thing is this may not only be relevant for the game state but may arise in any of the object substates.
- scene graph?
- so no need to create a specific screen class? right?
- implement it into the state system itself?
- let the state system have an update and draw queue?
- should the update be not attached to state?
- the update can be global. as each object has updatable flag. if set update else not. so all updatables can be pushed onto global queue.
- what about destruction of an object and removal of it from the update queue?
- once an object is destroyed move it up the chain to game to remove it or send an event saying an object has died and an id handle so that it may be removed from the queue.
- cool.. glbal updation can work this way. i think this is feasable.

- ## notes on global updation.
- there will be updatable interface for inheriting by objects needing updation.
- the updation system will have a queue containing these updatable obejcts..
- as before should there be multiple queues to allow for priority as z-index
- objects should be pushed automatically or manually have to be added every time a new object is created?
- should probably be automatic but should allow the dev to configure the priority and to which queue it should go to.maybe?
- ### further notes.

  - later we might need to have movement update, physics update and stuff. so that it resembles an entity system. and can update the same aspect at the same time instead of going through all of it at once and having race condition issue

- every game loop it will loop through this queue and execute their update function
- since we are not updating by components like movement, physics, collision etc and updating the entire object at a time the ordering in the queue might matter if something significant arises. will need to test the impact of this ordering.
- since the game is updating in small chunks, i dont think it will affect it to that high degree. if not processed in one frame it will be processed in the next.
- since we have fast update cycles it should appear smooth. test at what point does it actually might affect gameplay.
- during construction of entities itself specify the queue and the priority in the queue, otherwise default 1 queue and same priority.
- updation seems like done. this can be implemented.
- if entity is inheriting interface then the updation should be auotmativally delegated to the state machine if state machine is used.
- in construction why not also accept a parameter pointer to state machine if state machine exist, in which case the default update function just calls the states update function.?so the person might not have to write the update code delegation to state manually
- seems pretty good system for updation.
- any other issues?
- cant think of any at the moment
- this can be implemented, and it also has a solution for updation if state machine is used.
- should look into a way where pointer to state machine can be sent automatically while construction
- so only objects needing updation may be added to the queue and processed.
- what about an animation system. should the animation be part of this updation code?
- lets think about it later.
- will this system need to interact with drawing system.? dont think so.
- should keep the two separate
- but consider if we wanted to pause the game
- the game should be paused but the new game state like pause its menu should still be updating
- so should each screen of game have an update queue. so once the state of game changes then only objects in those states update.
- but this binds updation system to state system. same issue as drawing system.
- once any state is set non updatable then all objects under it also stop updating. so no need to go to each object and pause it.
- this pause issue is the only roadblock to global updation system
- once a solution has been found updation system can be implemented.
- if a solution can be found here it can passed onto drawable and allow for state with drawing too.
- now that i think about it only the game states need an update queue, all the objects underneath it can be stored inside this queue
- should we create a specific overriden class for state machine simply for game class for update queue.
- now that i think about it most(almost all) of the objects that will need updating and all will be part of gameplay
- will there be any objects which will be used in menu state or pause state?
- if not i can just forego the updation loop while not in the gameplay state, thus no updation will need to occur for objects if the state is in pause state.
- rendering can occur on a different pipeline, so forget anout rendering for now,
- let me try to think of some objects which mught be in different states other than gameplay which might need updation.
- consider a few basic states of a game: menu, options, credits, play, pause, stop, reload save, end?, (these are top of my head)
- the update function will basically handle position, movement, interaction, proximity triggers, inputs reactions,sprite shifting?, (of the top of my head)
- in menu options etc what kind of objects might need updation?
- there will mostly be just ui elements.. so check whether collision or in or out, and click callback. the object itself does not update anything in there.is there any objects that might need updation? cant think of any.
- so the system we will go for the above pause issue will be to simply stop processing the update queue if the state aint play state.
- since we dont have as statemachine setup lets thinkhow it will integrate and work with the state system
- the game will inherit from state machine, and initialise it, there will be an inital default play state so incase no states are defined the default state play will be directly be used. so no setup necessary and all the updation code will work
- in case new states needed to be added(most likely will be) the user will need to override the initial state of game state machine and since each state will encapsulate the transitions there will have to be a code to go to the defaut play state from some state,
- so only the objcets will need to be initialised to be added to the update queue and there will be no unnecessaru manual update calls for each object.
- create 2 new functions for startUpdatingObjects() and stopUpdatingObjects() so no need to have default play state. if custom states are made the user can call start update and stop update in the respective start and end functions of the state. so in case it needs updating in other states it can update also. this can work
- this seems flexible. so the user can start or disable when needed and no need for its own state at the start of the game
- lets go with this solution for now and see if we hit any roadblocks.

### implementing global updation queue

- an updation class which contains a queue.
- it should be initialised at the start.
- the number of queues needed can be set for priority stuff.
- at every game loop the updation of this is called.
- it will go through each queue in order and call each objects update function.
- 2 functions toggle whether to allow or prevent updation.
- the game is in no updation mode at the start and will have to call function to allow updation.
- an interface updatable exist to allow objects to be updated which will be stored in the queue.
- can the execution of specific queue be disabled. yes i think this is needed. so partial queues can run
- lets get to developing then.

- lets now think about state system and drawing
- should the two be part of the same system
- depending on the state the sprite to be drawn can change. like running jumping falling etc
- even the game class can have main, running pause states.
- but consider drawing a pause screen on top of a game running screen.
- here there are other objects that are drawn if the game screen is drawn. then we need to draw the pause screen
- so there is a hierarchy of drawing objects
- if one object is not drawn any under it is also not drawn.

---

- since the global updation system is done, we now focus on state system.
- updation system will have to be updated to interact with state system automatically once a state system is present on an object.

### Drawing system new thoughts

- drawing can be done in many layers.
- each layer can be like set of parallax, background, main, forground etc
- i know i should be working on state engine and drawing, but UI keeps coming to mind. :p
- tie drawing sytem to state system? how will it tie up the animation system?
- should the animation system be like updation system but single queue? just run through all objectsnd update the animation to new frame?
- ok i took a look at a basic animation system where the sprite class has been replacesd by animated sprite.
- so we an also have an animation system whic describes animation and animated sprites which referes to those animation.
- if so how is this going to tie in with state sytem.
- lets review state system with basic sprite system first.
- once the states draw system is called the it will update the sprtie of the object with new sprite.
- the enter method of a state should change the sprite.
- the draw method return image of sprite drawn into an image.
- so considering that each state can hold a pointer to an animation object which will replace the animated sprited with that animation.
- then each draw call of the state will just draw the animated sprite where the animation class will handle the switching of the frame.
- so the object can hold a animatedSprite object while the animation are handled in the state.
- without states the user can create multiple different animation in the object itself and pass to the sprite.
- how does the animation system tie in with the drawing system?
- how does drawing system work if there is no states system is required?
- #### quetions to be answered

  - how does the animation system work independently?
  - how does the drawing system work independently?
  - how does the drawing system work with animation system?
  - how does the state system work independently?
  - how does the state system work with animation system?
  - how does the state system work with drawing system?
  - how does the state system work with animation and drawing system?
  - how does the state system work with the updation system? // this is for later. we will need to update the updation system.
  - so there are 8 questions that need to be answered.
  - ###### how does the animation system work independently?
    - for animation there are 2 classes.
    - animation and animatedsprite.
    - animation stores the animation sprite sheet information.
    - each animation specifies the texture, the length and width of the entire sprite strip, and the number of frames in it, so it can automatically calculate each rect needed for each frame instead of creating muliptle rect objects.
    - but like that it will create a new rect object every time a new frame is needed.
    - hmmm.. lets just use a single rect object and simple change it's values and pass the same rect every time, so no need for multiple rect objects.
    - this should remove the cost of creating multiple rect.
    - so one rect, one texture, one width, one height variables needed only for an entire animation system. the only extra computation will be calaculation of different coords of the rect when switching frames. no fixed rects. less memory but more computation. how will this affect long time?
    - once a rect has been created, it need not be swapped out. so no extra calculation, but only at animation initialization.
    - hmmmmmm?
    - profile and see long term. graph the effect.
    - instead of fixed memeory footprint for each animation, the number of rect count wil increase with higher number of frames.
    - but this will allow for o extra calcualtion and simple passing of rect for new frame of animation.
    - for now lets use fixed memory footprint.
  - ##### how does the drawing system work independently?

    - havent really thought about this.
    - it could be really similar to the updation system.
    - so we can have a global drawing queue or multiple queues.
    - so when an entity is marked as drawable it would be added to the desired queue
    - then each game loop just loop the queue and draw the objects. so each layer(queue) can be drawn via painters algorithm.
    - each of these draw functions takes in an image and it adds to that image
    - should it add to the image of just return the image and add it manually in the engine render func..
    - let each layer draw themselves. but we get each multiple layer and just combine everything together.
    - should i have a priority queue instead? dunno.. each of these different queues do implement a kind of priority.
    - removal can be done same as updation
    - ok so thats done.. somewhat.. there are still issues
    - this design of drawing system can have issues when pause state needed to be drawm transparently in top od game UI.
    - so you will have to have a queue for the pause system. and another queue for game system.
    - this shows pause has highest priority.
    - this can be drawn like this. what about the state system interacting with the game itself.
    - we will need to think about some layers already and have it have some kind of fixed definition.
    - lets have 2 main queue. game -> menu.
    - game can have its own sub layers like parallax, background, main, foreground etc.
    - menu can have menu, settings pause etc. but most likely this will be just a single layer.
    - but that would mean setting options and what not, are actually objects. oh fuck. now i have to think about the UI system.
    - fuck me.
    - lets consider they are object with the same interface

  - ##### how does the drawing system work with animation system?

    - doesn't matter.
    - the drawing system is will call the draw function.
    - the draw function takes an image.
    - the animated sprite can be drawn onto it normally as you would.
    - so it seems both of them are independent systems.
    - the drawing system will go through all objects in its queue and call each objects draw function while passing a single image through for each queue.
    - the draw function will draw the animatedsprite to that image at the correct position and return it.
    - the returned image is then passed onto the next object in the queue.
    - at the end we have a single image of that queue in order of painters algorithm for each queue.
    - at the end of drawing loop all images for each queue is then combined in order of painters algorithm and then rendered to the screen.
    - so this system should work properly.
    - i think there is no need to return the image. since the image will be passed as a reference it will affect the original image.
    - so returning it basically does nothing as the user will have no access to that image.
    - if they wanted to post process the image, they can call the postfx func in the draw func with the image that is passed to it.
    - ok, i think this is a viable system, that can work without state systems.
    - now onto state system madness.

  - ##### how does the state sytem work independently?

    - at the highest level there is a single state manager class.
    - should this class be subclassed or should it just be object composition?
    - whatever... the statemanager manages the current state and changing of the state so that the code does not flow into the object.
    - so it will be clean for the programmer.
    - the object calls the update function of the state machine.
    - the state machine then just checks the current state for that object and invokes the current states update method.
    - the state is passed a pointer to the object of the state machine.
    - the statemachine is given the obect pointer when initlizing.
    - state machine is also templated to allow for different objects to store their this pointer.
    - the state for each object will be subclassed from a main state class and will have common function like enter, exit, update etc functions.
    - so the object will not have to manage any state code within it and will be handled by the manager.

  - ##### how does the state system work with animation system?

    - the object will contain the animated sprite object.
    - each state object will have to define animation object/s depending on how many are needed.
    - each time a new state is called, in the enter function of that animation, set the animatio of the animtedsprite to the correct animation belonging to that state.
    - this will allow the animation of the ainmated sprite to change with the change of the state.
    - if this is the case then the state objects will have to store some stateful information which makes them not static objects.
    - thus when switching objects we will have to delete and create new objects as required.
    - since it contains inforformation particular to that object, when we have multiple same objects we cant reuse the state objects and will have to create independent states for all of them.
    - but since it is animation, the animation of all objects should be the same i guess. so no need to actually create new state objects for all.
    - all the objects have the same properties and animation, switching states will produce the same animation.
    - so we can declare static state objects.
    - but since the state management is handles by the state manager class how will it be handled by the object..
    - hmmm.. lets see.
    - instead of the states themselves creating new objects and setting the current state of the state manager. we can wrap it up in a fucntion to call to return the required object
    - the user can then override this function the return the requested object however he need. whether to create new objcet or send a reference to a static object.

  - ##### how does the state system work with drawing system?

    - the drawing system will loop through all the objects in the queue related to that priority or depth.
    - it will pass a reference of an image into each object and have the object be drawn into it.
    - at the end of the queue loop we will get an image with all the objects drawn onto the image for that depth.
    - this is the working of the basic drawing system independently.
    - when we have a state system the sprite od the object may change due to the state like idle, running, jump etc. each of these state will have their own sprite to be drawn.
    - once the state is entered the sprite will be set to the relevant sprite. should we set the sprite?
    - should there be a change in the sprite. isn't it costly to keep changing sprites like that?
    - will have to profile it.
    - in drawing system the loop will call each object's draw function. when there is a state we will automatically delegate it to the state's draw function.
    - the image to be passed will also be passed to it.
    - no need to keep changing the sprites texture as that might be costly.
    - let each state have a sprite object defined and that sprite ca be drawn onto the image passed to the draw function.
    - this will require more memory but there wont be any computation over head to switching the sprites texture over and over.
    - although each state of the object will have its own sprite, neednt create multiple object since each state of every object has the same sprite static state objects can be created.
    - how does the drawing of a pause state with snapshot of gamestate underneath work?
    - since each state has a different drawing, shoudn't the drawing queue or whatever be part of the state.

  - ##### how does the state system work with animation and drawing system?
  - the state system and other system will work as described above in combination.

- after much thinking i have decided to use a global drawing system and let the programmer manage the objects to be drawn.
- public functions can be used to change the priority of the functions and whether to disable enable the drawing of the object.
- it will integrate with the animation and the state system the same wasy as described above in the answer to the questions.
- once the state system is implemented, all the systems will need to be integrated into the state system as an option and not a defualt.
- this will allow the programmer decide whether they want to use in conjunction or separately.
- this should allow for flexibility.
- there can be 2 default queue for objects and menu.. no.. lets just allow the programmer to decide. although we can give pointers and use cases in example programs and documentation for them to follow.
- the drawing system is a global system which will work the same way as the updation queue.
- there can be multiple queue as needed.
- i need to fincd a way to transfer the pointer to the objects stored in the vector to be tranferred to another vector as and when required.
- that will allow to change the priority as needed.
- in the documentation i can give the idea of having a defualt disabled queue, or when they just want to disable an object they can move it onto that queue. should i move it automatically to the new queue upon deactivation?
- or should i let the programmer decide the change in the queue.
- lets see the cost of moving from vector to vector or just simply have a boolean to prevent execution.
- to create the system we can simply duplicate the updation system and refactor the names as needed.

_Issue_ - no object other than the game can currently issue new events. change it to allow the passing of gamewindow to other objects to be able to trigger custom events as required.

### Animation System

- we will be working on the animation system next.
- should there be an animation manager which will hold all the animations like the resource manager.
- or should we just have the animation created every time the object is created.
- since the texture is allocated only once, the intrects will have to be created each time we create a new object.
- but the animation will be the same.
- each animation obhect will have reference to a texture and the rects needed for each frame. should we do it like thor to allow for veriety of animation functors of functions to be added.
- suchglobal functions/functors can be created by the developer when the need to, as this is just a simple transition function .
- these functions can be manually called in the update function if the need arises.
- the current systems that can be animated are frames, and transformables, colors with alpha. cant think of anything else that i can think of which would want to make such an animation system.
- it will be convinient but it is trivial to implement by themselves and are not usefull for me to integrate into the engine.
- so we will only deal with frames.and i dont want to use strings or whatever to call functions or whatever since the comparison of functions is much more heavy comparitively.
- so lets just leave the other animation for the programmers to implement by themselves as these are too case specific.
- only frame animation is generally used to a high degree.
- and transformables and color alpha is not used as much.
- although it can be used for example to create a bobbing animation, there are many parameters for the bobbing or whatever transformable which are too specific to allow for a generic class.
- so no other animation other than frame animation.
- for animation we will have a single class whose objects contain the information needed to create a frame animation.
- the needed variables are reference to the texture and the rects of each frame.
- the reason i am going with each rect of frame is since the frames can vary in sizes and positions.
- although position is much less varying, consider for example a person slashing their sword.
- the frame size will depend on how far out the sword has been drawn.
- same exmaple can be used for height also.
- thus the programmer will have to manually define these rects as needed.
- lets say that each object has its own animation object. so when a new object is created the same animation objectwill have to be created for it.
- when there are multiple such entities neing created and destroyed at a fast rate, the creation and destruction of these rects and animation objects can add to the processing needed.
- but this method allows for the user to have their own independant objects which can store things like animation state and how much it has progressed for each individual object.
- but if we have a single animation object for each animation and all objects having to refer to this object will prevent us form storing animation state related information since each object can have different positions in the animation cycle.
- so the user itself will have the variables needed for it.
- so if there is just a single animation object that every object is going to refer to we can have an animation manager, that will allow us to keep track of, load and destroy these animations as required.
- but if it like the resource system, the object which will need to reference the animation will need to code for it.how are different objects going to obtain this code for referencing it?
- the same issue is there for resource system.
- currently it is the game class which is loading these resources and holding onto their handles.
- and when an object is created in the game class, the resource handle is passed to the object so they may initialize it.
- this is a stupid way.
- we should have a map of these handles to custom enums(never gonna use string as comparison calculation is shit slow for string).
- so we need a handle manager class. it will have an enum of resources. once a resource is loaded add it automatically to the handle manager.
- when the programmers loads a resource they can also pass in the desired handle to store the reference to.
- thus later on the can query the handle manager with their desired enum, and retrieve the corresponding handle and then obtain the corresponding resource from its managers
- is animation a resource ? can we use it the same as texture, font, sfx etc. since they are all going to be used the same way.
- but since the other resources are loaded as files from disk and this is created in game, lets handle it separelty for now.
- in fact should we have a seaparate class for font texture sfx etc?
- let split them all into different class. change the current resource amnager into trexture manager and have the resource class be the handle manager.
- is there a way to determine if a path string for loading a resource is font or texture etc?
- if it is we can generically pass a path and resource manager can call the respetive manager to load the resource and store the handle.
- or should we just make the programmer use each individual class so as to force the type of resource?
- if they use resource manger for loading how will the load other resources like animation and anything else that might be needed later in the future.
- we cant pass a file path for the animation.
- so let the programmer invoke each manager to load the needed resources and when adding a new resource it will automatically add the handle into the resource manager.
- we can have the specific managers all be friends of the resource amanger so that the programmer cannot add handles arbitrarily and mess things up.
- the user can only get handles, not add them. we dont need to allow the programmer to manually add these handles as errors can occur.. moreover they can be automated and it is boilerplate code so why not bake it into the engine for easier use.
- **so there will need to be changes to the resource manager**
- continuing on with the animation system
- there should only be a single animation object which can be referenced by all the objects.
- so how will the objects handle the state.
- there can also be an animated sprite which refers to the animation. and that object can handle the specifics.
- anyways since upon creation and deletion of all objects each will need their own sprite, lets make them handle it on their own.
- also they should have some interface to allow changing those state variables of the animated sprite by the encompasing object.

- so lets design the animation system now.
- there will be an animation class.
- it will hold the reference to the texture.
- it will contain the vector of rects to the frames of the animation.
- we can allow a parameter to specify the count of times to show in the loop, so a rect of count 3 will show that frame 3 times while looping.
- this can be done by simply adding more references of the same rect to the vector.
- since we need that feature instead of pushing rect objects, lets push references to it. so multiple reference wont take more memory.
- so the programmer will have to create these rects on the heap instead of the stack.
- we can use pointers to these rects so that the memory management of that is automatically handled.
- so it will be a vector of pointer to rect objects.
- next it will need to store the time of the entire animation cycle.
- so that we can cycle through the animation in frame independant manner.
- but this animation class cannot contain any specific data related to objects, like the current frame or the progress of the animation.
- there will be an animatedsprite object, which will have a reference to the animation object.
- this sprite will also contain the object related information like animation progress, current frame etc.
- this should allow for multiple animated sprite objects to reference the same animation object.
- every time a object is created an animated sprite object will have to be created
- what is the overhead of the creation of animated sprite objects over and over.
- since the animation object is stored as a reference that wont be a big impact.
- animated sprite should hold the current frame.
- the current delta total time, will have to calculate the progress with the animation time.
- should it have a set current aniamtion frame method?
- anyway lets get to implementing the animation system.

- now that we have an animation system(albeit incomplete) set up, we will now focus on refactor, clean up, bug fixes, and documentation.

# CLEANUP

- first lets just go through all the system in order of execution through the game loop.
- first class to inspect is the game loop class.
- issue objects are not able to trigger events, currently only game is able to trigger events.
- issue objects cannot respond to events, currently only game is able to respond to events
- issue with animation using quads and not triangles
- issue with animation have no code for clearing of the rects used
- issue create a delegate function for adding mapping of keys of reactionmapper in enitity.
  ~~- MAJOR ISSUE - affect both drawing and updation~~ THIS ISSUE IS SOLVED
  - ~~after inserting a some objects and deleting some of it out. clean up will remove the delted objects~~
  - ~~this will rearrange the position of the pointers in the array.~~
  - ~~so \_2 will not correspond to the correct position in the array when it has to be removed for other pointer~~
  - ~~this will crash later. NEED FIX NOW.~~
  - ~~so after cleanup the new positions need to be recalculated.~~

# SOLUTION

- EVENT ISSUE

  - objects can neither create nor handle any events.
  - objects should be able to fire events
  - objects should be able to handle events if required.

  - problem 1 - objects cannot fire events.
    - how to make events be able to fire events
    - trigger events is part of Rwindow
    - should events have access to the current window

#### random thoughts on action system.

- have and or system to combine actinos
- but the actions should only be triggered when an event has occured otherwise it will check for every action every loop which i not only inefficient but also might check for wrong key combination. like an only release action could be triggered even though no event was made sicne it will check at the current time is it pressed or released.
- even when an acction is triggered need to quickly determine whether this action object needs to be parsed to check whether it is valid or invalid instead of just parsing all the action objects to find the correct one, which is inefficient.

#### Event system random notes.

- this sytem can be reduced and made more easily accessible and easier to work with. right now it looks convoluted and unwieldy.
- although it work works without any hitches currently , we will need to test it out thoroughly before changing it completely.
- i feel it can be made much more simpler.

- read the entire codebase and notes and readme and up to date with current progress of engine.
- i feel it is time to implement the state system
- after the state system has been implemented we can do all the needed fixes, refactoring of current objects to add the required functionalitis.

# EVENT SYSTEM

- we are going to design the event system that needs to be implemented
- lets start with the lowest unit, the state
- the state class will be a templated class so that it can be reused for multiple different entities
- it will have basic functions such as onenter, update and onexit. are there any more functions that are needed? hmmm will need to think about it
- this state class can be subclassed to create the actual states for any entity.
- since all the states for an entity will be tied to one another should we maybe create a behaviour object encapsulating them? this an idea for another time.
- any state transition logic will be baked into these objects.
- what about having state for these objects. ie context dependant variables.
- this is in order to understand having just a singleton state or need to create states as they are made.
- which is why i though of enapsulating it in a behaviour object or even having an interface for the entities to inherit from which would contain the necessary values needed for stateful states to function, and then the states can just query their parent object for these details so they dont really need to maintain it thus we can have all the states be singleton.
- lets consider both possibilities
- first is inherit an interface for usage of these states. or statemachine.
- the interface class will only contain the required dependant variables and their getter setter functions(if the variables are not public, which it most probably will be).
- any entity that inherits this interface class will be able to obtain those variables needed without having to directly manage them.
- if any of their values need to be accessed or set it can be set directly by the entity or the state since the state has access to the entity pointer.
- so any entity that want to use states of a set need to inherit the interface for that state.
- or they can also implement those needed variables themselves.
- this approach is very straight forward. but it makes the entity needing to inherit a class or to implement variables they may not directly use. also what if they forget to inherit the required interface. then the statemachine needs to check that the class has inherited the appropriate interface.
- but what if we need to switch behaviours of an entity, wouldnt they need to inherit both their interfaces. what if both the interface has the same variables.wont it cause a resolution error. but if the state use their own interfaces variables then those two separate variables would be out of sync
- here i think the best solution will to have the entity itself have the variables,instead of inheriting them. but they will inherit interfaces which are abstract and define the abstract functions of the interfaces to return the correct value or variable.
- thus two different states that need to access a variable for the same function can have their own functions that thay will call, but the programmer can define what variables those functions returned which will keep them in syncif the variables needed are the same.
- so if they are stateful states they will need the entity to inherit from an abstract base class with virtual methods which needs to be implemented by the programmer.
- this will allow us to have variables that are in sync with every state, where we can manipulate the variables to convert them into the right format needed for that state, and the variable can be used for outside purposes like displaying health or something without breaking.
- but a major issue is the inheritance. the entity will need to inherit for every interface that may be needed for any potential behaviours it may change into.
- which looks very shitty and i dont want that.
- also the same problem arises if two interface function are named the same it will cause resolution conflict..sooo...
- onto the seconf idea of encapsulating them into a behaviour object.
- the behaviour object will contain an instance of all the states that are needed to define that behaviour pattern within an entity.
- first i thought the behaviour object will contain all the stateful variables that the states may need to hold and such the actual entity need not define anything
- and these behaviour objects can be passed to the statemachine which will execute them.
- so the behaviours can be switched on the fly by simply switching the behaviour objects around.
- since the behaviour has its own state variables same as previously they may be out of sync, but we can solve that by initializing the correct values for that behaviour using the values from the previous behaviour object.
- this may need the entity to hold onto a copy of those variables that are common in the states transitioning to and thus will need to know beforehand itself what all states it can change into and hold their common variables.
- with this approach there will be no name conflict or function conflict or have the entity to define the accessor functions or even to inherit anything, so the objects can be switched on the fly without any impact, such as for checking whether it has inherited the correct interface or that the variable used is not in any conflict as they are all encapsulated under one behaviour object.
- another aspect it created is that the states need not be related to the entities as the needed variables and functions needed to function are defined in the behaviour object itself. so the behaviour object becomes entity independant. thus now the states need not be templated with the entity class.
- all they need is the reference to their encapsulating parent object. which is the behaviour class.
- i think this approach is better than the first one.
- what are the cons of this approach?
- the class will not have direct amangement of variables such as health thus will need to query the behaviour obejct to get the details such as health if needed for any other external purposes such as displaying health.
- so now we have a new behaviour class to think about.
- basically what is needed of the behaviour class is that it hold the necessary variables and methods for that set of states to function.
- behaviour object will also need to hold onto instances of states that are needed.
- upon creation of a behaviour object the necessary states are also created.
- since all of the required variables are held in behaviour and not in state , all the state objects can be singletons now.
- for any of the singleton states to access the variables they will need access to the encompasing behaviour object to query those variables.
- thus i think the state will still be templated, but they will be templated with behaviour class instead.
- will the behaviour object need to hold all the related states, or just to the current state?
- since the states are interconnected you dont really need to store all the states, when a state change happens the behaviour currentstate will be updated.
- so the behaviour class will act as if it is proxy for the entity
- whenever a state update happens instead of the entity or statemachines currentstate being updated, it will update the behaviour currentstate.
- instead of the statemachine holding the behaviour object let the entity hold the object and the statemachine can have a pointer to it.
- the state machine can be initialized with the behaviour object pointer or state object pointer.
- so now we can easily switch between the two different methods without any issues.
- anything with state will either be a behaviour object or normal state object with the required variables defined the entity itself
- since the states are still templated, the previous method can also be done without interference.
- we might run into problems while implementing and cleaning up some details on its working but it is a solid idea for now.
- then there is the statemachine object itself
- the entity holds a statemachine object.
- every update the entity will call the statemachines update function
- if the statemachine is an state holder it will simply execute the state execute method.
- if it is a behaviour it will execute the behaviours method.
- if we give them both the same interface then no need to change how the statemachine handles state or behaviour obejcts, it will be treated the same.
- the statemachine will hold onto the currentstate, and globalstate.
- maybe for previous state we will implement a pda.
- the state machine also holds a function to change the currently held currentstate pointer or global pointer.
- there it will execute the onenter on exit function and change the pointers around.
- if the behaviour object also contains the same interface as a state it can be seamlessly used without any extra code in the statemachine.
- that is all there is to the statemachine concept
- after implementation of state machine we will do a simple run and then see how to integrate animation drawing updation system as mentioned inthe questions above
- i think we finally have a clear picture for a state machine and switchable behaviour
- lets get to implementing it.

- during implementation found that switching will not be easy with the behaviour object encapsulation as it will just simply recreate the functionality of statemachine itself into the behaviour.
- so thought of a new approach which is not perfect but works with the contraints, can be swapped out for any other behaviour etc. the only issue here is the syncing of variables upon switching behaviours.
- so the method is behaviour is like a proxy entity.
- it will contain all the methods and variables needed for the states.
- a specific behaviour like person behaviour will need to be created inheriting fromt he aprent behaviour class
- this will allow the entities to hold all different type of behaviour objects irrespective of what they do by having a pointer to the base class
- since that behaviour object will act as a proxy entity , it will be the one to hold onto the state machine and not the entity.
- so the behaviour class will contain all the variables for state. it will also contain a state machine which works with that state, since state machine is currently also templated to hold the entity type this pointer and all.
- if we do it this way then state machine will always have a pointer to the proxy object whenever a new one is created and need not be bothered about having to handle any other type of behaviour. since each behaviour contains a statemachine which can handle it.
- this method also allows us to create state machine in the normal method by having the statemachine be held by the entity and the states being tied to the entity.
- so there is really no change to the code for state or statemachine from the initial time, it can be used as such and for dynamic behaviour a proxy entity can be used.
- now come to the problem, which is my guts. having the state machine inside a proxy object does not feel well. since the behaviour object is just a bunch of methods and data, i dont feel it should be responsible for state machine.
- just that the statemachine should not be templated and they should be able to work with all the behaviour objects as passed to them if needed.
- but if the state machine is taken out then it will need to be templated according to the behaviour data object which will then break being able to switch behaviour on the run. defeatingthe purpose.
- thus the statemachine should not be templated but at the same time should also handle all types of behaviour objects.
- let me see..
- if this is the case then stateamchine will store a pointer to behaviour class which holds the subclasses actual behaviour like person etc object.
- the statemachine will not be able to hold the specific state such as state personbehaviour but it will have to also hold a higher level parent class which we will need to make simply to be able to hold them.
- if the statemachine does not want to hold this data then it will be delegated to the behaviour object finally making it a clone of state amchine itself, so i dont want to put that functionality into behaviour, and subclassing statemachine with the required variables and methods for behaviour is feasable but for the switching mechanic will have to replace the entire statemachine. better than this is to have statemachine pointer in behaviour child object which will be neater to develop.
- so shoudl we just go with the design of having the behaviour class encapsulate the state machine and it will be entirely switched out?
- i think that is the best that we can do now
- since it wont break for those situation where changing of behaviours is needed dynamicallyand all the changable state groups are controlled.

- state machine has been implemented.
- we have been only talking about state machine up to this point assuming it would not react to input, ie uncontrolled.
- before we move on to implement the behaviour class, lets discuss how the a controlled entity is going to work with the state system.
- what immedietly comes to mind is that make the behaviour class inherit from inputhandler if the behaviour is controlled behaviour so that it will have an instance of reactionmapper and can set delegate callbacks that are needed
- this way the actual entity need not do anything and simple needs to let the behaviour change.
- when behaviour changes the controls may also change and thus we get dynamic behaviour.
- but the obvious issue is the input handler system itself. as soon as an object is created it is added to the queue.
- what if behaviour objects were created but they are not used yet and are waiting to be switched in, if they were created after the currently used behaviour and their daisy chain return false, the no input will reach the current system
- there also needs to be a way to allow or block an entity from processing input, and maybe even add and remove dynamically as needed at whatever position in the queue.
- i dont know how priority is going to help much but it should be useful
- we can have a similar multi queued system as updation or drawing, as those have functions for individual, queue, and entire blocking if needed, although switching of queues is not implemented as yet.
- lets go and revise to understand how the curernt input system works .

- curerntly input manager only handles one queue. it will check any events that it gets and get the action for it and then call the registered callback of the objects in the queue.
- made all of the functions and variables in the inutmanager static so now it can be accessed from outside without an object.
- it can be called by all objects to add or remove any objects in any queue
- programmer will have to responsible for it.
- but this allows any new object that was created to be immedietly added to the queue.
- before only the game object had access to the object so an event with a pointer to the new object telling to add to the queue was needed(although this was not implemented).
- now the object can just tell to insert intself into the queue.
- and maybe even remove onself.
- also now any built in sfml event can be triggered by simply creating the event object and passing it to inputmanager::processevents.
- this was not possible before. now we can manually trigger some key down or mouse down at some position.
- although i think if all functions should have been available to all. maybe adding and removing only to inputhandler.
- maybe changing of actionmapper to some setting object or so.
- anyways anyone can now modify anything so lets just use it properly in the engine itself so that the programmer will not have to fiddle with it unless really necessary
- what is remaing is multiple queus and adding and removing
- let think about hoiw it is going to work with state sytem before we go any further now
- now that i have thought a lot about this. i have come upon the fact that state system is not really dependant on the input system.
- it is just that there may be multiple inputs and we need to manage that
  -but for the state system to work does not necessarily need multiple queues or anything
- the only dependancy is that when multiple behaviour may be created or whatever may be created with inputhandlers and even if they are not being used they will process the input and they will consuime the input without even being active.
- so all that is needed is that entities need to be enabled for input and if they are disabled just skip them.
- so let input handler provide functions for enabling and disabling. so let it hold onto the positionin the queue
- and for removal no need for any clean up now. lets just make it nullptr so the ordering is not broken.
- added funcitonality to add remove disable or enable any enitty in the input queue.
- so now the actual blocker for behaviour objects is gone.
- so lets get onto making the behaviour class

- ive been doing a lot of thinking.
- using crtp the base behaviour is done. now they need to subclass it and set their states.
- what i thought was if an object with some behaviour is updated, then cant the behaviour itself subclass iupdatable and be in the update queueu. thus it just the main entity simply becomes useless.
- thus the behaviour object becomes what the entity was initially
- i feel that this system is not that usefull without an ECS system. since we are not really gonna make an ecs system and this is a project in learning to make a game engine that i did not want ecs in so i could understand how it should be done normally and what all will be its limitation and stuff.
- so since the behaviour just becomes close to what the actual entity was let us just discard this idea of having a behavviour objecct
- lets just follow the first approach were we have groups of states that are part related to an entity and that entity alone
- and even if the interface was same for another object that entity will need to hold the interface also.
- whatever.
- i know that not all the systems are that great even within this sytem and there may be much better methods to do things.
- but i want to just go on and see how far i can make it before i start another one with a different structure.
- many aspects may still remain the same since sfml is built the way it is but i might find better ways of doing other things.
- later on i want to also make a data oriented engine and also an ecs based engine.

- so with that our state system is completed
- although there is a need to brush up quite a few things it is in a usabel state now.
- let the programmer of the entity manually call stateupdate if needed.
- should the state also have a draw function to draw that current .. nah. the state machine will swtich the sprite which is stored in the entity.
- just simply draw it.
- another thing that ive thought about is that if a entity has a state machine it can have a state which just simply does nothing, which mimics the not updating state, so insteading of updatehandler or whatever checking whtehr the entity can be updated why not just leave it to the state to do it.
- so we can still run login where it can check whther the entity is ready to start being updating again by simply changing states,
- because currently now the entity cannot check whether it is ready to be updated again or not (this can include self or queue or maybe entirely disable of updation)
  although currently an entity only has power over its own updation and not of the queue.
- so what ive thought is that when en enityt is disabled it will call an alternate function in which the entity can do any process to check whether the entity should be enabled again.
- this will also provide us a method to update the animation of the sprite even if the entity is disabled.
- so lets do that now.
- the alternate function for updation has been added.

- now we have a lot of features with half completed stuff all over
- it should all be implemented or cleaned up
- but i dont feel like cleaning u p; hehe
- fuck. maintainance is hard
- i should start doing the maintainance and add pazzazz now to keep things smooth and shiny i guess.
- buuuuuuttt. before that lets just get onto other systems
- so now we need to research and identify core systems that may be needed
- lets see how that goes.

# CLEANUP

- so lets see what we need for cleanup. of the top of my head
- event should be triggerable from any entity.
- i dont know about entities handling events though.
- resource amanger must be made to texture manager
- make managers for fonts, music, sfx , animation
- create the actual resource manager interface to interface with these resource loaders and handlers
- updation and drawing queue switching between queues.
- multiple queue for input system. maybe we need to rethink the input manager.?
-

# Some Game ideas that popped up

- clicker
- advance wars strategy
- into the breach
- pokemon mystery dungeon

- one thing i realized i cant just make a clicker game. coz of gui input mouse
- how will an element know that it has been clicked or mouse is hovering over it.
- this will need the element to subscribe to the mouse events
- and we will have to generate these events by checking it every time, so it is not easy
- the mouse will be a point and we will have to check whether it does a collision check with every element on screen
- but that is stupid.
- so maybe i may need to think of a better system to handle input
- keyboard does not seem to have much issues since once it is not a visual input.
- so once a key is pressed it will just send it to the required object to execute.
- but a mouse is visual
- so it may hover over some element, mouseon or mouseoff , click on or release on an entity.
- so basically mouse needs a special handler for this.
- so this is a major blocker in creating any kind of games in this engine with robust mouse fucntionality.
- currently it may only be able to reliably and easily create games which are predominantly keyboard based
- fuck
- when interacting with gui elements every element will have to ckeck whether it has collided. so it can know when mouse has entered hovered over or exited, clicked etc when on top of the element
- we will take a look into all the events of the mouse that are available in the browser first to see what all are the most commonly needed event.
- if we just program those in we should have covered almost all use cases that may arise. there may be some quirky use case. but lets not think of that now,
- so we maybe the interactive elements will need to subscribe to the mouse. depending on what kind of event and where that event occured like a click, we will call that objects callback function.
- but this will make the ui into object based which we really did not want to and wanted to make it like html css kind of. shit. this is so confudsing.
- will need to research and find a good method to see how entities can interact with mouse.
- and if we do find a better approach maybe that may work for the keyboard as well.
- so now that this has been thought out a bit we may need to overhaul the entirety of the input system. fuck.

- ok i have thought up two issues.
- 1 . inoput manager not blocking inputs when like in pause state.
- 2 . a potential solution for the mouse issue, where whenever a mouse input comes up go through the draw queues and find the top one where it occured
- so all will get the event but the mouse system will keep track of the actual target that might have occured.
- so we might need a mouse system.

- although there are issues for mouse based games because of the above mentioned pronblems, it does not stop from making miouse involved games.
- like clicking on a screen to shoot projectile. or to turn a character in mouse direction.
- so i think the causes can be limited to a few cases.
- the case where we need to know exactly what entity it occured when there are multiple entity stacked on the same place
- this is probably the only issue.
  1
  ,/ once we can figure out the top entity on which the event occured, which will have to be calculated we can solve almost all issue of that i gues.
- like hover over or click on entity or mousenter exit kind of event.
- i am thinking that we can have a mouse system. whenever the entity needs a click or mouse over or enter exit events that are specific to the entity we can add it to a special queue
- then whenever such an event is triggered we can just check what the z-index of all the entities are and at what position the event occured so we can easily get the target entity.
- we can get the z-index by exposing a function from drawhandler to show the \_1 and \_2 variable value which is z- index.
- so whenever a mouse event occures we will go through this queue calculate if it happened to that event and call its special callback.
- so we will need to create a special event clickOnEntity, EnterEntity, ExitEntity, HoverEntity, MouseOverEntity etc.
- so all of these relate to mouse click and mouse move.
- what if there is mouse rightclick.? we will need to check that also.
- so there can be any click by that logic. the rest is just move event.
- these are special events since they occur on an entity.
- the other are general events which occur to the game window. or that which will be managed by the game object. and occur to the game as a whole.
- so if we want to make a game which use mouse that works on the game as a whole then it is possible. but on entity level there needs to be some thought.
- since entity level mouse is a visual issue , keyboard does not matter as it is just a toggle state and not visual need to identify.
- since it is visual it can be for anything visual. like maybe a cursor.
- but if the cursor was moved with keyboard like for advance wars then the button for A and B will act upon the cursor object and it will know which object it is selecting based on the scene raph or something. so it is not purely a cursor issue. it is just a mouse based issue.
- no. what if the cursor had super precision and moved with arrow button. now it has to highlight the entity below it even though it is being moved by a keyboard.
- so we need a way to solve the issue at a visual level. meaning it will need to interact with the drawing system.
- as said before we can have the entities that need these special mouse events be put in a queue.and the sorted to their z-index. then we can just go through the queue and find the first one at the correct coordinate. this might work.

- so those are some of the issues that are facing in mouse department.
- lets talk about input in pause state.
- oncethe state is paused i dont want any input to pass through to the character or whatever,
- this is helped by the daisy chain by having a pause oibject at the top which just returns false.
- but if it does not registers any other key it will passthrough.
- so how are we going to keep the input restricted to the needed objefcts only,
- i thought of having a multiple queue system, so when the state changes the queue will be enabled or disabled accordingly for input manager.
- since input manger is universal anyone anywhere can enable or disabel queues.
- so lets the game object have a state machine, which will be needed when checking the state at a game level like pause or so.
- when the state changed let the state just disable all other queues and just enable the one single queue for pause state.
- anyhow this cannot be built into the engine as this is game dependant and the programmer will need to do it.
- but it needs to be discusse dhere as i can build a system which will allow the programmer to implement such a system.
- so how should we go about implementing this system for blocking events based on events. let me read that shit agin.

- now that i think about it even more the only time when the mouse functionality oh hovver or click or whatever breaks is when muilitple entities are areoverlapping.
- if they were all independant then there would be no issue of whether we clicked on the entity or not because there would be no overlap between any entities
- in this case all the entities can maintain their own state of whether mouse enter hover or exit or what not whenever the mouse moves and clickes
- the only issue comesup when the entities are overlapping, meaning their collision masks are overlapping, so the entities cant distinguish on which entity the mouse is on
- so we just need to find a solution for this situation iof an entity is colliding.
- so instead of sinply sending a mouse event. we can alter it to contain some more information by precalculating if there are multiple entities under the mouse at that point.
- then the mouse can just set its own property of which entity is the actual target currently
- although all the entities will recieve the event.
- if they wasnt to avoid such collisoin and only need to handle when the mouse is actually over that entity then all they need to do is to simply to check whther the target is themseleves
- is they arent they need not process anything.
- this method of having a target will also simplify each object needing to maintain the onenter on exit hover mouseover kind of states by simply checking for each mouse event if they are the target or not and need not have to hold any other variables or do any other calcualtion other than just simply checking target == this.
- so the main bulk of the issue will eb how can we calcualte the mouse target whenever a mouse event occurs and how will we add this new information to the existing mouse event
- once a mouse event occurs it will need to check the current positionof mouse, and the poistions and zindex of all the objects that will interact with the mouse and set the property mouseOverEntity as some entity object pointer.

- what i though was once a mouse event occurs it will go through all the objects that has mouse handling callbacks, get their collision mask and z-index. then find the one that is colliding with the highesdt z-index.

- now although i say that, it may be inefficient as there may be many objects that may need to handle input events and not all need to handle specific mouse based events.
- so we may need to have a separate queue who want to participate inthis checking from mouse.

- another issue that i found while thinking was that what if there is a controller object that is not part of drawing system then they will not be drawn.
- so theywont have a zindex.
- so we cant just poll any and all objects that have inputhandlers. we will need to specify which of these objects are actually part of drawing system too. then only poll those objects.
- but we cant just go throuhg the drawing queues since there may be multiple objects thatoverlap like the ground or background asse4t or whatever which are not part of the input system.
- this will throw the system into whack.
- so it has to be partof bboth input and drawing.
- but what if they are part of them both. like a character who only takes in keyboard input. why check for suchan event if not needed.

- i think ive touched upon a core issue.
- this is basically collision checking of mouse on entities.
- in collision check also we will have to tell which all entities are going to need collision checking
- there can also be drawn entities that do not have collision check
- even when we have a gui we will be checking for collision against those elements.
- like buttons fields and maybe even emoty divs etc all come under collision checking
- a dom can contain hundreds of node that canall have their own event listeners for collision checking.
- even an empty div can have an event listener attached to it to check whther mouse is hovering.
- now thati think about it the most common mouse events are going to be hover which is defined in css.
- for js there is mouseenter, mouseexit, mousemove,mousehover and mouseclick
- we already have mousedown , up , and mousemove, the rest are just built upon this.
- it wont go checking for collision for all the entities only those that have callbacks registered.
- but that does not tell how bubbling happens.
- when we have parent listeneer all the vhild elements are also checked for clicks because the target can be those children instead of the one with listeners
- hmmm?

- today we will make a game and then after making it we will go on to implement a proper esource system
- the resource system to be split into multiple resources and accessed globally is needed.
- anotherthing to do is to change the readme so as to resemble that of an actual usable game engine and not that progress milestone stuff. remove that into its own file.
- give disclaimer that it is under heavy development and features are partially and not completely done or even properly tested and fixed

- now lets get on to the ideas for games.

- wait . lets do games later.

- an idea for intent syste.
- lets say that the input manager also can decide which actions are acgtive or can be active.
- so lets say, when the game is playing all the action related for playing like move left, move right, jusp etc intents are active.
- now lets say that the game is paused. all we need to do is change the mapping of controller input to actions and everything changes,
- since none of the game objects might have actions related in the pause screen, so player wont react to action_changeresolution or so.
- this might just work
- sothe action manager can have different files actionmappers loaded for each game state. and when the game state changes we just simply swap the actionmapper used.
- so this way the entiore mapping will change away.
- what this will allow us to do is that it will contain new mapping for each state.
- so even if we have the pause screen menu showing above the game screen pressing left or so will not trigger the player and will be handled by the menu because the actions are diffreet
- this will also work ven if the menu object does not bind all keys to prevent daisy chain effect. so we just need to swap out the action mapper.
- one issue with this technique is that although it a completely working solution, is the efficiency on swapping out this object. im gonna assume the objects are looaded first itself and the refernce to it is swapped around.
- so basically y swapiing references we will not have much of a performance impact.
- damn we got the solution for input issue here.
- anyways we need to test this sytem before we finalize on it.

- input system will need to be made into queue based like for updation.

- we will also need to be able to store multiple context and have them enabled and disabled as needed. this will only be accessed by the game object.
- but what if we need multiple active context, then how are we going to swap it or tell it to stop.hmmm. what about just having one intent pointer for now adn mapping all required for that state onto it,.
- yeah lets just go with one for now.

- since these issues will not actually impact us majorly currently. lets actually make a game now. need not even be usefull. but ;ets just.

---

- it has been some time now and now i can look at it with fresh eyes.
- for the input system. each actionmapper is now a context. so for different context we can have different inputs enabled.
- for the mouse collision issue we are going to implement the mouse as a in game cursor. so it is basically collision checking only. same as any other UI check.
- during this time i looked into a lot of html css ui tools to make ui in cpp. maybe we can use it.
- i have a new idea for a simple grid like game inspired kind of with action poinnts thingy. ore on this later.
- now i felt will work on the resource amanger. as that is a self contained module for the engine once that is done, i will not need to worry about loading of assets and i can just not think about that module any longer.

## cleanup of resource manager.

- so what we are going to need to know first are the different types of resources needed.
- resources can be anything that may only be loaded once and used multiple times later and need to be unloaded.

- some are textures, fonts, sfx, music, animation. i cant think of any more currently but im sure that others may pop up later .
- so as to acomodate all of this using a simple single interface it will have a modular design.
- this will allow me to add more resource loader modules later on if needed without much effort.

- shaders
- images
- textures
- fonts
- sound
- music
- animation

- these are the basic resources that i came up with once i went through the docs and animation while development
- i am only going to make a texture resource module for now.
- since once the system is made the other modules can be made when they are necessary
- since my engine is still just coming up music sound fonts and other stuff dont seem that important as being able to see something move and interact on the screen
- so the texture module is the only one that is really necessary as of now

- ### this is the specification for the new resource handling

  - each module will be a self contained loader.
  - a texture module will load a texture, a font module will load fonts etc.
  - what these modules will do is have functions for loading of the resource.
  - there are currently 3 main loaders in sfml that i found
  - load from file
  - load from memory
  - load from stream

  - load from file and memory i can understand. but need to check out how stream works and whether it is actually needed and/or widely used.
  - if not widely used it can be moved to a later release cycle.

  - currently we will only have method in module to load from file as that is what is really needed.
  - now that i look at it loading an animation resource does not load from a file.
  - so i dont think base classing these modules from a resourceLoader is a good idea as different resource may have different methods and signature for loading of the resource
  - the only odd one out currently is only the animation module which will have a different signature for loading of the resource.

  - so now lets talk about what these modules are going to do.
  - off the top of my head they will only contain function to load the resource and return a reference to the resource loaded
  - maybe also a function to unload it memory when a reference to the resource is passed to it?
  - or should it be part of the resourceManager class. maybe its better to be part of the resource manager class.

  - so what is the resource manager
  - the resource manager is what calls the respective modules' loaders and stores the reference.
  - what i want is that any object entity in the game can call the resource to get the reference to that resource
  - which is why i want it to be static .

  - all of these resource will be associated with a handle so they can be referenced via this handle
  - but the entity themselves may not know what the handle for that resource may be
  - ive been thinking of loading screens where these resources are loaded.
  - so i thought there could be a loader class which told which all resources need to be loaded. and just calling the loader instaces' load method would just load all those resources immedietly or clear them when needed.
  - but i dont know if that is needed. as some resources may be shared between sections and the resources will be unloaded atomically with all other unwanted resources.
  - also i dont know of a proper method to implement these loaders too.

  - also these modules also can be static as they do not store any information, but just simply encapsulate the related functions for that resource together.
  - since the modules may have their own signature for function to load the resources, they will have to be called directly.
  - so maybe we can have these loaders itself store the references to the handles.
  - so then what is the purpose of the resource manager? if we are directly calling these individual classes.?
  - i wanted the resource manager to hold the references and handles map. so the user only needs to ping resource manager with what type of resource and the handle to that resource
  - then resource manager will return that resource.
  - but for each type of resource there will be a need funtion to load and get the resource.
  - so basically it will simply be an aggregate getter and loader for all the modules. although that is useless and we can simly directly call the modules.
  - hmmmmm? ? ? ?
  - so if we added another module we will need to add the getter and setter to it also keep a reference to the acutal loader class. which is just a waste i feel
  - but i wanted a central hub to be able to call whatever resource type we needed.
  - hmmmmm?????????????????
  - let me think a bit

  - one idea that pops into my head is to ditch the module design. and just implement the needed loader getter function in resource manager itself.
  - when a new "module" needs to be implemented just make their functions defined in resourceamanger
  - this one will not need to have any reference to moudle as the loader and getter fucntions will differ automatically
  - and have unordered map for each differen type of resource
  - this method actually does not cause thatmuch problems anyways.
  - i think this is good

  - ultimately no change form the current way except for the feature of user defined handles
  - ok. i have thought about it.
  - the current method is still better.
  - we are going to allow custom handles and implement animation loaders and getters too for this iteration.
  - so lets get coding
  - wait. hmmmm. there are 3 loaders as mentioned above. so for each module we will have to have 3 loaders if we wanted support for all and 1 getter.
  - but since the interface is different, it sucks. we can make animation as load from memory buuutttt....? not really sure.
  - nah. fuck it. 3 laoders for whoever needs it. for now load from file and loader for animation.
  - so lets actually get to coding now.
  - lets make the loader function recieve the handle value as template so it needs to be constant and is not a variable.
  - why not let it be a variable. what if they have a list of handle and file paths or something which they want to load by simply looping through it.
  - ok let it be a variable.

  - one issue that has come into the light is that if an entity variable is dwclared insdewclared in the game object and the netity needs to load a resource in the constructor that can cause a problem
  - as the loading of resources has not been set yet andin the ggame class but the entity constructor was called first.
  - whihc will cause it to try and access an unloaded resource.
  - that could be mitigated by simoply havinf the entityh be a pointer and then initialize after game conmstrcutor has been loaded but that is not a proper solution as thois forces the programmer to use pointers.
  - one way around thatg is to just have a function in that entity to set the resource and af ter the resource is loaded in game just call that entoty resourcce loading functioun

  - truth be told now i have no idea what direction i should take this forward in anymore.

  - i think im gonna make a game. not exactly a game but a simple grid based structre.
  - the details will be available in the readme for that project.


  ~~- TODO make input handling on by defualt~~

  - one of the things that came up while i was working on grid selector was the need to have tranforms on the grid.
  - once we transform a grid, the cursor will also needto be transformed appropriatly
  - so i thought that if we had a parent object then whatever transform was appiled to the parent will also be aplied to itxs children.
  - so maybe i should look into scene graph next.

  - during thew making of grid selection i have realized that i need a tilemap system before i need the scene graph.
  - it is so i can easily make worlds that i can interact with
  - in fact im next going to work on the grid system to actually make a usable system like in advance wars.
  - i have downloaded the sprite sheet for advance wars and ill start using them to build a mini game once i have the tilemap system in place.
  - but now that i think about it i have no idea what or hoq exactly a tiolemap system is supposed to work.
  - so i will need to spend a couple of time to learn on it.

  - there will be no development today.
  - today i went through tutorials on tilemap engines and what not.
  - i feel i have understoodit fairly well
  - i have found 2 editors for tilemaps. 1st is obvious tiles. then the other one is ogmo.
  - i am going to use them both and see how they function. how they export and whatnot.
  - but i have been thinking that they may not be the most ideal
  - and i might want to write my own tilemap software
  - ive been thinking of using vue and electron to write it as writing one with qt or something is going to be much more trouble on a good looking app
  - since i am a web dev making UI and functionality will be much quicker using electron and a ui framework.
  - from what i have seen of the xported data of tiled i think the tilemap as a resource will be useless as it might only load the tilemap. generate the tilemap from the texture.
  - then it will load that texture into resourcemanager.
  - this will then make the tilemap obj useless other than a tilemap file loader.
  - hmmmmm?? so we might need to redesign somethings over here.
  - for tomorrow and maybe after that i will be playing around with these software and see how they work. what functionalities they offer and make notes.
  - and once i have better understanding of that i will see how i shoud redesign the tilemap obj or bring something new to the table. so there will not be much development for few days maybe.
  - but all the updates for every day will be recorded here.  

  - i have been thinking about the tile map editing feature.
  - irrespective of if i use tiled or ogo or any other tile editor i will have to have multiple layer support in that software
  - but if i want to load each layer separately into the resource manager it will havbe to be exported out as separate files
  - but that is not good, but instead export in single file.
  - that means whenever we load a tilemap file it will have all the layer.
  - the obj that will load that tilemap layer will then need to create all the separate layers into textures for it.
  - then the obj that loads the textures will be useless once the tilemap has been loaded.
  - if we load make a function for it all the required handles will need to be passed to it while loading, but different tilemaps may have different layers.so that is not feasable;
  - so we would still need an object which can parse the exported file and generate the textures. once generated we will have to manually assign it to a handle in resource manager.
  - then we will have to create a object to load the tilemaps
  - this is making the notion of having a loader object be available. such that this loadder object can be called in loading screens to auto load the resources with the correct handles.
  - this should eleiminate any loading of objects or resources in the game calss and a special loader instance can be called to load the needed resources.
  - so in the game class we should just load the loader obj
  - so there shoudl eb a new file format for loading of resources.
  - maybe we can have a loader to load the loaders lol.
  - yeah with that we can have dynamic loaders
  - i think this is a necessary addition as this will allow us to load a lot of stuff in a batch as well as provide a progress bar or something of the sort
  - maybe this can be called in a separate thread too. but lets leacve that for now.
  - what we need to do now is to create a format for the loader class to laod and actually design the loader class itslef
  - so first lets design the loader class itself

  # MAJOR UPDATE
    - since my current situation in life has hit a shit point i am going to put this project into haitus, until situation improves
    - since i need to work on other factors regarding my job and what not i will not have time to concentrate on this project. so i will not work on this project for some time till i can get into a better situation with my job.
    - so there wont be any updates for the foreseeable future as i have no idea when the situation might improve.
    - once it improvesi will immedietly pick it back up.

  # Update 
    - i have been looking to improve my skills these past one month approx.
    - now i see that i dont really study continuosly for days on stretch, so i think i should utilize these times to work on the engine to not be burnt out and to keep myself productive or motivated
    - i have read the last few paragraphs to get the gist of what i have been working on .
    - so here are the things that are needed work on. scene graph. tile editor, import export etc. and resource loaders.
    - so the main concern i saw was that a loader will be needed. so i am going to work on designing the loader file format.

    - so first lets get a grasp of the resources that can be loaded.

    - fonts
    - music
    - textures
    - sfx
    - shaders

    - these are the default resources.
    - but i have custom resource like animation curently. should that also be part of the loader.
    - it could be then we could just simply load a texture and it will load all the animations for us as defined in the loader file
    - so no new code to be written specific to the game to be able to load these animation per game
    - just write the loader class and and it will load according to the loader file
    - they will only need to write the loader file which is going to be much more straightforward to write.

    - so for the loader file we need to able to load sfml and our custom resources.
    - i just thought about unloaders , if we pass the same loader handle trhen it should unload qall the resource loaded in that file
    - this means that we will need to split the loadersinto multiple  file for those that persist or are needed in multiple loaders.
    - currently lets just assume it will unload everything in a loader file and continue dev on that idea.

    - ok i have come up with a format for the loader file. this may change in the future as i am not convinced by it.
    - any way here is a sample format for texture and animation

```
:TEXTURE              // Texture block
1 C:/.../text1.png    // handle file_path
2 C:/.../text1.png
3 C:/.../text1.png

:ANIM                 // Animation block
4 2 4                 // handle texture_handle num_of_frames // makes sure the texture referenced has already been loaded
32, 0, 32, 32         // coordinates of 1st frame
64, 0, 32, 32         // coordinates of 2st frame
32, 0, 32, 32         // coordinates of 3st frame
0, 0, 32, 32          // coordinates of 4st frame
```


    - as you an see im not too pleased by it since it has to be readc line by line or some shit for now
    - what i want to do is parse it to get a data structure like json and be able to query for the needed sections in order and check for syntax error or whatever.
    - for now we will just have to do with this incomplete albeit working structure
    - the format for fonts and the other will follow for that of texture as they all have the same load signatures.
    - animation has special signature as it is unique and has a different way of loading.
    - so now lets get to making the loader instance to be able to load these two resources for now

    - i am thinking making the loader also be considered as a resource.
    - then the loader can be called from anywhere at any time as needed
    - this will also allow us to load other loaders from a loader
    - so we can have a single file which will load all the other resource loaders.
    - this way we will only need to write code for that one file. 
    - and we can call load on the other loaders as needed
    - i think this is a good idea.
    - for now lets just get a working loader for texture and animation

    - now  we have completed a simple not great loader
    - next lets see what was needed.
    - so the next thing that is needed is tile editor
    - so now lets use tiled and ogmo to see how those work and see if we should make our own or just use those.
    


    - now we are just going to improve upon the loader system.
    - it will have a list of texture, animation, font etc array of details parsed from a loader file
    - so the file reading will be done at the beginning and stored in memory
    - this will give us control of loading and unloading of resources.
    - also will not need to parse the file to understand what resources are loaded where at the time of unloading.
    - it is also helpfull because we will then be able to define the loader sections without any ordering and the loading order can be done in code
    - so i have thought of a basic structure for this.
    - it may change later on
    - so what we are going to do is that we will have structs to store the information for the resources.
    - then inside the loader class we will have array of these struct objects.
    - these objects will contain the data that has been parsed from the file.
    - so now we can easily load these resources by simply looping across these arrays in the correct order without worry it was written out of order in the file
    - and the same goes for unloading. simply need to loop through these arrays and call the respective unload function with the correct handle for the resource.
    
    - so lets create a file for the definitions of these structs.
    - then add array of these struct to loader.
    - the loader will immedietly parse the file in the constructor and store the information in memory.
    - although all of the data will be stored in memory, i dont think it will impact much
    - if there are loads of resources that need to be loaded, we can simply load the the necessary loader file as and when needed.

    - the new loader system has been implement.
    - now i want to see if instead of reading a text file for loading the resource maybe we can have a binary file that will be easier to parse.
    - so to create those binary files we are going to create an application for it
    - i think i may want to use C++ and Qt for it. so that i can learn using Qt too.
    - so i will learn how to develop UI for C++ applications.

    - heres what i have thought up
    - if we have another application to make that binary file and our engine read the file, it will be exclusive. it cant be used else where
    - but if we make it into a library, which both creates the binary file or something of the sort and also parses that format, thenit can be used elsewhere to
    - so the game engine and the new application can reference the same library to both create and parse it.
    - in case the format or so changes then we only need to link to the new lib version and have minor changes to actual code.
    - yeah. so i think i will first make that library. the have it link to this and the other application which will need to be created.

    - ok the lib for loading teldr has been done andit has been integrated.
    - now we need to remove the previous code that was used to load the resources and use this new lib.
    - this previous code for the loading of the resources has been removed and the new lib has been integrated.

    - the next thing to work on this is the tile system.
    - so now i will need to check out tiled and ogmo editor.
    - i will first check up on the ogmo editor.

    - i checked out the data format of tiled map. it is base64b encoded. 
    - decoding it will give array of bytes, which is to be taken as 32 bit unsigned int.
    - this num that we get is the global tile id. 

    - ive been thinking about the rendering of this tile set.
    - we cant just willy nilly just render this crap as this will require a butt ton of draw calls, which will lead to lag,
    - so what we need to do is batch these vertices for the sprites and then do a single draw call.
    - since every layer may have multiple textures ascociated with it we will need to create a map of what texture to what sprite.
    - now we will have to make a draw call for every texture for every layer.
    - although it might seem like a lot of draw calls, it is much better than the num of sprites.
    - so we will need to implement this first to have efficient rendering of tile map.
    - so this is what we need to work on.
    - so i will need to get the texture, the vertices, the tranforms and any other shit needed.
    - then i will need to return that from the sprite, and then store it somewhere.
    - i will also need to keep lookout for the latest version or so of SFML as batch rending is in the works.
    - for now lets go see the tutorial on vertexarrays

    - I have taken a look at the vertexarray tutorial, it has a example on tilesets.
    - but it is so that the entire tileset is based on a single layer.
    - also there is the issue of multiple layers and animated sprites.
    - each loop we will have to do an update on the animated sprite to update on to the next animation frame.
    - and for each layer, it can be done with different layer system built into the drawing system already built.
    - so we will need to split the layers into the correct drawing layers.
    - also for the animated sprite we cannot just store the vertexes but need to store the actual animated sprite object.
    - so we may need to generate all the verteces for each loop.
    - that is not acceptable.
    - so what we need to actually store those vertices that does not change and only update the verteces for animated sprite.
    - can the vertex array store references to the actual vertices.?
    - if that is the case then we can simply update the animated sprite and it will also update in the array.
    - then we will not need to generate the vertexarray. it will be automatically be updated.
    - ok. we can look it into doing that. lets see if we can do that by storing the references to the vertices.

    - i just googled array of references and apparantly it is illegal. welp.
    - so we may need to create the array of verteces every loop. dont think that is gonna be much of an issue. lets just leave it as that now.
    - so for the tilemap object it will generate the entire vertex arrays.
    - since it is generated each loop we can also update the animated sprite without much trouble.
    - the next issue with this is the animated sprite itself.
    - how do we know that the sprite there needs to create a new sprite for animations.
    - shouldn't it automatically create the animated sprite as needed. yes it should. then we will need to generate the method to do that also.
    - let me take a look at the class of animatedsprite.
    - so the defaults for the animated sprite is enough.
    - the animation will have to be specified in the tilemap file that we are going to be loaded.
    - so the tilemap object will know that the current tile is an animation tile.
    - we will also need to set the time for animation in the tilemap file for each of the animation. with a default of 1 sec or something if not specified in the file.

    - so lets say in the tilemap file we will define that global tile id of 3 or so will have animation handle id of 5 or something. so the animation will need to be loaded before the tilemap file is loaded.
    - this will allow us to not define the animation in the tilemap file itself and use the loader as intended. also this reduces the information to be stored in the tilemap file.
    - since the animation data will not be stored in the tilemap file we will have to define the animations in the loader file separately. 
    - i think this is good as this will allow the tilemap to not dictate what the animation needed are, and can be changed without changing the tilemap file itself.
    - the purpose of the tilemap is to only tell what tiles go where and whether that particular tile is an animated one or not, and what the animation handle might be.
    - so we will only need to implement a function in the animated sprite to return the vertices that it has.

    - even though i have said that we have to generate the array, we only technically need to generate it once.
    - once it has generated we can simply store the positions in the array that contain the animatedsprites and simply update those positions with the new vertices.
    - so only the animated sprites vertices will be generated. so we will not need to loop through the entire tilemap, but only the indexes that contain the vertex for an animated sprite.
    - another simple matter is that we only need to create a single animated sprite object for each animation there will be and simply use that very sprite multiple times.
    - hmmmmmm....
    - if we only had a single animated sprite for many of the same animated tile in the tilemap then we will need to only call the update once every loop for that animated sprite and not multiple times for each animatedsprite which contains the same animation.
    - an issue with this approach is that it will have to change tehe position of the animated sprite every time which is not possible...
    - ok. we will create the animated sprite object only once. 
    - let me try to explain what i though here now.
    - first we will generate the entire tilemap array with simply vertices.
    - then whichever tile is animated we will keep track of its index and such and create an animated sprite for those tiles. so only 1 animated sprite for the same animated tiles everywhere
    - so during the first creation we only need to set the position of the tiles, and the textures locations.
    - and during every loop we just go through all the animated sprites and update it, then we will go to the respective index and update only the texture coordinates of the existing verteces.
    - so we will only need one set of animated sprites and can simply update it, and only need to update the texture coords of verteces every loop.
    - so that means we will have to have a mapping of all the index in the vertex array to the correct texture. how can we do that efficiently.
    - instead of storing the indexes in an array we will simply store it in a map to a reference of the animatedsprite.
    - so each index will have a reference to an animated sprite even if the animated sprite is the same.
    - the animated sprites and the indexes can be stored in their own arrays.

    - so to recap. we will have two arrays.
    - 1 for indexes of animated tiles, another for pointer to the created animatedsprites.
    - on loading we will create the default vertex arrays. then set its positions and its texture coordinates.
    - then on every loop we will update the animated sprites and and then loop through the indexes, for each index find the reference to the animated sprite in the map and apply its texture coordinates.
    - thus we will have updated all the textures and everything of the tilemap.
    - then we can simply draw the tilemap.

    - so for the first issue a solution has been found.
    - now the issues are of multiple textures and multiple layers.

    - multiple textures is an issue that cannot be solved with the current tileset class method.
    - as different tilemaps may use different textures. 

    - lets first tackle the issue of the layers first.
    - if anything is there in the tileset where one tile is on top of another but it comes in the array index earlier than the below one then due to painters algorithm this will draw it the other way around.
    - a simple solution to this is to not have tiles overlap each other in the same layer.
    - if they overlap then just move it to another layer instead.
    - so now the overlap problem with drawing is solved in the tileset itself.
    - each of these layers will then be a tilemap object in its own layer in the drawing system.
    - they will be in the appropriate layer given by the exported tilemap file. maybe add a custom property which tells which layer in the drawing system will this layer in the tilemap will it go to.
    - for simplicity sake we will have it just go from 1 to n as default. it may be overriden by manually specifying it.
    - now this solves the problem of layers and overlapping tiles in the tilemap with how it will be drawn using the drawing system.

    - now the last obvioud solution is the trickiest of all, the multiple texture per tilemap issue.
    - the issue is that we can only draw a set of vertices with a single texture in a single draw call.
    - so when there is multiple texture we will have to split up the texture into multiple draw calls.
    - each tilemap may also have n number of textures used. so we cannot hardcode it or anything.
    - the best possible method with a tilemap object way is to simply have separate tilemaps for separate textures.
    - but this in itself poses problems. like we will to figure out which global tileid refers to which texture and will need to split them up properly.
    - so a single layer in a drawing layer will have multiple tilemap objects which will store the vertices for their respective textures.
    - so implementing that will lead to the structure of the exported tilemap and the ease of parsing it whether we can actually parse it properly to make enough tilemap obejcts out of it as necessary.
    - one another way is to simply return the vertecesand textures and create a map of it in the drawing routine and the at the end draw it all.
    - this method will also allow use to collate other layers also into it like the sprites of players or entities or so if they use the same texture.
    - now another issue that arises with the texture is the ordering of it again. now we might have do like tex 1, 2 ,1 in can arise so the ordering is preserved.
    - this allows us to reduce the number of call to draw too but implementing is not that easy as of now, as not much thought has been put into handling all of its edge cases.
    - so what we will go here is to have multiple tilemap objects and then each have their respective textures and their verteces stores and just drawn in order.
    - the issue of generating these tilemap objects will arise if parsing of the exported file is not proper.
    - so we either need to set a standard for the format we are going to use so that all the other formats need to only convert into that format for its functioning, or we create separate handlers for each of the different formats.
    - the most popular and common tileset is most probably going to be tiled as it is used widely. it has both the xml and json format parser
    - for understanding it we can use an already existing lib for parsing the file. which is tmx or json parser.

    - so i also like the idea of defining our own format for the creation of the tilemaps as this will allow us to standardise and integrate it easily onto the engine
    - like for example be able to create multiple tilemap objects incase of different textures for a tilemap.
    - if we were using tiled or any other format then we will have to do special processing for each.
    - if we have a standar format then all we need to worry is about that format and we only need to work on it.
    - if anyone wants to use tiled format, then all they need to do will be to convert that into our used format and it should work without any issue.
    - also we can also make converters from our format to other format too.
    - this method is more extensible and standardised, and less work to do in the long run in case people want to use other formats, the overhead is that they will need to convert it into the standard format. 
    - on the other hand we can could simply use native format for tiled, but it will be very specific to tiled, and if any other formats are used we will have to write code to handle that format too.
    - distributing the standard format for this engine is little tricky as it will have to be converted to tiled or some other format for other engines to use, while using tiled we can simply send the tiled format which they probably already support.
    - so the issue is locking it in our engine ecosystem standard vs having a common standard that everyone can develop to.
    - the main trade of ease of implementation and integration, and distribution of the tilemap file.
    - to ease this problem we should also create a lib to convert between from and to the standard that we will make.
    - this will allow use to directly load tiled files and store it as standard defintions and will also allow us to export standard defined files to tiled or any other.

    - so lets recap on the tasks.
    - first is to create a standard format for the tilemap file. so we need to consider what all features are currently there in the engine and see how that all can be used in the tilemap.
    - second is to create the tilemap class which holds the vertexarray and the texture. it should store the needed arrays and indexes and what not for animated sprited and all.
    - then we need to have a parser for this tilemap file to be able properly create this tilemap objects, animated sprite and etc as needed.

    - now we need to define the format and the content of the tilemap file.
    - so i need to look at different markups for storing daata like xml or json.
    - im not gonna simply use json or something as this is very specific to my engine i probably can simply store it in binary format or some shit.
    - but storing it in binary format will not alloow us to edit it quickly if needed.
    - so we will allow for oth text and binary storage of these files.
    - once a production tilemap has been created we can store it efficiently in binary format inst3ead of text and waste memory.
    - also we will allow it to be stored and exported in text format for debugging or dev purposes so that it can easily be modified directly for quick changes if needed.
    - so this is going to work like the lib for loader but it will allow to export the data in binary and text formats.
    - so we will need to be able to both load and store in both binary and text formats.
    - so a total of 4 functions for loading and exporting.

    - now comes the data that needs to be stored.
    - we can consult the tiled format to see what all it supports and that will allow us to chalk up what all we might need.
    - there will be some features of tiled that we may have not implemented yet, so will skip those for now and add it as it goes along.
    - so the first is to identify what all data is there in tiled. then find out what all other data we might need while rendering the tilemaps. eg the arrays of indexes.
    - once we have that we can both find the common ground of data that will absolutely be needed.
    - then we can find out what data can be computed but can be usefull if included so another computation need not occur. so memory vs execution.
    - so we need to find a sweet spot for it.
    - so now let me go have a look and take notes on the data exported by tiled.

    - the details of the tiled map exported file will now be listed below
    - only those properties that are deemed to be important as of now will be noted here.
    - anything else will be discarded like hex or staggered or isometric details. etc.

    ### Map

      - orientation - orthogonal, hexagonal, isometric, staggered. currently we only have orhtogonal to work on.
      - renderorder - rendering order of the tiles. right-down, right-up etc. currently only supported for orthogonal maps.
      - compressionlevel - the level of compression. -1 is default algorithm compression.\
      - width - the map width in tiles.
      - height - the map height in tiles.
      - tilewidth - the width of a tile.
      - tileheight - the height of a tile.
      - backgroundcolor - default is fully transparent.
      - nextlayerid - stores the next available id for layers. (dont think this is that important as entire layering will be done at developer discretion).
      - nextobjectid - same as above for objects. again may be needed as dev needs to be allocate the ids manually accordingly.
      - infinite - whether the map is infinite map or not. may not be usefull currently as we will force it to have fixed size initiallly.

      this can contain max 1 property section, and any number of tileset, layer, objectgroup, imagelayer, group, editorsettings.

      #### editorsettigns
        
        - chunksize - the chunksize for infinite maps default to 16. contains the width and the height of the chunks
        - export - details about last exported file and the format of ot.

        these are generally not needed for reading a map, conatins editor specific settings.

      #### tileset

        - firstgid - so every tile is marked by a gid which tells the tilemap which tile go at a spot. so even if there are multiple tilemaps the gids allocated to them is in order. so once a tileset gid are allocated the next one will continue with next gid instead of starting at 1 again. so it can basically be considered that it is a continuous tileset where the gid are continuous but the texture files have been split. so this tells us what the gid of the first tile in this tileset is. so we can find the right tileset when needed to from the tilemap.
        - source - basically the texture being used as a tileset. if it is another tiled file then this will point to that. we cahn simply have this point to the texture handle as needed. since the texture will be loaded using the resource loader.
        - name - a name for this tileset. although i dont find any need to do this. could be usefull. but cant find any reason as of now. so pretty useless for now.
        - tilewidth - the maximum width of the tiles in the tileset. we are just gonna have uniform tile sizes for all the tiles in the tilemap.
        - tileheight - same as above but for height.
        - spacing - the amount of space in the tileset between the tiles. could be due to that the tilemap was made with some spacing to distinguish the tiles or so. but we wont be using it. we will require the tileset to not have any spacing in between them as i consider it as a waste for the texture size.
        - margin - the same as above but for margins. this too will be useless. this and the previous properties are good as they allow the tiled editor to automatically detect the tiles properly if there are any spacing or margins between them. but if we dont allow any spacing or such then we will force them to modify the texture file to fit. if we took the spacing and sch into consideration this will allow them to use the tilemap as needed without any issues. but we are going to force them to remove the spacings or so. since i feel it is just a waste of gfx memory to have it loaded. the lesser the space needed the better. so let them have it modified. i think we can use the tiled itself to create the tilesets as needed. 
        - columns - the number of columns in the tileset. it could be usefull when trying to find the correct tile to render. but then i think wont we need a count of rows as well. since it has not been specified, we could add it as we see fit.
        - objectalignment - controls the aligment of tile objects. i have no idea what this is so probs gonna ignore it.

        for all intents and purposes this reference to our tiles texture files. so basically the details of what all texture files for the tiles are used, how many, the dimesions and such details are specified in this section.
        so we can know the number of textures used in this tileset from this section.

        can contain at most 1 tileoffset, image, grid, properties, terraintypes, wangsets

        ##### tileoffset

          - x, y - offset to be applied when drawing a tile.

        ##### grid
          this is only used for isometric shit. so ignoring for now.

        ##### image
          this contains the actual texture file details such as its path, the supported file type etc
          - format, source, transparency color(like magenta or shit that used to be before alpha images), width, height

        ##### terraintypes
          contains different types of terrains that can be obtained from the tiles terrain attribute. terrain is prbably that automatic drawing of edges and shit for continuos crap. but we dont need to worry about it since once the tiles are exported terrain or not every tile id will be obtained, so simply drqaw as usual. i dont think knowing the terrain details other than for any other code or trigger kind of purposes has any use in rendering the actual tilemap.

        ##### tile
          this contains the actual details of a tile in a tilemap.
          - id, type such as object or what not, terrain if it is the represting tile of a terrain tile, some probablity shit.
          can contain some shit within like image , property, animation
          we dont need to actually worry about it for now. the animation will also be defined in another place as animation is loaded by the loader and is not part of a tilemap. 

        ignoring everything about wangsets as i have no idea about it.

        ##### layer

          - id, name, x y coords probably to set offset of layer from another. mostly not needed i guess,width height pretty much duplication of above data of map, visible or not which i think is useless as controlling of visibility will be from code and not reliant on the data of the tilemap, offsetx offsety whaaa. no make sense. but whatever. 

        ##### data
          contains the actual data of tiles in the tilemap
          - encoding, compression. pretty self explanatory.

          the highest 3 bits store the flipping infor for a tile. check the exmaple in the doc to know how to parse it.

        ##### object group
          contains different object shapes and their properties.
          You generally use objects to add custom information to your tile map, such as spawn points, warps, exits, etc.
          so there can be things like points, or regions of interests, like trigger region or spawn point.
          it can also define collision areas. but since some collision may need more fine grained collision detection that AABB so we may need to hold back on this aspect for a while until the details of the collision and spawn point and such information is understood better
          since objects help us define custom properties we cant really automate that part of it. so we will need to think of some other way to be able to handle those aspects too
          it can contain many different shapes of objects within it. for more info on the objects check the docs.

    - so this is basically the bulk of the actually needed info on tiled that we may be interested in. there are other shit too but i dont consider them to be that important to us currently
    - so we are gonna ignore some of the information in the tiled map file.
    - there is also the issue of having custom properties for tiles which may be needed but since it is custom i dont really know how to best handle. 
    - since what we are trying to do now is to automate quite a bit of the common gruelling work of rendering and other game enginey stuff. 
    - so the custom properties cant really be automated. if the custom properties define whether the rendering should be affected then that is even more of a problem if it is not a standard change to the rendering like simply having the feature to flip a tile or so.like maybe draw a specific tile scaled to 2 for eg. that eg is very rare but whatever.
    - so first answer to consider is whether we should even allow the addition o9f custom properties. next if we are going to add custom properties how are we going to give the dev access to it and if the property is to affect the rendering then we cannot handle it. so then what should we do at that time
    - the rendering itself is a great issue which means if rendering is to be affected then we will have to hand over the control of rendering to dev. but that is exactly what we are trying to avoid.
    - so we wont allow the dev to gain control of rendering, so any tile needed to modify rendering will have to be a standard rendering change like tile flipping which will be implemented into the rendering system of the tilemap.
    - so basically any properties that may be related to rendering is off limits.
    - so now what other kinds of properties would they want. i cant currently think of anything. so we will leave custom properties out of it for now.
    - the only custom properties that would need are the ones that may be related to objects points regions and such. since those need to be accessed by code to do stuff.
    - object layers may be drawn. but i dont think they will always be draw stuff. they are more coding related. like collision box. so for that aspect we may need to devise an entirely new mehtod, or if we use that method we will need to expose it probably via a resource or something. which i do not know as of now. 
    - so we will assume for the time being that tilemaps will only contain the tiledata that will need to be rendered on to the screen and will not have any information that will need to do or help additional calculation such as collision or such. any other information that it uses will be for purely redering purposes.
    - for eg we could have custom property on a layer which sayas that its parallax speed is gonna be x so a parallax effect takes place. hmmmmm.. this is very confuising. since that is coding aspect but since the layer is automatically created we have no access to it with code too. dammmnn... what a bind.
    - also there is the issue of tile culling so that entire tilemap is rendered even if it is outside the regions of camera. 
    - i dont see a good way with the current system. we might have to pass in a camera or view object to restrict its rendering array, so onyl the required vertecews are rendered. other than that this we can forget about for the time being. this is not a major concern as of now.
    - the major concern is the custom propertieds section.
    - so we may need to create a new layer class and be abkle to set some properties on it like the offset it is drawn at and all. then we can simply have a controller object chenge the ofset speed and any other properties. 
    - or we could even make the layer object updateable as needed if needed.
    - daammnn. now this is a problem. i have arrived at making the updatable layer updateable. shit.
    - ohhhh. what will i do for custom properties ...... hheeelppppp. shit. this engine may have very well reached a roadblock or i just cant think of a solution for it currently.

    - need whther tile is animation, which animation handle, and the time period of animation., should the animtion time be for each tile or for all all the animations of that tile.if it is for all same tiles then we can have a single definition. otherwise we will have to create multiple animated sprite each with different times. i think we will just go with 1 time for time of all same tile. so it will be easier to create and manage and will only need a single animated sprite.
    - array of indexes to their respective animated sprite reference. so each loop we only need to go through those indexes and update the texture coords from their animated sprite object. the issue is how are we going to store this data. the first that came is a map of index to sprite reference. another that i thought was animated sprite ref to array of indexes. the latter approach is better than first as it collects all the repective indexes into a entry in map. is there any better way to do this. let me think.
    yeah i think map of pointer to animated sprite to array of indexes is good enough.
    - the layers in the tilemap will be used as is like layers in the drawing system. the issue is to assign the layer number. since we are not doing any custom properties we will have to define this layer in the format of the tilemap itself. otherwise there is no other issue with layering that i can think of.
    - for the textures we will need to split it up into multiple tilemap files each with their own respective tileids and the textures. storing the respective gid for each texture for a layer separate is usefull for its ease of parsing, then the problem arises that we mess up the order of the tiles if they are jumbled. to preserve the order we will have to fill in the blanks of other texture with 0 or -1 or something. but this will use more memory. best we can simply use a single array and then the lib will parse it out into multiple arrays for each texture. the lib should also handle the coords as needed.this has led me to thinking, we will use the texture itself as a resource and get its coords. but what if we have a new resource now called tileset. this tileset will define the tile size, the iwdth etc, so we can simply call the tile by passing in the gid. so we get all the coords and all for the tile. this does basically what the tioled does. like spacing and margins and stuff. only here that it will make parsing of the tileset easier and not have to do a lot of repetetive or mundane code to get the tile needed. this object will need the tile size and it can calculate where the tile is located within it. we will not need to do any of the calculation for the tiles. this also has an added benefit that now we can reduce the animation data and simply specify the global tile ids instead of the coords needed. so this will fetch the coords for those tiles. this relies on having a good consistent tileset. which is anyways a given, except for the ones that have been ripped from games where they add extra details like headings and stuff. so they will have to trim the file down. but for quick usage purposes they can create it by using defaults coords too. so first maybe we need to create a tilemap class which can handle the things such as finding tile by gid. getting the tex coords. these two are basically the only functionality that will be needed. one issue that remains is that what if the tileset is not set in exact shapes. like what if the tile has varying widths during the animation. we cant simply have all the width for every frame be set to max. hmmmm.. some conundrum this has become.

    - ok for the tileset information we can look at the tileset info in tiled and how they might be used. 
           
  - ok i have thought up on how the tileset class is going to look like.
  - 1 it will have 2 constructors.
  - 1st one will take teture handle, region, and the tilesizes.
  - this will then calculate the verteces that will fall with that range and will be stored in an array
  - the 2nd will take in the texture handle and will also take in an array of rects for the verteces that will be free form defined.
  - and then it will be stored in the same array
  - the 2nd methos is simpler to implement as it is a simple copy to the built in array with just some constrain checks.
  - this will force that the mixing of these two sections will not be possible. one will be of free form and the other type will be region defined.
  - i dont think separating the two of them is that much of a problem.
  - so now lets get onto defining the tileset class.
  
  - the tileset class has been defined.
  - now lets see how we cam implement this in the loader file.
  - for the loader file we will need to create a new struct with the data to be passed in the constructor.
  - lets go to the TE-loader and define this new resource and integrate it into this.




      

