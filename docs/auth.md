# AUTH
    * register device
    * user login
    * get device token

## local plugin
    * NotificationCenter::register(appId, appKey, listener) (signals: refreshToken(), newNotification())
    <!-- * NotificationCenter::addNotificationListener(appId, listener) -->
    * get device_token, NcUser infomation, and send them to your app server



# remote plugin
    * authorization with logged-in user
    * get access_token (this is user-specific)
