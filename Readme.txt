WARNING
=======
This is version is an early 0.6 development version. It is not yet feature complete or bug free.

ABOUT
=======
Function : This program list information about all block devices in a nice GUI.
           Note: This program is only for displaying information, it is not possible to mount or change the drives.
Os       : Linux
License  : Gpl
Version  : 0.6


BUILDING
=======

For building this program the following is necessary:

extra-cmake-modules
cmake and c++ 
Gettext


KF5 (kde) +Develop packages:
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

Blkid+ Development packages
==========================
libblkid

Libudev + development packages
==============================
libudev.so.1

Building the exec_program:
* mkdir build
* cd build
* cmake ..
* make
* make install

Running:
This program can run as normal user, but running under root (with kdesu) will show slightly more information (see next section).
Note: When there is an unmounted disk in a cd-rom/dvd drive, the program will take more time to start up.

FUNCTIONS
==================
This program displays the follow information

* Information over all devices and partitions
* Raid
* Iscsi
* Fstab

It support the following type of block devices:
* Physical drives
* iScsi drives
* loopback device
* MD raid drives
* LVM
* MD Software raid
* BTRFS


Devices:
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

File system type is determined with information under /sys/fs and from /proc/mounts and as fallback libblkid
Libblkid can only get information from the block devices when this program is run as root, under normal user libblkid uses cashed 
information(if available).

Other functions:
* Pressing the "Refresh" button will refresh the information 
* Auto refresh: on (un)mount/remove medium
* Settings=>Fields: For configuring the fields shown under the "Disk" tab. (There is no field configuration for the raid and fstab tab yet)
* Double clicking the row in the "Disk" tab will show more information about the selected device

Changes:
=======


0.6<=0.5
* Code cleanup
	- Linklist iterators
	- Configuration manager
* Configure which tabs are visible
* New columns:
	-Start of partition
* Device details:
	-Redone partition tab: Add start of partition
        -Select different device
        -Display scsi bus
        -Display iscsi host
* Partition details:
	-Navigate to device.
* Fix: free size
* Fix: raid level
* Fix: few memory leaks
