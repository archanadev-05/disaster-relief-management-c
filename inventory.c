/* ============================================================
   inventory.c — Module 2: Aid Inventory Management
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "distribution.h"

/* ── FUNCTION 1: Add new item ───────────────────────────────── */
void addAidItem(AidItem *arr, int *count) {
    if (*count >= MAX) { printf("  Inventory full!\n"); return; }
    AidItem *item = &arr[*count];
    item->itemID = 2000 + *count + 1;
    while(getchar()!='\n');
    printf("  Item Name                            : "); scanf(" %49[^\n]", item->itemName);
    printf("  Category (Food/Water/Shelter/Medicine): "); scanf("%29s", item->category);
    do {
        printf("  Quantity                             : "); scanf("%d", &item->quantity);
        if (item->quantity <= 0) printf("  [!] Must be greater than 0.\n");
    } while (item->quantity <= 0);
    printf("  Unit (Packets/Bottles/Pieces)        : "); scanf("%14s", item->unit);
    printf("  Received Date (YYYY-MM-DD)           : "); scanf("%11s", item->details.receivedDate);
    printf("  Expiry Date   (YYYY-MM-DD)           : "); scanf("%11s", item->details.expiryDate);
    while(getchar()!='\n');
    printf("  Supplier Name                        : "); scanf(" %59[^\n]", item->details.supplier);
    printf("  Camp ID                              : "); scanf("%d", &item->campID);
    (*count)++;
    printf("\n  [OK] Item added! ID: %d\n", item->itemID);
}

/* ── FUNCTION 2: Search item by ID ─────────────────────────── */
void searchItemByID(AidItem *arr, int count, int id) {
    for (int i = 0; i < count; i++)
        if (arr[i].itemID == id) {
            printf("\n  ── ITEM DETAILS ────────────────────────\n");
            printf("  ID           : %d\n",  arr[i].itemID);
            printf("  Name         : %s\n",  arr[i].itemName);
            printf("  Category     : %s\n",  arr[i].category);
            printf("  Quantity     : %d %s\n", arr[i].quantity, arr[i].unit);
            printf("  Received     : %s\n",  arr[i].details.receivedDate);
            printf("  Expiry       : %s\n",  arr[i].details.expiryDate);
            printf("  Supplier     : %s\n",  arr[i].details.supplier);
            printf("  Camp ID      : %d\n",  arr[i].campID);
            printf("  ────────────────────────────────────────\n");
            return;
        }
    printf("  [!] Item ID %d not found.\n", id);
}

/* ── FUNCTION 3: Edit item details ─────────────────────────── */
void editItem(AidItem *arr, int count, int id) {
    int index = -1;
    for (int i = 0; i < count; i++)
        if (arr[i].itemID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Item ID %d not found.\n", id); return; }

    AidItem *item = &arr[index];
    printf("  Editing: %s (ID:%d)\n", item->itemName, item->itemID);
    printf("  Press Enter to keep current value.\n\n");

    char buf[60];
    printf("  Name [%s]: ", item->itemName);
    while (getchar() != '\n');
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(item->itemName, buf, 49);

    printf("  Category [%s]: ", item->category);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(item->category, buf, 29);

    printf("  Expiry Date [%s]: ", item->details.expiryDate);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(item->details.expiryDate, buf, 11);

    printf("  Supplier [%s]: ", item->details.supplier);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(item->details.supplier, buf, 59);

    printf("\n  [OK] Item ID %d updated.\n", id);
}

/* ── FUNCTION 4: Delete item ────────────────────────────────── */
void deleteItem(AidItem *arr, int *count, int id,
                Distribution *dists, int dCount) {
    int index = -1;
    for (int i = 0; i < *count; i++)
        if (arr[i].itemID == id) { index = i; break; }
    if (index == -1) { printf("  [!] Item ID %d not found.\n", id); return; }

    printf("  Deleting: %s (ID:%d, Qty:%d)\n",
           arr[index].itemName, arr[index].itemID, arr[index].quantity);

    /* Warn if distribution records exist */
    int distCount = 0;
    for (int i = 0; i < dCount; i++)
        if (dists[i].itemID == id) distCount++;
    if (distCount > 0)
        printf("  [!] WARNING: %d distribution record(s) reference this item!\n",
               distCount);

    printf("  Are you sure? (1=Yes 0=No): ");
    int confirm; scanf("%d", &confirm);
    if (!confirm) { printf("  [OK] Cancelled.\n"); return; }

    for (int i = index; i < *count - 1; i++)
        arr[i] = arr[i + 1];
    (*count)--;
    printf("  [OK] Item ID %d deleted.\n", id);
}

/* ── FUNCTION 5: View stock by category ─────────────────────── */
void viewStockByCategory(AidItem *arr, int count, char *category) {
    printf("\n  %-6s %-25s %-6s %-10s %s\n","ID","Item Name","Qty","Unit","Expiry");
    printf("  ──────────────────────────────────────────────────────\n");
    int found = 0;
    for (int i = 0; i < count; i++)
        if (strcasecmp(arr[i].category, category) == 0) {
            printf("  %-6d %-25s %-6d %-10s %s\n",
                arr[i].itemID, arr[i].itemName,
                arr[i].quantity, arr[i].unit,
                arr[i].details.expiryDate);
            found++;
        }
    if (!found) printf("  No items in category: %s\n", category);
}

/* ── FUNCTION 6: Check low stock ────────────────────────────── */
void checkLowStock(AidItem *arr, int count) {
    int found = 0;
    printf("\n  ── LOW STOCK WARNINGS (under 50 units) ──\n");
    for (int i = 0; i < count; i++)
        if (arr[i].quantity < 50) {
            printf("  [!] [%d] %-25s — Only %d %s left!\n",
                arr[i].itemID, arr[i].itemName,
                arr[i].quantity, arr[i].unit);
            found++;
        }
    if (!found) printf("  [OK] All stock levels are healthy.\n");
}

/* ── FUNCTION 7: Update quantity ────────────────────────────── */
void updateQuantity(AidItem *arr, int count, int itemID, int qty) {
    for (int i = 0; i < count; i++)
        if (arr[i].itemID == itemID) {
            if (arr[i].quantity + qty < 0) {
                printf("  [!] Cannot remove %d. Only %d %s available.\n",
                       -qty, arr[i].quantity, arr[i].unit);
                return;
            }
            arr[i].quantity += qty;
            printf("  [OK] %s updated. New quantity: %d\n",
                arr[i].itemName, arr[i].quantity);
            if (arr[i].quantity < 50)
                printf("  [!] WARNING: Stock is now low! Only %d left.\n",
                       arr[i].quantity);
            return;
        }
    printf("  [!] Item ID %d not found.\n", itemID);
}

/* ── FUNCTION 8: Stock summary ──────────────────────────────── */
void getStockSummary(AidItem *arr, int count) {
    int food=0, water=0, shelter=0, medicine=0;
    for (int i=0; i<count; i++) {
        if      (strcasecmp(arr[i].category,"Food")==0)     food     += arr[i].quantity;
        else if (strcasecmp(arr[i].category,"Water")==0)    water    += arr[i].quantity;
        else if (strcasecmp(arr[i].category,"Shelter")==0)  shelter  += arr[i].quantity;
        else if (strcasecmp(arr[i].category,"Medicine")==0) medicine += arr[i].quantity;
    }
    printf("\n  ── STOCK SUMMARY ──────────────────────\n");
    printf("  Food Items    : %d units\n", food);
    printf("  Water         : %d units\n", water);
    printf("  Shelter Items : %d units\n", shelter);
    printf("  Medicine      : %d units\n", medicine);
    printf("  ───────────────────────────────────────\n");
    printf("  Total items on record: %d\n", count);
}

/* ── MENU ───────────────────────────────────────────────────── */
void inventoryMenu(AidItem *arr, int *count,
                   Distribution *dists, int dCount) {
    int ch;
    do {
        printf("\n  +── AID INVENTORY MODULE ──────────────────+\n");
        printf("  |  1. Add New Aid Item                     |\n");
        printf("  |  2. Search Item by ID                    |\n");
        printf("  |  3. Edit Item Details                    |\n");
        printf("  |  4. Delete Item                          |\n");
        printf("  |  5. View Stock by Category               |\n");
        printf("  |  6. Check Low Stock Warnings             |\n");
        printf("  |  7. Update Item Quantity                 |\n");
        printf("  |  8. View Full Stock Summary              |\n");
        printf("  |  0. Back to Main Menu                    |\n");
        printf("  +──────────────────────────────────────────+\n");
        printf("  Choice: ");
        if (scanf("%d",&ch)!=1) { while(getchar()!='\n'); continue; }
        switch(ch) {
            case 1: addAidItem(arr, count); break;
            case 2: {
                int id;
                printf("  Item ID: "); scanf("%d", &id);
                searchItemByID(arr, *count, id); break;
            }
            case 3: {
                int id;
                printf("  Item ID to edit: "); scanf("%d", &id);
                editItem(arr, *count, id); break;
            }
            case 4: {
                int id;
                printf("  Item ID to delete: "); scanf("%d", &id);
                deleteItem(arr, count, id, dists, dCount); break;
            }
            case 5: {
                char cat[30];
                printf("  Category (Food/Water/Shelter/Medicine): ");
                scanf("%29s", cat);
                viewStockByCategory(arr, *count, cat); break;
            }
            case 6: checkLowStock(arr, *count); break;
            case 7: {
                int id, qty;
                printf("  Item ID : "); scanf("%d", &id);
                printf("  Qty to add (+) or remove (-): "); scanf("%d", &qty);
                updateQuantity(arr, *count, id, qty); break;
            }
            case 8: getStockSummary(arr, *count); break;
            case 0: break;
            default: printf("  Invalid option.\n");
        }
    } while (ch != 0);
}