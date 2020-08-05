#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>
#include <signal.h>
#include <unistd.h>

static DBusConnection *connection;
static int terminate = 0;

static DBusConnection *_dbus_connection_get()
{
	return connection;
}

static void print_to_stderr(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

static void print_error_reply(const char *err_msg, DBusError error)
{
	printf("%s\n", err_msg);
	printf(": %s %s\n", error.name, error.message);
	dbus_error_free(&error);
	exit(EXIT_FAILURE);
}

static int _dbus_connection_init()
{
	DBusConnection *conn = NULL;
	DBusError error;

	dbus_error_init(&error);
	conn = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

	if(dbus_error_is_set(&error)) {
		print_error_reply("Error connection to system bus", error);
	}

	connection = conn;
	printf("Connected to system bus\n");
}

static void ctrl_c_handler()
{
	terminate = 1;
	exit(EXIT_SUCCESS);
}

static int _dbus_request_name(const char *bus_name)
{
	DBusError error;
	dbus_error_init(&error);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	dbus_bus_request_name(conn, bus_name, DBUS_NAME_FLAG_REPLACE_EXISTING,
			&error);
	if(dbus_error_is_set(&error)) {
		print_error_reply("unable to request bus", error);
	}

	return 0;
}

static int _dbus_release_name(const char *bus_name)
{
	DBusError error;
	dbus_error_init(&error);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	dbus_bus_release_name(conn, bus_name, &error);
	if(dbus_error_is_set(&error)) {
		print_error_reply("unable to release bus_name", error);
	}

	return 0;
}

static int _dbus_emit_signal()
{
	DBusError error;
	dbus_error_init(&error);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	static int color = 0;
	const char *colors[] = {"red", "orange", "yellow", "green", "blue",
			"indigo", "violet"};

	DBusMessage *msg = dbus_message_new_signal("/test/myapp/eg",
			"test.myapp.eg", "First");

	if(!msg) {
		print_to_stderr("unable to create new msg\n");
	}

	const char *a = colors[(color++) % 7];
	if(!dbus_message_append_args(msg, DBUS_TYPE_STRING, &a,
			DBUS_TYPE_INVALID)) {
		print_to_stderr("unable to append args to signal\n");
	}

	if(!dbus_connection_send(conn, msg, NULL)) {
		print_to_stderr("unable to send signal\n");
	}

	printf("Signal: First, Color: %s\n", a);
	dbus_connection_flush(conn);
	dbus_message_unref(msg);
	return 1;
}

int main(int argc, char **argv)
{
	_dbus_connection_init();
	signal(SIGINT, ctrl_c_handler);

	_dbus_request_name("test.myapp.eg");
	while(_dbus_emit_signal()) {
		sleep(1);
		if(terminate)
			break;
	}

	_dbus_release_name("test.myapp.eg");
	return 0;
}
