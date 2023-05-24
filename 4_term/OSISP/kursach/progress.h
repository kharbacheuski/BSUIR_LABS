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

struct progress_info {
    double download_size;   // общий размер файла для загрузки
    double bytes_downloaded; // количество байт, уже загруженных
    double upload_size;     // общий размер файла для загрузки
    double bytes_uploaded;  // количество байт, уже загруженных
};

void printProgressBar(char label[], int step, int total ) {
    const int pwidth = 50;

    int width = pwidth - strlen( label );
    int pos = ( step * width ) / total ;

    
    int percent = ( step * 100 ) / total;

    printf("%s[", label );

    for ( int i = 0; i < pos; i++ )  
        printf( "%c", '=' );
    printf("%s", "] ");
    printf("%d%c\r", percent, '%');
}

static int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    // Получить указатель на структуру с информацией о прогрессе
    struct progress_info *progress = (struct progress_info *)clientp;

    // Обновить значения структуры
    progress->download_size = dltotal;
    progress->bytes_downloaded = dlnow;
    progress->upload_size = ultotal;
    progress->bytes_uploaded = ulnow;

    // Вывести информацию о прогрессе
    printf("Downloaded %.0lf \r", (double)(dlnow/(double)dltotal)*100);

    return 0;
}