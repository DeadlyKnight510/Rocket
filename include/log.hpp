//number of logs per second
#define LOGS_PER_SEC 4
//millisecond gap to log
#define LOG_MS (1000 / LOGS_PER_SEC)
//seconds to log
#define LOG_TIME 50
#define MAX_LOG (LOGS_PER_SEC * LOG_TIME)
#define LOG_SCALE 100

void log();
void start_log();

int logs[MAX_LOG];
int time;

