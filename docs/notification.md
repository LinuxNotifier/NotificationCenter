# Notification
    * notificationId (this will replace that notificaion with the same notificaionId)
    * applicationId
    * applicaitonName
    * applicationUrl (for remotely use)
    * title
    * icon
    * preview
    * body
    * <QJsonDocument::actions> (available only in local, {actions:{"action": "reply", "text": "~reply to Xu"}, "edits": {"textEdit": "address", "text": "street 1", "label": "address", "type": "textinput"}}) (array as an layer)
    * data
    * priority (Low/Normal/High/Critical) (remotely notificaion cannot set priority to Critical)
    * duration (Default, TillConfirmation, TillShutdown, TillDue,)

    * createdTime
    * triggerTime
    
    * "Closed, Expired, "
