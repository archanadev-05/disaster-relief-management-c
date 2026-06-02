/* ============================================================
   distribution.c — Module 5: Aid Distribution & Reports
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include "distribution.h"

/* ── FUNCTION 1: Distribute aid ────────────────────────────── */
void distributeAid(Distribution *dArr, int *dCount,
                   AffectedPerson *people, int pCount,
                   AidItem *items, int iCount) {
    int personID, itemID, qty;
    printf("  Enter Person ID : "); scanf("%d", &personID);

    AffectedPerson *p = NULL;
    for (int i = 0; i < pCount; i++)
        if (people[i].personID == personID) { p = &people[i]; break; }
    if (!p) { printf("  [!] Person not found.\n"); return; }

    printf("  [OK] Found: %s | Family: %d\n", p->name, p->familySize);
    if (p->specialNeed) printf("  [*] PRIORITY: Special needs case!\n");

    if (p->aidReceived) {
        printf("  [!] WARNING: %s has already received aid!\n", p->name);
        printf("  Proceed anyway? (1=Yes 0=No): ");
        int confirm; scanf("%d", &confirm);
        if (!confirm) return;
    }

    printf("  Enter Item ID   : "); scanf("%d", &itemID);
    do {
        printf("  Enter Quantity  : "); scanf("%d", &qty);
        if (qty <= 0) printf("  [!] Must be greater than 0.\n");
    } while (qty <= 0);

    for (int i = 0; i < iCount; i++)
        if (items[i].itemID == itemID) {
            if (items[i].quantity < qty) {
                printf("  [!] Not enough stock! Available: %d\n", items[i].quantity);
                return;
            }
            items[i].quantity -= qty;
            if (items[i].quantity < 50)
                printf("  [!] WARNING: %s running low! Only %d %s left!\n",
                       items[i].itemName, items[i].quantity, items[i].unit);

            Distribution *d = &dArr[*dCount];
            d->distID = 5000 + *dCount + 1;
            d->personID = personID;
            d->itemID   = itemID;
            d->quantityGiven = qty;
            d->campID   = 0;
            while(getchar()!='\n');
            printf("  Distributed by       : "); scanf(" %49[^\n]", d->distributedBy);
            printf("  Distribution Date (YYYY-MM-DD): "); scanf("%11s", d->distributedDate);
            p->aidReceived = 1;
            (*dCount)++;
            printf("\n  ── DISTRIBUTION RECEIPT ────────────────\n");
            printf("  Dist ID   : D-%d\n",     d->distID);
            printf("  Person    : %s (ID:%d)\n", p->name, personID);
            printf("  Item      : %s x %d %s\n", items[i].itemName, qty, items[i].unit);
            printf("  Stock Left: %d\n",         items[i].quantity);
            printf("  Date      : %s\n",          d->distributedDate);
            printf("  By        : %s\n",          d->distributedBy);
            printf("  ────────────────────────────────────────\n");
            printf("  [OK] Aid distributed successfully!\n");
            return;
        }
    printf("  [!] Item not found.\n");
}

/* ── FUNCTION 2: Search distribution by ID ──────────────────── */
void searchDistByID(Distribution *arr, int count, int id,
                    AffectedPerson *people, int pCount,
                    AidItem *items, int iCount) {
    for (int i = 0; i < count; i++)
        if (arr[i].distID == id) {
            /* Resolve names */
            char pName[50] = "Unknown", iName[50] = "Unknown";
            for (int j = 0; j < pCount; j++)
                if (people[j].personID == arr[i].personID) {
                    strncpy(pName, people[j].name, 49); break;
                }
            for (int j = 0; j < iCount; j++)
                if (items[j].itemID == arr[i].itemID) {
                    strncpy(iName, items[j].itemName, 49); break;
                }
            printf("\n  ── DISTRIBUTION DETAILS ────────────────\n");
            printf("  Dist ID  : D-%d\n",  arr[i].distID);
            printf("  Person   : %s (ID:%d)\n", pName, arr[i].personID);
            printf("  Item     : %s (ID:%d)\n", iName, arr[i].itemID);
            printf("  Quantity : %d\n",    arr[i].quantityGiven);
            printf("  Date     : %s\n",    arr[i].distributedDate);
            printf("  By       : %s\n",    arr[i].distributedBy);
            printf("  ────────────────────────────────────────\n");
            return;
        }
    printf("  [!] Distribution ID %d not found.\n", id);
}

/* ── FUNCTION 3: Delete distribution record ─────────────────── */
void deleteDistribution(Distribution *arr, int *count, int id,
                        AffectedPerson *people, int pCount) {
    int index = -1;
    for (int i = 0; i < *count; i++)
        if (arr[i].distID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Distribution ID %d not found.\n", id); return; }

    printf("  Deleting: D-%d | Person:%d | Item:%d | Qty:%d\n",
           arr[index].distID, arr[index].personID,
           arr[index].itemID, arr[index].quantityGiven);
    printf("  [!] NOTE: Stock will NOT be auto-restored. Update manually if needed.\n");
    printf("  Are you sure? (1=Yes 0=No): ");
    int confirm; scanf("%d", &confirm);
    if (!confirm) { printf("  [OK] Cancelled.\n"); return; }

    /* Reset aidReceived if this was the only distribution for that person */
    int otherDists = 0;
    for (int i = 0; i < *count; i++)
        if (i != index && arr[i].personID == arr[index].personID)
            otherDists++;
    if (otherDists == 0)
        for (int i = 0; i < pCount; i++)
            if (people[i].personID == arr[index].personID) {
                people[i].aidReceived = 0;
                printf("  [OK] Aid status reset for Person ID %d.\n",
                       arr[index].personID);
                break;
            }

    for (int i = index; i < *count - 1; i++)
        arr[i] = arr[i + 1];
    (*count)--;
    printf("  [OK] Distribution D-%d deleted.\n", id);
}

/* ── FUNCTION 4: View full history ─────────────────────────── */
void viewDistributionHistory(Distribution *arr, int count) {
    if (count == 0) { printf("  No distributions recorded yet.\n"); return; }
    printf("\n  %-8s %-10s %-8s %-6s %-12s %s\n",
           "DistID","PersonID","ItemID","Qty","Date","By");
    printf("  ──────────────────────────────────────────────────────\n");
    for (int i = 0; i < count; i++)
        printf("  %-8d %-10d %-8d %-6d %-12s %s\n",
            arr[i].distID, arr[i].personID, arr[i].itemID,
            arr[i].quantityGiven, arr[i].distributedDate,
            arr[i].distributedBy);
    printf("\n  Total distributions: %d\n", count);
}

/* ── FUNCTION 5: District report ────────────────────────────── */
void generateDistrictReport(AffectedPerson *people, int pCount,
                            char *district,
                            Distribution *dists, int dCount) {
    int total = 0, received = 0, special = 0, districtDists = 0;
    for (int i = 0; i < pCount; i++)
        if (strcasecmp(people[i].location.district, district) == 0) {
            total++;
            if (people[i].aidReceived) received++;
            if (people[i].specialNeed > 0) special++;
        }
    for (int i = 0; i < dCount; i++)
        for (int j = 0; j < pCount; j++)
            if (dists[i].personID == people[j].personID &&
                strcasecmp(people[j].location.district, district) == 0) {
                districtDists++; break;
            }
    printf("\n  ══════════════════════════════════════════\n");
    printf("   %s DISTRICT — SUMMARY REPORT\n", district);
    printf("  ══════════════════════════════════════════\n");
    printf("  Total Affected Persons : %d\n", total);
    if (total > 0) {
        printf("  Aid Received           : %d (%.1f%%)\n",
            received, (float)received/total*100);
        printf("  Pending Aid            : %d\n", total-received);
    }
    printf("  Special Needs Cases    : %d\n", special);
    printf("  District Distributions : %d\n", districtDists);
    printf("  ══════════════════════════════════════════\n");
}

/* ── SAVE / LOAD ─────────────────────────────────────────────── */
void saveAllData(AffectedPerson *p, int pc,
                 AidItem *a, int ac,
                 Distribution *d, int dc) {
    FILE *fp;
    fp = fopen("data/people.dat","wb");
    if (!fp) printf("  [!] ERROR: Could not save people data!\n");
    else { fwrite(&pc,sizeof(int),1,fp); fwrite(p,sizeof(AffectedPerson),pc,fp); fclose(fp); }

    fp = fopen("data/inventory.dat","wb");
    if (!fp) printf("  [!] ERROR: Could not save inventory data!\n");
    else { fwrite(&ac,sizeof(int),1,fp); fwrite(a,sizeof(AidItem),ac,fp); fclose(fp); }

    fp = fopen("data/distribution.dat","wb");
    if (!fp) printf("  [!] ERROR: Could not save distribution data!\n");
    else { fwrite(&dc,sizeof(int),1,fp); fwrite(d,sizeof(Distribution),dc,fp); fclose(fp); }

    printf("  [OK] All data saved!\n");
}

void loadAllData(AffectedPerson *p, int *pc,
                 AidItem *a, int *ac,
                 Distribution *d, int *dc) {
    FILE *fp;
    fp = fopen("data/people.dat","rb");
    if (fp) { fread(pc,sizeof(int),1,fp); fread(p,sizeof(AffectedPerson),*pc,fp); fclose(fp); }
    fp = fopen("data/inventory.dat","rb");
    if (fp) { fread(ac,sizeof(int),1,fp); fread(a,sizeof(AidItem),*ac,fp); fclose(fp); }
    fp = fopen("data/distribution.dat","rb");
    if (fp) { fread(dc,sizeof(int),1,fp); fread(d,sizeof(Distribution),*dc,fp); fclose(fp); }
    if (*pc>0||*ac>0||*dc>0)
        printf("  [OK] Loaded: %d persons, %d items, %d distributions.\n",*pc,*ac,*dc);
}

/* ── MENU ───────────────────────────────────────────────────── */
void distributionMenu(Distribution *dArr, int *dCount,
                      AffectedPerson *people, int pCount,
                      AidItem *items, int iCount) {
    int ch;
    do {
        printf("\n  +── AID DISTRIBUTION MODULE ───────────────+\n");
        printf("  |  1. Distribute Aid to Person             |\n");
        printf("  |  2. Search Distribution by ID            |\n");
        printf("  |  3. Delete Distribution Record           |\n");
        printf("  |  4. View Distribution History            |\n");
        printf("  |  5. Generate District Report             |\n");
        printf("  |  0. Back to Main Menu                    |\n");
        printf("  +──────────────────────────────────────────+\n");
        printf("  Choice: ");
        if (scanf("%d",&ch)!=1) { while(getchar()!='\n'); continue; }
        switch(ch) {
            case 1: distributeAid(dArr,dCount,people,pCount,items,iCount); break;
            case 2: {
                int id;
                printf("  Distribution ID: "); scanf("%d", &id);
                searchDistByID(dArr,*dCount,id,people,pCount,items,iCount); break;
            }
            case 3: {
                int id;
                printf("  Distribution ID to delete: "); scanf("%d", &id);
                deleteDistribution(dArr,dCount,id,people,pCount); break;
            }
            case 4: viewDistributionHistory(dArr,*dCount); break;
            case 5: {
                char dist[50];
                printf("  Enter District: "); scanf("%49s",dist);
                generateDistrictReport(people,pCount,dist,dArr,*dCount); break;
            }
            case 0: break;
            default: printf("  Invalid option.\n");
        }
    } while (ch != 0);
}