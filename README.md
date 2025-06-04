# Inverted-Index-and-Comparative-Analysis

## 📋Introduction
This project implements an **inverted index** using three different data structures for comparative performance analysis:

- **BST (Binary Search Tree)**
- **AVL** - AVL Tree (Self-Balancing)
- **RBT (Red-Black Tree)**

An inverted index is a fundamental structure in search systems that maps words to the documents in which they appear, allowing for fast retrieval of documents containing a given word.

## 🛠️ How to Run
**Prerequisites**:
- C++ Compiler (`g++ 11.4.0`)
- Make

### Compilation and Execution
The project uses a flexible Makefile that allows configuring different parameters:

**Basic Execution**:
```bash
cd src
make
```

This runs by default: `./main_bst search 10103 ../data/`

### Configurable Parameters

| Parameter | Description                        | Default     | Example           |
|:---------:|------------------------------------|-------------|-------------------|
| `tree`    | Data structure to use <br> (`bst`, `avl`, `rbt`) | `bst`       | `tree=avl`        |
| `num`     | Number of documents <br> to process | `10103`     | `num=1000`        |
| `cmd`     | Command <br> (`search`, `stats`)    | `search`    | `cmd=stats`       |
| `path`    | Path to the documents               | `../data/`  | `path=../data/`    |


### Usage Examples

AVL with stats on 1000 documents:
```bash
make tree=avl num=1000 cmd=stats
```

BST with search over 300 documents:
```bash
make num=300
```

### Clean Commands
```bash
make clean
```
Removes object files and executables.


## 👥 Developers
This project was developed by:

- [Eric Manoel Ribeiro de Sousa](https://github.com/derik713)
- [Everton Costa Reis](https://github.com/Everton-Reis)
- [Lucas Menezes de Lima](https://github.com/MenezesLima)
- [Rodrigo Severo Araújo](https://github.com/rodrisevero)
- [Victor Gabriel Haruo Iwamoto](https://github.com/VictorGHaruo)