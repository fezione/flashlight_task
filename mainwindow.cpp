#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle( "FlashLight" );
    this->setMinimumHeight( 400 );

    view = new myView(this);

    puf = new commandsType(this);
    connect( puf, SIGNAL(sgn_showFlash(QColor)), view, SLOT(slt_drawFlashLight(QColor)));

    QLabel *lab_adress = new QLabel("Адрес", this);
    QLabel *lab_port = new QLabel("Порт", this);

    le_adress = new QLineEdit( "127.0.0.1", this );
    le_adress->setReadOnly( true );

    le_port = new QLineEdit( "2333", this );
    le_port->setReadOnly( true );

    QPushButton *but = new QPushButton("Start", this );
    connect( but, SIGNAL(clicked()), this, SLOT(slt_startTcpSocket()) );

    QGridLayout* lay_server = new QGridLayout(this);
        lay_server->addWidget( lab_adress, 0, 0 );
        lay_server->addWidget( le_adress, 0, 1 );
        lay_server->addWidget( lab_port, 1, 0 );
        lay_server->addWidget( le_port, 1, 1 );

    QVBoxLayout *lay = new QVBoxLayout(this);
        lay->addWidget( view );
        lay->addLayout( lay_server );
        lay->addWidget( but );

    ui->centralWidget->setLayout( lay );
}

MainWindow::~MainWindow()
{
    if ( socket ) {
        delete socket;
    }

    delete ui;
}

void MainWindow::slt_getDataFromSocket()
{
    if ( socket->getLength() == 3 ) {
        puf->doWork( socket->getType(), socket->getColor_r(), socket->getColor_g(), socket->getColor_b() );
    }
}

void MainWindow::slt_startTcpSocket()
{
    QString adr = le_adress->text();            //"127.0.0.1";
    quint16 port = le_port->text().toUInt();    //2333;

    if ( !onSocket ) {
        socket = new tcpClient( adr, port);
        connect( socket, SIGNAL(sgn_dataRead()), this, SLOT(slt_getDataFromSocket()));
        onSocket = true;
    }
}
