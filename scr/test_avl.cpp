#include <iostream>
#include "tree_utils.h"
#include "avl.h"
using namespace std;

int main(){
    BinaryTree *tree = AVL::create();
    InsertResult insert_root;
    InsertResult insert_last;

    cout << "========= Teste Right Rotation =========" << endl;
    insert_root = AVL::insert(tree, "charizard", 3);
    AVL::insert(tree, "bulbasaur", 2);
    AVL::insert(tree, "arceus", 1); // Right Rotation
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Left Rotation =========" << endl;
    AVL::insert(tree, "dratini", 4);
    AVL::insert(tree, "elekid", 5); // Left Rotation 
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Right-Left Rotation =========" << endl;
    AVL::insert(tree, "ivysaur", 8);
    AVL::insert(tree, "flareon", 6); // Left-Right Rotation
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Left-Right Rotation =========" << endl;
    AVL::insert(tree, "gallade", 9);
    AVL::insert(tree, "hypno", 8); // Right-Left Rotation 
    printTree(tree);

    cout << endl ;

        string pokemons[] = {
        "bulbasaur", "ivysaur", "venusaur", "charmander", "charmeleon", "charizard",
        "squirtle", "wartortle", "blastoise", "caterpie", "metapod", "butterfree",
        "weedle", "kakuna", "beedrill", "pidgey", "pidgeotto", "pidgeot",
        "rattata", "raticate", "spearow", "fearow", "ekans", "arbok",
        "pikachu", "raichu", "sandshrew", "sandslash", "nidoran-f", "nidorina",
        "nidoqueen", "nidoran-m", "nidorino", "nidoking", "clefairy", "clefable",
        "vulpix", "ninetales", "jigglypuff", "wigglytuff", "zubat", "golbat",
        "oddish", "gloom", "vileplume", "paras", "parasect", "venonat",
        "venomoth", "diglett", "dugtrio", "meowth", "persian", "psyduck",
        "golduck", "mankey", "primeape", "growlithe", "arcanine", "poliwag",
        "poliwhirl", "poliwrath", "abra", "kadabra", "alakazam", "machop",
        "machoke", "machamp", "bellsprout", "weepinbell", "victreebel", "tentacool",
        "tentacruel", "geodude", "graveler", "golem", "ponyta", "rapidash",
        "slowpoke", "slowbro", "magnemite", "magneton", "farfetchd", "doduo",
        "dodrio", "seel", "dewgong", "grimer", "muk", "shellder",
        "cloyster", "gastly", "haunter", "gengar", "onix", "drowzee",
        "hypno", "krabby", "kingler", "voltorb", "electrode", "exeggcute",
        "exeggutor", "cubone", "marowak", "hitmonlee", "hitmonchan", "lickitung",
        "koffing", "weezing", "rhyhorn", "rhydon", "chansey", "tangela",
        "kangaskhan", "horsea", "seadra", "goldeen", "seaking", "staryu",
        "starmie", "mr-mime", "scyther", "jynx", "electabuzz", "magmar",
        "pinsir", "tauros", "magikarp", "gyarados", "lapras", "ditto",
        "eevee", "vaporeon", "jolteon", "flareon", "porygon", "omanyte",
        "omastar", "kabuto", "kabutops", "aerodactyl", "snorlax", "articuno",
        "zapdos", "moltres", "dratini", "dragonair", "dragonite", "mewtwo", "mew"
    };

    for (int i = 0; i < 151; i++) {
        AVL::insert(tree, pokemons[i], i + 1); 
        if (i == 150)
            insert_last = AVL::insert(tree, pokemons[i], i + 1);
    }
    float height = getHeight(tree->root);
    float minHeight = getMinOrMaxPath(tree->root, false);

    cout << "========= Insert: Root =========" << endl;
    cout << "Execution Time: " << insert_root.executionTime << endl;
    cout << "Number of Comparisons:" << insert_root.numComparisons << endl;
    cout << endl;

    cout << "========= Insert: Last =========" << endl;
    cout << "Execution Time: " << insert_last.executionTime << endl;
    cout << "Number of Comparisons:" << insert_last.numComparisons << endl;

    cout << "========= Balance test: =========" << endl;
    cout << "Tree height :" << height<< endl;
    cout << "Min height :" << minHeight << endl;
    cout << "Ratio :" << height/minHeight << endl;

    cout << "========= Delete Tree =========" << endl;
    AVL::destroy(tree);

}