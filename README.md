# FileSystem Implementaion
## Written by Po 1552662 , in 2016/6/18
## Overview

&emsp; <font size=4>This is our third project for our OS course .This time ,we are required to implement a file system based on one of our favored programming languages.To gain qulification of homework standard, we need to meet two prerequisites , one is pratical programming skills ,another one is a full understanding of how real file system operates. And the deadline of homework is 2017/06/25.</font>

- <font size=6>1.The final interface of my application
- <font size=6>2.The thought of my application(platform and GUI dependencies)
- <font size=6>3.The architecture of my app
- <font size=6>4.Code implement of my file system
- <font size=6>5.Evaluation of my project

### <font size=6>Ⅰ. The final inteface
&emsp; <font size=4>First,I want to share the interface of my application with you.As you can see beneath,this time,I use a CPP GUI to implement a CLI(conmman line interface) because I am a huge fan of that fat penguin.Fine,i am just kidding.Actually,I am quite fancy of linux operating system's interface so I decide to do it this way.
When you enter my CLI, you could see this

![](http://i65.tinypic.com/11uf0gk.jpg...)

&emsp; <font size=4>And you can see all the command line you can use to operate on the virtual file system.FORMAT、MKDIR、RMDIR、Ls、etc.Next,you can use mkdir,rmdir to create or delete directory,and you can use touch、rm command to create or delete new files.

![](http://i64.tinypic.com/148kzh3.jpg...)
![](http://i66.tinypic.com/qporrt.jpg...)

&emsp; <font size=4>And you can use ls command to list all the files and sub-directory and you can use open to open a file and edit the content of specificed file


![](http://i67.tinypic.com/52f6rn.jpg)

&emsp; <font size=4>Last,you can use cat command to read the content of a file and quit to exit the system,and the application will store the information of system in a physical file automatically

![](http://i65.tinypic.com/30vejae.jpg)

### <font size=6>Ⅱ. The thought within my application
&emsp; <font size=4>The file system I simulate is of much difference of the actual file system running on a laptop.However ,the main thought and framework is the same mechanism.First,you need to simulate a virtual disk in your computer memory which contains the data within a file or directory.Then , i implement a BitVector map to indicate the occupation condition of all the virtual disk block.Next, a tree-structure directory is required because i need to manage all the directory and sub-directory whthin the system,and I think tree  is a good way data structure to use.Last ,i choose FAT table to manage the link condition of a file ,in account of the saving space in the virtual disk.

&emsp;<font size=4> FIY,my app is compiled in the VS2015 platform with the GUI library ----SFML, you need to add the path of SFML's include to the search path and lib to the linker path(SFML should be compliled in the VS2015 first) to compile my project.What's more , the directory structure stored in the real file is in a XML form so you need to add the header file to the project ,available on [http://rapidxml.sourceforge.net/](http://rapidxml.sourceforge.net/)
###<font size=6>Ⅲ.Architecture of my app
&emsp; This time , my app is written on a native MVC pattern written by me(actually i don't believe it is a MVC pattern:) ) The filemodel.h contain the defination of class filemodel which is the model layer of MVC ,containing all the data like FAT table ,BitVector map,virtual disk,etc. The FileController.h contain the class FileController which defien all the operation to response to the external users' action and modify the filemodel's data.The fileView.h include class fileview,which show show the interface of this app.
###Ⅳ.Code Implement
Here is some code from my project
####Defination of class FileModel

![](http://i66.tinypic.com/be8wmo.jpg)
#### Defination of class FileController
![](http://i66.tinypic.com/34oxd9y.jpg)
#### Defination of class FileView
![](http://i68.tinypic.com/2ryrf2s.jpg)
#### Main Loop
![](http://i65.tinypic.com/14kk66d.jpg)
![](http://i65.tinypic.com/2drx7uw.jpg)
#### Main Function
![](http://i67.tinypic.com/2qtfzop.jpg)
![](http://i65.tinypic.com/2d9sohx.jpg)
### Ⅴ. Evaluation of my project
&emsp; I think my CLI is very similar to the native ubuntu CLI which I fancy very much.But,to be honest,there are some shortcomings in my project.First,I don't store the directory in the disk which I assume it is hard to store the tree data struture in the virtual disk.Secondly,the total block number of my app is too small and the string each block store is too short,so I think it is vital for me to lengthen the space of my disk.
