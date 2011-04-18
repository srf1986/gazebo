#include <QtGui>

#include "common/Console.hh"
#include "common/Exception.hh"
#include "common/XMLConfig.hh"

#include "rendering/Rendering.hh"

#include "gui/TimePanel.hh"
#include "gui/RenderWidget.hh"
#include "gui/GLWidget.hh"
#include "gui/OgreWidget.h"
#include "gui/MainWindow.hh"

using namespace gazebo;
using namespace gui;

const std::string default_config =
"<?xml version='1.0'?>\
<gazebo>\
  <config>\
    <verbosity>4</verbosity>\
    <gui>\
      <size>800 600</size>\
      <pos>0 0</pos>\
    </gui>\
  </config>\
</gazebo>\
";


MainWindow::MainWindow()
  : glWidget(0)
{
  (void) new QShortcut(Qt::CTRL + Qt::Key_Q, this, SLOT(close()));
  this->CreateActions();
  this->CreateMenus();
  this->CreateToolbars();
  
  QWidget *mainWidget = new QWidget;
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainWidget->show();


  this->glWidget = new RenderWidget(mainWidget);
  this->glWidget->hide();

  this->timePanel = new TimePanel(mainWidget);

  mainLayout->addWidget( this->glWidget );
  mainLayout->addWidget( this->timePanel );
  mainWidget->setLayout(mainLayout);

  this->setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::Load( const std::string &filename )
{
  gzdbg << "Main Window Load\n";

  // Load the world file
  common::XMLConfig *xmlFile = new common::XMLConfig();

  try
  {
    if (!filename.empty())
      xmlFile->Load(filename);
    else
      xmlFile->LoadString(default_config);
  }
  catch (common::Exception e)
  {
    gzthrow("The XML config file can not be loaded, please make sure is a correct file\n" << e); 
  }

  // Get the root node, and make sure we have a gazebo config
  common::XMLConfigNode *rootNode(xmlFile->GetRootNode());
  if (!rootNode || rootNode->GetName() != "gazebo")
    gzthrow("Invalid xml. Needs a root node with the <gazebo> tag");

  // Get the config node
  common::XMLConfigNode *configNode = rootNode->GetChild("config");
  if (!configNode)
    gzthrow("Invalid xml. Needs a <config> tag");
 
  // Get the gui node
  common::XMLConfigNode *guiNode = configNode->GetChild("gui");
  if (!guiNode)
    gzthrow("Invalid xml. Needs a <gui> tag");

  // Load the Ogre rendering system
  if (!rendering::load(configNode))
    gzthrow("Failed to load the rendering engine");

  delete xmlFile;
}

void MainWindow::Init()
{
  this->glWidget->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  gzdbg << "Close Event\n";
}

void MainWindow::New()
{
  gzdbg << "New world\n";
}

void MainWindow::Open()
{
  gzdbg << "Open file\n";
}

void MainWindow::Save()
{
  gzdbg << "Save to file\n";
}

void MainWindow::About()
{
  QMessageBox::about(this, tr("About Gazebo"),
      tr("The <b>Gazebo</b> is awesome."));
}

void MainWindow::Play()
{
  gzdbg << "Play\n";
}

void MainWindow::Pause()
{
  gzdbg << "Pause\n";
}

void MainWindow::Step()
{
  gzdbg << "Step\n";
}

void MainWindow::CreateBox()
{
}

void MainWindow::CreateSphere()
{
}

void MainWindow::CreateCylinder()
{
}

void MainWindow::CreatePointLight()
{
}

void MainWindow::CreateSpotLight()
{
}

void MainWindow::CreateDirectionalLight()
{
}

void MainWindow::CreateActions()
{
  this->newAct = new QAction(tr("&New"), this);
  this->newAct->setShortcut(tr("Ctrl+N"));
  this->newAct->setStatusTip(tr("Create a new world"));
  connect(this->newAct, SIGNAL(triggered()), this, SLOT(New()));

  this->openAct = new QAction(tr("&Open"), this);
  this->openAct->setShortcut(tr("Ctrl+O"));
  this->openAct->setStatusTip(tr("Open an world file"));
  connect(this->openAct, SIGNAL(triggered()), this, SLOT(Open()));

  this->saveAct = new QAction(tr("&Save"), this);
  this->saveAct->setShortcut(tr("Ctrl+S"));
  this->saveAct->setStatusTip(tr("Save to a world file"));
  connect(this->saveAct, SIGNAL(triggered()), this, SLOT(Save()));

  this->aboutAct = new QAction(tr("&About"), this);
  this->aboutAct->setStatusTip(tr("Show the about info"));
  connect(this->aboutAct, SIGNAL(triggered()), this, SLOT(About()));

  this->quitAct = new QAction(tr("&Quit"), this);
  this->quitAct->setStatusTip(tr("Quit"));
  connect(this->quitAct, SIGNAL(triggered()), this, SLOT(close()));

  this->playAct = new QAction(QIcon(":/images/play.png"), tr("Play"), this);
  this->playAct->setStatusTip(tr("Run the world"));
  connect(this->playAct, SIGNAL(triggered()), this, SLOT(Play()));

  this->pauseAct = new QAction(QIcon(":/images/pause.png"), tr("Pause"), this);
  this->pauseAct->setStatusTip(tr("Pause the world"));
  connect(this->pauseAct, SIGNAL(triggered()), this, SLOT(Pause()));

  this->stepAct = new QAction(QIcon(":/images/end.png"), tr("Step"), this);
  this->stepAct->setStatusTip(tr("Step the world"));
  connect(this->stepAct, SIGNAL(triggered()), this, SLOT(Step()));

  this->boxCreateAct = new QAction(QIcon(":/images/box.png"), tr("Box"), this);
  this->boxCreateAct->setStatusTip(tr("Create a box"));
  connect(this->boxCreateAct, SIGNAL(triggered()), this, SLOT(CreateBox()));

  this->sphereCreateAct = new QAction(QIcon(":/images/sphere.png"), tr("Sphere"), this);
  this->sphereCreateAct->setStatusTip(tr("Create a sphere"));
  connect(this->sphereCreateAct, SIGNAL(triggered()), this, SLOT(CreateSphere()));

  this->cylinderCreateAct = new QAction(QIcon(":/images/cylinder.png"), tr("Cylinder"), this);
  this->cylinderCreateAct->setStatusTip(tr("Create a sphere"));
  connect(this->cylinderCreateAct, SIGNAL(triggered()), this, SLOT(CreateCylinder()));

  this->pointLghtCreateAct = new QAction(QIcon(":/images/pointlight.png"), tr("Point Light"), this);
  this->pointLghtCreateAct->setStatusTip(tr("Create a point light"));
  connect(this->pointLghtCreateAct, SIGNAL(triggered()), this, SLOT(CreatePointLight()));

  this->spotLghtCreateAct = new QAction(QIcon(":/images/spotlight.png"), tr("Spot Light"), this);
  this->spotLghtCreateAct->setStatusTip(tr("Create a spot light"));
  connect(this->spotLghtCreateAct, SIGNAL(triggered()), this, SLOT(CreateSpotLight()));

  this->dirLghtCreateAct = new QAction(QIcon(":/images/directionallight.png"), tr("Directional Light"), this);
  this->dirLghtCreateAct->setStatusTip(tr("Create a directional light"));
  connect(this->dirLghtCreateAct, SIGNAL(triggered()), this, SLOT(CreateDirectionalLight()));

}

void MainWindow::CreateMenus()
{
  this->fileMenu = this->menuBar()->addMenu(tr("&File"));
  this->fileMenu->addAction(this->openAct);
  this->fileMenu->addAction(this->newAct);
  this->fileMenu->addAction(this->saveAct);
  this->fileMenu->addSeparator();
  this->fileMenu->addAction(this->quitAct);

  this->viewMenu = this->menuBar()->addMenu(tr("&View"));

  this->menuBar()->addSeparator();

  this->helpMenu = this->menuBar()->addMenu(tr("&Help"));
  this->helpMenu->addAction(this->aboutAct);
}

void MainWindow::CreateToolbars()
{
  this->playToolbar = this->addToolBar(tr("Play"));
  this->playToolbar->addAction(this->playAct);
  this->playToolbar->addAction(this->pauseAct);
  this->playToolbar->addAction(this->stepAct);

  this->editToolbar = this->addToolBar(tr("Edit"));
  this->editToolbar->addAction(this->boxCreateAct);
  this->editToolbar->addAction(this->sphereCreateAct);
  this->editToolbar->addAction(this->cylinderCreateAct);
  this->editToolbar->addSeparator();
  this->editToolbar->addAction(this->pointLghtCreateAct);
  this->editToolbar->addAction(this->spotLghtCreateAct);
  this->editToolbar->addAction(this->dirLghtCreateAct);
}
