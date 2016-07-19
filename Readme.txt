WARNING
=======
This is version is an early 0.1 development version. It is not yet feature complete or bug free.

ABOUT
=======
Function : This program list information about all block devices in a nice GUI.
           Note: This program is only for displaying information, it is not possible to mount or change the drives.
Os       : Linux
License  : Gpl
Version  : 0.1

BUILDING
=======

For building this program the following is necessary:

*QT/KDE + dev packages v 5.2 or higher
*libblkid + dev packages
*CMake and c++

Building the exec_program:
* cmake.
* make
* make install

Running:
This program can run as normal user, but running under root (with kdesu) will show slightly more information (see next section).
Note: When there is an unmounted disk in a cd-rom/dvd drive, the program will take more time to start up.

FUNCTIONS
==================
This program displays information about:
* Physical drives
* connected iScsi drives
* loopback device
* MD raid drives

And displays information about the following raid system 
* MD Software raid
* BTRFS

This program displays the following information:
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
Raid:
	* Device
	* Raid type
	* Mount points
	* Raid level
	
	
File system type is determined with information under /sys/fs and from /proc/mounts and as fallback libblkid
Libblkid can only get information from the block devices when this program is run as root, under normal user libblkid uses cashed 
information(if available).

Other functions:
* Pressing the "Refresh" button will refresh the information (There is no auto refresh yet)
* Settings=>Fields: For configuring the fields shown under the "Disk" tab. (There is no field configuration for the raid tab yet)
* Double clicking the row in the "Disk" tab will show more information about the selected device