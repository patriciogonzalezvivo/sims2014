# Setup

## 1. Download and Install openFrameworks and IDE

Go to [openFrameworks.cc/download](http://openframeworks.cc/download/) and download the right OF version for your platform. Close to it you will find a nice tutorial of how to install it. Please install the ```openFrameworks``` folder on your Desktop in order everybody have it in the same place ```~/Desktop/openFrameworks```. 

OpenFrameworks is essentially a toolbox, you need to get familiarize with it tools, for that you should spend a significative amount of time compiling, checking and understanding each single example.

A really good material you should read to know OF's folder structure together with your IDE interface is the [Chapter 03: Setup and Project Structure](https://github.com/openframeworks/ofBook/blob/master/03_setup_and_project_structure/chapter.md) of the OFBOOK.

## 2. Install Git and these repository

On a Linux Machine you just need to type:

	sudo apt-get install git-core

But in MacOS you need to install a package manager like [Homebrew](http://brew.sh/) or [MacPorts](https://www.macports.org/). 

### 2.1. First install Homebrew 
According to their website you just need to open the terminal and type:

	ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"

### 2.2. Then install Git

	brew install git-core

## 3. Clone these repository

Go to you openFrameworks root dir:

	cd ~/Desktop/openFrameworks
	
And clone these directory

	git clone http://github.com/patriciogonzalezvivo/sims2014.git

You will see that the folder is together with the ```apps/```, ```libs/``` and ```addons/``` folders

* ```addons/```
* ```apps/```
* ```libs/```
* ```examples/```
* ```scripts/```
* ```sims2014/```

These will preserve the examples on 3 levels over the root directory (if you don't understand what I mean, read [Chapter 03](https://github.com/openframeworks/ofBook/blob/master/03_setup_and_project_structure/chapter.md)! seriously! READ IT! ).

## 4. Make a GitHub Account and a repository for your Homework

Create a github account if you don't have one already and create a repo for the class that you'll use to submit your homework.  Name it as follows, '[newSchoolID]_sims2014' (ex: 'gonzp378_sims2014' ).
 