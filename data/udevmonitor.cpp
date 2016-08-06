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
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "bdi", nullptr);

	udev_monitor_enable_receiving(monitor);
	waitFd=udev_monitor_get_fd(monitor);
	return true;
}

bool TUDevMonitor::isSomethingChanged(QString &p_comment)
{
	bool l_found=false;
	const char *l_action;
	const char *l_subSystem;
	struct udev_device *l_dev;
	p_comment="";
	while(true){
		l_dev=udev_monitor_receive_device(monitor);
		if(l_dev != nullptr){
			l_action=udev_device_get_action(l_dev);
			if(p_comment.length()>0) p_comment +=",";
			l_subSystem=udev_device_get_subsystem(l_dev);
			if(strcmp(l_subSystem,"bdi")==0){
				if(strcmp(l_action,"add")==0){
					p_comment += "Device mounted";
				} else {
					p_comment += "Device unmounted";
				}
			} else{
				p_comment+=udev_device_get_devnode(l_dev);
				p_comment +=":";
				if(strcmp(l_action,"add")==0){
					p_comment += i18n("Added");
				} else if(strcmp(l_action,"remove")==0){
					p_comment += i18n("Removed");
				} else {
					p_comment += i18n("Unkown");
				}
				udev_device_unref(l_dev);
			}
			l_found=true;
		} else {
			break;
		}
	}
	return l_found;
	
}