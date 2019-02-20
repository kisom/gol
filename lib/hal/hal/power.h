#ifndef __POWER_H
#define __POWER_H


namespace hal {


double	batteryVoltage();
void	batteryVoltageString(char *buf);
void	sleep();


} // namespace hal
#endif // __POWER_H
