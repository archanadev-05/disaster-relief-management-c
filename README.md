# 🆘 Disaster Relief & Aid Distribution Management System

> A console-based C application simulating Sri Lanka DMC disaster relief operations.  
> Developed for **IN1101 — Programming Fundamentals | Group Project 2026**  
> **University of Moratuwa — Faculty of Information Technology**

---

## 📋 Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [System Requirements](#system-requirements)
- [How to Compile and Run](#how-to-compile-and-run)
- [Module Overview](#module-overview)
- [Data Entry Order](#data-entry-order)
- [File Structure](#file-structure)
- [Data Persistence](#data-persistence)
- [Bug Fixes](#bug-fixes)
- [Group Members](#group-members)

---

## 📖 About the Project

This system simulates a real-world disaster relief management operation inspired by Sri Lanka's Disaster Management Centre (DMC). It manages affected people, aid inventory, volunteers, relief camps and aid distribution across multiple districts during a disaster event such as a flood, landslide or cyclone.

The system is built entirely in **C programming language** using:
- Structs and nested structs
- Arrays and pointers
- File handling with binary I/O
- Modular functions
- Menu-driven console interface

---

## ✅ Features

### Module 1 — Affected People Management
- Register affected persons with location and special needs
- View persons by district
- Search person by ID
- Edit and delete person records
- List priority cases (disabled, pregnant, elderly)
- Sort by family size
- Update aid received status

### Module 2 — Aid Inventory Management
- Add aid items (Food, Water, Shelter, Medicine)
- Search and edit item details
- Delete items with distribution record warnings
- View stock by category
- Low stock warnings (under 50 units)
- Auto low stock alert after distribution
- Update quantities with negative stock prevention
- Full stock summary

### Module 3 — Volunteer Management
- Register volunteers with skills
- Search and edit volunteer details
- Delete volunteers
- Assign and unassign volunteers to camps
- View by skill
- Log hours worked
- List available volunteers

### Module 4 — Relief Camp Management
- Setup relief camps with GPS coordinates
- Search and edit camp details
- Delete camps with dependency warnings
- View all camp capacities
- Update occupancy
- Find camps by district
- Sort by available space

### Module 5 — Aid Distribution and Reports
- Distribute aid with full validation
- Duplicate aid detection with confirmation
- Auto low stock warning during distribution
- Search distribution records by ID
- Delete distribution records with aid status reset
- View full distribution history
- Generate district-level summary reports

### Data Persistence
- All data saved to binary files automatically on exit
- All data loaded back on startup
- Manual save option available

---

## 💻 System Requirements

| Requirement | Details |
|---|---|
| Operating System | Windows / Linux / Mac |
| Compiler | GCC (MinGW on Windows) |
| Language | C (C99 or later) |
| Storage | ~10MB for data files |

---

## 🚀 How to Compile and Run

### Windows
```cmd
gcc main.c affected.c inventory.c volunteer.c camp.c distribution.c -o relief.exe
relief.exe
```

### Linux / Mac
```bash
gcc main.c affected.c inventory.c volunteer.c camp.c distribution.c -o relief
./relief
```

### With Warnings Check
```cmd
gcc main.c affected.c inventory.c volunteer.c camp.c distribution.c -o relief.exe -Wall -Wextra
```

### If Using Single File Version
```cmd
gcc main.c -o relief.exe
relief.exe
```

> **Note:** The `data/` folder is created automatically when the programme runs for the first time.

---

## 📦 Module Overview

```
main.c
│
├── STRUCTS (top of file)
│     AffectedPerson, AidItem, Volunteer, ReliefCamp, Distribution
│
├── GLOBAL ARRAYS
│     people[], items[], volunteers[], camps[], dists[]
│
├── MODULE 1 — Affected People
│     registerPerson(), viewByDistrict(), searchPersonByID()
│     editPerson(), deletePerson(), listSpecialNeeds()
│     updateAidStatus(), sortByFamilySize()
│
├── MODULE 2 — Inventory
│     addAidItem(), searchItemByID(), editItem(), deleteItem()
│     viewStockByCategory(), checkLowStock()
│     updateQuantity(), getStockSummary()
│
├── MODULE 3 — Volunteer
│     registerVolunteer(), searchVolunteerByID(), editVolunteer()
│     deleteVolunteer(), assignToCamp(), unassignFromCamp()
│     viewBySkill(), logHoursWorked(), listAvailableVolunteers()
│
├── MODULE 4 — Relief Camp
│     setupCamp(), searchCampByID(), editCamp(), deleteCamp()
│     viewCampCapacity(), updateOccupancy()
│     findCampByDistrict(), sortByAvailableSpace()
│
├── MODULE 5 — Distribution
│     distributeAid(), searchDistByID(), deleteDistribution()
│     viewDistributionHistory(), generateDistrictReport()
│
└── SAVE / LOAD
      saveAllData(), loadAllData()
```

---

## 📝 Data Entry Order

**Always follow this order when entering data:**

```
Step 1 → Add Relief Camps       (Module 4)
Step 2 → Add Inventory Items    (Module 2)
Step 3 → Register People        (Module 1)  ← needs camps to exist
Step 4 → Register Volunteers    (Module 3)
Step 5 → Distribute Aid         (Module 5)  ← needs people and items
```

> Affected people registration requires at least one camp to exist first.
> Aid distribution requires both people and inventory items to exist first.

---

## 📁 File Structure

```
project/
│
├── main.c                  ← entire programme in one file
│
└── data/                   ← auto-created on first run
      ├── people.dat          ← affected persons (binary)
      ├── inventory.dat       ← aid items (binary)
      ├── distribution.dat    ← distribution records (binary)
      ├── volunteers.dat      ← volunteers (binary)
      └── camps.dat           ← relief camps (binary)
```

---

## 💾 Data Persistence

All data is saved as **binary files** using `fwrite` and loaded back using `fread`.

```
On Exit  → saveAllData() writes all 5 arrays to disk
On Start → loadAllData() reads all 5 arrays back into memory
```

Each file stores:
1. The count (how many records) as one integer
2. All struct records as raw binary data

> ⚠️ If you modify any struct definition, delete the `.dat` files before running again to avoid data corruption.

---

## 🐛 Bug Fixes

The following bugs were identified and fixed during development:

| # | Bug | Module | Fix |
|---|---|---|---|
| 1 | Negative stock allowed | Inventory | Added lower bound check before update |
| 2 | Distribution date hardcoded | Distribution | User now enters actual date |
| 3 | Fake camp name accepted | Affected | Validates against camps array |
| 4 | No auto low stock alert | Distribution | Warning shown after stock deducted |
| 5 | Camp occupancy never updated | Affected | Increments on person registration |
| 6 | specialNeed out of bounds crash | Affected | Validates 0-3 range with do-while |
| 7 | mkdir -p fails on Windows | Main | Uses #ifdef _WIN32 for correct command |
| 8 | fopen failure not reported | All save functions | Error message shown if save fails |
| 9 | Duplicate aid not detected | Distribution | Warning with confirmation prompt |
| 10 | District report wrong count | Distribution | Filters distributions by district |
| 11 | No input validation | Multiple | Validates age, quantity, capacity |
| 12 | Buffer overflow on strings | All modules | Width-limited scanf throughout |

---


## 👥 Group Members

| Member | Module | Responsibility |
|---|---|---|
| Thathsarani R.A.T | Module 1 | Affected People Management |
| Tharmigan.S.      | Module 2 | Aid Inventory Management |
| Tharusha H.K.N.N  | Module 3 | Volunteer Management |
| Thakshila H.G.H   | Module 4 | Relief Camp Management |
| Thanuwana P.G.A   | Module 5 | Aid Distribution and Reports |

---


## 🏫 Project Information

```
Course    : IN1101 — Programming Fundamentals
Project   : Group Project 2026
Institute : University of Moratuwa
           Faculty of Information Technology
Language  : C (Console Application)
Version   : 2.0
```

---

## 📌 Important Notes

- Run as **Administrator** on Windows if data folder cannot be created
- Do not manually edit `.dat` files — they are binary format
- Always use **Option 6** or **Option 0** to save before closing
- Minimum one camp must exist before registering affected people
- Distribution requires both people and inventory to be set up first

---

*Disaster Relief & Aid Distribution Management System — University of Moratuwa — IN1101 — 2026*