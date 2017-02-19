#ifndef LOG_HPP
#define LOG_HPP
//number of logs per second
#define LOGS_PER_SEC 4
//millisecond gap to log
#define LOG_MS (1000 / LOGS_PER_SEC)
//seconds to log
#define LOG_TIME 50
#define MAX_LOG (LOGS_PER_SEC * LOG_TIME)
#define LOG_SCALE 100

void log_baro();
void start_baro();
void start_log();
float get_height();

uint16_t logs[MAX_LOG];

void update_timer();

//zeroing the barometer
float zero=0;
#endif
