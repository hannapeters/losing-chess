**Questions and Answers**

**What did you learn from this assignment?**

**Answer**

I learned about how classes inherit from another, and how that can be done in more than one way (diamond inheritance) and also how shared pointers work.


**What was most difficult to do in this assignment?**

**Answer**

To understand how all classes should be linked and connected to one another. And to keep track of which class should inherrit from which, since there was a lot of files.

**The code relies on virtual functions. Could the code have been written without virtual functions?**

**Answer**

Yes, but then we would have a lot of redundancy in the code since we would make copies of the same functions that are common for all pieces.

**Could ChessPiece have been an abstract class?**

**Answer**

Yes, since all chess pieces overwrite all virtual functions from ChessPiece we could have just made them pure virtual functions.

**There was no separate unit test for each function in this assignment, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?**

**Answer**

A benefit with this kind of testing is that it is less time-consuming than writing several tests for all functions. Unit tests individually test units of code which isnt the most effective for programs like this since a few functions uses many of the other functions as underlying functions. So by testing that these few functions are correct, most other functions are implicitly tested. A drawback is that it doesnt test all functions as thorough. Therefore we might pass the tests by coincidence even if the code is incorrect. For example if one piece has one more possible move than it should and another one has one less, the right result will still be returned. But with unit testing, the different functions are tested individually and these kind of errors would be found.
 

**What is the problem with a diamond inheritance?**

**Answer**

If a class inherherits from more than one class  that shares members with the same name, like the Queen class, we have to specify which of the base classes we are using when we are accessing member with common name from that class. Otherwise, the program doesnt know which one we are refering to.

**Did you encounter any problem with protected member variables and, if so, how did you solve them?**

**Answer**

Yes, when including other files in a file, I couldnt access the protected variables from the class from the included file in the current class. I created public accessor functions functions that returned the protected variabels from so they could be accessed from other classes too.
