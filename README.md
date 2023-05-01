# snake-game
![Screenshot from 2023-05-01 10-15-58](https://user-images.githubusercontent.com/127039716/235428066-b32ae457-19e1-4a5b-9846-e61941157d1b.png)


## General Information
This was written as a project for a university course - Object Orienter Programming, at VUT Brno. It is a simple snake game.

It is written in C++ utilizing SDL2 software development library.


## Game Controls
* Move snake with arrow keys
* Pause the game by pressing [esc] - press any of the arrow keys to resume gameplay


## Prerequisites
  ### Linux
  Make sure to have libsdl2-2.0-0 and libsdl2-dev packages installed (name of these packages may differ based on Linux distribution), e.g., on Debian/Ubuntu based systems can be installed by running: 
  ```bash
  sudo apt install libsdl2-2.0-0 libsdl2-dev
  ```

## Build Instructions
  ### Clone this repository
  ```bash
  git clone https://github.com/niedobam/snake-game
  ```
  ### Go into repository
  ```bash
  cd snake-game
  ```
  ### Compile
  ```bash
  make
  ```
  ### Run game
  ```bash
  ./snake-game
  ```