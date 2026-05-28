#include <stdio.h>
#include <stdbool.h>

#define FRAMES 3
#define PAGES 12

int reference_string[PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};

bool isInFrames(int frames[], int page) {
    for (int i = 0; i < FRAMES; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

void fifo() {
    int frames[FRAMES];
    for (int i = 0; i < FRAMES; i++) frames[i] = -1;

    int page_faults = 0, index = 0;

    printf("\nFIFO Simulation:\n");
    for (int i = 0; i < PAGES; i++) {
        int page = reference_string[i];
        if (!isInFrames(frames, page)) {
            frames[index] = page;
            index = (index + 1) % FRAMES;
            page_faults++;
        }
        printf("Step %2d: ", i+1);
        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf(" %d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

void lru() {
    int frames[FRAMES];
    int last_used[FRAMES];
    for (int i = 0; i < FRAMES; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

    printf("\nLRU Simulation:\n");
    for (int i = 0; i < PAGES; i++) {
        int page = reference_string[i];
        if (isInFrames(frames, page)) {
            for (int j = 0; j < FRAMES; j++) {
                if (frames[j] == page) last_used[j] = i;
            }
        } else {
            int lru_index = 0;
            for (int j = 1; j < FRAMES; j++) {
                if (last_used[j] < last_used[lru_index]) lru_index = j;
            }
            frames[lru_index] = page;
            last_used[lru_index] = i;
            page_faults++;
        }
        printf("Step %2d: ", i+1);
        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf(" %d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

void optimal() {
    int frames[FRAMES];
    for (int i = 0; i < FRAMES; i++) frames[i] = -1;

    int page_faults = 0;

    printf("\nOptimal Simulation:\n");
    for (int i = 0; i < PAGES; i++) {
        int page = reference_string[i];
        if (!isInFrames(frames, page)) {
            int replace_index = -1, farthest = i;
            for (int j = 0; j < FRAMES; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
                int next_use = -1;
                for (int k = i+1; k < PAGES; k++) {
                    if (frames[j] == reference_string[k]) {
                        next_use = k;
                        break;
                    }
                }
                if (next_use == -1) {
                    replace_index = j;
                    break;
                }
                if (next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }
            frames[replace_index] = page;
            page_faults++;
        }
        printf("Step %2d: ", i+1);
        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf(" %d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

int main() {
    fifo();
    lru();
    optimal();
    return 0;
}
