 A simple D-Bus client and server system.

 Contains:
  1. `dbus_client`: A client emitting a pre-configured message on the system bus.
  2. `dbus_server`: A server listening for the client emitted values and echoing them back.
 
 Use:
  1. Run `make` and then execute the client and the server binaries.
  2. Run `dbus-monitor --system` to view the messages emitted and received on the system bus. 
