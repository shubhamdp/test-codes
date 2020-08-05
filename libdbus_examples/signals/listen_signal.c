#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dbus/dbus.h>

static DBusConnection *connection;
static int terminate = 0;

static DBusConnection *_dbus_connection_get()
{
	return connection;
}

static void print_to_stderr(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

static void print_error_reply(const char *err_msg, DBusError error)
{
	fprintf(stderr, "%s\n", err_msg);
	fprintf(stderr, ": %s %s\n", error.name, error.message);
	dbus_error_free(&error);
	exit(EXIT_FAILURE);
}

static void _dbus_connection_init()
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
}

static void _dbus_signal_subscribe(const char *rule)
{
	DBusError error;
	dbus_error_init(&error);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	dbus_bus_add_match(conn, rule, &error);
	dbus_connection_flush(conn);

	if(dbus_error_is_set(&error)) {
		print_error_reply("unable to add signal match", error);
	}
}

static void _dbus_signal_unsubscribe(const char *rule)
{
	DBusError error;
	dbus_error_init(&error);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	dbus_bus_remove_match(conn, rule, &error);
	dbus_connection_flush(conn);

	if(dbus_error_is_set(&error)) {
		print_error_reply("unable to remove signal match", error);
	}
}

static int _dbus_signal_handle_test_myapp_eg_First(DBusMessage *msg)
{
	DBusMessageIter iter;
	dbus_message_iter_init(msg, &iter);
	if(dbus_message_iter_get_arg_type(&iter) == DBUS_TYPE_STRING) {
		const char *val;
		dbus_message_iter_get_basic(&iter, &val);
		printf("Received signal from test.myapp.eg with data: %s\n",
				val);
	}
	return 1;
}

static DBusHandlerResult _dbus_signal_handler(DBusConnection *conn,
		DBusMessage *msg, void *user_data)
{
	if(dbus_message_is_signal(msg, "test.myapp.eg", "First")) {
		return _dbus_signal_handle_test_myapp_eg_First(msg);
	}
	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int main(int argc, char **argv)
{
	_dbus_connection_init();
	signal(SIGINT, ctrl_c_handler);
	DBusConnection *conn = _dbus_connection_get();
	if(!conn) {
		print_to_stderr("unablet to connect to dbus\n");
	}

	dbus_connection_add_filter(conn, _dbus_signal_handler, NULL, NULL);
	const char *rule =
			"type='signal',interface='test.myapp.eg',member='First'";
	_dbus_signal_subscribe(rule);

	while(dbus_connection_read_write_dispatch(conn, 500)){
		if (terminate)
			break;
	}

	_dbus_signal_unsubscribe(rule);

	return 0;
}
