#include <stdint.h>

struct index_s {
    double time; // временная метка (модифицированная юлианская дата)
    uint64_t recordNumber; // первичный индекс в таблице БД
};

struct index_hdr_s {
    uint64_t recordsCount; // количество записей
    struct index_s idx[]; // массив записей в количестве recordsCount
};