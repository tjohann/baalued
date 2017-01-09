#!/bin/bash

# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH}

sudo make uninstall
make distclean

autoreconf --install || exit 1
./configure --sysconfdir=/etc --prefix=/usr --enable-debug

cd po
make update-po

cd ..
make
sudo make install
