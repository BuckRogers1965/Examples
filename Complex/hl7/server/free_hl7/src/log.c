/*
    All program logging goes through this code modual
*/

#include "includes.h"

/*
*/

void
set_log_level ( ) {
}

void
set_log_file ( ) {
}

/*
    Central method of writing to the main log file.
*/

void notify(char *file, int line, char *error) {

    FILE *logfile;

    logfile = fopen ("/home/jrogers/html/projects/free_hl7/log/main", "a+");

    /* If the logfile doesn't open,  exit with an error. */

    fprintf (logfile, "%s %d %s\n", file, line, error);
    fflush (logfile);
    fclose (logfile);
}
  
