# LCS Gene Sequence Similarity

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

Two complementary command-line tools that apply the classic **Longest Common Subsequence (LCS)** dynamic-programming algorithm to DNA-style gene sequences.

Originally written as a school programming assignment; cleaned, modernised (C++17, const-correct, zero-warning), and packaged for a professional GitHub portfolio.

---

## What it does

| Tool | Purpose |
|------|---------|
| **`lcs`** | Computes one actual Longest Common Subsequence string (and its length) for any two sequences supplied on the command line. |
| **`sim`** | Reads a file of *N* sequences, computes pairwise LCS lengths with a space-optimised DP, and classifies every pair as **H**igh / **M**edium / **L**ow / **D**issimilar. |

### Similarity rules

| Label | Condition |
|-------|-----------|
| **H** | length-ratio > 0.9 **and** LCS-ratio > 0.9 |
| **M** | length-ratio > 0.8 **and** LCS-ratio > 0.8 |
| **L** | length-ratio > 0.5 **and** LCS-ratio > 0.5 |
| **D** | everything else |

(where *length-ratio* = min(len₁,len₂)/max(len₁,len₂) and *LCS-ratio* = LCS-length / min(len₁,len₂))

---

## Project Structure
```
LCS-Gene-Similarity/
├── lcs.cpp / lcs.hpp          # Reconstructs the LCS string (full DP table)
├── sim.cpp / sim.hpp          # Pairwise similarity matrix (space-optimised LCS length)
├── itemLoader.cpp / .hpp      # Simple line-based file loader
├── seqs.txt                   # Sample data set (8 gene sequences)
├── Makefile                   # One-command build
├── .gitignore
├── LICENSE
└── README.md
```

## Building & Running

```
### Prerequisites
- A C++17-compatible compiler (`g++` ≥ 7 or `clang++`)
- `make`

### Quick start

```Bash
# Build both tools
make

# Run similarity analysis on the included sample
make run-sim
# or
./sim seqs.txt

# Compute an LCS interactively
./lcs AGCTCGAGCTCGACTCGAGCT AGCTCGAGCGA
```

## Clean
```
Bash
make clean
```

# Sample Output
**./sim seqs.txt**

```
Gene Sequence Similarity Matrix
(H = High, M = Medium, L = Low, D = Dissimilar, - = self)

      1  2  3  4  5  6  7  8
 1    -  L  D  D  L  D  M  L
 2    L  -  D  D  L  D  L  H
 3    D  D  -  M  D  M  D  D
 4    D  D  M  -  D  H  D  D
 5    L  L  D  D  -  D  M  L
 6    D  D  M  H  D  -  D  D
 7    M  L  D  D  M  D  -  L
 8    L  H  D  D  L  D  L  -
```

**./lcs AGCTCGAGCTCGACTCGAGCT AGCTCGAGCGA**
```
LCS: 11 AGCTCGAGCGA
```

# Algorithms at a glance
## Full LCS reconstruction (lcs)

- Classic bottom-up DP table of size (m+1) × (n+1).
- Reconstructs one valid LCS by tracing back from the bottom-right cell.
- Time O(m·n), Space O(m·n).

## Length-only space-optimised LCS (sim)

- Uses a single rolling array of length n+1 (plus a few scalars).
- Optionally swaps the two strings so the DP array is allocated against the shorter sequence.
- Time O(m·n), Space O(min(m,n)).

Both implementations are pure standard C++ with no external dependencies.

# Technical Insights
- Demonstrates mastery of the classic LCS DP recurrence and its space optimisation.
- Clean separation of concerns (loader, length-only engine, reconstruction engine).
- Modern C++17 style: const-correct APIs, range-based loops where appropriate, RAII, no raw new/delete.
- Production-ready build system and documentation suitable for an open-source repository.
- Real-world flavour: the same technique underpins sequence alignment tools used in bioinformatics.

# Author
**Elijah Kenning.**

# License
MIT – see LICENSE.
