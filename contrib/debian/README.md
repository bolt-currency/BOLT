
Debian
====================
This directory contains files used to package boltd/bolt-qt
for Debian-based Linux systems. If you compile boltd/bolt-qt yourself, there are some useful files here.

## Bolt: URI support ##


dash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bolt-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bolt-qt binary to `/usr/bin`
and the `../../share/pixmaps/bolt128.png` to `/usr/share/pixmaps`

bolt-qt.protocol (KDE)

