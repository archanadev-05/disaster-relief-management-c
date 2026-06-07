#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#ifndef MAX
#define MAX 100
#endif

typedef struct {
    char organization[60];
    char joinedDate[12];
    int  hoursWorked;
} VolMeta;

typedef struct {
    int     volunteerID;
    char    name[50];
    char    phone[15];
    char    skill[50];
    char    assignedCamp[60];
    int     isAvailable;
    VolMeta meta;
} Volunteer;

void registerVolunteer(Volunteer *arr, int *count);
void searchVolunteerByID(Volunteer *arr, int count, int id);
void editVolunteer(Volunteer *arr, int count, int id);
void deleteVolunteer(Volunteer *arr, int *count, int id);
void assignToCamp(Volunteer *arr, int count, int volID, char *camp);
void unassignFromCamp(Volunteer *arr, int count, int volID);
void viewBySkill(Volunteer *arr, int count, char *skill);
void logHoursWorked(Volunteer *arr, int count, int volID, int hours);
void listAvailableVolunteers(Volunteer *arr, int count);
void saveVolunteers(Volunteer *v, int vc);
void loadVolunteers(Volunteer *v, int *vc);
void volunteerMenu(Volunteer *arr, int *count);
#endif