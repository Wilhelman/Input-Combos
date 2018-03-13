
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

//todo put foot image some way D:

En Street Fighter, el usuario es capaz de realizar una gran variedad de combos ya definidos. Algunas claves de su sistema de input combo son:

* Para realizar un combo no basta con pulsar correctamente una série definida de teclas, ha de ser en un timing correcto y en un tiempo limite.
* La piscina de inputs posibles no es excesivamente larga.

### Heavy Rain

![Heavy Rain Example](images/heavy_rain_example.gif)

//todo put foot image some way D:

Heavy Rain utiliza un sistema de input combo bastante interesante:
* Almacena los eventos introducidos por el usuario y te permite continuar el combo (mostrándote en este caso) la nueva tecla de evento a seguir.
* El sistema comprueba constantemente que estés manteniendo las teclas ya pulsadas sin tener en cuenta cuanto tardas en pulsar la siguiente.

## Description in detail for the selected approach

Talk about the last games approaches 

# Fighting game approach

Street Fighter y la gran mayoría de titulos de lucha utilizan un vector o arbol (explicado en detalle la diferencia más adelante //todo poner enlace guay) para almacenar los ultimos inputs introducidos por el usuario. Como ya sabemos la memória no es ilimitada y por lo tanto, se suele realizar el almacenamiento mediante un sistema de buffer circular que mantiene en memoria los inputs más recientes.
De esta manera, cada vez que se introduce un nuevo input (y por ende se elimina el más antiguo) se comprueba desde el primer evento encontrado al último creado y es entonces cuando se busca una coincidencia entre la cadena de inputs y alguno de nuestros combos.
En caso de encontrar una coincidencia, eliminaremos o no la lista de nuestros ultimos eventos y se realizará el movimiento o acción apropiado.

# Other approach

## Our approach step by step

Dado que en un juego de género lucha / beat em' up el sistema de input combo llega a ser más complejo por el factor del tiempo entre eventos, he decidido realizar un guía paso a paso donde llegaremos a realizar un sistema de input de combos de manera eficiente y simple.

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
