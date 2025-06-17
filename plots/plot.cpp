#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
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
    QColor grid_color = QColor(100, 100, 100);

    QColor BST_color = QColor(255, 0, 0);
    QColor AVL_color = QColor(0, 255, 0);
    QColor RBT_color = QColor(0, 0, 255);

    QColor legend_brush = QColor(255, 255, 255, 255);
    QColor legend_border_pen = QColor(30, 30, 30);

    QPen GridStyle = QPen(grid_color, 1, Qt::DashLine);

    // Fontes
    QFont title_font = QFont("Sans", 12, QFont::Bold);
    QFont legend_font = QFont("Helvetica", 9);

    // Estilos de pontos
    QPen AvlStyle = QPen(AVL_color, 3, Qt::DashLine);
    QPen BstStyle = QPen(BST_color, 3, Qt::DashLine);
    QPen RbtStyle = QPen(RBT_color, 3, Qt::DashLine);
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
        customPlot.xAxis->grid()->setPen(config.GridStyle);
        customPlot.yAxis->grid()->setPen(config.GridStyle);
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
    customPlot.graph(0)->setPen(config.BstStyle);
    customPlot.graph(0)->setName("BST");

    customPlot.addGraph();
    customPlot.graph(1)->setData(x, avl);
    customPlot.graph(1)->setPen(config.AvlStyle);
    customPlot.graph(1)->setName("AVL");

    customPlot.addGraph();
    customPlot.graph(2)->setData(x, rbt);
    customPlot.graph(2)->setPen(config.RbtStyle);
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

    QCustomPlot first_plot;
    QCustomPlot second_plot;
    QCustomPlot third_plot;
    QCustomPlot fourth_plot;

    QVector<double>  x;
    QVector<double>  AVL_1;
    QVector<double>  BST_1;
    QVector<double>  RBT_1;
    QVector<double>  AVL_2;
    QVector<double>  BST_2;
    QVector<double>  RBT_2;
    QVector<double>  AVL_3;
    QVector<double>  BST_3;
    QVector<double>  RBT_3;


    // Lendo os dados da Inserção

    QFile InsertBST("../stats/insertResultsBST.csv");
    if (!InsertBST.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/insertResultsBST.csv";
        return 1;
    }
    QTextStream in_InsertBST(&InsertBST);

    int index = 0;
    double acumulado = 0;
    double valor = 0;
    while (!in_InsertBST.atEnd()) {
        QStringList campos = in_InsertBST.readLine().split(',');
        if (campos[1].trimmed() == "1"){ 
            x.append(index);
            BST_1.append(campos[4].toDouble());
            BST_2.append(campos[5].toDouble());  
            valor = campos[0].toDouble(); 
            acumulado += valor;
            BST_3.append(acumulado);
            
            index++;
        }
    }
    InsertBST.close();

    QFile InsertAVL("../stats/insertResultsAVL.csv");
    if (!InsertAVL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/insertResultsAVL.csv";
        return 1;
    }
    QTextStream in_InsertAVL(&InsertAVL);
    
    acumulado = 0;
    while (!in_InsertAVL.atEnd()) {
        QStringList campos = in_InsertAVL.readLine().split(',');
        if (campos[1].trimmed() == "1"){ 
            AVL_1.append(campos[4].toDouble()); 
            AVL_2.append(campos[5].toDouble()); 
            valor = campos[0].toDouble(); 
            acumulado += valor;
            AVL_3.append(acumulado);
        }
    }
    InsertAVL.close();

    QFile InsertRBT("../stats/insertResultsRBT.csv");
    if (!InsertRBT.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/insertResultsRBT.csv";
        return 1;
    }
    QTextStream in_InsertRBT(&InsertRBT);

    acumulado = 0;
    while (!in_InsertRBT.atEnd()) {
        QStringList campos = in_InsertRBT.readLine().split(',');
        if (campos[1].trimmed() == "1"){ 
            RBT_1.append(campos[4].toDouble()); 
            RBT_2.append(campos[5].toDouble()); 
            valor = campos[0].toDouble(); 
            acumulado += valor;
            RBT_3.append(acumulado);
        }
    }
    InsertRBT.close();

    // Lendo os dados da Procura

    int MaxHeight = static_cast<int>(BST_1.last());

    QVector<double> x2(MaxHeight,0);
    for (int i = 0; i < MaxHeight; ++i) x2[i] = i + 1;

    QVector<double>  AVL_4(MaxHeight);
    QVector<double>  BST_4(MaxHeight);
    QVector<double>  RBT_4(MaxHeight);

    QFile SearchBST("../stats/searchResultsBST.csv");
    if (!SearchBST.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsBST.csv";
        return 1;
    }
    QTextStream in_SearchBST(&SearchBST);

    int CurrentIndex;

    while (!in_SearchBST.atEnd()) {
        QStringList campos = in_SearchBST.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        if (CurrentIndex >= 0 && CurrentIndex < BST_4.size())
            BST_4[CurrentIndex]++;
        }
    SearchBST.close();

    QFile SearchAVL("../stats/searchResultsAVL.csv");
    if (!SearchAVL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsAVL.csv";
        return 1;
    }
    QTextStream in_SearchAVL(&SearchAVL);

    while (!in_SearchAVL.atEnd()) {
        QStringList campos = in_SearchAVL.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        if (CurrentIndex >= 0 && CurrentIndex < AVL_4.size())
            AVL_4[CurrentIndex]++;
        }
    SearchAVL.close();

    QFile SearchRBT("../stats/searchResultsRBT.csv");
    if (!SearchRBT.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsRBT.csv";
        return 1;
    }
    QTextStream in_SearchRBT(&SearchRBT);

    while (!in_SearchRBT.atEnd()) {
        QStringList campos = in_SearchRBT.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        if (CurrentIndex >= 0 && CurrentIndex < RBT_4.size())
            RBT_4[CurrentIndex]++;
    }
    SearchRBT.close();

    // Adicionando os dados
    add_graph(first_plot, x, BST_1, AVL_1, RBT_1, config);
    setLogScale(first_plot,true,false);
    add_graph(second_plot, x, BST_2, AVL_2, RBT_2, config);
    setLogScale(second_plot,true,false);
    add_graph(third_plot, x, BST_3, AVL_3, RBT_3, config);
    add_graph(fourth_plot, x2, BST_4, AVL_4, RBT_4, config);

    // Aplicar configuração de estilo
    configurePlot(first_plot, config,"Altura das árvores durante a inserção","Número de palavras únicas adicionadas","Altura" );
    configurePlot(second_plot, config,"Profundidade da folha mais rasa durante a inserção","Número de palavras únicas adicionadas","Profundidade" );
    configurePlot(third_plot, config, "Soma dos tempos de execução durante a inserção","Número de palavras inseridas","Soma dos tempos de execução");
    configurePlot(fourth_plot, config, "Distribuição do número de comparações por número de palavras","Número de comparações","Número de palavras");

    // Ajustar escalas
    first_plot.rescaleAxes();
    second_plot.rescaleAxes();
    third_plot.rescaleAxes();
    fourth_plot.rescaleAxes();

    // Salvar em PNG
    first_plot.savePng("Graph_1_10103.png", 1000, 600);
    second_plot.savePng("Graph_2_10103.png", 1000, 600);
    third_plot.savePng("Graph_3_10103.png", 1000, 600);
    fourth_plot.savePng("Graph_4_10103.png", 1000, 600);

    return 0;
}
