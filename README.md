# SimpleFTPServer
A Simple FTP Client &amp; Server for a School Project

## How to launch 
1- Lauch server executable
2- Lauch client exectuable
3- Enter the IPv4 address you want to access to
4- Enter the username you want to use
5- You are now abble to use the server !

## Command list
| Command             | Description                                                 |
|---------------------|-------------------------------------------------------------|
| help                | list all availables commands                                |
| cd _directory_      | change the active directory to _directory_                  |
| get _file_          | dowload _file_ from the server to the client computer       |
| ls                  | display all files and directories in the active directory   | 
| mkdir _directory_   | create _directory_ in the active directory                  |
| delete _file_       | delete _file_ (or directory)                                |
| put _file_          | upload _file_ from the client computer to ther server       |
| status              | list all connected users                                    |
| quit                | close server connection                                     |

## Specifications
- Server is using the **TCP port 1337**
- The **cd** command, unlike unix-style cd, works with absolute paths. You must specify the entire path of the directory you want to access.

## Current known bugs
- When closing the server, you need to wait for up to 5 mins before launching it again. The socket won't work otherwise.
