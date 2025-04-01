#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "table.h"
#include "row.h"


Pager* create_pager(const char* filename) {
    int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    if (fd == -1) {
        printf("cannot open file. \n");
        exit(EXIT_FAILURE);
    }

    off_t fileLength = lseek(fd, 0, SEEK_END);

    Pager* pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = fileLength;
    strcpy(pager->filename, filename);

    for (uint32_t i = 0; i < PAGES_PER_TABLE; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

Pager* get_page(Pager* pager, uint32_t pageNum) {
    if (pageNum > PAGES_PER_TABLE) {
        printf("page number out of range. must be less than %d", PAGES_PER_TABLE);
        exit(EXIT_FAILURE);
    }

    // cache miss
    if (pager->pages[pageNum] == NULL) {
        void* page = malloc(PAGE_SIZE);
        uint32_t numPages = pager->file_length / PAGE_SIZE;

        // remaining data - write to partial page
        if (pager->file_length % PAGE_SIZE) {
            numPages += 1;
        }

        if (pageNum <= numPages) {
            lseek(pager->file_descriptor, pageNum * PAGE_SIZE, SEEK_SET);
            ssize_t bytesRead = read(pager->file_descriptor, page, PAGE_SIZE);

            if (bytesRead == -1) {
                printf("cannot read file '%s'", pager->filename);
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[pageNum] = page;
    }

    return pager->pages[pageNum];
};

void flush_page(Pager* pager, uint32_t pageNum, uint32_t size) {
    if (pager->pages[pageNum] == NULL) {
        printf("error: cannot flush null page. \n");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(pager->file_descriptor, pageNum * PAGE_SIZE, SEEK_SET);

    if (offset == -1) {
        printf("error: cannot seek.\n");
        exit(EXIT_FAILURE);
    }

    ssize_t bytesWritten = write(pager->file_descriptor, pager->pages[pageNum], size);

    if (bytesWritten == -1) {
        printf("error: cannot write page to file.\n");
        exit(EXIT_FAILURE);
    }
};