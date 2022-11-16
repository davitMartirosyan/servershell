# include "logger.h"

void mylog(Logger* log, char* state, int line, const char* file, char* format, ...)
{
    va_list args;
    va_start(args, format);

    if (!log->wr_file)
    {
//        printf("%s [%s | %s] [line: %d, file: %s] : ", state, __DATE__, __TIME__, line, file);
        vprintf(format, args);
    }
    else
    {
        fprintf(log->fd, "%s [%s | %s] [line: %d, file: %s] : ", state, __DATE__, __TIME__, line, file);
        vfprintf(log->fd, format, args);
    }

    va_end(args);
}

void log_init(Logger *log)
{
    log->file_path = malloc(7);
    strcpy(log->file_path, "log.txt");
    log->wr_file = false;
}

void log_in_file(Logger *log, bool wr_file)
{
    if (!log->wr_file && wr_file)
        log->fd = fopen(log->file_path, "a+");

    log->wr_file = wr_file;
}

void log_change_file(Logger *log, char* file_path)
{
    log->file_path = realloc(log->file_path, strlen(file_path));
    strcpy(log->file_path, file_path);
    fclose(log->fd);
    log->fd = fopen(log->file_path, "a+");
}

void log_close(Logger* log)
{
    free(log->file_path);
    if(log->wr_file)
        fclose(log->fd);
}