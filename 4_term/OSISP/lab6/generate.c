#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

#define INDEX_RECORD_SIZE 16
#define HEADER_SIZE 8

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Usage: %s filename size_in_MB\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int size = atoi(argv[2]);
    int recordsNum = (size * 1024 * 1024) / INDEX_RECORD_SIZE;

    int header_size = HEADER_SIZE + recordsNum * INDEX_RECORD_SIZE;
    struct index_hdr_s *header = (struct index_hdr_s *) malloc(header_size);

    if (header == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    header->recordsCount = recordsNum;

    srand(time(NULL)); // устанавливает в качестве базы текущее время

    for (int i = 0; i < recordsNum; i++) {
        struct index_s *record = header->idx + i;

        double days_since_1900 = (double) (rand() % (365 * 123)) + 15020.0;
        double fraction_of_day = (double) rand() / RAND_MAX / 2.0;
        record->time = days_since_1900 + fraction_of_day;

        record->recordNumber = i;
    }

    FILE *fp = fopen(filename, "wb");
    
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    fwrite(header, header_size, 1, fp);
    fclose(fp);

    printf("Generated %d index recordsCount in file %s\n", recordsNum, filename);

    return 0;
}