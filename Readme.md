

# Operating Systems Assignment 6

#### A part of a university assignment

</br>

## Project Overview

In this project we have implemented multipule design patterns (Active Object , Singleton , Reactor) in C/C++



</br>

## How To Run & Notes (Please make sure to read the notes relevant to the question being examed)

</br>

#### For **Q.1\2\3** we have the following files:
    
    1- main1.cpp/hpp

    2- server.cpp

    3- client.cpp

      for compling and exec: 
        
        make server
        make client 

        ./server
        ./client

</br>

![](imgs%5Creactor%20in%20action.png)

</br>

    you can insert a string from the client and get a response back with the encoded message




</br>

#### For **Q.4** we have the following files:

    guard.cpp/hpp



    the answer for the question is in .hpp file !


    to run the guard example:

      make test_guard
      ./test_guard



</br>

#### For **Q.5** we have the following files:

    singleton.cpp/hpp

    to run the singleton example:

      make test_singleton
      ./test_singleton

</br>

#### For **Q.6** we have the following files:

    reactor.cpp/hpp
    poll_server

    for compling and exec: 
        
        make poll_server
        make client 

        ./poll_server
        ./client



this poll server is using the **Reactor**



</br>
</br>

#### Tests

      run:
      make test

</br>
</br>

#### Notes

the shared library name is "aa.so"


</br>
</br>

## Authors

  **Tarik Husin**  - linkedin -> https://www.linkedin.com/in/tarik-husin-706754184/

  **Wissam Kabha**  - github -> https://github.com/Wissam111