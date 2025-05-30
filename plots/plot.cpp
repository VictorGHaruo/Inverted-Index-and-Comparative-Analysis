#include <QApplication>
#include <QMainWindow>
#include "qcustomplot.h"
#include "../scr/tree_utils.h"
#include "../scr/data.h"
#include "../scr/avl.h"
#include "../scr/bst.h"
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

void configurePlot(QCustomPlot &customPlot, const PlotConfig &config) {
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

    QVector<double>  x(config.texts.size());
    QVector<double>  AVL_1(config.texts.size());
    QVector<double>  BST_1(config.texts.size());
    QVector<double>  AVL_2(config.texts.size());
    QVector<double>  BST_2(config.texts.size());
    QVector<double>  AVL_3(config.texts.size());
    QVector<double>  BST_3(config.texts.size());
    QVector<double>  AVL_4(config.texts.size());
    QVector<double>  BST_4(config.texts.size());
    QVector<double>  extra(config.texts.size());

    BinaryTree *AVLtree = AVL::create();
    BinaryTree *BSTtree = BST::create();

    double totalComparisonsAVL = 0;
    double totalComparisonsBST = 0;
    double timeAVL = 0;
    double timeBST = 0;
    vector<string> words;
    int sizeTexts = config.texts.size();

    for(int i = 0; i < sizeTexts; i++){
        int sizeT = config.texts[i].size();
        double meanAVL = 0;
        double meanBST = 0;

        for(int j = 0; j < sizeT; j++){

            SearchResult found = AVL::search(AVLtree, config.texts[i][j]);
            if (found.found == 0)
                words.push_back(config.texts[i][j]);
            InsertResult avlResult = AVL::insert(AVLtree, config.texts[i][j], i);
            meanAVL += avlResult.numComparisons;
            timeAVL += avlResult.executionTime;
            InsertResult bstResult = BST::insert(BSTtree, config.texts[i][j], i);
            meanBST += bstResult.numComparisons;
            timeBST += bstResult.executionTime;

        }
        totalComparisonsBST += meanBST;
        totalComparisonsAVL += meanAVL;
        x[i] = i + 1;
        AVL_1[i] = totalComparisonsAVL;
        BST_1[i] = totalComparisonsBST;
        AVL_2[i] = TreeUtils::getHeight(AVLtree->root);
        BST_2[i] = height(BSTtree->root);
        AVL_3[i] = meanAVL/sizeT;
        BST_3[i] = meanBST/sizeT;
        AVL_4[i] = timeAVL;
        BST_4[i] = timeBST;
    }

    QVector<double> x2 = {1, 2, 3, 4, 5, 6, 7, 8};
    QVector<double> AVL_5(8);
    QVector<double> BST_5(8);

    int size = words.size();
    for (int i = 0; i < size; i++) {
        SearchResult avlResult = AVL::search(AVLtree, words[i]);
        SearchResult bstResult = BST::search(BSTtree, words[i]);

        int idx_avl = round(static_cast<double>(avlResult.numComparisons) / 8.0);
        int idx_bst = round(static_cast<double>(bstResult.numComparisons) / 8.0);

        idx_avl = min(max(idx_avl, 0), 7);
        idx_bst = min(max(idx_bst, 0), 7);

        AVL_5[idx_avl]++;
        BST_5[idx_bst]++;
    }
    // Adicionando os dados

    first_plot.addGraph();
    first_plot.graph(0)->setData(x, AVL_1);
    first_plot.graph(0)->setPen(QPen(config.AVL_color));
    first_plot.graph(0)->setScatterStyle(config.AVL_style);
    first_plot.graph(0)->setName("AVL");

    first_plot.addGraph();
    first_plot.graph(1)->setData(x, BST_1);
    first_plot.graph(1)->setPen(QPen(config.BST_color));
    first_plot.graph(1)->setScatterStyle(config.BST_style);
    first_plot.graph(1)->setName("BST");

    second_plot.addGraph();
    second_plot.graph(0)->setData(x, AVL_2);
    second_plot.graph(0)->setPen(QPen(config.AVL_color));
    second_plot.graph(0)->setScatterStyle(config.AVL_style);
    second_plot.graph(0)->setName("AVL");

    second_plot.addGraph();
    second_plot.graph(1)->setData(x, BST_2);
    second_plot.graph(1)->setPen(QPen(config.BST_color));
    second_plot.graph(1)->setScatterStyle(config.BST_style);
    second_plot.graph(1)->setName("BST");

    third_plot.addGraph();
    third_plot.graph(0)->setData(x, AVL_3);
    third_plot.graph(0)->setPen(QPen(config.AVL_color));
    third_plot.graph(0)->setScatterStyle(config.AVL_style);
    third_plot.graph(0)->setName("AVL");

    third_plot.addGraph();
    third_plot.graph(1)->setData(x, BST_3);
    third_plot.graph(1)->setPen(QPen(config.BST_color));
    third_plot.graph(1)->setScatterStyle(config.BST_style);
    third_plot.graph(1)->setName("BST");

    fourth_plot.addGraph();
    fourth_plot.graph(0)->setData(x, AVL_4);
    fourth_plot.graph(0)->setPen(QPen(config.AVL_color));
    fourth_plot.graph(0)->setScatterStyle(config.AVL_style);
    fourth_plot.graph(0)->setName("AVL");

    fourth_plot.addGraph();
    fourth_plot.graph(1)->setData(x, BST_4);
    fourth_plot.graph(1)->setPen(QPen(config.BST_color));
    fourth_plot.graph(1)->setScatterStyle(config.BST_style);
    fourth_plot.graph(1)->setName("BST");

    fifth_plot.addGraph();
    fifth_plot.graph(0)->setData(x2, AVL_5);
    fifth_plot.graph(0)->setPen(QPen(config.AVL_color));
    fifth_plot.graph(0)->setScatterStyle(config.AVL_style);
    fifth_plot.graph(0)->setName("AVL");

    fifth_plot.addGraph();
    fifth_plot.graph(1)->setData(x2, BST_5);
    fifth_plot.graph(1)->setPen(QPen(config.BST_color));
    fifth_plot.graph(1)->setScatterStyle(config.BST_style);
    fifth_plot.graph(1)->setName("BST");

    // Aplicar configuração de estilo
    configurePlot(first_plot, config);
    configurePlot(second_plot, config);
    configurePlot(third_plot, config);
    configurePlot(fourth_plot, config);
    configurePlot(fifth_plot, config);

    // Layout e título
    first_plot.plotLayout()->insertRow(0);
    QCPTextElement *title_1 = new QCPTextElement(
        &first_plot,
        "Comparações feitas durante as inserções em cada árvore",
        config.title_font
    );
    title_1->setTextColor(config.text_color);
    first_plot.plotLayout()->addElement(0, 0, title_1);

    second_plot.plotLayout()->insertRow(0);
    QCPTextElement *title_2 = new QCPTextElement(
        &second_plot,
        "Altura das árvores em função dos documentos lidos",
        config.title_font
    );
    title_2->setTextColor(config.text_color);
    second_plot.plotLayout()->addElement(0, 0, title_2);

    third_plot.plotLayout()->insertRow(0);
    QCPTextElement *title_3 = new QCPTextElement(
        &third_plot,
        "Média do número de compações por documento lido",
        config.title_font
    );
    title_3->setTextColor(config.text_color);
    third_plot.plotLayout()->addElement(0, 0, title_3);

    fourth_plot.plotLayout()->insertRow(0);
    QCPTextElement *title_4 = new QCPTextElement(
        &fourth_plot,
        "Tempo de execução na inserção",
        config.title_font
    );
    title_4->setTextColor(config.text_color);
    fourth_plot.plotLayout()->addElement(0, 0, title_4);

    fifth_plot.plotLayout()->insertRow(0);
    QCPTextElement *title_5 = new QCPTextElement(
        &fifth_plot,
        "Número de palavras por número de comparações",
        config.title_font
    );
    title_5->setTextColor(config.text_color);
    fifth_plot.plotLayout()->addElement(0, 0, title_5);

    // Labels dos eixos
    first_plot.xAxis->setLabel("Número de documentos lidos");
    first_plot.yAxis->setLabel("Número de comparações");

    second_plot.xAxis->setLabel("Número de documentos lidos");
    second_plot.yAxis->setLabel("Altura das árvores");

    third_plot.xAxis->setLabel("Número de documentos lidos");
    third_plot.yAxis->setLabel("Média do número de comparações");

    fourth_plot.xAxis->setLabel("Número de documentos lidos");
    fourth_plot.yAxis->setLabel("Tempo médio");

    fifth_plot.xAxis->setLabel("Número de comparações");
    fifth_plot.yAxis->setLabel("Número de palavras");

    // Ajustar escalas
    first_plot.rescaleAxes();
    second_plot.rescaleAxes();
    third_plot.rescaleAxes();
    fourth_plot.rescaleAxes();
    fifth_plot.rescaleAxes();

    // Salvar em PNG
    first_plot.savePng("Comparações_na_inserção.png", 1000, 600);
    second_plot.savePng("Comparação_das_alturas.png", 1000, 600);
    third_plot.savePng("Média_das_comparações_na_inserção.png", 1000, 600);
    fourth_plot.savePng("Tempo_de_execução.png", 1000, 600);
    fifth_plot.savePng("Número_de_comparações.png", 1000, 600);

    BST::deleteTree(BSTtree);
    AVL::deleteTree(AVLtree);

    return 0;
}


