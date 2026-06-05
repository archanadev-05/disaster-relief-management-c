/* ============================================================
   MODULE 4 — RELIEF CAMP
   ============================================================ */

void setupCamp() {
    if (cCount >= MAX) { printf("  System full!\n"); return; }
    ReliefCamp *c = &camps[cCount];
    c->campID = 4000 + cCount + 1;
    while(getchar()!='\n');
    printf("  Camp Name              : "); scanf(" %59[^\n]", c->campName);
    printf("  District               : "); scanf("%49s", c->district);
    do {
        printf("  Maximum Capacity       : "); scanf("%d", &c->capacity);
        if (c->capacity <= 0) printf("  [!] Must be greater than 0.\n");
    } while (c->capacity <= 0);
    do {
        printf("  Current Occupancy      : "); scanf("%d", &c->currentOccupancy);
        if (c->currentOccupancy < 0 || c->currentOccupancy > c->capacity)
            printf("  [!] Must be between 0 and %d.\n", c->capacity);
    } while (c->currentOccupancy < 0 || c->currentOccupancy > c->capacity);
    printf("  GPS Latitude           : "); scanf("%f", &c->geo.lat);
    printf("  GPS Longitude          : "); scanf("%f", &c->geo.lon);
    printf("  Nearest Town           : "); scanf("%49s", c->geo.nearestTown);
    do {
        printf("  Has Medical Unit? (1/0): "); scanf("%d", &c->hasMedical);
        if (c->hasMedical != 0 && c->hasMedical != 1) printf("  [!] Enter 1 or 0.\n");
    } while (c->hasMedical != 0 && c->hasMedical != 1);
    do {
        printf("  Has Clean Water? (1/0) : "); scanf("%d", &c->hasWater);
        if (c->hasWater != 0 && c->hasWater != 1) printf("  [!] Enter 1 or 0.\n");
    } while (c->hasWater != 0 && c->hasWater != 1);
    while(getchar()!='\n');
    printf("  Manager Name           : "); scanf(" %49[^\n]", c->managerName);
    printf("  Setup Date (YYYY-MM-DD): "); scanf("%11s", c->setupDate);
    cCount++;
    printf("\n  [OK] Camp registered! ID: %d\n", c->campID);
}

void searchCampByID() {
    int id;
    printf("  Camp ID: "); scanf("%d", &id);
    for (int i = 0; i < cCount; i++)
        if (camps[i].campID == id) {
            int free = camps[i].capacity - camps[i].currentOccupancy;
            printf("\n  ── CAMP DETAILS ────────────────────────\n");
            printf("  ID           : %d\n",  camps[i].campID);
            printf("  Name         : %s\n",  camps[i].campName);
            printf("  District     : %s\n",  camps[i].district);
            printf("  Capacity     : %d\n",  camps[i].capacity);
            printf("  Occupancy    : %d\n",  camps[i].currentOccupancy);
            printf("  Free Spots   : %d\n",  free);
            printf("  Medical Unit : %s\n",  camps[i].hasMedical ? "YES":"NO");
            printf("  Clean Water  : %s\n",  camps[i].hasWater   ? "YES":"NO");
            printf("  Manager      : %s\n",  camps[i].managerName);
            printf("  Nearest Town : %s\n",  camps[i].geo.nearestTown);
            printf("  Setup Date   : %s\n",  camps[i].setupDate);
            printf("  ────────────────────────────────────────\n");
            return;
        }
    printf("  [!] Camp ID %d not found.\n", id);
}

void editCamp() {
    int id;
    printf("  Camp ID to edit: "); scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < cCount; i++)
        if (camps[i].campID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Camp ID %d not found.\n", id); return; }

    ReliefCamp *c = &camps[index];
    printf("  Editing: %s (ID:%d)\n", c->campName, c->campID);
    printf("  Press Enter to keep current value.\n\n");

    char buf[60];
    printf("  Camp Name [%s]: ", c->campName);
    while (getchar() != '\n');
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(c->campName, buf, 59);

    printf("  Manager Name [%s]: ", c->managerName);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(c->managerName, buf, 49);

    printf("  Max Capacity [%d] (0=keep): ", c->capacity);
    int val; scanf("%d", &val);
    if (val > 0) c->capacity = val;

    printf("  Has Medical (1/0) [%d] (-1=keep): ", c->hasMedical);
    scanf("%d", &val);
    if (val == 0 || val == 1) c->hasMedical = val;

    printf("  Has Water (1/0) [%d] (-1=keep): ", c->hasWater);
    scanf("%d", &val);
    if (val == 0 || val == 1) c->hasWater = val;

    printf("\n  [OK] Camp ID %d updated.\n", id);
}

void deleteCamp() {
    int id;
    printf("  Camp ID to delete: "); scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < cCount; i++)
        if (camps[i].campID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Camp ID %d not found.\n", id); return; }

    printf("  Deleting: %s (ID:%d)\n", camps[index].campName, camps[index].campID);

    int pInCamp = 0;
    for (int i = 0; i < pCount; i++)
        if (strcasecmp(people[i].location.campName, camps[index].campName) == 0)
            pInCamp++;
    if (pInCamp > 0)
        printf("  [!] WARNING: %d person(s) registered under this camp!\n", pInCamp);

    int vInCamp = 0;
    for (int i = 0; i < vCount; i++)
        if (strcasecmp(volunteers[i].assignedCamp, camps[index].campName) == 0)
            vInCamp++;
    if (vInCamp > 0)
        printf("  [!] WARNING: %d volunteer(s) assigned to this camp!\n", vInCamp);

    printf("  Are you sure? (1=Yes 0=No): ");
    int confirm; scanf("%d", &confirm);
    if (!confirm) { printf("  [OK] Cancelled.\n"); return; }

    for (int i = index; i < cCount - 1; i++)
        camps[i] = camps[i + 1];
    cCount--;
    printf("  [OK] Camp ID %d deleted.\n", id);
}

void viewCampCapacity() {
    if (cCount == 0) { printf("  No camps registered yet.\n"); return; }
    printf("\n  %-5s %-25s %-5s %-5s %-5s %-7s %-5s\n",
           "ID","Camp Name","Cap","Occ","Free","Medical","Water");
    printf("  ─────────────────────────────────────────────────────────\n");
    for (int i = 0; i < cCount; i++) {
        int free = camps[i].capacity - camps[i].currentOccupancy;
        printf("  %-5d %-25s %-5d %-5d %-5d %-7s %-5s\n",
            camps[i].campID, camps[i].campName,
            camps[i].capacity, camps[i].currentOccupancy, free,
            camps[i].hasMedical ? "YES":"NO",
            camps[i].hasWater   ? "YES":"NO");
        if (free == 0) printf("  [!] FULL — redirect incoming persons!\n");
    }
}

void updateOccupancy() {
    int id, people_count;
    printf("  Camp ID : "); scanf("%d", &id);
    printf("  People to add (+) or remove (-): "); scanf("%d", &people_count);
    for (int i = 0; i < cCount; i++)
        if (camps[i].campID == id) {
            if (camps[i].currentOccupancy + people_count > camps[i].capacity) {
                printf("  [!] Over capacity! Max: %d\n", camps[i].capacity);
                return;
            }
            if (camps[i].currentOccupancy + people_count < 0) {
                printf("  [!] Cannot go below 0!\n");
                return;
            }
            camps[i].currentOccupancy += people_count;
            printf("  [OK] %s: %d/%d people now.\n",
                camps[i].campName, camps[i].currentOccupancy, camps[i].capacity);
            return;
        }
    printf("  [!] Camp ID %d not found.\n", id);
}

void findCampByDistrict() {
    char district[50];
    printf("  District: "); scanf("%49s", district);
    printf("\n  ── Camps in %s ──\n", district);
    int found = 0;
    for (int i = 0; i < cCount; i++)
        if (strcasecmp(camps[i].district, district) == 0) {
            int free = camps[i].capacity - camps[i].currentOccupancy;
            printf("  [%d] %-25s | Manager: %-15s | Free: %d spots\n",
                camps[i].campID, camps[i].campName,
                camps[i].managerName, free);
            found++;
        }
    if (!found) printf("  No camps in district: %s\n", district);
}

void sortByAvailableSpace() {
    ReliefCamp temp;
    for (int i = 0; i < cCount-1; i++)
        for (int j = 0; j < cCount-i-1; j++) {
            int fA = camps[j].capacity   - camps[j].currentOccupancy;
            int fB = camps[j+1].capacity - camps[j+1].currentOccupancy;
            if (fA < fB) { temp=camps[j]; camps[j]=camps[j+1]; camps[j+1]=temp; }
        }
    printf("  [OK] Sorted by available space.\n");
    viewCampCapacity();
}

void campMenu() {
    int ch;
    do {
        printf("\n  +── RELIEF CAMP MODULE ────────────────────+\n");
        printf("  |  1. Setup New Relief Camp                |\n");
        printf("  |  2. Search Camp by ID                    |\n");
        printf("  |  3. Edit Camp Details                    |\n");
        printf("  |  4. Delete Camp                          |\n");
        printf("  |  5. View All Camp Capacities             |\n");
        printf("  |  6. Update Camp Occupancy                |\n");
        printf("  |  7. Find Camps by District               |\n");
        printf("  |  8. Sort Camps by Available Space        |\n");
        printf("  |  0. Back to Main Menu                    |\n");
        printf("  +──────────────────────────────────────────+\n");
        printf("  Choice: ");
        if (scanf("%d",&ch)!=1) { while(getchar()!='\n'); continue; }
        switch(ch) {
            case 1: setupCamp();            break;
            case 2: searchCampByID();       break;
            case 3: editCamp();             break;
            case 4: deleteCamp();           break;
            case 5: viewCampCapacity();     break;
            case 6: updateOccupancy();      break;
            case 7: findCampByDistrict();   break;
            case 8: sortByAvailableSpace(); break;
            case 0: break;
            default: printf("  Invalid option.\n");
        }
    } while (ch != 0);
}
