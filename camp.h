#ifndef CAMP_H
#define CAMP_H
#ifndef MAX
#define MAX 100
#endif

#include "affected.h"
#include "volunteer.h"

typedef struct {
    float lat;
    float lon;
    char  nearestTown[50];
} GeoLocation;

typedef struct ReliefCamp_s {
    int         campID;
    char        campName[60];
    char        district[50];
    int         capacity;
    int         currentOccupancy;
    GeoLocation geo;
    int         hasMedical;
    int         hasWater;
    char        managerName[50];
    char        setupDate[12];
} ReliefCamp;

void setupCamp(ReliefCamp *arr, int *count);
void searchCampByID(ReliefCamp *arr, int count, int id);
void editCamp(ReliefCamp *arr, int count, int id);
void deleteCamp(ReliefCamp *arr, int *count, int id,
                AffectedPerson *people, int pCount,
                Volunteer *volunteers, int vCount);
void viewCampCapacity(ReliefCamp *arr, int count);
void updateOccupancy(ReliefCamp *arr, int count, int campID, int people);
void findCampByDistrict(ReliefCamp *arr, int count, char *district);
void sortByAvailableSpace(ReliefCamp *arr, int count);
void saveCamps(ReliefCamp *c, int cc);
void loadCamps(ReliefCamp *c, int *cc);
void campMenu(ReliefCamp *arr, int *count,
              AffectedPerson *people, int pCount,
              Volunteer *volunteers, int vCount);
#endif
