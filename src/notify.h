#ifndef NOTIFY_H
#define NOTIFY_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>

void send_notification(char *NAME,uint32_t ID, char *ICON, char *SUMMARY, char *BODY, int32_t EXPIRE) {
    DBusError err;
    DBusConnection *conn;
    DBusMessage *msg;
    DBusMessageIter args;

    dbus_error_init(&err);
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error: %s\n", err.message);
        dbus_error_free(&err);
        return;
    }

    msg = dbus_message_new_method_call(
        "org.freedesktop.Notifications",   // Destination service
        "/org/freedesktop/Notifications",  // Object path
        "org.freedesktop.Notifications",   // Interface
        "Notify"                           // Method name
    );
    if (msg == NULL) {
        fprintf(stderr, "Message Null\n");
        return;
    }

    dbus_message_iter_init_append(msg, &args);

    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &NAME);      // s, app_name
    dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &ID);        // u, notification ID
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &ICON);      // s, icon (empty string for now)
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &SUMMARY);   // s, summary
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &BODY);      // s, body
    DBusMessageIter actions_iter; // for asa
    dbus_message_iter_open_container(&args, DBUS_TYPE_ARRAY, "s", &actions_iter);  // as
    dbus_message_iter_close_container(&args, &actions_iter);
    DBusMessageIter dict_iter; // for a{sv}
    dbus_message_iter_open_container(&args, DBUS_TYPE_ARRAY, "{sv}", &dict_iter);  // {sv}
    dbus_message_iter_close_container(&args, &dict_iter);
    dbus_message_iter_append_basic(&args, DBUS_TYPE_INT32, &EXPIRE);

    if (!dbus_connection_send(conn, msg, NULL)) {
        fprintf(stderr, "Out of Memory!\n");
        return;
    }

    dbus_connection_flush(conn);
    dbus_message_unref(msg);
    dbus_connection_unref(conn);
    return;
}
#endif
