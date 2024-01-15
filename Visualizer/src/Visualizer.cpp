#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Orbit.h"
#include "QTimer"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mpushButtonStart, &QPushButton::clicked, this, &Visualizer::startBtn);
    connect(mpushButtonStop, &QPushButton::clicked, this, &Visualizer::stopBtn);
    connect(mpushButtonReset, &QPushButton::clicked, this, &Visualizer::resetBtn);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi() {

    QWidget* mCentralWidget = new QWidget(this);
    //mCentralWidget->setStyleSheet("background-color:#000000; color: white;");

    QVBoxLayout* mainVerticalLayout = new QVBoxLayout(mCentralWidget);

    QHBoxLayout* buttonsLayout = new QHBoxLayout(this);
    QMargins marginsHorizontalLayout(50, 20, 50, 50);
    buttonsLayout->setContentsMargins(marginsHorizontalLayout);

    mpushButtonStart = new QPushButton(this);
    //mpushButtonStart->setText("Start Simulation");
    QIcon startIcon("D:\\Visualizer\\resources\\startbutton.jpg");  // Provide the actual path to your image file
    mpushButtonStart->setIcon(startIcon);
    mpushButtonStart->setIconSize(QSize(150, 150)); // Set the size of the icon
    mpushButtonStart->setFixedSize(150, 100);
    mpushButtonStart->setStyleSheet("QPushButton {"
        "background-color: transparent;" // Make the background transparent
        "border: none;" // Remove the border
        "}");

    mpushButtonStop = new QPushButton(this);
    //mpushButtonStart->setText("Start Simulation");
    QIcon pauseIcon("D:\\Visualizer\\resources\\stopbutton.jpg");  // Provide the actual path to your image file
    mpushButtonStop->setIcon(pauseIcon);
    mpushButtonStop->setIconSize(QSize(150, 150)); // Set the size of the icon
    mpushButtonStop->setFixedSize(150, 100);
    mpushButtonStop->setStyleSheet("QPushButton {"
        "background-color: transparent;" // Make the background transparent
        "border: none;" // Remove the border
        "}");

    mpushButtonReset = new QPushButton(this);
    //mpushButtonStart->setText("Start Simulation");
    QIcon resetIcon("D:\\Visualizer\\resources\\resetbutton.jpg");  // Provide the actual path to your image file
    mpushButtonReset->setIcon(resetIcon);
    mpushButtonReset->setIconSize(QSize(150, 150)); // Set the size of the icon
    mpushButtonReset->setFixedSize(150, 100);
    mpushButtonReset->setStyleSheet("QPushButton {"
        "background-color: transparent;" // Make the background transparent
        "border: none;" // Remove the border
        "}");

    buttonsLayout->addWidget(mpushButtonStart);
    buttonsLayout->addWidget(mpushButtonStop);
    buttonsLayout->addWidget(mpushButtonReset);

    mainVerticalLayout->addLayout(buttonsLayout);

    mRenderer = new OpenGLWindow(QColor(1.0, 1.0, 0.0), this);
    mainVerticalLayout->addWidget(mRenderer);

    setCentralWidget(mCentralWidget);
    showMaximized();
    setWindowTitle(QCoreApplication::translate("Collision Viewer", "Collision Viewer", nullptr));
}

void Visualizer::readSTL()
{
    std::string filePath = "D:/sphere3.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
    //int c = 100;
    while (std::getline(dataFile, line))
    {
      
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices.push_back(x * 0.1);
            mVertices.push_back(y * 0.1);
            mVertices.push_back(z * 0.1);

            mColors.push_back(1.0f);
            mColors.push_back(0.0f);
            mColors.push_back(0.0f);
           
        }
    }
    
    mRenderer->updateData(mVertices, mColors);
    /*mVertices.clear();
    mColors.clear();
    dataFile.close();*/
    update();
}

void Visualizer::startBtn()

{
    mRenderer->startRendering(mVelocity);
}

void Visualizer::stopBtn()

{

    mRenderer->stopRevolving();

}

void Visualizer::resetBtn()

{

    mRenderer->resetPositions();

}