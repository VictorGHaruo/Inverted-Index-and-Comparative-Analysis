#include <iostream>
#include "tree_utils.h"
#include "rbt.h"
using namespace std;

// TESTS With color

void printRBTAux(Node* root, const std::string &prefix, bool isLast){

    if (root == nullptr) return;

    cout << prefix;

    if (! prefix.empty()){
        if (isLast) {
            cout << "└──";
        } else {
            cout << "├──";
        }
    }
 
    cout << root->word << " c: " << root->isRed << endl;

    string newPrefix = prefix + (isLast ? "   " : "│  ");

    if(root->right == nullptr)
        printRBTAux(root->left, newPrefix, true);
    else {
        printRBTAux(root->left,  newPrefix, false);
        printRBTAux(root->right, newPrefix, true);
    }
        
}

void printRBT(BinaryTree* tree){

    Node* n = tree->root;
    int counter = 0;
    
    if (n != nullptr) {
        printRBTAux(n, "", true);
    }
}


int main(){

    BinaryTree *tree = RBT::create();

    // Inserting when the root is a null pointer
    // Need more tests...
    InsertResult insert_root = RBT::insert(tree, "arnaldo", 1); 
    RBT::insert(tree, "bernaldo", 2);
    RBT::insert(tree, "cernaldo", 3);
    RBT::insert(tree, "dernaldo", 4);
    RBT::insert(tree, "enaldo", 5);
    RBT::insert(tree, "fernaldo", 5);
    RBT::insert(tree, "gernaldo", 5);
    
    //Adding a node that already exists, but with a different ID
    RBT::insert(tree, "dernaldo", 4);

    printRBT(tree);

    // InsertResult insert_last;

    // string pokemons[] = {
    //     "bulbasaur", "ivysaur", "venusaur", "charmander", "charmeleon", "charizard",
    //     "squirtle", "wartortle", "blastoise", "caterpie", "metapod", "butterfree",
    //     "weedle", "kakuna", "beedrill", "pidgey", "pidgeotto", "pidgeot",
    //     "rattata", "raticate", "spearow", "fearow", "ekans", "arbok",
    //     "pikachu", "raichu", "sandshrew", "sandslash", "nidoran-f", "nidorina",
    //     "nidoqueen", "nidoran-m", "nidorino", "nidoking", "clefairy", "clefable",
    //     "vulpix", "ninetales", "jigglypuff", "wigglytuff", "zubat", "golbat",
    //     "oddish", "gloom", "vileplume", "paras", "parasect", "venonat",
    //     "venomoth", "diglett", "dugtrio", "meowth", "persian", "psyduck",
    //     "golduck", "mankey", "primeape", "growlithe", "arcanine", "poliwag",
    //     "poliwhirl", "poliwrath", "abra", "kadabra", "alakazam", "machop",
    //     "machoke", "machamp", "bellsprout", "weepinbell", "victreebel", "tentacool",
    //     "tentacruel", "geodude", "graveler", "golem", "ponyta", "rapidash",
    //     "slowpoke", "slowbro", "magnemite", "magneton", "farfetchd", "doduo",
    //     "dodrio", "seel", "dewgong", "grimer", "muk", "shellder",
    //     "cloyster", "gastly", "haunter", "gengar", "onix", "drowzee",
    //     "hypno", "krabby", "kingler", "voltorb", "electrode", "exeggcute",
    //     "exeggutor", "cubone", "marowak", "hitmonlee", "hitmonchan", "lickitung",
    //     "koffing", "weezing", "rhyhorn", "rhydon", "chansey", "tangela",
    //     "kangaskhan", "horsea", "seadra", "goldeen", "seaking", "staryu",
    //     "starmie", "mr-mime", "scyther", "jynx", "electabuzz", "magmar",
    //     "pinsir", "tauros", "magikarp", "gyarados", "lapras", "ditto",
    //     "eevee", "vaporeon", "jolteon", "flareon", "porygon", "omanyte",
    //     "omastar", "kabuto", "kabutops", "aerodactyl", "snorlax", "articuno",
    //     "zapdos", "moltres", "dratini", "dragonair", "dragonite", "mewtwo", "mew"
    // };

    // for (int i = 0; i < 151; i++) {
    //     RBT::insert(tree, pokemons[i], i + 1); 
    //     if (i == 150)
    //         insert_last = RBT::insert(tree, pokemons[i], i + 1);
    // }

    // cout << "========= Insert: Root =========" << endl;
    // cout << "Execution Time: " << insert_root.executionTime << endl;
    // cout << "Number of Comparisons:" << insert_root.numComparisons << endl;
    // cout << endl;

    // cout << "========= Insert: Last =========" << endl;
    // cout << "Execution Time: " << insert_last.executionTime << endl;
    // cout << "Number of Comparisons:" << insert_last.numComparisons << endl;
    // cout << endl ;

    // printRBT(tree);

    cout << "========= Delete Tree =========" << endl;
    RBT::deleteTree(tree);


}