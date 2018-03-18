# OOP-BibliotecaScolastica

This is the C++ project I made for my Object-Oriented Programming exam, during the second year of University in Padua. 

It's a software that could be used in a school library: it keeps track of all the objects (books, textbooks, CDs, magazines) that are stored in the library, their informations and whether they are avaiable or rented; moreover, it also keeps the informations about the users who are registered to the system (which are accessible only by the administrator).

The software has different functionalities depending of the kind of user who authenticates to it: 
 * _External user_, _Student_, _Contributor_: these users can research items in the library, and view their informations. Each type of user has different privileges for researching items.
 * _Administrator_: can manage all the informations about library items and registered users. 

All the data get stored in a XML file, which can be overwritten at any time by the administrator, by clicking on the save button after he's done with the changes.

A more detailed explanation (in Italian) of the project and a user guide to the GUI can be found in the file _relazione.pdf_.

### Instructions

Make sure you have the Qt library and qmake installed, then clone this repository and enter the project directory

```
git clone https://github.com/gcoro/OOP-BibliotecaScolastica.git
cd OOP-BibliotecaScolastica/bibliotecaScolastica
``` 

Generate the makefile using qmake

```
qmake
```

Build the project and start it

```
make
./bibliotecaScolastica
```

Login using the following credentials to have access as all the different types of user

 * _Administrator_: 
    * username: admin 
    * password: admin
 * _External user_: 
    * username: est
    * password: est
 * _Student_: 
    * username: stud
    * password: stud
 * _Contributor_: 
    * username: cont
    * password: cont
