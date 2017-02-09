baalued - bananapi cluster node controller
==========================================

The baalue daemon provide a socket based interface to a cluster node. With that interface you can control and trigger standard task like halt (via inet datagram socket) or get runtime infos like top.

Baalued is part of the sdk https://github.com/tjohann/a20_sdk.git . It runs on a embedded device like Bananapi-M1.

To interact/control the daemon you can use baalue (https://github.com/tjohann/baalue.git).

Note: Although its named bananapi cluster node daemon you can use it on any other target devices too.


Requirements
------------

To build and run baalued you need libbaalue (https://github.com/tjohann/libbaalue.git). All main dependencys are "handled" there.


Configuration/defaults
----------------------

	Port UDP - 8111 (device managment -> UDP socket)
	/var/run/baalued.socket (UDS socket)


Device managment
----------------

The following tasks are provided:

	halt a node
	reboot a node
	ping/alive
	...
