all: dbus_server dbus_client

%.o: %.c
	gcc -Wall -c $< `pkg-config --cflags dbus-1`

dbus_server: dbus_server.o
	gcc dbus_server.o -o dbus_server `pkg-config --libs dbus-1`

dbus_client: dbus_client.o
	gcc dbus_client.o -o dbus_client `pkg-config --libs dbus-1`

.PHONY: clean
clean:
	rm *.o dbus_server dbus_client