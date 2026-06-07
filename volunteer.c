/* ============================================================
   volunteer.c — Module 3: Volunteer Management
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include "volunteer.h"

/* ── FUNCTION 1: Register volunteer ────────────────────────── */
void registerVolunteer(Volunteer *arr, int *count) {
    if (*count >= MAX) { printf("  System full!\n"); return; }
    Volunteer *v = &arr[*count];
    v->volunteerID = 3000 + *count + 1;
    while(getchar()!='\n');
    printf("  Name                                  : "); scanf(" %49[^\n]", v->name);
    printf("  Phone                                 : "); scanf("%14s", v->phone);
    printf("  Skill (Medical/Cooking/Driving/Rescue): "); scanf("%49s", v->skill);
    while(getchar()!='\n');
    printf("  Organisation                          : "); scanf(" %59[^\n]", v->meta.organization);
    printf("  Joined Date (YYYY-MM-DD)              : "); scanf("%11s", v->meta.joinedDate);
    v->isAvailable   = 1;
    v->meta.hoursWorked = 0;
    strcpy(v->assignedCamp, "Unassigned");
    (*count)++;
    printf("\n  [OK] Volunteer registered! ID: %d\n", v->volunteerID);
}

/* ── FUNCTION 2: Search volunteer by ID ─────────────────────── */
void searchVolunteerByID(Volunteer *arr, int count, int id) {
    for (int i = 0; i < count; i++)
        if (arr[i].volunteerID == id) {
            printf("\n  ── VOLUNTEER DETAILS ───────────────────\n");
            printf("  ID           : %d\n",  arr[i].volunteerID);
            printf("  Name         : %s\n",  arr[i].name);
            printf("  Phone        : %s\n",  arr[i].phone);
            printf("  Skill        : %s\n",  arr[i].skill);
            printf("  Organisation : %s\n",  arr[i].meta.organization);
            printf("  Joined       : %s\n",  arr[i].meta.joinedDate);
            printf("  Camp         : %s\n",  arr[i].assignedCamp);
            printf("  Status       : %s\n",  arr[i].isAvailable ? "Available" : "On Duty");
            printf("  Hours Worked : %d\n",  arr[i].meta.hoursWorked);
            printf("  ────────────────────────────────────────\n");
            return;
        }
    printf("  [!] Volunteer ID %d not found.\n", id);
}

/* ── FUNCTION 3: Edit volunteer ─────────────────────────────── */
void editVolunteer(Volunteer *arr, int count, int id) {
    int index = -1;
    for (int i = 0; i < count; i++)
        if (arr[i].volunteerID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Volunteer ID %d not found.\n", id); return; }

    Volunteer *v = &arr[index];
    printf("  Editing: %s (ID:%d)\n", v->name, v->volunteerID);
    printf("  Press Enter to keep current value.\n\n");

    char buf[60];
    printf("  Name [%s]: ", v->name);
    while (getchar() != '\n');
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(v->name, buf, 49);

    printf("  Phone [%s]: ", v->phone);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(v->phone, buf, 14);

    printf("  Skill [%s]: ", v->skill);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(v->skill, buf, 49);

    printf("  Organisation [%s]: ", v->meta.organization);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(v->meta.organization, buf, 59);

    printf("\n  [OK] Volunteer ID %d updated.\n", id);
}

/* ── FUNCTION 4: Delete volunteer ───────────────────────────── */
void deleteVolunteer(Volunteer *arr, int *count, int id) {
    int index = -1;
    for (int i = 0; i < *count; i++)
        if (arr[i].volunteerID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Volunteer ID %d not found.\n", id); return; }

    printf("  Deleting: %s (ID:%d)\n", arr[index].name, arr[index].volunteerID);

    if (!arr[index].isAvailable)
        printf("  [!] WARNING: This volunteer is currently On Duty at %s!\n",
               arr[index].assignedCamp);

    printf("  Are you sure? (1=Yes 0=No): ");
    int confirm; scanf("%d", &confirm);
    if (!confirm) { printf("  [OK] Cancelled.\n"); return; }

    for (int i = index; i < *count - 1; i++)
        arr[i] = arr[i + 1];
    (*count)--;
    printf("  [OK] Volunteer ID %d deleted.\n", id);
}

/* ── FUNCTION 5: Assign to camp ─────────────────────────────── */
void assignToCamp(Volunteer *arr, int count, int volID, char *camp) {
    for (int i = 0; i < count; i++)
        if (arr[i].volunteerID == volID) {
            strcpy(arr[i].assignedCamp, camp);
            arr[i].isAvailable = 0;
            printf("  [OK] %s assigned to %s.\n", arr[i].name, camp);
            return;
        }
    printf("  [!] Volunteer ID %d not found.\n", volID);
}

/* ── FUNCTION 6: Unassign from camp ─────────────────────────── */
void unassignFromCamp(Volunteer *arr, int count, int volID) {
    for (int i = 0; i < count; i++)
        if (arr[i].volunteerID == volID) {
            if (arr[i].isAvailable) {
                printf("  [!] %s is already available (not assigned).\n",
                       arr[i].name);
                return;
            }
            printf("  [OK] %s unassigned from %s.\n",
                   arr[i].name, arr[i].assignedCamp);
            strcpy(arr[i].assignedCamp, "Unassigned");
            arr[i].isAvailable = 1;
            return;
        }
    printf("  [!] Volunteer ID %d not found.\n", volID);
}

/* ── FUNCTION 7: View by skill ──────────────────────────────── */
void viewBySkill(Volunteer *arr, int count, char *skill) {
    printf("\n  ── Volunteers with skill: %s ──\n", skill);
    int found = 0;
    for (int i = 0; i < count; i++)
        if (strcasecmp(arr[i].skill, skill) == 0) {
            printf("  [%d] %-20s | Camp: %-20s | %s\n",
                arr[i].volunteerID, arr[i].name,
                arr[i].assignedCamp,
                arr[i].isAvailable ? "Available" : "On Duty");
            found++;
        }
    if (!found) printf("  No volunteers with skill: %s\n", skill);
}

/* ── FUNCTION 8: Log hours ──────────────────────────────────── */
void logHoursWorked(Volunteer *arr, int count, int volID, int hours) {
    if (hours <= 0) { printf("  [!] Hours must be greater than 0.\n"); return; }
    for (int i = 0; i < count; i++)
        if (arr[i].volunteerID == volID) {
            arr[i].meta.hoursWorked += hours;
            printf("  [OK] Logged %d hrs for %s. Total: %d hrs.\n",
                hours, arr[i].name, arr[i].meta.hoursWorked);
            return;
        }
    printf("  [!] Volunteer ID %d not found.\n", volID);
}

/* ── FUNCTION 9: List available ─────────────────────────────── */
void listAvailableVolunteers(Volunteer *arr, int count) {
    printf("\n  ── AVAILABLE VOLUNTEERS ──────────────\n");
    int found = 0;
    for (int i = 0; i < count; i++)
        if (arr[i].isAvailable) {
            printf("  [%d] %-20s | Skill: %-12s | Org: %s\n",
                arr[i].volunteerID, arr[i].name,
                arr[i].skill, arr[i].meta.organization);
            found++;
        }
    if (!found) printf("  No available volunteers.\n");
    else        printf("\n  Total available: %d\n", found);
}

/* ── SAVE / LOAD ─────────────────────────────────────────────── */
void saveVolunteers(Volunteer *v, int vc) {
    FILE *fp = fopen("data/volunteers.dat", "wb");
    if (!fp) { printf("  [!] ERROR: Could not save volunteers!\n"); return; }
    fwrite(&vc, sizeof(int), 1, fp);
    fwrite(v, sizeof(Volunteer), vc, fp);
    fclose(fp);
    printf("  [OK] Volunteers saved!\n");
}

void loadVolunteers(Volunteer *v, int *vc) {
    FILE *fp = fopen("data/volunteers.dat", "rb");
    if (fp) { fread(vc, sizeof(int), 1, fp);
              fread(v, sizeof(Volunteer), *vc, fp); fclose(fp); }
}

/* ── MENU ───────────────────────────────────────────────────── */
void volunteerMenu(Volunteer *arr, int *count) {
    int ch;
    do {
        printf("\n  +── VOLUNTEER MODULE ──────────────────────+\n");
        printf("  |  1. Register New Volunteer               |\n");
        printf("  |  2. Search Volunteer by ID               |\n");
        printf("  |  3. Edit Volunteer Details               |\n");
        printf("  |  4. Delete Volunteer                     |\n");
        printf("  |  5. Assign Volunteer to Camp             |\n");
        printf("  |  6. Unassign Volunteer from Camp         |\n");
        printf("  |  7. View Volunteers by Skill             |\n");
        printf("  |  8. Log Hours Worked                     |\n");
        printf("  |  9. List Available Volunteers            |\n");
        printf("  |  0. Back to Main Menu                    |\n");
        printf("  +──────────────────────────────────────────+\n");
        printf("  Choice: ");
        if (scanf("%d",&ch)!=1) { while(getchar()!='\n'); continue; }
        switch(ch) {
            case 1: registerVolunteer(arr, count); break;
            case 2: {
                int id;
                printf("  Volunteer ID: "); scanf("%d", &id);
                searchVolunteerByID(arr, *count, id); break;
            }
            case 3: {
                int id;
                printf("  Volunteer ID to edit: "); scanf("%d", &id);
                editVolunteer(arr, *count, id); break;
            }
            case 4: {
                int id;
                printf("  Volunteer ID to delete: "); scanf("%d", &id);
                deleteVolunteer(arr, count, id); break;
            }
            case 5: {
                int id; char camp[60];
                printf("  Volunteer ID : "); scanf("%d", &id);
                while(getchar()!='\n');
                printf("  Camp Name    : "); scanf(" %59[^\n]", camp);
                assignToCamp(arr, *count, id, camp); break;
            }
            case 6: {
                int id;
                printf("  Volunteer ID to unassign: "); scanf("%d", &id);
                unassignFromCamp(arr, *count, id); break;
            }
            case 7: {
                char skill[50];
                printf("  Skill: "); scanf("%49s", skill);
                viewBySkill(arr, *count, skill); break;
            }
            case 8: {
                int id, hrs;
                printf("  Volunteer ID: "); scanf("%d", &id);
                printf("  Hours worked: "); scanf("%d", &hrs);
                logHoursWorked(arr, *count, id, hrs); break;
            }
            case 9: listAvailableVolunteers(arr, *count); break;
            case 0: break;
            default: printf("  Invalid option.\n");
        }
    } while (ch != 0);
}