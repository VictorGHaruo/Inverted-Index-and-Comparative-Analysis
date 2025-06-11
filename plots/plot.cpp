#include <QApplication>
#include <QMainWindow>
#include "qcustomplot.h"
#include "../scr/tree_utils.h"
#include "../scr/data.h"
#include "../scr/avl.h"
#include "../scr/bst.h"
#include "../scr/rbt.h"
using namespace std;

struct PlotConfig {
    // Cores
    QColor background_color = QColor(255, 255, 255);
    QColor text_color = QColor(0, 0, 0);
    QColor grid_color = QColor(0, 0, 0);

    QColor BST_color = QColor(255, 0, 0);
    QColor AVL_color = QColor(0, 255, 0);
    QColor RBT_color = QColor(0, 0, 255);

    QColor legend_brush = QColor(50, 50, 50, 200);
    QColor legend_border_pen = QColor(30, 30, 30);

    // Fontes
    QFont title_font = QFont("Sans", 12, QFont::Bold);
    QFont legend_font = QFont("Helvetica", 9);

    // Estilos de pontos
    QCPScatterStyle AVL_style = QCPScatterStyle(QCPScatterStyle::ssCircle, 5);
    QCPScatterStyle BST_style = QCPScatterStyle(QCPScatterStyle::ssSquare, 5);
    QCPScatterStyle RBT_style = QCPScatterStyle(QCPScatterStyle::ssTriangle, 5);

    // Dados
    vector<vector<string>> texts;
};

int height(Node* root) {
    if (root == nullptr) {
        return -1;  
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

int getHeightTree(Node* node, string type){
    if(node == nullptr) return -1;

    if(type == "max") return 1 + max(getHeightTree(node->left, type), getHeightTree(node->right, type)); 
    if(type == "min") return 1 + min(getHeightTree(node->left, type), getHeightTree(node->right, type)); 

    return -1;
}

void configurePlot(QCustomPlot &customPlot, const PlotConfig &config, const char* title, const char* x_label, const char* y_label) {
    // Cor de fundo
    customPlot.setBackground(config.background_color);
    customPlot.axisRect()->setBackground(config.background_color);

    // Configuração dos eixos
    for (auto *axis : {customPlot.xAxis, customPlot.yAxis}) {
        axis->grid()->setVisible(true);
        axis->grid()->setPen(QPen(config.grid_color));
        axis->setBasePen(QPen(config.text_color, 1));
        axis->setTickPen(QPen(config.text_color, 1));
        axis->setSubTickPen(QPen(config.text_color, 1));
        axis->setTickLabelColor(config.text_color);
        axis->setLabelColor(config.text_color);
    }

    // Legenda
    customPlot.legend->setVisible(true);
    customPlot.legend->setFont(config.legend_font);
    customPlot.legend->setBrush(config.legend_brush);
    customPlot.legend->setBorderPen(config.legend_border_pen);
    customPlot.legend->setTextColor(config.text_color);
    customPlot.axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

    // Título
    customPlot.plotLayout()->insertRow(0);
    QCPTextElement *title_1 = new QCPTextElement(
        &customPlot,
        title,
        config.title_font
    );
    title_1->setTextColor(config.text_color);
    customPlot.plotLayout()->addElement(0, 0, title_1);

    // Labels
    customPlot.xAxis->setLabel(x_label);
    customPlot.yAxis->setLabel(y_label);
}

void add_graph(QCustomPlot &customPlot, QVector<double> x, QVector<double> bst, QVector<double> avl, QVector<double> rbt, const PlotConfig &config ){

    customPlot.addGraph();
    customPlot.graph(0)->setData(x, bst);
    customPlot.graph(0)->setPen(QPen(config.BST_color));
    customPlot.graph(0)->setScatterStyle(config.BST_style);
    customPlot.graph(0)->setName("BST");

    customPlot.addGraph();
    customPlot.graph(1)->setData(x, avl);
    customPlot.graph(1)->setPen(QPen(config.AVL_color));
    customPlot.graph(1)->setScatterStyle(config.AVL_style);
    customPlot.graph(1)->setName("AVL");

    customPlot.addGraph();
    customPlot.graph(2)->setData(x, rbt);
    customPlot.graph(2)->setPen(QPen(config.RBT_color));
    customPlot.graph(2)->setScatterStyle(config.RBT_style);
    customPlot.graph(2)->setName("RBT");
}

void setLogScale(QCustomPlot &plot, bool logX = true, bool logY = true) {

    if (logX) {
        plot.xAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTickerX(new QCPAxisTickerLog);
        plot.xAxis->setTicker(logTickerX);
    }

    if (logY) {
        plot.yAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTickerY(new QCPAxisTickerLog);
        plot.yAxis->setTicker(logTickerY);
    }

    plot.replot();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PlotConfig config;
    config.texts = data::readData("../data/", 10103); 

    QCustomPlot first_plot;
    QCustomPlot second_plot;
    QCustomPlot third_plot;
    QCustomPlot fourth_plot;
    QCustomPlot fifth_plot;
    QCustomPlot sixth_plot;
    QCustomPlot seventh_plot;

    QVector<double>  x(config.texts.size());
    QVector<double>  AVL_1(config.texts.size());
    QVector<double>  BST_1(config.texts.size());
    QVector<double>  RBT_1(config.texts.size());
    QVector<double>  AVL_2(config.texts.size());
    QVector<double>  BST_2(config.texts.size());
    QVector<double>  RBT_2(config.texts.size());
    QVector<double>  AVL_3(config.texts.size());
    QVector<double>  BST_3(config.texts.size());
    QVector<double>  RBT_3(config.texts.size());
    QVector<double>  AVL_4(config.texts.size());
    QVector<double>  BST_4(config.texts.size());
    QVector<double>  RBT_4(config.texts.size());
    QVector<double>  AVL_7(config.texts.size());
    QVector<double>  BST_7(config.texts.size());
    QVector<double>  RBT_7(config.texts.size());

    BinaryTree *AVLtree = AVL::create();
    BinaryTree *BSTtree = BST::create();
    BinaryTree *RBTtree = RBT::create();

    double totalComparisonsAVL = 0;
    double totalComparisonsBST = 0;
    double totalComparisonsRBT = 0;
    double timeAVL = 0;
    double timeBST = 0;
    double timeRBT = 0;
    vector<string> words;
    vector<int> comparisons_bst;
    vector<int> comparisons_avl;
    vector<int> comparisons_rbt;
    int sizeTexts = config.texts.size();

    for(int i = 0; i < sizeTexts; i++){
        int sizeT = config.texts[i].size();
        double meanAVL = 0;
        double meanBST = 0;
        double meanRBT = 0;

        for(int j = 0; j < sizeT; j++){

            InsertResult avlResult = AVL::insert(AVLtree, config.texts[i][j], i);
            meanAVL += avlResult.numComparisons;
            timeAVL += avlResult.executionTime;
            InsertResult bstResult = BST::insert(BSTtree, config.texts[i][j], i);
            meanBST += bstResult.numComparisons;
            timeBST += bstResult.executionTime;
            InsertResult rbtResult = RBT::insert(RBTtree, config.texts[i][j], i);
            meanRBT += rbtResult.numComparisons;
            timeRBT += rbtResult.executionTime;

            if(avlResult.isNew){
                comparisons_bst.push_back(bstResult.numComparisons);
                comparisons_avl.push_back(avlResult.numComparisons);
                comparisons_rbt.push_back(rbtResult.numComparisons);
                words.push_back(avlResult.word);
            }
        }
        totalComparisonsBST += meanBST;
        totalComparisonsAVL += meanAVL;
        totalComparisonsRBT += meanRBT;
        x[i] = i + 1;
        AVL_1[i] = totalComparisonsAVL;
        BST_1[i] = totalComparisonsBST;
        RBT_1[i] = totalComparisonsRBT;
        AVL_2[i] = TreeUtils::getHeight(AVLtree->root);
        BST_2[i] = height(BSTtree->root);
        RBT_2[i] = height(RBTtree->root);
        AVL_3[i] = meanAVL/sizeT;
        BST_3[i] = meanBST/sizeT;
        RBT_3[i] = meanRBT/sizeT;
        AVL_4[i] = timeAVL;
        BST_4[i] = timeBST;
        RBT_4[i] = timeRBT;
        AVL_7[i] = getHeightTree(AVLtree->root, "min");
        BST_7[i] = getHeightTree(BSTtree->root, "min");
        RBT_7[i] = getHeightTree(RBTtree->root, "min");
    }
    int h = height(BSTtree->root );
    int size = words.size();

    QVector<double> AVL_6(size);
    QVector<double> BST_6(size);
    QVector<double> RBT_6(size);
    QVector<double> x3(size);

    QVector<double> x2(h,0);
    for (int i = 0; i < h; ++i) x2[i] = i + 1;

    QVector<double> AVL_5(h);
    QVector<double> BST_5(h);
    QVector<double> RBT_5(h);

    for (int i = 0; i < size; i++) {
        SearchResult avlResult = AVL::search(AVLtree, words[i]);
        SearchResult bstResult = BST::search(BSTtree, words[i]);
        SearchResult rbtResult = RBT::search(RBTtree, words[i]);

        int idx_avl = avlResult.numComparisons -1;
        int idx_bst = bstResult.numComparisons -1;
        int idx_rbt = rbtResult.numComparisons -1;

        if (idx_avl >= 0 && idx_avl < AVL_5.size()) AVL_5[idx_avl]++;
        if (idx_bst >= 0 && idx_bst < BST_5.size()) BST_5[idx_bst]++;
        if (idx_rbt >= 0 && idx_rbt < RBT_5.size()) RBT_5[idx_rbt]++;

        if(i>0){ 
        AVL_6[i] = comparisons_avl[i] + AVL_6[i-1];
        BST_6[i] = comparisons_bst[i] + BST_6[i-1];
        RBT_6[i] = comparisons_rbt[i] + RBT_6[i-1];
        }
        else{
        AVL_6[i] = comparisons_avl[i];
        BST_6[i] = comparisons_bst[i];
        RBT_6[i] = comparisons_rbt[i];
        }
        x3[i] = i + 1;
}
    // Adicionando os dados
    add_graph(first_plot, x, BST_1, AVL_1, RBT_1, config);
    add_graph(second_plot, x, BST_2, AVL_2, RBT_2, config);
    add_graph(third_plot, x, BST_3, AVL_3, RBT_3, config);
    add_graph(fourth_plot, x, BST_4, AVL_4, RBT_4, config);
    add_graph(fifth_plot, x2, BST_5, AVL_5, RBT_5, config);
    add_graph(sixth_plot, x3, BST_6, AVL_6, RBT_6, config);
    add_graph(seventh_plot,x,BST_7,AVL_7,RBT_7,config);

    // Aplicar configuração de estilo
    configurePlot(first_plot, config,"Soma do número de comparações em cada árvore","Número de documentos lidos","Número de comparações" );
    configurePlot(second_plot, config,"Altura das árvores em função dos documentos lidos","Número de documentos lidos","Altura das árvores" );
    configurePlot(third_plot, config, "Média do número de comparações por documento lido","Número de documentos lidos","Média do número de comparações");
    configurePlot(fourth_plot, config, "Soma dos tempos de execução","Número de documentos lidos","Tempo médio");
    configurePlot(fifth_plot, config,  "Número de palavras por número de comparações","Número de comparações","Número de palavras");
    configurePlot(sixth_plot, config, "Soma do número de comparações na inserção","Número de comparações","Número de palavras");
    configurePlot(seventh_plot,config, "Menor caminho de uma folha até a raiz","Menor caminho","Número de documentos lidos");

    // Ajustar escalas
    first_plot.rescaleAxes();
    second_plot.rescaleAxes();
    setLogScale(second_plot, true, false);
    third_plot.rescaleAxes();
    fourth_plot.rescaleAxes();
    fifth_plot.rescaleAxes();
    sixth_plot.rescaleAxes();
    setLogScale(seventh_plot, true, false);
    seventh_plot.rescaleAxes();

    // Salvar em PNG
    first_plot.savePng("Graph_1.png", 1000, 600);
    second_plot.savePng("Graph_2.png", 1000, 600);
    third_plot.savePng("Graph_3.png", 1000, 600);
    fourth_plot.savePng("Graph_4.png", 1000, 600);
    fifth_plot.savePng("Graph_5.png", 1000, 600);
    sixth_plot.savePng("Graph_6.png", 1000, 600);
    seventh_plot.savePng("Graph_7.png", 1000, 600);

    //Destruindo as árvores
    BST::destroy(BSTtree);
    AVL::destroy(AVLtree);
    RBT::destroy(RBTtree);

    return 0;
}
