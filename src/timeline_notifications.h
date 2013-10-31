
// Copyright (c) 2013 Toggl

#ifndef SRC_TIMELINE_NOTIFICATIONS_H_
#define SRC_TIMELINE_NOTIFICATIONS_H_

#include "./timeline_event.h"

#include <vector>
#include <string>

#include "Poco/Notification.h"

// A timeline event is detected, window has changes
// or there's and idle event.
class TimelineEventNotification : public Poco::Notification {
 public:
    explicit TimelineEventNotification(TimelineEvent _event) : event(_event) {}
    TimelineEvent event;
};

// Find timeline events (for upload).
class CreateTimelineBatchNotification : public Poco::Notification {
 public:
    explicit CreateTimelineBatchNotification(unsigned int _user_id) :
        user_id(_user_id) {}
    unsigned int user_id;
};

// A batch of timeline events has been found in database, that
// is ready for upload.
class TimelineBatchReadyNotification : public Poco::Notification {
 public:
    TimelineBatchReadyNotification(unsigned int _user_id,
            std::vector<TimelineEvent> _batch,
            std::string _desktop_id) :
        user_id(_user_id),
        batch(_batch),
        desktop_id(_desktop_id) {}
    unsigned int user_id;
    std::vector<TimelineEvent> batch;
    std::string desktop_id;
};

// A batch of timeline events has been upladed and may be deleted.
class DeleteTimelineBatchNotification : public Poco::Notification {
 public:
    explicit DeleteTimelineBatchNotification(std::vector<TimelineEvent> _batch)
        : batch(_batch) {}
    std::vector<TimelineEvent> batch;
};

// Timeline must shut down.
class RequestShutdownNotification : public Poco::Notification {
 public:
    RequestShutdownNotification() {}
};

// User-specific timeline settings; for example, if user has
// timeline recording enabled at all. These will be fetched
// from the server.
class UserTimelineSettingsNotification : public Poco::Notification {
 public:
    UserTimelineSettingsNotification(unsigned int _user_id,
        bool _record_timeline) :
        user_id(_user_id),
        record_timeline(_record_timeline) {}
    unsigned int user_id;
    bool record_timeline;
};

#endif  // SRC_TIMELINE_NOTIFICATIONS_H_
