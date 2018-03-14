
I am [Guillermo García Subirana](https://www.linkedin.com/in/guillermo-garc%C3%ADa-subirana-36a783b5/), student of the
[Bachelor’s Degree in
Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s
subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

## **Intro to the problem** 

An input combo system can vary greatly from one video game to another. That's why we have not established a fixed system to follow when we're developing a system for our video game.
In this guide we will investigate about the input combos system that some video games have developed, we will discuss the different techniques that can be applied and, finally, we will make step by step our input system combo.

## Different approaches by different games

First let's analyze some games that use a input combo system significantly different between them. In this way we can distinguish some key parts of the system more easily.

### Street Fighter

![Street Fighter Example](images/street_fighter_example.gif)
_Street Fighter - Ryu vs Ken_


In Street Fighter, the user is able to perform a variety of combos already defined. Some keys of their input combo system are:

* To make a combo it is not enough to press a defined series of keys correctly, it must be in correct timing and in a limited time.
* The pool of possible inputs is not excessively long.

### Heavy Rain

![Heavy Rain Example](images/heavy_rain_example.gif)
_Heavy Rain example_
//todo put foot image some way D:

In Heavy Rain they usually use a very interesting input combo system:
* The system stores the events entered by the user and allows you to continue the combo (showing in this case) the new event key to follow.
* The system constantly checks that you are keeping the keys already pressed without taking into account how long it takes to press the next one.

## Description in detail for the selected approach

In all the titles that use an input combo system, they use a vector or tree (explained in detail the difference later // all put cool link) to store the last inputs introduced by the user.

# Input Storage

* Vector

* Tree

# Buffer circular

As we already know the memory is not unlimited and, therefore, storage is usually carried out using a circular buffer system that keeps the most recent inputs in memory.
In this way, every time a new input is introduced (and therefore the oldest one is deleted) it is checked from the first found event to the last one created and then look for a match between the chain of inputs and one of our combos.

It should be noted that conditions can be added to eliminate events such as in a fighting game: the time between events.

# Finite state machine

In case of finding a match, we will eliminate or not the list of our last events and the appropriate movement or action will be carried out by means of a finite state machine.

## Our approach step by step

Since in a fight / beat em 'up genre the input combo system becomes more complex due to the time factor between events, I decided to make a step-by-step guide where we will get to make an input combo system in a efficient and simple way.

TODO 1: mimimi

RESOLVED TODO 1: mimimi

Optional Homework for practicing!

## Ways to improve

Explanation of any other improvements on the system

## References

references about the project

## License

~~~~~~~~~~~~~~~

MIT License

Copyright (c) 2018

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

~~~~~~~~~~~~~~~
