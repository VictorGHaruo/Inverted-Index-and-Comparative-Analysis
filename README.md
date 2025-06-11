# Inverted Index & Comparative Analysis

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
- Unzip
- Qt5 Development Libraries

### Prepare the Datasets

The project datasets are provided as compressed .zip files. Due to how they are archived, unzipping them creates a nested directory structure (e.g., data/data/). The commands below will unzip the archives and move the files into their correct locations.


```bash
# Unzip the dataset into the right directory
unzip data/data.zip -d data/
unzip data2/data_v2.zip -d data2/

# Move the files out of the nested 'data' directories
mv data/data/* data/
mv data2/data/* data2/
```

### Compilation and Execution
The project uses a flexible Makefile that allows configuring different parameters:

**Basic Execution**:
```bash
#To run with default settings:
(cd scr/ ; make)

#To specify the number of documents (uses default BST tree):
(cd scr/ ; make num=n)
    
#To run with fully custom parameters:
(cd scr/ ; make tree=tree path="../data_folder/" num=num cmd=stats)

#Delete object files and executables: 
(cd scr/ ; make clean)
```


### Configurable Parameters

| Parameter | Description | Default | Arguments | Example |
| :---: | :--- | :---: | :--- | :---: |
| `tree` | Data structure to use | `bst` | bst, avl, rbt | `tree=avl` |
| `num` | Number of documents to process | `10103` | 1, 2, 3, ... | `num=1000` |
| `cmd` | Command to execute | `search` | search, stats | `cmd=stats` |
| `path` | Path to the documents folder | `../data/` | `../data/`, `../data2/` | `path=../data2/` |

### Usage Examples

AVL with stats on 1000 documents using the second data:
```bash
make tree=avl path="../data2/" num=1000 cmd=stats
```

BST with search over 300 documents:
```bash
make num=300
```



## 👥 Developers
This project was developed by:

- [Eric Manoel Ribeiro de Sousa](https://github.com/derik713)
- [Everton Costa Reis](https://github.com/Everton-Reis)
- [Lucas Menezes de Lima](https://github.com/MenezesLima)
- [Rodrigo Severo Araújo](https://github.com/rodrisevero)
- [Victor Gabriel Haruo Iwamoto](https://github.com/VictorGHaruo)