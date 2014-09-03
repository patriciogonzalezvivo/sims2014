
## Review 

[Chapter 01: Vectors](http://natureofcode.com/book/chapter-1-vectors/) from The Nature of Code by Daniel Shiffman. Videos: [1.1](https://vimeo.com/channels/natureofcode/58734251), [1.2](https://vimeo.com/channels/natureofcode/58943395), [1.3](https://vimeo.com/channels/natureofcode/58943394), [1.4](https://vimeo.com/channels/natureofcode/58943396), [1.5](https://vimeo.com/channels/natureofcode/58943393), [1.6](https://vimeo.com/channels/natureofcode/59028636) 

[Chapter 02](http://natureofcode.com/book/chapter-2-forces/) from The Nature of Code by Daniel Shiffman . Videos: [2.1](https://vimeo.com/channels/natureofcode/59028633), [2.2](https://vimeo.com/channels/natureofcode/59028634), [2.3](https://vimeo.com/channels/natureofcode/59028632), [2.4](https://vimeo.com/channels/natureofcode/59435251), [2.5](https://vimeo.com/channels/natureofcode/59435250), [2.6](https://vimeo.com/channels/natureofcode/59435252)

## Read
* [Chapter 01: intro](https://github.com/openframeworks/ofBook/blob/master/chapters/intro/chapter.md) by Zachary Lieberman from the ofBook

* [Chapter 03: setup and project structure](https://github.com/openframeworks/ofBook/blob/master/chapters/setup_and_project_structure/chapter.md) from the ofBook

* [Chapter 03: a. OOP](https://github.com/openframeworks/ofBook/blob/master/chapters/OOPs!/chapter.md) from the ofBook

* [Chapter 04: Animation](https://github.com/openframeworks/ofBook/blob/master/chapters/animation/chapter.md) by Zachary Lieberman  from the ofBook (until **Function based movement**) 

## Class Notes

* Numbers from 0-1 
* Linear interpolation: ```myPoss = (1-pct) * a + pct * b``` (note the fancy name for this is , aka LERP)
* Shapers using power: 

	pct = powf(num,exp);
	myPoss = (1-pct) * a + pct * b;

* Xeno: ``myPos = (1-pct) * myPos + pct * targetPos```. based on xeno's paradox.

* Robert Penner’s Easing Equations: [JS](http://gizma.com/easing/) [C++](https://github.com/jesusgollonet/ofpennereasing)

![Kynd’s graphic](https://farm8.staticflickr.com/7346/9546075099_18ccc66a2d_o_d.png)

* Advance shaping functions: [Bezier and Other Parametric Shaping Functions](http://www.flong.com/texts/code/shapers_bez/), [Circular & Elliptical Shaping Functions](http://www.flong.com/texts/code/shapers_circ/), [Exponential Shaping Functions](http://www.flong.com/texts/code/shapers_exp/) and [Polynomial Shaping Functions](http://www.flong.com/texts/code/shapers_poly/)