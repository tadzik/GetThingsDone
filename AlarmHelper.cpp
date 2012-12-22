#include "AlarmHelper.hpp"

#include <QDebug>

#ifdef Q_WS_MAEMO_5
    #include <alarmd/libalarm.h>
#endif

void AlarmHelper::setAlarm(int timeout, const char *message)
{
    qDebug() << "Setting alarm to ring in" << timeout << "seconds";

#ifdef Q_WS_MAEMO_5
    cookie_t cookie     = 0;
    alarm_event_t *eve  = NULL;
    alarm_action_t *act = NULL;

    eve = alarm_event_create();
    alarm_event_set_alarm_appid(eve, "GetThingsDone");
    alarm_event_set_message(eve, message);

    eve->alarm_time = time(0) + timeout;

    /* Add stop button action */
    act = alarm_event_add_actions(eve, 1);
    alarm_action_set_label(act, "Stop");
    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
    act->flags |= ALARM_ACTION_TYPE_NOP;

    /* Add snooze button action */
    /* FUTURE ME: FOR FUCK'S SAKE NEVER REMOVE THIS
     * FOR SOME REASON IT MAKES THE ALARM RECUR INDEFINITELY
     * WITH NO WAY TO TURN IT OFF BESIDES USING alarmclient
     * YOU HAVE BEEN WARNED. NEVER. EVER. REMOVE. THIS */
    act = alarm_event_add_actions(eve, 1);
    alarm_action_set_label(act, "Snooze");
    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
    act->flags |= ALARM_ACTION_TYPE_SNOOZE;
    /* DO NOT TOUCH THE CODE ABOVE */

    cookie = alarmd_event_add(eve);
    alarm_event_delete(eve);

    qDebug() << "alarm cookie is" << cookie;
#else
    Q_UNUSED(message);
#endif
}
