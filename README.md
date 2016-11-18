baalued - bananapi cluster node controller
==========================================

The baalue daemon provide a socket based interface to a cluster node. With that interface you can control and trigger standard task like halt (via inet datagram socket) or set scheduling propertys of a process and its time-triggert threads (via unix domain socket). The daemon has different threads which handles the requests and depending on the configured the thread/service will be started or not.

Actually three different services, which are described below, are supported:

	1). set scheduling propertys
	2). device managment
	3). ping/alive info (via device managment)
	4). display control


Baalued is part of my sdk's like https://github.com/tjohann/a20_sdk.git . It runs on a embedded device like Bananapi-M1. To interact/control the daemon you can use baalue (https://github.com/tjohann/baalue.git).

Note: Although its named bananapi cluster node daemon you can use it on any other target devices too.

Requirements
------------

To build and run baalued you need libbaalue (https://github.com/tjohann/libbaalue.git). All main dependencys are "handled" there.


Configuration/defaults
----------------------

	Port UDP - 8111 (device managment -> UDP socket)
	/var/run/baalued.socket (UDS socket)


Ping/alive info
---------------

t.b.d.


Display control (LCD160x)
-------------------------

t.b.d.


Device managment
----------------

t.b.d.


Set scheduling propertys
------------------------

t.b.d.


Future services
---------------

	update device via libxbps
	control jailhouse hypervisor
	can bus monitoring
	...
