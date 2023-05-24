#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

#include "progress.h"
#include "functions.h"

// ./dd https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js textCopy.js

// ./dd ./data/text textCopy.txt -b 8 -s 0 -sk 0 -p -u

void localOperation(int argc, char *argv[], struct Flags flags) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file> -b <block_size> -s <seek> -sk <skip> -p -l -u\n", argv[0]);
        exit(1);
    }

    int fd_in = open(flags.in_file, O_RDONLY);

    if (fd_in == -1) {
        perror("Error opening input file");
        exit(1);
    }

    struct stat st;
    if (fstat(fd_in, &st) == -1) {
        perror("Error getting input file size");
        exit(1);
    }

    int fd_out = open(flags.out_file, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd_out == -1) {
        perror("Error opening output file");
        exit(1);
    }

    ssize_t allSize = lseek(fd_in, 0L, SEEK_END);

    lseek(fd_in, 0L, SEEK_SET);

    // Начать запись с seek-ого блока
    if (lseek(fd_in, flags.seek * flags.block_size, SEEK_SET) == -1) {
        perror("Error seeking input file");
        exit(EXIT_FAILURE);
    }

    // Пропустить skip блоков
    if (lseek(fd_out, flags.skip * flags.block_size, SEEK_CUR) == -1) {
        perror("Error skipping blocks in input file");
        exit(EXIT_FAILURE);
    }

    // размер блока данных для чтения, записи и смещения
    char *buf = malloc(flags.block_size); 
    if (buf == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    ssize_t bytes_read, bytes_written, status;

    int percent, prevPercent = 0;

    while ((bytes_read = read(fd_in, buf, flags.block_size)) > 0) {

        if(flags.uppercaseflag)
            buf = toUpperCase(buf, flags.block_size);
        if(flags.lowercaseflag)
            buf = toLowerCase(buf, flags.block_size);

        bytes_written = write(fd_out, buf, bytes_read);

        if(flags.progressFlag) {
            prevPercent = (status/(double)allSize) * 100;
            status += bytes_read;
            percent = (status/(double)allSize) * 100;

            if(percent != prevPercent)
                printProgressBar("Status: ", status, allSize);
        }
        
        if (bytes_written != bytes_read) {
            perror("Error writing output file");
            exit(1);
        }
    }

    if (bytes_read == -1) {
        perror("Error reading input file");
        exit(1);
    }

    free(buf);
    close(fd_in);
    close(fd_out);
}

void networkOperation(int argc, char *argv[], struct Flags flags) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s url output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    CURL *curl;
    CURLcode res;
    FILE *fp;

    struct progress_info data;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(flags.out_file, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, flags.in_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &data);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);


        flags.in_file = flags.out_file;
        flags.out_file = "tmpName";

        localOperation(argc, argv, flags);

        remove(flags.in_file);
        rename("tmpName", flags.in_file); 

        fclose(fp);
    } else {
        fprintf(stderr, "Could not initialize libcurl\n");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[]) {
    struct Flags flags = parseCMD(argc, argv);

    if(strstr(flags.in_file, "http") != NULL) networkOperation(argc, argv, flags);
    else localOperation(argc, argv, flags);

    printf("\n\nCopy completed successfully.\n");
    return 0;
}