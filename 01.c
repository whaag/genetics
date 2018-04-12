#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    short weight;
    short value;
};

const short max_weight = 15;

char* generateCandidate(struct Item *items);
short totalWeight(struct Item* items, char* candidate);
short totalValue(struct Item* items, char* candidate);
char* cross(char* candidateA, char* candidateB);

int main(void) {
    struct Item itemA, itemB, itemC, itemD,
            itemE, itemF, itemG, itemH;
    itemA.weight = 10;
    itemA.value  = 11;
        itemB.weight = 4;
        itemB.value  = 8;
        itemC.weight = 5;
        itemC.value  = 6;
        itemD.weight = 2;
        itemD.value  = 12;
        itemE.weight = 8;
        itemE.value  = 5;
        itemF.weight = 2;
        itemF.value  = 8;
        itemG.weight = 6;
        itemG.value  = 4;
        itemH.weight = 7;
        itemH.value  = 13;
    
    struct Item items[8];
    items[0] = itemA;
        items[1] = itemB;
        items[2] = itemC;
        items[3] = itemD;
        items[4] = itemE;
        items[5] = itemF;
        items[6] = itemG;
        items[7] = itemH;


        char* candidates[20];
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < 20; i++) {

        candidates[i] = generateCandidate(items);
    }
    char crossControl[20];
    short BestOverallValue = 0;
    short BestOverallWeight = 0;
    int bestGeneration = 0;
    for (int i = 0; i < 20; i++) {
        char* children[10];
        for (int j = 0; j < 20; j++) {
            crossControl[j] = 0;
        }

        short candidatesCrossed = 0;
        short childrenIndex = 0;

        while (candidatesCrossed < 20) {
            const int indexA = rand() % 20;
            const int indexB = rand() % 20;

            if (!crossControl[indexA] && !crossControl[indexB] && indexA != indexB) {
                crossControl[indexA] = 1;
                crossControl[indexB] = 1;
                candidatesCrossed += 2;

                char *childCandidate = cross(candidates[indexA], candidates[indexB]);

                children[childrenIndex] = childCandidate;
                childrenIndex += 1;
            }
        }

        short best = -1;
        short secondBest = -1;
        short worst = 99;
        short indexBest = -1;
        short indexSecondBest = -1;
        short indexWorst = -1;
        for (int j = 0; j < 10; j++ ) {
            // for (int k = 0; k < 8; k++) {
            //     printf("%d ",children[j][k]);
            // }
            // printf("\n");
            const short totalValues = totalValue(items, children[j]);
            const short totalWeights = totalWeight(items, children[j]);

            if (totalValues > BestOverallValue && totalWeights <= max_weight) {
                BestOverallValue = totalValues;
                BestOverallWeight = totalWeights;
                bestGeneration = i;
            }

            if (totalValues > best & totalWeights <= max_weight) {
                secondBest = best;
                indexSecondBest = indexBest;
                best = totalValues;
                indexBest = j;
            } else if (totalValues > secondBest & totalWeights <= max_weight) {
                secondBest = totalValues;
                indexSecondBest = j;
            } else if (totalValues < worst & totalWeights <= max_weight) {
                worst = totalValues;
                indexWorst = j;
            }
        }

        int broughtFromPast = 0;
        if (totalWeight(items, children[indexBest]) <= max_weight) {
            candidates[0] = children[indexBest];
            broughtFromPast += 1;
        }
        if (totalWeight(items, children[indexSecondBest]) <= max_weight) {
            candidates[1] = children[indexSecondBest];
            broughtFromPast += 1;
        }
        if (totalWeight(items, children[indexWorst]) <= max_weight) {
            candidates[2] = children[indexWorst];
            broughtFromPast += 1;
        }
        printf("Generation %d \n", i);
        printf("Best Value: %d Weight: %d \n", totalValue(items, children[indexBest]), totalWeight(items, children[indexBest]));
        printf("Sec  Value: %d Weight: %d \n", totalValue(items, children[indexSecondBest]), totalWeight(items, children[indexSecondBest]));
        printf("Dive Value: %d Weight: %d \n", totalValue(items, children[indexWorst]), totalWeight(items, children[indexWorst]));
        printf("===========================================================\n");
        
        for (int y = broughtFromPast; y < 20; y++) {
            candidates[y] = generateCandidate(items);
        }    
    }

    printf("Best found in Generation %d\n", bestGeneration);
    printf("Value:  %d\n", BestOverallValue);
    printf("Weight: %d\n", BestOverallWeight);

    return 0;
}

char* generateCandidate(struct Item *items) {
    short weightsSum = 0;
    char *generated = malloc(8 * sizeof(char));
    char tried[8];
    short sumOfAllIndexes = 0;
    for (int i = 0; i < 8; i++) {
        generated[i] = 0;
        tried[i] = 0;
    }

    for (int i = 0; i < 8; i++) {
    //while (sumOfAllIndexes < 36) {
        const int item = rand() % 8;
        // if (tried[item] == 0) {
            if ((weightsSum + items[item].weight) < 16) {
                generated[item] = 1;
                weightsSum += items[item].weight;
            }
            sumOfAllIndexes += item + 1;
            tried[item] = 1;
        // }
    }
    
    return generated;
}

short totalWeight(struct Item* items, char* candidate) {
    short total = 0;
    for (int i = 0; i < 8; i++) {
        if (candidate[i]) {
            total += items[i].weight;
        }
    }
    
    return total;
}

short totalValue(struct Item* items, char* candidate) {
        short total = 0;
        for (int i = 0; i < 8; i++) {
                if (candidate[i]) {
                        total += items[i].value;;
                }
        }

        return total;
}

char* cross(char* candidateA, char* candidateB) {

    char* child = malloc(8 * sizeof(char));
    for (int i = 0; i < 8; i++) {
        child[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        if (!(i & 1)) {
            child[i] = candidateA[i];
        } else {
            child[i] = candidateB[i];
        }
    }

    free(candidateA);
    free(candidateB);

    return child;
}
