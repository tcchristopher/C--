# Anxiety Clarity

#### Video Demo: https://youtu.be/sozjOS6KU7M

#### Description:

**Anxiety Clarity** is a command-line application that transforms anxiety into ordered, actionable steps. Basically, it's project management for your mind.

The core of it is writing down everything that's bothering you, rate each one by your own interpretation of its impact and stress, and see them sorted by priority. It makes everything into a series of lists and lists can be worked through.

## The Problem It Solves

```
BEFORE:
"Everything is falling apart I have no money and my lease is 
ending and I haven't talked to my family and CS50x is due and I 
can't sleep and what am I doing with my life and—"

AFTER:
1. INCOME (Priority 80) — 1/4 steps done
2. HOUSING (Priority 63) — 0/2 steps done  
3. CS50X (Priority 36) — 0/3 steps done
4. FAMILY (Priority 24) — ready to resolve

Now, it's four things that I can work on in order. And I've already started on #1.
```

## Features

- **Add Anxieties** — Describe what's worrying you in your own words
- **Rate & Prioritise** — Score difficulty (1-10) and life impact (1-10)
- **Auto-Sort** — Anxieties sorted by priority (difficulty × impact)
- **Break It Down** — Add your own action steps to each anxiety
- **Track Progress** — Mark steps complete, see progress percentage
- **Celebrate Wins** — Victory screens when you complete steps or resolve anxieties
- **Edit & Correct** — Fix mistakes with full edit/delete functionality
- **Persistence** — Data saves to file, survives restarts

## Installation

### Prerequisites

- C++17 compatible compiler (clang++ or g++)
- macOS, Linux, or Windows with WSL

### Build

```bash or zsh
# Clone or download the project
cd anxiety_clarity

# Option 1: Using Make
make

# Option 2: Direct compilation
clang++ -std=c++17 -Wall -o anxiety_clarity \
    main.cpp \
    action_step.cpp \
    anxiety_item.cpp \
    anxiety_list.cpp \
    ui.cpp
```

### Run

```bash or zsh
./anxiety_clarity
```

## Usage

### Main Menu

```
╔══════════════════════════════════════╗
║         ANXIETY CLARITY              ║
║   Project Management for Your Mind   ║
╠══════════════════════════════════════╣
║                                      ║
║  Active anxieties: 3                 ║
║  Resolved (victories): 2             ║
║                                      ║
║  [1] View & Work on Anxieties        ║
║  [2] Add New Anxiety                 ║
║  [3] View Victories                  ║
║  [4] Save & Exit                     ║
║                                      ║
╚══════════════════════════════════════╝
```

### Adding an Anxiety

1. Describe what's worrying you
2. Select a category (Income, Bills, Family, Health, Work, Housing, Relationships, Other)
3. Rate difficulty (1-10): "How hard does this feel?"
4. Rate impact (1-10): "How much does this affect my life?"
5. Add action steps (optional)
6. Review and confirm

### Working on an Anxiety

- **[A]** Add new action steps
- **[C]** Complete a step (with confirmation)
- **[E]** Edit anxiety details or steps
- **[D]** Delete the anxiety
- **[R]** Resolve — mark as conquered!

## File Structure

```
anxiety_clarity/
├── main.cpp              # Entry point and main loop
├── action_step.h         # ActionStep class declaration
├── action_step.cpp       # ActionStep implementation
├── anxiety_item.h        # AnxietyItem class declaration
├── anxiety_item.cpp      # AnxietyItem implementation
├── anxiety_list.h        # AnxietyList manager declaration
├── anxiety_list.cpp      # AnxietyList implementation + file I/O
├── category.h            # Category enum and helpers
├── ui.h                  # UI function declarations
├── ui.cpp                # All user interface code
├── Makefile              # Build configuration
├── README.md             # This file
└── anxieties.txt         # Data file (created at runtime)
```

## Technical Design

### Class Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      AnxietyList                            │
│  - Manages collection of AnxietyItems                       │
│  - Handles sorting, filtering, persistence                  │
│                                                             │
│    ┌─────────────────────────────────────────────────┐      │
│    │                 AnxietyItem                     │      │
│    │  - Text description                             │      │
│    │  - Category, difficulty, impact ratings         │      │
│    │  - Resolved status                              │      │
│    │  - Collection of ActionSteps                    │      │
│    │                                                 │      │
│    │    ┌─────────────────────────────────────┐      │      │
│    │    │           ActionStep                │      │      │
│    │    │  - Text description                 │      │      │
│    │    │  - Completion status                │      │      │
│    │    └─────────────────────────────────────┘      │      │
│    └─────────────────────────────────────────────────┘      │
└─────────────────────────────────────────────────────────────┘
```

### Design Decisions

**Why a text file instead of a database?**

For this scope (a final project for CS50x), a simple pipe-delimited text file provides:
- Zero dependencies (standard library only)
- User friendly data (easy debugging)
- Simpler implementation versus a database (~50 lines vs 200+)

**Why CLI instead of GUI?**

- Faster but manageable development
- No external library dependencies
- CLI can still be highly interactive

**Why users provide their own solutions?**

- You know your life better than anyone, you just need help to see the bigger picture
- The act of breaking down anxiety in itself is relieving
- You get to tell yourself what you should do and have it electronically

### Data Format

```
# Anxiety Clarity Data File v1
ANXIETY|INCOME|8|10|false|No job, savings running out
STEP|0|true|Update CV with C++ projects
STEP|0|false|Apply to 5 junior dev positions
ANXIETY|FAMILY|4|6|true|Mom's birthday coming up
STEP|1|true|Order gift online
```

### Error Handling

- **Input validation** — Rejects invalid numbers, empty required fields
- **Confirmation dialogs** — Y/N/E for adding, Y/N for completing/resolving
- **Destructive action protection** — Must type "DELETE" to delete an anxiety
- **File error tolerance** — Corrupted lines skipped, rest of data preserved
- **Edit/undo functionality** — Fix mistakes without losing data

## CS50x Concepts Applied

| Concept | Application |
|---------|-------------|
| Object-Oriented Programming | Three interconnected classes with encapsulation |
| File I/O | Save/load with custom text format |
| Error Handling | Input validation, try-catch for file parsing |
| Data Structures | Vectors, enums, strings |
| Algorithms | Sorting with custom comparator (lambda) |
| Memory Management | References, pointers for filtered access |
| User Interface Design | Menu system, formatted output, progress bars |

## Philosophy

**"Keep it simple, stupid."**
The app does what your brain struggles with:
- Holding all anxieties at once in your head versus Lists them externally
- Rates and sorts by priority
- Tracking progress and maintaining completion state
- Feeling accomplishment, like a game

## Future Enhancements

I will work on these after the CS50x submission:

- [ ] GUI version (Qt or wxWidgets) or native for iOS
- [ ] Export to other formats
- [ ] Cloud sync

## Author

**Thabiso Christopher**

- CS50x 2025
- GitHub: https://github.com/tcchristopher
- Location: Johannesburg, South Africa

## Acknowledgments

- Prof David J. Malan and the CS50 team - Stellar work to make CS50x available to the world!!!!!
- Bjarne Stroustrup for "Programming: Principles and Practice Using C++"

---

