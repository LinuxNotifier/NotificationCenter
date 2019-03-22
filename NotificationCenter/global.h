#ifndef GLOBAL_H
#define GLOBAL_H

// for testing private methods
#ifdef DEBUG
#define private public
#endif

#ifndef NC_APP
#define NC_APP(applicationId) \
void notify(std::shared_ptr<Notification> notification) { \
    notification->setApplicationId(applicationId); \
    NotificationService::postNotification(notification); \
};
// #else
// ERROR: macro NC_APP already defined
#endif

#define __NOTIFICATIONCENTER_VERSION__ "ver 0.2.0"
#define __INTERFACE_VERSION__ "ver 0.2.0"
// #define __NOTIFICATIONCENTER_VERSION__ "ver 0.5.0"
// #define __INTERFACE_VERSION__ "ver 0.5.0"

#define ICON_SIZE 24

#define BORDER_RADIUS 5px

// TOOD: change to const int
#define WIDGET_MINIMUM_HEIGHT 40
#define WIDGET_MAXIMUM_HEIGHT_IN_PREVIEW 200

#endif // GLOBAL_H
