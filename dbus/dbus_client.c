#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>

const char *const CLIENT_BUS_NAME = "org.marcopolo.client";
const char *const CLIENT_OBJECT_PATH_NAME = "/org/marcopolo/client";
const char *const INTERFACE_NAME = "org.marcopolo.dbus_example";
const char *const FIRST_SIGNAL_VALUE = "Brave";
const char *const SECOND_SIGNAL_VALUE = "Trail Blazer";

DBusError error;
void print_dbus_error(char *str);

int main()
{
    DBusConnection *conn;
    DBusMessage *msg;
    DBusMessageIter iter;

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

    // We're connected to the system bus and now want to initiate a new connection(service)
    // Ask the bus to assign the given name to this connection by invoking the RequestName method on the bus.
    dbus_bus_request_name(conn, CLIENT_BUS_NAME, 0, &error);

    if (dbus_error_is_set(&error))
    {
        print_dbus_error("Error while dbus_bus_get for client");
    }

    // create a new message representing a signal emission
    // A signal is identified by its originating object path,
    // interface, and the name of the signal.
    msg = dbus_message_new_signal(CLIENT_OBJECT_PATH_NAME, INTERFACE_NAME, "Explorer");

    // init a DBusMessageIter for adding arguments to the signal
    dbus_message_iter_init_append(msg, &iter);

    // Add
    if (!dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &FIRST_SIGNAL_VALUE))
    {
        fprintf(stderr, "Error in first dbus_message_iter_append_basic\n");
        exit(1);
    }
    if (!dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &SECOND_SIGNAL_VALUE))
    {
        fprintf(stderr, "Error in second dbus_message_iter_append_basic\n");
        exit(1);
    }
    // send the message
    if (!dbus_connection_send(conn, msg, NULL))
    {
        fprintf(stderr, "error sending message");
        exit(1);
    }

    // decrement the reference count of a DBusMessage. Free the msg if count
    // reaches 0
    dbus_message_ref(msg);

    // Flush the connection buffer. Blocks until the outgoing message queue is empty
    dbus_connection_flush(conn);
}

void print_dbus_error(char *str)
{
    fprintf(stderr, "%s: %s\n", str, error.message);
    dbus_error_free(&error);
}