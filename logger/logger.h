# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>

#define LOG_TRACE(log, msg, ...) mylog(log, "[Trace]", __LINE__, __FILE__, msg, __VA_ARGS__)
#define LOG_WARNING(log, msg, ...) mylog(log, "[Warning]", __LINE__, __FILE__, msg, __VA_ARGS__)
#define LOG_ERROR(log, msg, ...) mylog(log, "[Error]", __LINE__, __FILE__, msg, __VA_ARGS__)

typedef struct
{
    char* file_path;
    FILE* fd;
    bool wr_file;
}Logger;

void mylog(Logger* log, char* state, int line, const char* file, char* msg, ...);
void log_init(Logger *log);
void log_in_file(Logger *log, bool wr_file);
void log_change_file(Logger *log, char* file_path);
void log_close(Logger *log);