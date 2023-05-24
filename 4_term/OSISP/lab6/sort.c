#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct.h"
#define MAX_THREADS 5000

struct sort_block {
    int num;        // номер блока
    void *start;    // смещение блока
    size_t size;    // размер блока
    bool free;      // статус блока
};

int memsize; 
int granul; 
int threads; 
char *filename; // файл индекса, например index.bin

pthread_mutex_t mutex;
pthread_t tid[MAX_THREADS];

struct sort_block *blocks;

size_t block_size;

size_t recordsCount; 
struct index_s *data;

void* merging(void* args); 

int comparator(const void *a, const void *b) {
    struct index_s *ia = (struct index_s *)a;
    struct index_s *ib = (struct index_s *)b;

    if (ia->time < ib->time) return -1;
    else if (ia->time > ib->time) return 1;
    else return 0;
}

void *sorting(void *arg) {
    int num = *(int*)arg;

    while(true) {
        struct sort_block *block;
        struct index_s *dt;

        pthread_mutex_lock(&mutex);
        
        // ищем неотсортированный блок
        int i;
        for(i = 0; i < granul; i++) {
            if(blocks[i].free == true) {
                block = &blocks[i];

                printf("Thread %d find block %d", num, block->num);

                block->free = false;
                break;
            }
        }
        
        pthread_mutex_unlock(&mutex);

        // сработает если неотсортированный блок не найден
        if(i == granul) pthread_exit(NULL);

        // сортировка блока
        dt = (struct index_s*) block->start;
        // в котором n записей
        size_t n = block->size / sizeof(struct index_s);

        qsort(dt, n, sizeof(struct index_s), (int (*)(const void *, const void *)) comparator);

        printf("%lu %lf \n", dt->recordNumber, dt->time);
    } 
}

void prepareThreadsAndRun() {        
    // рассовываем данные по блокам (начальная стадия алгоритма)
    for (int i = 0; i < granul; i++) {
        blocks[i].start = data + (block_size * i) / sizeof(struct index_s); 
        struct index_s* dt = (struct index_s*)(blocks[i].start);
        
        printf("Data details in blok i = %d %lu %lf\n", i, dt->recordNumber, dt->time);

        blocks[i].size = block_size;
        blocks[i].free = true;
        blocks[i].num = i;
    }
    
    // запуск потоков
    for (int i = 0; i < threads; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&tid[i], NULL, sorting, arg);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < threads; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&tid[i], NULL, merging, arg);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(tid[i], NULL);
    }
}

void initialize(void* file_data, int fd) {
    // заполняем основные глобальные переменные
    int res = pthread_mutex_init(&mutex, NULL);

    if (res) {
        fprintf(stderr, "Failed mutex initialize \n");
        exit(1);
    }

    block_size = memsize / granul; // общий размер / количество блоков
    printf("Block size: %lu", block_size);
    blocks = (struct sort_block*)malloc(sizeof(struct sort_block)*granul);
    
    struct index_hdr_s *header = (struct index_hdr_s *) file_data;
    printf("\nCount of recordsCount: %lu\n", header->recordsCount);
    recordsCount = header->recordsCount;
    data = header->idx;

    if (file_data == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        exit(1);
    }

    prepareThreadsAndRun();
}

void* merging(void* args) {
    int threadNum = *(int*)args;

    while(true) {
        int num1 = -1, num2 = -1;

        pthread_mutex_lock(&mutex);
        printf("thread %d is founding his pair\n", threadNum);

        for(int i = 0; i < granul; i++) {
            // ищем 2 блока для слияния
            if(blocks[i].free == false) {
                blocks[i].free = true;
                
                // нашли первый
                if(num1 == -1) {
                    printf("He found num1 = %d", i);
                    num1 = blocks[i].num;
                }
                // нашли второй
                else if(num2 == -1) {
                    printf("He found num2 = %d", i);
                    num2 = blocks[i].num;
                    break;
                }
            }
        }

        pthread_mutex_unlock(&mutex);

        // если один из блоков не найден
        if(num1 == -1 || num2 == -1) {
            printf("thread %d found nothing\n", threadNum);
            pthread_exit(NULL);
        }

        size_t offset1 = blocks[num1].size;
        size_t offset2 = blocks[num2].size;

        // переносим второй найденный блок, сразу за первый
        memcpy(blocks[num1].start+offset1, blocks[num2].start, offset2);
        printf("Thread %d merge %d to %d \n", threadNum, num2, num1);

        blocks[num1].size = offset1 + offset2;
        blocks[num1].free = false;

        if(offset1 + offset2 == memsize) {
            printf("Thread %d see, that 0 block is over", threadNum);
            pthread_exit(NULL);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage error!!!\n");
        exit(1);
    }

    memsize = atoi(argv[1]);
    granul = atoi(argv[2]);
    threads = atoi(argv[3]);
    filename = argv[4];

    int fd = open(filename, O_RDWR);

    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    size_t file_size = lseek(fd, 0, SEEK_END);

    int memsize_count = file_size / memsize;
    memsize = file_size;

    void* file_data = mmap(NULL, memsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    initialize(file_data, fd);
    
    if (munmap(file_data, memsize) < 0) perror("Error unmapping file");  

    close(fd);
    printf("Success\n");
    return 0;
}