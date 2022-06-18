#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>

const char *const SERVER_BUS_NAME = "org.marcopolo.server";
const char *const SERVER_OBJECT_PATH_NAME = "/org/marcopolo/server";
const char *const MATCH_RULE = "type='signal',interface='org.marcopolo.dbus_example'";

DBusError error;
void print_dbus_error(char *str);
DBusHandlerResult signalHandler(DBusConnection *conn, DBusMessage *message, void *user_data);

int main()
{
    DBusConnection *conn;

    // connect to the system bus
    dbus_error_init(&error);
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

    if (dbus_error_is_set(&error))
    {
        print_dbus_error("Error while dbus_bus_get");
    }

    if (!conn)
    {
        fprintf(stderr, "%s: %s\n",
                error.name, error.message);
        exit(1);
    }

    if (dbus_error_is_set(&error))
        print_dbus_error("Error in server for dbus_bus_get");

    dbus_bus_add_match(conn, MATCH_RULE, &error);

    // filter each incoming signal according to the handler
    dbus_connection_add_filter(conn, signalHandler, NULL, NULL);

    while (dbus_connection_read_write_dispatch(conn, -1))
    {
        fprintf(stdout, "%s\n", "Server listening...");
    }

    return 0;
}

void print_dbus_error(char *str)
{
    fprintf(stderr, "%s: %s\n", str, error.message);
    dbus_error_free(&error);
}

DBusHandlerResult signalHandler(DBusConnection *conn, DBusMessage *message, void *user_data)
{
    const char *interfaceName;
    const char *memberName;

    interfaceName = dbus_message_get_interface(message);
    memberName = dbus_message_get_member(message);

    fprintf(stdout, " Got signal member: %s from interface: %s\n", memberName, interfaceName);

    return DBUS_HANDLER_RESULT_HANDLED;
}
