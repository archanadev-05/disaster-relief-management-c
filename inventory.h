#ifndef INVENTORY_H
#define INVENTORY_H
#ifndef MAX
#define MAX 100
#endif

typedef struct {
    char receivedDate[12];
    char expiryDate[12];
    char supplier[60];
} ItemInfo;

typedef struct {
    int      itemID;
    char     itemName[50];
    char     category[30];
    int      quantity;
    char     unit[15];
    ItemInfo details;
    int      campID;
} AidItem;

/* Forward declare only — full definition is in distribution.h */
typedef struct Distribution_s Distribution;

void addAidItem(AidItem *arr, int *count);
void searchItemByID(AidItem *arr, int count, int id);
void editItem(AidItem *arr, int count, int id);
void deleteItem(AidItem *arr, int *count, int id,
                Distribution *dists, int dCount);
void viewStockByCategory(AidItem *arr, int count, char *category);
void checkLowStock(AidItem *arr, int count);
void updateQuantity(AidItem *arr, int count, int itemID, int qty);
void getStockSummary(AidItem *arr, int count);
void inventoryMenu(AidItem *arr, int *count,
                   Distribution *dists, int dCount);
#endif