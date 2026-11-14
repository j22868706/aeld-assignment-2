#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID, LOG_USER);

    // Check the number of arguments
    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments");
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return EXIT_FAILURE;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Open the file for writing
    FILE *fp = fopen(writefile, "w");

    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to open %s: %s",
               writefile, strerror(errno));
        closelog();
        return EXIT_FAILURE;
    }

    // Log the writing operation
    syslog(LOG_DEBUG, "Writing %s to %s",
           writestr, writefile);

    // Write the string
    size_t len = strlen(writestr);

    if (fwrite(writestr, 1, len, fp) != len) {
        syslog(LOG_ERR, "Failed to write to %s: %s",
               writefile, strerror(errno));
        fclose(fp);
        closelog();
        return EXIT_FAILURE;
    }

    // Close the file
    if (fclose(fp) != 0) {
        syslog(LOG_ERR, "Failed to close %s: %s",
               writefile, strerror(errno));
        closelog();
        return EXIT_FAILURE;
    }

    closelog();
    return EXIT_SUCCESS;
}

