# Overview

Imagine that one day, you develop a certain application and you want a limited instance of this app in the entire world, so the key of that is to create a limited ticket so every user want to use your software he needs to ask for a ticket if it is available. So this project will solve that problem for you. The idea of this project can be more developed because the code develop to be used locally we simulate user as processes indide the system these processes talks to the server to demande ticket to run the main application. Its a client-server based application.

# Project structure

This project is devided into 4 modules:

1. **lib** : In the lib module you will find a library that handles the communication between client and the server.

2. **doc**: Inside the doc module, you will find an image that illustrate the protocol.

3. **client**: The client module contains the code of the main app, if you need to change the service that the application provide to the client, all you need is to override tha **app()** function.

4. **server**: Within the server module, you will find the code of the server part that handle all client requests. 

#  Run

Follow these steps to execute the project correctly:

1. Download the repository to your local machine.
2. Navigate to the server and client modules within your directory.
3. Execute the make command.

The executable files, namely client.exe and server.exe, will be located in the subdirectory named **build**.
