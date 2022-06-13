all: dbus_client

%.o: %.c
	gcc -g -Wall -c $< `pkg-config --cflags dbus-1`

dbus_client: dbus_client.o
	gcc -g dbus_client.o -o dbus_client `pkg-config --libs dbus-1`


.PHONY: clean
clean:
	rm *.o dbus_client