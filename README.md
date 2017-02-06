baalued - bananapi cluster node controller
==========================================

The baalue daemon provide a socket based interface to a cluster node. With that interface you can control and trigger standard task like halt (via inet datagram socket) or set scheduling propertys of a process and its time-triggert threads. The daemon has different threads which handles the requests (via inet socket) and then connects to the specific daemons (like ttenv-daemon).

Actually four different services, which are described below, are supported:

	1). set scheduling propertys
	2). device managment
	3). ping/alive info (via device managment)
	4). display control

Baalued is part of my sdk's like https://github.com/tjohann/a20_sdk.git . It runs on a embedded device like Bananapi-M1. To interact/control the daemon you can use baalue (https://github.com/tjohann/baalue.git).

Note: Although its named bananapi cluster node daemon you can use it on any other target devices too.


Overview
--------

There're are 3 different way to use this daemon:

1). as the device manager for one baalue cluster node (or similiar device)
2). as the entry point to initiate device managment tasks for a single baalue cluster node (via xfce panel application)
3). as a entry node to a baalue cluster via baalue-master node (via xfce panel application)


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
