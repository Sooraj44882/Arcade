# Arcade 

This is a 2-in-1 arcade hub I built using C. You can launch the app and choose between two different games right from the main menu.

![alt text](<Screenshot 2026-11-02 090539.png>)

##  Games Included

![alt text](<Screenshot 2026-11-02 090603.png>)

1. **Brick Break** 
   A classic breakout clone. You bounce a ball with a paddle to smash through 50 blocks. I added wall collisions, paddle physics and sound effects.
2. **Snake** 

![alt text](<Screenshot 2026-11-02 090630.png>)

   The standard grid survival game. Steer the snake to eat the apples and grow, but don't hit the walls or bite your own tail.

## Features


I used several different Raylib tools and basic physics concepts to make everything work:

1. Collision Detection in Brick i used Raylib built-in CheckCollisionCircleRec function so the circular ball bounces perfectly off the rectangular paddle and bricks. For Snake i used basic coordinate math to check if the head X and Y positions crossed the screen borders or touched any part of its own tail array.

2. Physics Movemen in Brick break uses  velocity vectors. The ball has an X and Y speed that reverses (multiplies by -1) when it hits an object. Snake uses strict grid-based movement where the body shifts exactly one cell size per frame instead of moving smoothly.

3. Both games use simple enum state machines (Start, Play, Game Over, Win) alongside switch statements. This is how the program knows exactly which screen to draw and when to ignore player inputs.

4. Audio Management: I used Raylib's audio device to load .wav files into memory and trigger them exactly when a specific collision happens, like the snake eating an apple or the ball hitting a brick.

##  Controls

**Arcade Menu**
* Press **1** to play Brick Break
* Press **2** to play Snake
* Press **ESC** inside any game to return to the menu
* Close the window to quit

**Brick Break**
* **Left / Right Arrows:** Move the paddle
* **Enter:** Start game
* **R:** Restart after Game Over

**Snake**
* **Up / Down / Left / Right Arrows:** Steer the snake
* **Enter:** Start game
* **R:** Restart after Game Over

##  How to Play (Windows)

You don't need to install any coding software to play!
1. Download and extract the `.zip` file from realses page.

2. Double-click `main.exe` to launch the arcade.

## Built With
* **Language:** C
* **Library:** [Raylib](https://www.raylib.com/)

