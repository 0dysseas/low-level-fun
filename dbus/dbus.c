#include <stdio.h>
#include <dbus/dbus.h>

int main()
{
    DBusError *error;
    DBusConnection *conn;

    // connect to the system bus
    dbus_error_init(error);
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, error);

    if (!conn)
    {
        fprintf(stderr, "%s: %s\n",
                error->name, error->message);
        return 1;
    }

    // We're connected to the system bus and now want to initiate a new connection(service)
    // Ask the bus to assign the given name to this connection by invoking the RequestName method on the bus.     
    dbus_bus_request_name(conn, "org.pirate.parrot", 0, error);

    if (dbus_error_is_set(error))
    {
        fprintf(stderr, "%s: %s\n",
                error->name, error->message);
        dbus_connection_close(conn);
    }
}
