all:ftpclient inet_aton udpclient udpserver inet_pton
udpserver:udpserver.c
	gcc udpserver.c -o udpserver
udpclient:udpclient
	gcc udpclient.c -o udpclient

ftpclient:ftpclient.c
	gcc ftpclient.c -o ftpclient
inet_aton:inet_aton.c
	gcc inet_aton.c -o inet_aton
inet_pton:inet_pton.c
	gcc inet_pton.c -o inet_pton
clean:
	rm ftpclient inet_aton udpclient udpserver inet_pton
