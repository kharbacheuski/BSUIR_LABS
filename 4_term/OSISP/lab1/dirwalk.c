#include <stdio.h>
#include <string.h>  
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>

char** find(const char* dirname, int flags[], int *elemsCount) {
    char** file_names = (char**) malloc(1*sizeof(char*));

    DIR* directory;
    struct dirent* de;

	directory = opendir(dirname); 

    if (directory == NULL) {
		printf("Missing second parameter - directory!\n");

		return NULL;
	}
        
    while (de = readdir(directory)) {
        // проверка, что имя каталога не равно «.» и «..»

        if (!strcmp(".", de->d_name) || !strcmp("..", de->d_name))
            continue;


		int pushCondition = (
			(flags[0] && flags[1] && flags[2] && flags[3] == 0)  || 
			flags[0] && de->d_type == DT_LNK || 
			flags[1] && de->d_type == DT_DIR || 
			flags[2] && de->d_type == DT_REG
		);

        if(pushCondition) {
            file_names = (char**)realloc(file_names, sizeof(char*)*(*elemsCount+1)); 
            file_names[*elemsCount] = (char*)malloc(sizeof(char)*NAME_MAX);

            memcpy(file_names[*elemsCount], de->d_name, NAME_MAX); // создаем элемент массива с именем найденного элемента
			
            *elemsCount += 1;
        }  
    }

    closedir(directory); // закрытие директории

    return file_names; // функция возвращает массив имен элементов
}

int sortCondition(const void *s1, const void *s2) {
	return strcmp((char*)s1, (char*)s2) == 1 ? 1 : 2;
}

int* getFlags(int argc, char** argv) {

	int* flags = (int*)calloc(4, sizeof(int));

    for(int i = 2; i < argc; i++) { 
		switch (argv[i][1]) {
			case 'l':
				flags[0] = 1; break;
			case 'd':
				flags[1] = 1; break;
			case 'f':
				flags[2] = 1; break;
			case 's':
				flags[3] = 1; break;
		
			default:
				break;
		}
    }

	printf("\n\nflags - (l = %d | d = %d | f = %d | s = %d)\n\n", flags[0], flags[1], flags[2], flags[3]);

	return flags;
}

int main(int argc, char** argv) {

	int *flags = getFlags(argc, argv);

    int elemsCount = 0;
    char** files = find( argc >= 2 ? argv[1] : "./", flags, &elemsCount);

	if(!elemsCount) {
		printf("Elements not found...\n"); // вывод в консоль имя элемента
	}
    
    if(flags[3]) {
		printf("Sorted: \n\n"); // вывод в консоль имя элемента
        qsort(files, elemsCount, sizeof(char*), sortCondition); // сортировка по алфавиту
	}

    for(int i = 0; i < elemsCount; i++) {
        printf("  -  %s\n", files[i]); // вывод в консоль имя элемента

        free(files[i]); // освобождаем память, выделенную под элемент массива
    }

    free(files); // освобождаем память, выделенную под массив
    return 0;
}