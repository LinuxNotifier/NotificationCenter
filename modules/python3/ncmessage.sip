class NcMessage {
    %TypeHeaderCode
        #include "notificationcenter.h"
        #include "ncmessage.h"
        #include <memory>
        #include <QDebug>
    %End

    public:
        ~NcMessage();

        QString createdTime() const;
        QIcon icon() const;
        /* NcMessage& setIcon(const QString& icon); */
        NcMessage& setIcon(const QIcon& icon);
        QString messageId() const;
        QString notificationId() const;
        QString applicationId() const;

        bool isValid() const;

    private:
        /* NcMessage() /Factory/; */
        /* NcMessage(const NcMessage&); */
        /* NcMessage& operator=(const NcMessage&); */
};
