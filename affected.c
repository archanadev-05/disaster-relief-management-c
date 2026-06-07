/* ============================================================
   affected.c — Module 1: Affected People Management
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include "affected.h"
#include "camp.h"
#include "distribution.h"

/* ── FUNCTION 1: Register a new affected person ────────────── */
void registerPerson(AffectedPerson *arr, int *count,
                    ReliefCamp *camps, int cCount) {
    if (*count >= MAX) { printf("  System full!\n"); return; }
    if (cCount == 0) {
        printf("  [!] No camps registered yet! Add a camp first (Menu 4).\n");
        return;
    }
    AffectedPerson *p = &arr[*count];
    p->personID = 1000 + *count + 1;

    printf("  Enter Name            : "); scanf(" %49[^\n]", p->name);
    do {
        printf("  Enter Age (1-120)     : "); scanf("%d", &p->age);
        if (p->age < 1 || p->age > 120)
            printf("  [!] Invalid age.\n");
    } while (p->age < 1 || p->age > 120);
    while (getchar() != '\n');
    printf("  Enter Gender (M/F)    : "); scanf("%9s",  p->gender);
    printf("  Enter Phone           : "); scanf("%14s", p->phone);
    printf("  Enter District        : "); scanf("%49s", p->location.district);
    printf("  Enter Grama Division  : "); scanf("%49s", p->location.grama);

    printf("\n  Available Camps:\n");
    for (int i = 0; i < cCount; i++)
        printf("    [%d] %s (%d/%d)\n",
               camps[i].campID, camps[i].campName,
               camps[i].currentOccupancy, camps[i].capacity);

    int validCamp = 0;
    do {
        while (getchar() != '\n');
        printf("  Enter Camp Name       : "); scanf(" %59[^\n]", p->location.campName);
        for (int i = 0; i < cCount; i++)
            if (strcasecmp(camps[i].campName, p->location.campName) == 0) {
                validCamp = 1;
                camps[i].currentOccupancy++;
                break;
            }
        if (!validCamp) printf("  [!] Camp not found! Try again.\n");
    } while (!validCamp);

    do {
        printf("  Enter Family Size     : "); scanf("%d", &p->familySize);
        if (p->familySize < 1) printf("  [!] Must be at least 1.\n");
    } while (p->familySize < 1);

    do {
        printf("  Special Need (0=None 1=Disabled 2=Pregnant 3=Elderly): ");
        scanf("%d", &p->specialNeed);
        if (p->specialNeed < 0 || p->specialNeed > 3)
            printf("  [!] Enter 0, 1, 2 or 3 only.\n");
    } while (p->specialNeed < 0 || p->specialNeed > 3);

    while (getchar() != '\n');
    printf("  Disaster Type (Flood/Landslide/Cyclone): ");
    scanf("%39s", p->disasterType);

    p->aidReceived = 0;
    (*count)++;
    printf("\n  [OK] Person registered! ID: %d\n", p->personID);
}

/* ── FUNCTION 2: View all persons in a district ─────────────── */
void viewByDistrict(AffectedPerson *arr, int count, char *district) {
    int found = 0;
    printf("\n  %-6s %-20s %-4s %-12s %-7s %s\n",
           "ID","Name","Age","Phone","Family","Aid Status");
    printf("  ──────────────────────────────────────────────────────\n");
    for (int i = 0; i < count; i++)
        if (strcasecmp(arr[i].location.district, district) == 0) {
            printf("  %-6d %-20s %-4d %-12s %-7d %s\n",
                arr[i].personID, arr[i].name, arr[i].age,
                arr[i].phone, arr[i].familySize,
                arr[i].aidReceived ? "[Received]" : "[Pending]");
            found++;
        }
    if (!found) printf("  No records found for district: %s\n", district);
    else        printf("\n  Total: %d person(s)\n", found);
}

/* ── FUNCTION 3: Search person by ID ───────────────────────── */
void searchPersonByID(AffectedPerson *arr, int count, int id) {
    char *needs[] = {"None","Disabled","Pregnant","Elderly"};
    for (int i = 0; i < count; i++)
        if (arr[i].personID == id) {
            printf("\n  ── PERSON DETAILS ──────────────────────\n");
            printf("  ID           : %d\n",  arr[i].personID);
            printf("  Name         : %s\n",  arr[i].name);
            printf("  Age          : %d\n",  arr[i].age);
            printf("  Gender       : %s\n",  arr[i].gender);
            printf("  Phone        : %s\n",  arr[i].phone);
            printf("  District     : %s\n",  arr[i].location.district);
            printf("  Grama        : %s\n",  arr[i].location.grama);
            printf("  Camp         : %s\n",  arr[i].location.campName);
            printf("  Family Size  : %d\n",  arr[i].familySize);
            printf("  Special Need : %s\n",
                   (arr[i].specialNeed >= 0 && arr[i].specialNeed <= 3)
                   ? needs[arr[i].specialNeed] : "Unknown");
            printf("  Disaster     : %s\n",  arr[i].disasterType);
            printf("  Aid Status   : %s\n",  arr[i].aidReceived ? "Received" : "Pending");
            printf("  ────────────────────────────────────────\n");
            return;
        }
    printf("  [!] Person ID %d not found.\n", id);
}

/* ── FUNCTION 4: Edit person details ───────────────────────── */
void editPerson(AffectedPerson *arr, int count, int id,
                ReliefCamp *camps, int cCount) {
    int index = -1;
    for (int i = 0; i < count; i++)
        if (arr[i].personID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Person ID %d not found.\n", id); return; }

    AffectedPerson *p = &arr[index];
    printf("  Editing: %s (ID:%d)\n", p->name, p->personID);
    printf("  Press Enter to keep current value.\n\n");

    /* Name */
    char buf[60];
    printf("  Name [%s]: ", p->name);
    while (getchar() != '\n');
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(p->name, buf, 49);

    /* Phone */
    printf("  Phone [%s]: ", p->phone);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(p->phone, buf, 14);

    /* District */
    printf("  District [%s]: ", p->location.district);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(p->location.district, buf, 49);

    /* Camp with validation */
    printf("  Camp [%s]: ", p->location.campName);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) {
        int valid = 0;
        for (int i = 0; i < cCount; i++)
            if (strcasecmp(camps[i].campName, buf) == 0) { valid = 1; break; }
        if (valid) strncpy(p->location.campName, buf, 59);
        else printf("  [!] Camp not found — camp name unchanged.\n");
    }

    /* Family size */
    printf("  Family Size [%d] (0=keep): ", p->familySize);
    int val; scanf("%d", &val);
    if (val > 0) p->familySize = val;

    /* Special Need */
    printf("  Special Need [%d] 0=None 1=Disabled 2=Pregnant 3=Elderly (-1=keep): ",
           p->specialNeed);
    scanf("%d", &val);
    if (val >= 0 && val <= 3) p->specialNeed = val;

    printf("\n  [OK] Person ID %d updated.\n", id);
}

/* ── FUNCTION 5: Delete person ──────────────────────────────── */
void deletePerson(AffectedPerson *arr, int *count, int id,
                  Distribution *dists, int dCount,
                  ReliefCamp *camps, int cCount) {
    int index = -1;
    for (int i = 0; i < *count; i++)
        if (arr[i].personID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Person ID %d not found.\n", id); return; }

    printf("  Deleting: %s (ID:%d, Camp:%s)\n",
           arr[index].name, arr[index].personID,
           arr[index].location.campName);

    /* Warn if distribution records exist */
    int distCount = 0;
    for (int i = 0; i < dCount; i++)
        if (dists[i].personID == id) distCount++;
    if (distCount > 0)
        printf("  [!] WARNING: %d distribution record(s) exist for this person!\n",
               distCount);

    printf("  Are you sure? (1=Yes 0=No): ");
    int confirm; scanf("%d", &confirm);
    if (!confirm) { printf("  [OK] Delete cancelled.\n"); return; }

    /* Decrease camp occupancy */
    for (int i = 0; i < cCount; i++)
        if (strcasecmp(camps[i].campName, arr[index].location.campName) == 0) {
            if (camps[i].currentOccupancy > 0) camps[i].currentOccupancy--;
            break;
        }

    /* Shift left */
    for (int i = index; i < *count - 1; i++)
        arr[i] = arr[i + 1];
    (*count)--;
    printf("  [OK] Person ID %d deleted.\n", id);
}

/* ── FUNCTION 6: List special needs ────────────────────────── */
void listSpecialNeeds(AffectedPerson *arr, int count) {
    char *needs[] = {"None","Disabled","Pregnant","Elderly"};
    int found = 0;
    printf("\n  ── PRIORITY CASES (Special Needs) ──\n");
    for (int i = 0; i < count; i++)
        if (arr[i].specialNeed > 0) {
            char *label = (arr[i].specialNeed >= 1 && arr[i].specialNeed <= 3)
                          ? needs[arr[i].specialNeed] : "Unknown";
            printf("  [%d] %-20s | %-10s | Camp: %s\n",
                arr[i].personID, arr[i].name, label,
                arr[i].location.campName);
            found++;
        }
    if (!found) printf("  No special needs cases registered.\n");
}

/* ── FUNCTION 7: Update aid status ─────────────────────────── */
void updateAidStatus(AffectedPerson *arr, int count, int id) {
    for (int i = 0; i < count; i++)
        if (arr[i].personID == id) {
            arr[i].aidReceived = 1;
            printf("  [OK] Aid status updated for %s.\n", arr[i].name);
            return;
        }
    printf("  [!] Person ID %d not found.\n", id);
}

/* ── FUNCTION 8: Sort by family size ───────────────────────── */
void sortByFamilySize(AffectedPerson *arr, int count) {
    AffectedPerson temp;
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (arr[j].familySize < arr[j+1].familySize) {
                temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
    printf("  [OK] Sorted by family size (largest first).\n");
    printf("\n  %-6s %-20s %-7s %s\n","ID","Name","Family","District");
    printf("  ────────────────────────────────────────\n");
    for (int i = 0; i < count; i++)
        printf("  %-6d %-20s %-7d %s\n",
            arr[i].personID, arr[i].name,
            arr[i].familySize, arr[i].location.district);
}

/* ── MENU ───────────────────────────────────────────────────── */
void affectedMenu(AffectedPerson *arr, int *count,
                  ReliefCamp *camps, int cCount,
                  Distribution *dists, int dCount) {
    int ch;
    do {
        printf("\n  +── AFFECTED PEOPLE MODULE ────────────────+\n");
        printf("  |  1. Register New Person                  |\n");
        printf("  |  2. View by District                     |\n");
        printf("  |  3. Search Person by ID                  |\n");
        printf("  |  4. Edit Person Details                  |\n");
        printf("  |  5. Delete Person                        |\n");
        printf("  |  6. List Special Needs (Priority Cases)  |\n");
        printf("  |  7. Update Aid Received Status           |\n");
        printf("  |  8. Sort by Family Size                  |\n");
        printf("  |  0. Back to Main Menu                    |\n");
        printf("  +──────────────────────────────────────────+\n");
        printf("  Choice: ");
        if (scanf("%d", &ch) != 1) { while(getchar()!='\n'); continue; }
        switch (ch) {
            case 1: registerPerson(arr, count, camps, cCount); break;
            case 2: {
                char d[50];
                printf("  Enter District: "); scanf("%49s", d);
                viewByDistrict(arr, *count, d); break;
            }
            case 3: {
                int id;
                printf("  Enter Person ID: "); scanf("%d", &id);
                searchPersonByID(arr, *count, id); break;
            }
            case 4: {
                int id;
                printf("  Enter Person ID to edit: "); scanf("%d", &id);
                editPerson(arr, *count, id, camps, cCount); break;
            }
            case 5: {
                int id;
                printf("  Enter Person ID to delete: "); scanf("%d", &id);
                deletePerson(arr, count, id, dists, dCount, camps, cCount); break;
            }
            case 6: listSpecialNeeds(arr, *count); break;
            case 7: {
                int id;
                printf("  Enter Person ID: "); scanf("%d", &id);
                updateAidStatus(arr, *count, id); break;
            }
            case 8: sortByFamilySize(arr, *count); break;
            case 0: break;
            default: printf("  Invalid option.\n");
        }
    } while (ch != 0);
}