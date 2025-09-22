
# 🏋️ Fitness Advisor

**Fitness Advisor** is a fitness management and guidance program, developed by **Team 14 (banana\_screaming)**.
It helps users build training profiles, explore categorized exercises, keep workout records, and manage personalized fitness goals through an interactive SDL2 interface.

---

## ⚙️ Installation & Execution

1. Download the repository and open `FP-main\FP-main` in **Visual Studio Code** (or any C compiler environment).

2. Compile with the following command:

   ```bash
   gcc -I src/include -L src/lib -o run FP_MAIN.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
   ```

3. This will generate an executable `run.exe`.

4. Run `run.exe` to start the program.

---

## 📂 Program Structure

The program is divided into **four main modules**:

### 1. Initial Profile

* Input personal information to set up exercise recommendations tailored to the user.

### 2. Movement Library

* Explore all supported movements, classified into **six categories**:

  * Chest
  * Leg
  * Back
  * Shoulder
  * Arm
  * Core
* A demonstration window (SDL2-based) visually shows the selected movement.

  * ⚠️ *Important: The SDL window must be closed before continuing with the program.*
* Users can also **add training records** and **bucket list items** here.

### 3. Training Records

* Add, display, and sort workout records.
* Get feedback on **training intensity** and **training frequency** after inputting data.
* Records can be sorted based on the six movement categories.

  * ⚠️ *Important: Records must be entered in chronological order (each new entry should be at least one day after the previous one).*

### 4. Bucket List

* Manage a personalized fitness bucket list:

  * Add new goals
  * Delete existing goals
  * Search by movement category
  * Display all bucket list items

---

## 🛠️ Dependencies

* **GCC** (MinGW recommended for Windows)
* **SDL2**
* **SDL2\_image**

Ensure these libraries are installed and properly linked before compilation.

---

## 🚀 Future Improvements (Optional section)

* Enhanced UI for easier navigation.
* Data visualization for progress tracking.
* Export/import user profiles for long-term tracking.

---
