#include <CompuCell3D/CC3D.h>

using namespace CompuCell3D;

using namespace std;

#include "SaveCOM.h"

SaveCOM::SaveCOM()
    : cell_field_(0), simulator_(0), potts_(0), xml_data_(0), cell_inventory_ptr_(0), frequency_(1),
      com_fname_("com.tsv") { }

SaveCOM::~SaveCOM() {
}


void SaveCOM::init(Simulator *simulator, CC3DXMLElement *xml_data) {
  xml_data_ = xml_data;

  simulator_ = simulator;
  potts_ = simulator_->getPotts();
  cell_inventory_ptr_ = &potts_->getCellInventory();
  cell_field_ = (WatchableField3D<CellG *> *) potts_->getCellFieldG();

  simulator_->registerSteerableObject(this);

  update(xml_data_, true);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveCOM::extraInit(Simulator *simulator) {
  bool is_registered;
  Plugin *plugin = Simulator::pluginManager.get("CenterOfMass", &is_registered);
  if (!is_registered)
    plugin->init(simulator);
  ASSERT_OR_THROW("CenterOfMass plugin not initialized!", plugin);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveCOM::start() {

  //PUT YOUR CODE HERE

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveCOM::step(const unsigned int current_step) {
  //REPLACE SAMPLE CODE BELOW WITH YOUR OWN
  CellInventory::cellInventoryIterator cell_iterator;
  CellG *cell = 0;

  cerr << "currentStep=" << current_step << endl;
  for (cell_iterator = cell_inventory_ptr_->cellInventoryBegin();
       cell_iterator != cell_inventory_ptr_->cellInventoryEnd(); ++cell_iterator) {
    cell = cell_inventory_ptr_->getCell(cell_iterator);
    cerr << "cell.id=" << cell->id << " vol=" << cell->volume << endl;
  }

}


void SaveCOM::update(CC3DXMLElement *xml_data, bool full_init_flag) {
  if (xml_data->findAttribute("Frequency")) {
    char *end;
    frequency_ = (int) strtol(xml_data->getAttribute("Frequency").c_str(), &end, 10);
  }

  if (xml_data->findElement("COMFileName")) {
    CC3DXMLElement *COMFileNameElement = xml_data->getFirstElement("COMFileName");
    com_fname_ = COMFileNameElement->getText();
  }

}

std::string SaveCOM::toString() {
  return "SaveCOM";
}

std::string SaveCOM::steerableName() {
  return toString();
}
        
