diff: diff.c
	gcc -g -O0 diff.c -o diff

filecopy: filecopy.c
	gcc -g -O0 filecopy.c -o filecopy

server: server.c
	gcc -g -O0 server.c -o server

client: client.c
	gcc -g -O0 client.c -o client

test: test.c
	gcc -g -O0 test.c -o test