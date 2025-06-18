#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <cmath>
#include <algorithm>
#include <random>
#include <QRandomGenerator>
#include <iostream>
#include "qcustomplot.h"

using namespace std;

struct PlotConfig {
    // Colors
    QColor backgroundColor = QColor(255, 255, 255);
    QColor textColor = QColor(0, 0, 0);
    QColor gridColor = QColor(100, 100, 100);

    QColor BSTColor = QColor(255, 0, 0);
    QColor AVLColor = QColor(255, 165, 0);
    QColor RBTColor = QColor(0, 0, 255);

    QColor legendBrush = QColor(255, 255, 255, 230);
    QColor legendBorderPen = QColor(30, 30, 30);

    // Margins
    QMargins margins = QMargins(10, 10, 10, 10);

    // Fonts
    QFont titleFont = QFont("Latin Modern Roman", 14, QFont::Bold);
    QFont labelFont = QFont("Latin Modern Roman", 12);

    // Styles
    QPen BstStyle = QPen(BSTColor, 3, Qt::DashLine);
    QPen AvlStyle = QPen(AVLColor, 3, Qt::DashDotLine);
    QPen RbtStyle = QPen(RBTColor, 3, Qt::DotLine);
    QPen GridStyle = QPen(gridColor, 1, Qt::DashLine);
};

void configurePlot(QCustomPlot &customPlot, const PlotConfig &config, const char* title, const char* xLabel, const char* yLabel) {
    // Background color
    customPlot.setBackground(config.backgroundColor);
    customPlot.axisRect()->setBackground(config.backgroundColor);

    // Configuration of the axes
    for (auto *axis : {customPlot.xAxis, customPlot.yAxis}) {
        axis->grid()->setVisible(true);
        axis->grid()->setPen(QPen(config.gridColor));
        axis->setBasePen(QPen(config.textColor, 1));
        axis->setTickPen(QPen(config.textColor, 1));
        axis->setSubTickPen(QPen(config.textColor, 1));
        axis->setTickLabelColor(config.textColor);
        axis->setLabelColor(config.textColor);
        customPlot.xAxis->grid()->setPen(config.GridStyle);
        customPlot.yAxis->grid()->setPen(config.GridStyle);
    }
    // Grid

    customPlot.xAxis->grid()->setPen(config.GridStyle);
    customPlot.yAxis->grid()->setPen(config.GridStyle);

    // Legend
    customPlot.legend->setVisible(true);
    customPlot.legend->setFont(config.labelFont);
    customPlot.legend->setBrush(config.legendBrush);
    customPlot.legend->setBorderPen(config.legendBorderPen);
    customPlot.legend->setTextColor(config.textColor);
    customPlot.axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);
    customPlot.legend->setRowSpacing(3);

    // Title
    customPlot.plotLayout()->insertRow(0);
    QCPTextElement *title_1 = new QCPTextElement(
        &customPlot,
        title,
        config.titleFont
    );
    title_1->setTextColor(config.textColor);
    customPlot.plotLayout()->addElement(0, 0, title_1);

    // Labels
    customPlot.xAxis->setLabel(xLabel);
    customPlot.yAxis->setLabel(yLabel);
    customPlot.xAxis->setLabelFont(config.labelFont);
    customPlot.yAxis->setLabelFont(config.labelFont);
    customPlot.plotLayout()->setMargins(config.margins);
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
        plot.xAxis->setScaleType(QCPAxis::stLogarithmic);
        plot.xAxis->setNumberFormat("eb"); 
        plot.xAxis->setNumberPrecision(1);
    }

    if (logY) {
        plot.yAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTickerY(new QCPAxisTickerLog);
        plot.yAxis->setTicker(logTickerY);
        plot.yAxis->setScaleType(QCPAxis::stLogarithmic);
        plot.yAxis->setNumberFormat("eb"); 
        plot.yAxis->setNumberPrecision(1);
    }

    plot.replot();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PlotConfig config; 

    QCustomPlot firstPlot;
    QCustomPlot secondPlot;
    QCustomPlot thirdPlot;
    QCustomPlot fourthPlot;
    QCustomPlot fifthPlot;
    QCustomPlot sixthPlot;
    QCustomPlot seventhPlot;

    QVector<double>  x;
    QVector<double>  AVL_1;
    QVector<double>  BST_1;
    QVector<double>  RBT_1;
    QVector<double>  AVL_2;
    QVector<double>  BST_2;
    QVector<double>  RBT_2;
    QVector<double>  x2;
    QVector<double>  AVL_3;
    QVector<double>  BST_3;
    QVector<double>  RBT_3;
    QVector<double>  x3;
    QVector<double>  AVL_4;
    QVector<double>  BST_4;
    QVector<double>  RBT_4;

    // Reading the data from the Insertion

    QFile InsertBST("../stats/insertResultsBST.csv");
    if (!InsertBST.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening:" << "../stats/insertResultsBST.csv";
        return 1;
    }
    QTextStream in_InsertBST(&InsertBST);

    int index = 0;
    int index2 = 0;
    int index3 = 0;
    int intervaslSize = 100;
    double accumulated = 0;
    double accumulated2 = 0;
    double CurrentValue = 0;
    double max= 0;
    double min = 1;
    vector <double> TempBST;
    vector <double> TempAVL;
    vector <double> TempRBT;

    while (!in_InsertBST.atEnd()) {
        QStringList campos = in_InsertBST.readLine().split(',');
        CurrentValue = campos[0].toDouble(); 
        accumulated2 += CurrentValue;
        BST_4.append(accumulated2);
        x3.append(index2);
        if (campos[1].trimmed() == "1"){ 
            x.append(index);
            index++;
            BST_1.append(campos[4].toDouble());
            BST_2.append(campos[5].toDouble());  
            accumulated += campos[2].toDouble();
            if (index % intervaslSize == 0){
                BST_3.append(accumulated/intervaslSize);
                x2.append(index3);
                accumulated = 0;
                index3++;
            }
            TempBST.push_back(CurrentValue);
            if (max < CurrentValue)
                max = CurrentValue;
            if (min > CurrentValue)
                min = CurrentValue;
        }
        index2++;
    }
    InsertBST.close();

    QFile InsertAVL("../stats/insertResultsAVL.csv");
    if (!InsertAVL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening :" << "../stats/insertResultsAVL.csv";
        return 1;
    }
    QTextStream in_InsertAVL(&InsertAVL);
    
    accumulated = 0;
    accumulated2 = 0;
    index = 0;
    while (!in_InsertAVL.atEnd()) {
        QStringList campos = in_InsertAVL.readLine().split(',');
        CurrentValue = campos[0].toDouble(); 
        accumulated2 += CurrentValue;
        AVL_4.append(accumulated2);
        if (campos[1].trimmed() == "1"){ 
            index++;
            AVL_1.append(campos[4].toDouble()); 
            AVL_2.append(campos[5].toDouble()); 
            accumulated += campos[2].toDouble();
            if (index % intervaslSize == 0){
                AVL_3.append(accumulated/intervaslSize);
                accumulated = 0;
            }
            TempAVL.push_back(CurrentValue);
            if (max < CurrentValue)
                max = CurrentValue;
            if (min > CurrentValue)
                min = CurrentValue;
        }
    }
    InsertAVL.close();

    QFile InsertRBT("../stats/insertResultsRBT.csv");
    if (!InsertRBT.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening:" << "../stats/insertResultsRBT.csv";
        return 1;
    }
    QTextStream in_InsertRBT(&InsertRBT);

    accumulated = 0;
    accumulated2 = 0;
    index = 0;
    while (!in_InsertRBT.atEnd()) {
        QStringList campos = in_InsertRBT.readLine().split(',');
        CurrentValue = campos[0].toDouble(); 
        accumulated2 += CurrentValue;
        RBT_4.append(accumulated2);
        if (campos[1].trimmed() == "1"){ 
            index++;
            RBT_1.append(campos[4].toDouble()); 
            RBT_2.append(campos[5].toDouble());  
            accumulated += campos[2].toDouble();
            if (index % intervaslSize == 0){
                RBT_3.append(accumulated/intervaslSize);
                accumulated = 0;
            }
            TempRBT.push_back(CurrentValue);
            if (max < CurrentValue)
                max = CurrentValue;
            if (min > CurrentValue)
                min = CurrentValue;
        }
    }
    InsertRBT.close();

    int Size = 100;
    QVector<double> x4(Size);
    QVector<double> AVL_5(Size);
    QVector<double> BST_5(Size);
    QVector<double> RBT_5(Size);

    double logMin = log10(min);
    double logMax = log10(max);
    double bin = (logMax - logMin) / Size;

    for (int i = 0; i < Size; ++i)
        x4[i] = std::pow(10, logMin + bin * (i + 0.5));  

    for (size_t i = 0; i < TempBST.size(); ++i) {
        int idxBST = std::min(std::max(static_cast<int>((log10(TempBST[i]) - logMin) / bin), 0), Size - 1);
        int idxAVL = std::min(std::max(static_cast<int>((log10(TempAVL[i]) - logMin) / bin), 0), Size - 1);
        int idxRBT = std::min(std::max(static_cast<int>((log10(TempRBT[i]) - logMin) / bin), 0), Size - 1);

        BST_5[idxBST]++;
        AVL_5[idxAVL]++;
        RBT_5[idxRBT]++;
    }

    // Reading the search data

    int MaxHeight = static_cast<int>(BST_1.last());

    QVector<double> x5(MaxHeight,0);
    for (int i = 0; i < MaxHeight; ++i) x5[i] = i + 1;

    QVector<double>  AVL_6(MaxHeight);
    QVector<double>  BST_6(MaxHeight);
    QVector<double>  RBT_6(MaxHeight);
    QVector<double> x6;
    QVector<double>  AVL_7;
    QVector<double>  BST_7;
    QVector<double>  RBT_7;
    QVector<double>  AVL_8;
    QVector<double>  BST_8;
    QVector<double>  RBT_8;

    QFile SearchBST("../stats/searchResultsBST.csv");
    if (!SearchBST.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsBST.csv";
        return 1;
    }
    QTextStream in_SearchBST(&SearchBST);

    int CurrentIndex;
    accumulated = 0;

    index3 = 0;
    index = 0;
    while (!in_SearchBST.atEnd()) {
        QStringList campos = in_SearchBST.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        BST_7.append(CurrentIndex);
        if (CurrentIndex >= 0 && CurrentIndex < BST_6.size())
            BST_6[CurrentIndex]++;
        }
    auto rng = QRandomGenerator::global();
    shuffle(BST_7.begin(), BST_7.end(), *rng);

    for (int i = 0; i < BST_7.size(); i++){
        CurrentIndex = BST_7[index];
        accumulated += CurrentIndex;
        index++;
        if (index % intervaslSize == 0){ 
            BST_8.append(accumulated/intervaslSize);
            x6.append(index3);
            accumulated = 0 ;
            index3++;
        }
    }

    
    SearchBST.close();

    QFile SearchAVL("../stats/searchResultsAVL.csv");
    if (!SearchAVL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsAVL.csv";
        return 1;
    }
    QTextStream in_SearchAVL(&SearchAVL);

    index = 0;
    accumulated= 0;

    while (!in_SearchAVL.atEnd()) {
        QStringList campos = in_SearchAVL.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        AVL_7.append(CurrentIndex);
        if (CurrentIndex >= 0 && CurrentIndex < AVL_6.size())
            AVL_6[CurrentIndex]++;
        }

    shuffle(AVL_7.begin(), AVL_7.end(), *rng);

    for (int i = 0; i < AVL_7.size(); i++){
        CurrentIndex = AVL_7[index];
        accumulated += CurrentIndex;
        index++;
        if (index % intervaslSize == 0){ 
            AVL_8.append(accumulated/intervaslSize);
            accumulated = 0 ;
        }
    }
    SearchAVL.close();

    QFile SearchRBT("../stats/searchResultsRBT.csv");
    if (!SearchRBT.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir:" << "../stats/searchResultsRBT.csv";
        return 1;
    }
    QTextStream in_SearchRBT(&SearchRBT);

    index = 0;
    accumulated = 0;

    while (!in_SearchRBT.atEnd()) {
        QStringList campos = in_SearchRBT.readLine().split(',');
        CurrentIndex = campos[2].toInt() - 1;
        RBT_7.append(CurrentIndex);
        if (CurrentIndex >= 0 && CurrentIndex < RBT_6.size())
            RBT_6[CurrentIndex]++;
    }

    shuffle(RBT_7.begin(), RBT_7.end(), *rng);

    for (int i = 0; i < RBT_7.size(); i++){
        CurrentIndex = RBT_7[index];
        accumulated += CurrentIndex;
        index++;
        if (index % intervaslSize == 0){ 
            RBT_8.append(accumulated/intervaslSize);
            accumulated = 0 ;
        }
    }
    SearchRBT.close();

    // Adding the data
    add_graph(firstPlot, x, BST_1, AVL_1, RBT_1, config);
    setLogScale(firstPlot,true,false);
    add_graph(secondPlot, x, BST_2, AVL_2, RBT_2, config);
    setLogScale(secondPlot,true,false);
    add_graph(thirdPlot, x2, BST_3, AVL_3, RBT_3, config);
    add_graph(fourthPlot, x3, BST_4, AVL_4, RBT_4, config);
    setLogScale(fifthPlot,true,false);
    add_graph(fifthPlot, x4, BST_5, AVL_5, RBT_5, config);
    add_graph(sixthPlot, x5, BST_6, AVL_6, RBT_6, config);
    add_graph(seventhPlot, x6, BST_8, AVL_8, RBT_8, config);


    // Apply style configuration
    configurePlot(firstPlot, config,"Tree Height During Insertions","Number of Unique Words Inserted", "Tree Height");
    configurePlot(secondPlot, config,"Shallowest Leaf Depth During Insertions","Number of Unique Words Inserted","Minimum Depth" );
    configurePlot(thirdPlot, config, "Average number of comparisons (for every 100 insertions)", "Number of Unique Words Inserted(x100)", "Average");
    configurePlot(fourthPlot, config, "Total Insertion Time per Word","Number of Words Read","Total Time (ms)");
    configurePlot(fifthPlot, config, "Execution Time Distribution (Insertions)", "Insertion Time (ms)", "Frequency");
    configurePlot(sixthPlot, config, "Comparison Count Distribution per Word", "Number of Comparisons", "Frequency");
    configurePlot(seventhPlot, config, "Average number of comparisons (for every 100 searchs)", "Number of Words(x100)", "Number of Comparisons");

    // Adjust scales
    firstPlot.rescaleAxes();
    secondPlot.rescaleAxes();
    thirdPlot.rescaleAxes();
    fourthPlot.rescaleAxes();
    fifthPlot.rescaleAxes();
    fifthPlot.xAxis->setRange(min, 0.01); // Cutting out the outliers
    sixthPlot.rescaleAxes();
    seventhPlot.rescaleAxes();

    // Save as PDF

    QString title1 = "graphs/Graph_1_" + QString::number(index) + ".pdf";
    QString title2 = "graphs/Graph_2_" + QString::number(index) + ".pdf";
    QString title3 = "graphs/Graph_3_" + QString::number(index) + ".pdf";
    QString title4 = "graphs/Graph_4_" + QString::number(index) + ".pdf";
    QString title5 = "graphs/Graph_5_" + QString::number(index) + ".pdf";
    QString title6 = "graphs/Graph_6_" + QString::number(index) + ".pdf";
    QString title7 = "graphs/Graph_7_" + QString::number(index) + ".pdf";
    firstPlot.savePdf(title1,1000, 600);
    secondPlot.savePdf(title2, 1000, 600);
    thirdPlot.savePdf(title3, 1000, 600);
    fourthPlot.savePdf(title4, 1000, 600);
    fifthPlot.savePdf(title5, 1000, 600);
    sixthPlot.savePdf(title6, 1000, 600);
    seventhPlot.savePdf(title7, 1000, 600);

    return 0;
}
