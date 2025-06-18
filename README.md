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
#Running Manually
#Compile all the files to run the trees (*substitute tree_name with a tree name):
(cd scr/ ; ./main_tree_name <command> <n_docs> <directory_path>)

#Running with Makefile
(cd scr/ ; make tree=tree path="../data_folder/" num=num cmd=stats)

#Delete object files and executables: 
(cd scr/ ; make clean)

#Delete all object(data, i.e .CSV .txt) files and executables created by the code.
(cd scr/ ; make cleanall)

```


### Configurable Parameters

| Parameter | Description | Arguments | Example |
| :---: | :--- | :--- | :---: |
| `tree` | Data structure to use | bst, avl, rbt | `tree=avl` |
| `num` | Number of documents to process | 1, 2, 3, ... | `num=1000` |
| `cmd` | Command to execute | search, stats | `cmd=stats` |
| `path` | Path to the documents folder | `../data/`, `../data2/` | `path=../data2/` |

### Usage Examples

AVL with stats on 1000 documents using the second data:
```bash
(cd scr/ ; make tree=avl path="../data2/" num=1000 cmd=stats)
```

BST with search on 10 documents from data2:
```bash
(cd scr/ ; ./main_bst stats 10 ../data2/)
```

**For more informations about the how to run the code, read the .pdf file in docs/ folder.**


## 👥 Developers
This project was developed by:

- [Eric Manoel Ribeiro de Sousa](https://github.com/derik713)
- [Everton Costa Reis](https://github.com/Everton-Reis)
- [Lucas Menezes de Lima](https://github.com/MenezesLima)
- [Rodrigo Severo Araújo](https://github.com/rodrisevero)
- [Victor Gabriel Haruo Iwamoto](https://github.com/VictorGHaruo)
