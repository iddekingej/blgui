WARNING
=======
This is version is an early 0.8 development version. It is not yet feature complete or bug free.

ABOUT
=======
Function : This program list information about all block devices in a nice GUI.
Os       : Linux/KDE5 or KDE4
License  : Gpl
Version  : 0.8



BUILDING
=======

For building this program the following is necessary:

extra-cmake-modules
cmake and c++ 
Gettext

Blkid+ Development packages
==========================
libblkid

Libudev + development packages
==============================
libudev.so.1

KDE4:

	LibQt
	===================
	libQtNetwork.so.4
	libQtXml.so.4
	libQtDBus.so.4
	libQtGui.so.4
	libQtSvg.so.4
	libQtCore.so.4
	qjson
	
	When Building KDE5:

	LibKDE
	===================
	libkdeui.so.5
	libkdecore.so.5

KDE5:
	KF5
	=========================
	libKF5ConfigCore
	libKF5CoreAddons
	libKF5I18n

	QT5 + Develop packages
	=======================
	libQt5Core
	libQt5Core
	libQt5Core
	libQt5Gui
	libQt5Widgets


Building the exec_program:
* mkdir build
* cd build
* Configuration
	For KDE5: cmake .. 
	For KDE4: cmake -Dkde=4  -DQT_QMAKE_EXECUTABLE=<qmake 4 exec>  ..
* make
* make install

Problems:
* If you get message like 'Compile your code with -fPIC or -fPIE' ,remove the contents of the build folder and run cmake again. This will happen 
  when first build for kde5 and then for kde4.
* If you get an error message that "QT_QT_INCLUDE_DIR" is used in this project but not found than add -DQT_QMAKE_EXECUTABLE=<qmake executable> to the cmake command line

Running:
This program can run as normal user, but running under root (with kdesu) will show slightly more information (see next section).
Note: When there is an unmounted disk in a cd-rom/dvd drive, the program will take more time to start up.

FUNCTIONS
==================
This program has the following features:

* Information over all devices and partitions
* Raid
* Iscsi
* Fstab
* Mounting devices

It support the following type of block devices:
* Physical drives
* iScsi drives
* loopback device
* MD raid drives
* LVM
* MD Software raid
* BTRFS


Disks:
	* Device name
	* Partition name
	* Drive model
	* Read only
	* Removable
	* Mount points
	* label 
	* size
	* file system type
	* loop back backing file
	* scsi bus
	* iscsi hostname
Raid:
	* Device
	* Raid type
	* Mount points
	* Raid level
	
*fstab
*iscsi
*Statistics

File system type is determined with information under /sys/fs and from /proc/mounts and as fallback libblkid
Libblkid can only get information from the block devices when this program is run as root, under normal user libblkid uses cashed 
information(if available).

Other functions:
* Pressing the "Refresh" button will refresh the information 
* Auto refresh: on (un)mount/remove medium
* Settings=>Fields: For configuring the fields shown under the "Disks" tab. (There is no field configuration for the raid and fstab tab yet)
                    And switch between tree and grid view for "Disks" tab
* Double clicking the row in the "Disks" tab will show more information about the selected device

Changes:
=======


Version 0.8:

* Mounting of devices
* Display if device is rotational or SSD
* Fix speed and memory leaks and code cleanup
* Some small gui fixes (disable grid edit,label etc)


