# 🔍 Mini Search Engine (C++)

> A lightweight terminal-based search engine built from scratch in **C++17**, featuring **TF-IDF ranking**, **Trie-based autocomplete**, and **edit-distance spell correction** — all without external libraries.

---

## 🚀 Overview

This project simulates the core components of a real-world search engine in a simplified environment. It indexes a collection of documents and enables efficient querying with intelligent ranking and suggestions.

---
## ▶️ Try it instantly (no install needed)

1. Click the green **Code** button on this repo
2. Click **Codespaces** tab
3. Click **Create codespace on main**
4. Wait ~30 seconds for it to load
5. In the terminal type:
```bash
   ./search
```
6. Then start searching!
---
## ✨ Features

### 🔢 TF-IDF Ranking
Ranks documents based on relevance using:
- **TF (Term Frequency):** Frequency of a word in a document  
- **IDF (Inverse Document Frequency):** Rarity of a word across documents  
- **TF-IDF = TF × IDF**

➡️ Ensures rare but important terms are weighted higher.

---

### 📚 Inverted Index
Efficient lookup structure built at startup:

```
word → [(docID, frequency), ...]
```

---

### 🔤 Autocomplete (Trie)
Provides real-time suggestions for partially typed queries:

```
pyr   → pyramids
foot  → football
```

---

### 🧠 Spell Correction (Edit Distance)
Corrects misspelled words using dynamic programming:

```
mechine   → machine
pharohs   → pharaohs
```

---

### 📄 Snippet Display
Displays the most relevant sentence from matched documents.

---

### 🕘 Query History
Supports command-based interaction:

```
!history       → View past queries
!rerun <n>     → Rerun query number n
!clear         → Clear history
!help          → Show all commands
```

---

### 🎨 Terminal UI
- ANSI-colored output  
- Clean formatting and banners  
- User-friendly CLI experience  

---

## 📁 Project Structure

```
mini-search-engine/
├── docs/                   # Text documents to search
├── include/
│   ├── preprocessor.hpp   # Tokenization & stopword removal
│   ├── index.hpp          # Inverted index builder
│   ├── tfidf.hpp          # TF-IDF scoring logic
│   ├── trie.hpp           # Autocomplete (Trie)
│   ├── search.hpp         # Query engine & spell correction
│   ├── history.hpp        # Query history manager
│   └── ui.hpp             # Terminal UI (ANSI colors)
└── main.cpp               # Entry point
```

---

## ⚙️ Build & Run

### 📌 Requirements
- `g++` with **C++17** support

### 🛠️ Compile
```bash
g++ -std=c++17 main.cpp -o search
```

### ▶️ Run
```bash
./search        # Linux / Mac
.\search        # Windows
```

---

## 💡 Example Queries

| Query | Top Result |
|------|-----------|
| `pyramids ancient nile` | `doc_egypt.txt` |
| `football messi argentina` | `doc_argentina.txt` |
| `technology samsung electronics` | `doc_southkorea.txt` |
| `rainforest biodiversity` | `doc_brazil.txt` |
| `fjords northern lights` | `doc_norway.txt` |

---

## 🧠 Core Concepts

| Concept | Implementation |
|--------|--------------|
| File I/O | `main.cpp` |
| String Processing | `preprocessor.hpp` |
| Hash Maps | `index.hpp`, `tfidf.hpp` |
| Logarithms | `tfidf.hpp` |
| Trie (Tree DS) | `trie.hpp` |
| Dynamic Programming | `search.hpp` (edit distance) |
| Sorting Algorithms | `search.hpp` |
| OOP Design | `trie.hpp`, `history.hpp` |

---

## 📊 Time Complexity

| Operation | Complexity |
|----------|-----------|
| Index Building | O(N × L) |
| TF-IDF Computation | O(N × V) |
| Search Query | O(Q × D) |
| Autocomplete | O(P + R) |
| Spell Correction | O(V × A × B) |

> **Where:**  
> N = number of documents  
> L = average document length  
> V = vocabulary size  
> Q = query terms  
> D = documents per term  
> P = prefix length  
> R = results returned  
> A, B = word lengths  

---

## 🎯 Highlights

- ⚡ Fully implemented **from scratch** (no external libraries)
- 🧩 Combines multiple **core CS concepts**
- 💼 Strong **resume-ready project**
- 🧠 Demonstrates understanding of **search engine internals**

---

## 🚀 Future Improvements

- Add **file indexing from directories**
- Support **phrase queries ("exact match")**
- Implement **ranking optimizations (BM25)**
- Build a **GUI or web interface**

---

## 📜 License

This project is licensed under the MIT License.

---

⭐ If you found this project useful, consider giving it a star!
