#include "udevmonitor.h"
#include <stdio.h>
#include <libudev.h>
#include <QString>
#include <klocalizedstring.h>
bool TUDevMonitor::open()
{
	udev=udev_new();
	if(udev==nullptr) return false;
	monitor=udev_monitor_new_from_netlink(udev,"udev");
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "block", nullptr);
	udev_monitor_enable_receiving(monitor);
	return true;
}


/**
 * Checks trough udev changes in device state (added/removed)
 * Added devices are added to the "added" list and removed
 * devicdes to the "removed" list.
 * 
 * \param  p_added   List of added devices
 * \param  p_removed List of removed devices
 * \return true -changes detected
 */
bool TUDevMonitor::isSomethingChanged(QSet<QString> &p_added,QSet<QString> &p_removed)
{
	bool l_found=false;
	const char *l_action;
	const char *l_devName;
	struct udev_device *l_dev;
	while(true){
		l_dev=udev_monitor_receive_device(monitor);
		if(l_dev != nullptr){
			l_action=udev_device_get_action(l_dev);
			l_devName=udev_device_get_devnode(l_dev);
			
			if(strcmp(l_action,"add")==0){				
				p_added.insert(l_devName);
			} else if(strcmp(l_action,"remove")==0){
				p_removed.insert(l_devName);
				
			} 
			udev_device_unref(l_dev);
			
			l_found=true;
		} else {
			break;
		}
	}
	return l_found;
	
}

TUDevMonitor::~TUDevMonitor()
{
	if(udev !=nullptr)udev_unref(udev);
	if(monitor != nullptr) udev_monitor_unref(monitor);
}
