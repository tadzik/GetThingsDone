#ifndef _ALARM_HELPER_HPP
#define _ALARM_HELPER_HPP

#include <QString>

class AlarmHelper {
    void setAlarm(int timeout,
                  const QString& message = "Pomodoro timeout");
};

#endif
