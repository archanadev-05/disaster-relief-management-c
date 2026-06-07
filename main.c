/* ============================================================
   main.c — Disaster Relief & Aid Distribution System
   IN 1101 — Programming Fundamentals | Group Project
   University of Moratuwa
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include "affected.h"
#include "inventory.h"
#include "volunteer.h"
#include "camp.h"
#include "distribution.h"

int main() {
    AffectedPerson people[MAX];      int pCount = 0;
    AidItem        items[MAX];       int iCount = 0;
    Volunteer      volunteers[MAX];  int vCount = 0;
    ReliefCamp     camps[MAX];       int cCount = 0;
    Distribution   dists[MAX];       int dCount = 0;

#ifdef _WIN32
    system("mkdir data 2>nul");
#else
    system("mkdir -p data");
#endif

    loadAllData(people, &pCount, items, &iCount, dists, &dCount);
    loadVolunteers(volunteers, &vCount);
    loadCamps(camps, &cCount);

    int choice;
    do {
        printf("\n  +============================================+\n");
        printf("  |   DISASTER RELIEF & AID DISTRIBUTION      |\n");
        printf("  |   Management System  v2.0                 |\n");
        printf("  |   Programming Fundamentals — IN 1101        |\n");
        printf("  +============================================+\n");
        printf("  |  1. Affected People Management            |\n");
        printf("  |  2. Aid Inventory Management              |\n");
        printf("  |  3. Volunteer Management                  |\n");
        printf("  |  4. Relief Camp Management                |\n");
        printf("  |  5. Aid Distribution & Reports            |\n");
        printf("  |  6. Save All Data to File                 |\n");
        printf("  |  0. Exit                                  |\n");
        printf("  +============================================+\n");
        printf("  Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("  [!] Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: affectedMenu(people, &pCount,
                        camps, cCount, dists, dCount);                      break;
            case 2: inventoryMenu(items, &iCount, dists, dCount);           break;
            case 3: volunteerMenu(volunteers, &vCount);                     break;
            case 4: campMenu(camps, &cCount,
                        people, pCount, volunteers, vCount);                break;
            case 5: distributionMenu(dists, &dCount,
                        people, pCount, items, iCount);                     break;
            case 6: saveAllData(people, pCount, items, iCount, dists, dCount);
                    saveVolunteers(volunteers, vCount);
                    saveCamps(camps, cCount);                               break;
            case 0: saveAllData(people, pCount, items, iCount, dists, dCount);
                    saveVolunteers(volunteers, vCount);
                    saveCamps(camps, cCount);
                    printf("\n  Data saved. Goodbye!\n\n");                  break;
            default: printf("  [!] Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}