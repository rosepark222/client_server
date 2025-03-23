# client_server
 
Ben Eater's TCP/IP network experiment

https://www.youtube.com/watch?v=F27PLin3TV0&list=PLowKtXNTBypH19whXTVoG3oKSuOcw_XeW&index=13

created code on chatgpt 

```
write a c code doing the below prompt:

client ip address and port number is 192.168.1.193 and 13
server ip address and port number is  192.168.1.193 and 13
1, client opens a connection to server
2, server sends date to the client
3, client and server closes connection 
```

gcc -o zclient zclient.c -lws2_32

gcc -o zserver zserver.c -lws2_32

download wireshark

run zserver and zclient in the same computer

enable only loopback capture ( because IP packet will not go out to wifi )

should see the below capture:

![image](https://github.com/user-attachments/assets/8cf3761f-c3c1-43e0-82a2-9810562d4ea1)

