#ifndef _ALARM_HELPER_HPP
#define _ALARM_HELPER_HPP

class AlarmHelper {
public:
    static void setAlarm(int timeout,
                         const char* message = "Pomodoro timeout");
};

#endif
