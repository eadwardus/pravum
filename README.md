# Pravum

Another game test, basically the same rules as the [pacman](https://github.com/eadwardus/pacman)
tough this one had no time limit, and was done during the free time of the
free time (and is not finished).

#### Internal Structure
The game is built around a "map model", where the main loop draws the
"map" objects and receives input to pass an event to the "map" common routines.

#### Know Problems
* keydown and keyup routines are a mistake as update exists
* the draw functions does not consider the frames per second
* probably a scene model is a better abstraction (to avoid code duplication)

#### External Resources
* "Up in the Sky" by "Memoraphile @ You're Perfect Studio" under public domain
