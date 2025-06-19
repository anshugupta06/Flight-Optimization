#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Backend.h"

#include <QMessageBox>
#include <QStringListModel>
#include <QCompleter>
#include <QDebug>
#include <QElapsedTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backend(new Backend())
    , airportListModel(new QStringListModel(this))
{
    ui->setupUi(this);

    ui->totalDistanceLabel->setTextFormat(Qt::RichText);
    ui->totalTimeLabel->setTextFormat(Qt::RichText);

    ui->totalDistanceLabel->setStyleSheet("color: white; font-weight: bold;");
    ui->totalTimeLabel->setStyleSheet("color: white; font-weight: bold;");


    setWindowTitle("Optimised Flight Path Finder for Domestic Routes");

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    QWidget *central = new QWidget(this);
    QVBoxLayout *outerLayout = new QVBoxLayout(central);
    outerLayout->setContentsMargins(30, 50, 100, 50);  // Slight left padding to avoid image
      // 10px left margin


    // --- Top Section (Title + Description) ---
    QLabel *titleLabel = new QLabel("Optimized Flight Path Finder");
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: black;");
    //titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setAlignment(Qt::AlignLeft);

    QLabel *descLabel = new QLabel(
        "<b>An optimized flight path finder for domestic routes across India,<br>"
        "designed to calculate the most efficient route between airports<br>"
        "using Dijkstra and A* algorithms.</b>");
    descLabel->setStyleSheet("color: black;");
    descLabel->setAlignment(Qt::AlignLeft);
    descLabel->setWordWrap(true);

    // --- Center Form Layout ---
    QVBoxLayout *formLayout = new QVBoxLayout();
    //formLayout->setAlignment(Qt::AlignCenter);
    formLayout->setAlignment(Qt::AlignLeft);
    formLayout->setSpacing(12); // spacing between widgets
    formLayout->setContentsMargins(20, 0, 400, 0);


    formLayout->addWidget(ui->algorithmComboBox);
    formLayout->addWidget(ui->resultTextEdit);
    formLayout->addWidget(ui->startAirportLineEdit);
    formLayout->addWidget(ui->endAirportLineEdit);
    formLayout->addWidget(ui->findPathButton);

    // --- Add everything to the outer layout ---
    outerLayout->addWidget(titleLabel);
    outerLayout->addWidget(descLabel);
    outerLayout->addLayout(formLayout);
    outerLayout->addStretch(); // pushes form to vertical center


    // --- Info Box for Total Distance and Time ---
    QFrame *infoFrame = new QFrame();
    infoFrame->setStyleSheet(
        "background-color: rgba(0, 0, 0, 160);"  // Semi-transparent black
        "border: 2px solid white;"
        "border-radius: 10px;"
        );
    infoFrame->setFrameShape(QFrame::StyledPanel);
    infoFrame->setFrameShadow(QFrame::Raised);

    // Use rich text for both labels
    ui->totalDistanceLabel->setTextFormat(Qt::RichText);
    ui->totalTimeLabel->setTextFormat(Qt::RichText);

    // Set initial placeholder text (white + bold)
    ui->totalDistanceLabel->setText("<span style='color:white; '>Total Distance:</span>");
    ui->totalTimeLabel->setText("<span style='color:white;'>Total Time:</span>");

    QVBoxLayout *infoLayout = new QVBoxLayout(infoFrame);
    infoLayout->setContentsMargins(10, 10, 10, 10);
    infoLayout->addWidget(ui->totalDistanceLabel);
    infoLayout->addWidget(ui->totalTimeLabel);

    // Add to form layout
    formLayout->addWidget(infoFrame);
    this->setCentralWidget(central);



    // Load the background image once and scale it
    QPixmap bkgnd("C:/Users/anshu/OneDrive/Desktop/AirportsProject/background.jpg");
    if (bkgnd.isNull()) {
        qDebug() << "Failed to load background image!";
    } else {
        // Scale with KeepAspectRatioByExpanding to fill window nicely
        bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }

    // Set stylesheets for controls
    ui->algorithmComboBox->setStyleSheet(
        "QComboBox { background-color: #2c2c2c; color: white; border: 1px solid #555; padding: 5px; }"
        "QComboBox::drop-down { border-left: 1px solid #555; }"
        "QComboBox QAbstractItemView { background-color: #2c2c2c; selection-background-color: #555; }"
        );

    ui->resultTextEdit->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #dcdcdc; border: 1px solid #444; padding: 5px; }"
        );

    ui->startAirportLineEdit->setStyleSheet(
        "QLineEdit { background-color: #1e1e1e; color: white; border: 1px solid #555; border-radius: 4px; padding: 5px; }"
        );
    ui->endAirportLineEdit->setStyleSheet(
        "QLineEdit { background-color: #1e1e1e; color: white; border: 1px solid #555; border-radius: 4px; padding: 5px; }"
        );

    ui->findPathButton->setStyleSheet(
        "QPushButton { background-color: #007acc; color: white; border-radius: 6px; padding: 6px 12px; }"
        "QPushButton:hover { background-color: #005f99; }"
        );

    ui->totalDistanceLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; margin-top: 10px; color: black; }");
    ui->totalTimeLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; margin-top: 10px; color: black; }");

    // Check if backend loaded data successfully
    if (!backend->isDataLoaded()) {
        QMessageBox::critical(this, "Error", "Failed to load airport connection data.");
        return;
    }

    // Prepare airport names for the completers
    const auto& airportNamesMap = backend->getAirportNames();
    QStringList airportNames;
    for (const auto& pair : airportNamesMap) {
        airportNames << QString::fromStdString(pair.second + " (" + pair.first + ")");
    }
    airportNames.sort();
    airportListModel->setStringList(airportNames);

    QCompleter* completerStart = new QCompleter(airportListModel, this);
    completerStart->setCaseSensitivity(Qt::CaseInsensitive);
    ui->startAirportLineEdit->setCompleter(completerStart);
    ui->startAirportLineEdit->setPlaceholderText("Start Airport (e.g., Indira Gandhi Intl (DEL))");

    QCompleter* completerEnd = new QCompleter(airportListModel, this);
    completerEnd->setCaseSensitivity(Qt::CaseInsensitive);
    ui->endAirportLineEdit->setCompleter(completerEnd);
    ui->endAirportLineEdit->setPlaceholderText("End Airport (e.g., Chhatrapati Shivaji Intl (BOM))");

    ui->algorithmComboBox->addItem("Dijkstra");
    ui->algorithmComboBox->addItem("A*");

    // Tooltips for better UX
    ui->startAirportLineEdit->setToolTip("Type the starting airport (IATA code or full name)");
    ui->endAirportLineEdit->setToolTip("Type the destination airport");
    ui->algorithmComboBox->setToolTip("Choose the pathfinding algorithm");
    ui->findPathButton->setToolTip("Find the shortest path between airports");

    ui->resultTextEdit->setReadOnly(true);

    connect(ui->findPathButton, &QPushButton::clicked, this, &MainWindow::findPathButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete backend;
    delete airportListModel;
}

QString MainWindow::extractIataCode(const QString& airportText) const
{
    QString trimmed = airportText.trimmed();

    int startIndex = trimmed.lastIndexOf('(');
    int endIndex = trimmed.lastIndexOf(')');

    if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
        return trimmed.mid(startIndex + 1, endIndex - startIndex - 1).trimmed();
    } else if (trimmed.length() == 3 && trimmed.toUpper() == trimmed) {
        return trimmed;
    }
    return "";
}

void MainWindow::findPathButtonClicked()
{
    QString startAirportText = ui->startAirportLineEdit->text();
    QString endAirportText = ui->endAirportLineEdit->text();
    QString selectedAlgorithm = ui->algorithmComboBox->currentText();

    std::string startCode = extractIataCode(startAirportText).toStdString();
    std::string endCode = extractIataCode(endAirportText).toStdString();

    qDebug() << "Start Code:" << QString::fromStdString(startCode);
    qDebug() << "End Code:" << QString::fromStdString(endCode);

    if (startCode.empty() || endCode.empty()) {
        QMessageBox::warning(this, "Input Error", "Please enter valid airport names or IATA codes.");
        return;
    }

    std::pair<std::vector<std::string>, int> result;
    QElapsedTimer timer;
    timer.start();

    if (selectedAlgorithm == "Dijkstra") {
        result = backend->dijkstra(startCode, endCode);
    } else if (selectedAlgorithm == "A*") {
        result = backend->aStar(startCode, endCode);
    } else {
        QMessageBox::warning(this, "Algorithm Error", "Please select a valid algorithm.");
        return;
    }

    qint64 elapsedNano = timer.nsecsElapsed();  // nanoseconds
    double elapsedMs = elapsedNano / 1e6;       // milliseconds

    const auto& path = result.first;
    int distance = result.second;

    if (path.empty() || distance == -1) {
        ui->resultTextEdit->setText("No path found.");
        ui->totalDistanceLabel->setText("<span style='color:white; font-weight:bold;'>Total Distance: No path found</span>");
        ui->totalTimeLabel->setText("<span style='color:white; font-weight:bold;'>Total Time: "
                                    + QString::number(elapsedMs, 'f', 3) + " ms</span>");


        return;
    }

    QString pathText;
    for (size_t i = 0; i < path.size(); ++i) {
        pathText += QString::fromStdString(backend->getAirportNames().at(path[i])) + " (" + QString::fromStdString(path[i]) + ")";
        if (i < path.size() - 1) {
            pathText += " -> ";
        }
    }

    ui->resultTextEdit->setText("Path: " + pathText);
    ui->totalDistanceLabel->setText("<span style='color:white;'>Total Distance: "
                                    + QString::number(distance) + " km</span>");

    ui->totalTimeLabel->setText("<span style='color:white;'>Total Time: "
                                + QString::number(elapsedMs, 'f', 3) + " ms</span>");

}
