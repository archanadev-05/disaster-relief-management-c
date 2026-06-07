#ifndef AFFECTED_H
#define AFFECTED_H
#define MAX 100

typedef struct {
    char district[50];
    char grama[50];
    char campName[60];
} Location;

typedef struct {
    int      personID;
    char     name[50];
    int      age;
    char     gender[10];
    char     phone[15];
    Location location;
    int      familySize;
    int      specialNeed;
    char     disasterType[40];
    int      aidReceived;
} AffectedPerson;

typedef struct ReliefCamp_s ReliefCamp;
typedef struct Distribution_s Distribution;

void registerPerson(AffectedPerson *arr, int *count,
                    ReliefCamp *camps, int cCount);
void viewByDistrict(AffectedPerson *arr, int count, char *district);
void searchPersonByID(AffectedPerson *arr, int count, int id);
void editPerson(AffectedPerson *arr, int count, int id,
                ReliefCamp *camps, int cCount);
void deletePerson(AffectedPerson *arr, int *count, int id,
                  Distribution *dists, int dCount,
                  ReliefCamp *camps, int cCount);
void listSpecialNeeds(AffectedPerson *arr, int count);
void updateAidStatus(AffectedPerson *arr, int count, int id);
void sortByFamilySize(AffectedPerson *arr, int count);
void affectedMenu(AffectedPerson *arr, int *count,
                  ReliefCamp *camps, int cCount,
                  Distribution *dists, int dCount);
#endif