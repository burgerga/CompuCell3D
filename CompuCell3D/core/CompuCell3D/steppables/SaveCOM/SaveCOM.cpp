#include <CompuCell3D/CC3D.h>

using namespace CompuCell3D;

using namespace std;

#include "SaveCOM.h"

SaveCOM::SaveCOM()
    : cellFieldG(0), sim(0), potts(0), xmlData(0), boundaryStrategy(0), automaton(0), cellInventoryPtr(0), frequency(1),
      COMFileName("com.tsv") { }

SaveCOM::~SaveCOM() {
}


void SaveCOM::init(Simulator *simulator, CC3DXMLElement *_xmlData) {
  xmlData = _xmlData;

  potts = simulator->getPotts();
  cellInventoryPtr = &potts->getCellInventory();
  sim = simulator;
  cellFieldG = (WatchableField3D<CellG *> *) potts->getCellFieldG();
  fieldDim = cellFieldG->getDim();


  simulator->registerSteerableObject(this);

  update(_xmlData, true);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveCOM::extraInit(Simulator *simulator) {
  bool pluginAlreadyRegisteredFlag;
  Plugin *plugin = Simulator::pluginManager.get("CenterOfMass",
                                                &pluginAlreadyRegisteredFlag); //this will load VolumeTracker plugin if it is not already loaded
  if (!pluginAlreadyRegisteredFlag)
    plugin->init(simulator);
  ASSERT_OR_THROW("CenterOfMass plugin not initialized!", plugin);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveCOM::start() {

  //PUT YOUR CODE HERE

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveCOM::step(const unsigned int currentStep) {
  //REPLACE SAMPLE CODE BELOW WITH YOUR OWN
  CellInventory::cellInventoryIterator cInvItr;
  CellG *cell = 0;

  cerr << "currentStep=" << currentStep << endl;
  for (cInvItr = cellInventoryPtr->cellInventoryBegin(); cInvItr != cellInventoryPtr->cellInventoryEnd(); ++cInvItr) {
    cell = cellInventoryPtr->getCell(cInvItr);
    cerr << "cell.id=" << cell->id << " vol=" << cell->volume << endl;
  }

}


void SaveCOM::update(CC3DXMLElement *_xmlData, bool _fullInitFlag) {

  //PARSE XML IN THIS FUNCTION
  //For more information on XML parser function please see CC3D code or lookup XML utils API
  automaton = potts->getAutomaton();
  ASSERT_OR_THROW("CELL TYPE PLUGIN WAS NOT PROPERLY INITIALIZED YET. MAKE SURE THIS IS THE FIRST PLUGIN THAT YOU SET",
                  automaton)
  set<unsigned char> cellTypesSet;

  if (_xmlData->findAttribute("Frequency")) {
    frequency = (int) strtol(_xmlData->getAttribute("Frequency"));
  }

  if (_xmlData->findElement("COMFileName")) {
    CC3DXMLElement *COMFileNameElement = _xmlData->getFirstElement("COMFileName");
    COMFileName = COMFileNameElement->getText();
  }

  //boundaryStrategy has information aobut pixel neighbors
  boundaryStrategy = BoundaryStrategy::getInstance();

}

std::string SaveCOM::toString() {
  return "SaveCOM";
}

std::string SaveCOM::steerableName() {
  return toString();
}
        
