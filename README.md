# Final Project Proposal | Simple PacMan Game

## Summary:

We will be creating a traditional PacMan game. The user will be able to input their information (i.e. username) and we will store that along with their score in a server through serialization and deserialization. The user will be able to use the arrow keys to move PacMan and gain points when they “eat” the food. The ghosts will be moving at random, and the player will lose a life if they run into a ghost. We will also create the “arena” to ensure that neither the ghosts nor PacMan move to a point outside of the arena. At the end of the game, we will send the scores to our database to be stored, alongside with the player and game’s highest scores.

## Features:
  - ### Classes:
    - #### Game Object
      - An interface with all the required functions needed for a game object, which includes the PacmMan and Ghosts, as well as the Food
    - #### PacMan
      - Move functions, current position variables, constant intersection checks (with the ghosts, food, and arena/borders
    - #### Ghosts
      - Random movement functions, speed, constant intersection checks (with the PacMan and arena/borders)
    - #### Player
      - Keeps track of highest score, name, id
    - #### Arena
      - Boundary positions in the game
    - #### Food
      - Position of food, constant intersection checks (with the ghosts and PacMan)
    - #### User Interface
      - Manages startup screen and different visuals such as the score and number of lives
      - Key mappings to move the PacMan
  - ### Database: AWS Cloud System / Local Server
    - This will keep track of the player's names and their scores
    - After each game is over, the highest scores are displayed based on the data saved in the dataase (The username will be the unique qualifier)
  - ### Server: httplib
    - Send server post requests to save the player's name and score to the database
    - Send server get requests to retreive all the information from the server and store it locally (in the database)
  - ### GUI: SFML (Simple and Fast Multimedia Library) with OpenGL
    - Handles graphical user interface with key binding and displaying game in an interactable window
    - Handles in-game menu ("Reset", "Clear High Score", "Exit") and title screen with a visual for all the high scores
  - ### Serialization/Deserialization: Nlohmann::json
    - Generates json and coverts C++ types to json to store in the server
    - Retreive and send information to/from the server to make sure the scoreboard is saved regardless of what instance of the game is being played and regardless of where it's coming from

## Plan of Action:

Our group will start off with everyone helping creating the core classes of the game, specifically all the game objects, and making sure that we can setup the GUI with SFML and OpenGL. We will then focus on implementing the local server / AWS Cloud System server and make sure that we can serialize the game information into a json file with Nlohmann:json, post to the server with httplib, and also retreive from the server and deserialize the information for the client. This step will take the longest time so it might spill over into the third week. After accomplishing the main hurdles of setting up the core foundations of the project, we will focus on implementing the functions and specifically drawing / obtaining image fiels to be displayed, creating different functions/interfaces for every game object, and handling different keyboard/mouse input using different C++ libraries. The final week we will focus on tackling different gameplay issues and bugs and add on to the project if time permits.

