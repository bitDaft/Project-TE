Random thoughts and musings

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
  - ~~so _2 will not correspond to the correct position in the array when it has to be removed for other pointer~~
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
  - but the obvious issue is the input handler system itself. as soon as  an object is created it is added to the queue.
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