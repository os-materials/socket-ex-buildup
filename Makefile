server: server.c
	gcc $^ -o $@ -lpthread
client: client.c
	gcc $^ -o $@ -lpthread
