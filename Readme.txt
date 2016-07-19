WARNING
=======
This is version is a early 0.1 development version. It is not yet feature compleet or bug free.

ABOUT
=======
Function : This program list information about all block devices in a nice gui.
           Note: This program is only for displaying information, it is not possible to mount or change the drives.
Os       : Linux
License  : Gpl
Version  : 0.1

BUILDIG
=======

For building this program the following is neccesary:

*QT/KDE + dev packages v 5.2 or higher
*libblkid + dev packages
*CMake and c++

Building the exec_program:
* cmake .
* make
* make install

Running:
THis program can run as normal user , but running under root (with kdesu) will show slightly more indeformation (see next section).
Note: When there is a umounted disk in a cd-rom/dvd drive, the program wil take more time to startup.

FUNCIONS
==================
This program displays information about:
* Physical drives
* connected iScsi drives
* loopback device
* MD raid drives

And displays information about the following raid system 
* MD Softwareraid
* BTRFS

This program displays the following infiormation
Devices:
	* Device name
	* Partitionname
	* Drive model
	* Readonly
	* Removable
	* Mountpoints
	* label 
	* size
	* filesystem type
	* loopback backing file
Raid:
	* Device
	* Raid type
	* Mount points
	* Raid level
	
	
Filesystem type is determined with information under /sys/fs and from /proc/mounts and as fallback libblkid
Libblkid can only get information from the blockdevices when this program is run as root, under normal user libblkid uses cashed 
information(if available).

Other functions:
* Pressing the "Refresh" button wil refresh the information (There is no auto refresh yet)
* Settings=>Fields : For seting up te fields shown under the "Disk" tab. (There is no field configuration for the raid tab yet)
* Double clicking the row in the "Disk" tab will show more information about the selected device