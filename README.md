# UpDoP

***
This is a project for a new simple protocol.
The protocol name is UpDoP (Upload Download Protocol)
It is used for uploading and downloading files to and from a server.
It is similar to HTTP and is working with client-server-model
***

How it works:

CLIENT:
The client sends a request to the server.
There are two different type of actions the client can request from the server: UPLOAD and DOWNLOAD
It's self-explanatory UPLOAD is uploading a file to the server and DOWNLOAD is downloading a file from the server.

SERVER: 
The server replies to the request of the client.
There are a few status the server can send to tell the client if an error occurred

Status:

UPLOAD:
100 OK
300 SRVERR -> Server Error
400 NOTA -> Not allowed to access this resource
500 BDRQ -> Bad request f.e. weird client request

DOWNLOAD:
100 OK
200 RQSTFNF -> Requested file not found
300 SRVERR -> Server Error
400 NOTA -> Not allowed to access this resource
500 BDRQ -> Bad request f.e. weird client request

### UPLOAD ###

Client                      Server

RQST  --------------------->
      <--------------------- RESP
DATA  ---------------------> 
      <--------------------- CFRMD
DATA  ---------------------> 
      <--------------------- CFRMD
END   ---------------------> 
      <--------------------- ACK

RQST:

| ACTION | SRCFILE  | 
| UPLOAD | test.txt |  

RESP:

| VERSION  | STATUS | 
| UPDOP1.0 | 100    |

END:

| END |

ACK:

| ACK |

### DOWNLOAD ###

Client                      Server

RQST  --------------------->
      <--------------------- RESP
      <--------------------- DATA
CFRMD ---------------------> 
      <--------------------- DATA
CFRMD ---------------------> 
      <--------------------- END 
ACK   --------------------->

RQST:

| ACTION   | FILE       | 
| DOWNLOAD | server.txt |

RESP:

| VERSION  | STATUS | 
| UPDOP1.0 | 100    |

END:

| END |

ACK:

| ACK |

### CONFIGURATION ###

Client:

ServerIP=
Port=

Server:

Port=
DataDirectory=