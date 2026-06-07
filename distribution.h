#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#ifndef MAX
#define MAX 100
#endif

#include "affected.h"
#include "inventory.h"

typedef struct Distribution_s {
    int  distID;
    int  personID;
    int  campID;
    int  itemID;
    int  quantityGiven;
    char distributedDate[12];
    char distributedBy[50];
} Distribution;

void distributeAid(Distribution *dArr, int *dCount,
                   AffectedPerson *people, int pCount,
                   AidItem *items, int iCount);
void searchDistByID(Distribution *arr, int count, int id,
                    AffectedPerson *people, int pCount,
                    AidItem *items, int iCount);
void deleteDistribution(Distribution *arr, int *count, int id,
                        AffectedPerson *people, int pCount);
void viewDistributionHistory(Distribution *arr, int count);
void generateDistrictReport(AffectedPerson *people, int pCount,
                            char *district,
                            Distribution *dists, int dCount);
void saveAllData(AffectedPerson *p, int pc,
                 AidItem *a, int ac,
                 Distribution *d, int dc);
void loadAllData(AffectedPerson *p, int *pc,
                 AidItem *a, int *ac,
                 Distribution *d, int *dc);
void distributionMenu(Distribution *dArr, int *dCount,
                      AffectedPerson *people, int pCount,
                      AidItem *items, int iCount);
#endif