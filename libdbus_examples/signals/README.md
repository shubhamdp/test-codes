# Compile as follows:
	gcc listen_signal.c -o listen_signal `pkg-config --libs --cflags dbus-1`
	gcc emit_signal.c -o emit_signal `pkg-config --libs --cflags dbus-1`

# Execute as follows:
	Open the terminal and execute `emit_signal`
	Open new terminal and execute `listen_signal`
	Open new terminal and execute `dbus-monitor --system`, this is helpful in monitoring what dbus messages.

# File: emit_signal.c
	Owns a Bus Name: "test.myapp.eg"
	Send signal on Object Path: "/test/myapp/eg"
	With Interface "test.myapp.eg"
	With Signal Name: "First"
	With Argument Signature: s

# File: listen_signal.c
	Listen on Interace "test.myapp.eg" and
	Object Path "/test/myapp/eg" and 
	Member "First"

# dbus-monitor --system
	signal time=1558247610.672769 sender=:1.2766 -> destination=(null destination) serial=21 path=/test/myapp/eg; interface=test.myapp.eg; member=First
	   string "blue"
	signal time=1558247611.673466 sender=:1.2766 -> destination=(null destination) serial=22 path=/test/myapp/eg; interface=test.myapp.eg; member=First
	   string "indigo"
	signal time=1558247612.674252 sender=:1.2766 -> destination=(null destination) serial=23 path=/test/myapp/eg; interface=test.myapp.eg; member=First
	   string "violet"

