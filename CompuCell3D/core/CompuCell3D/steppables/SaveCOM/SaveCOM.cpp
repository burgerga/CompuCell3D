#include <CompuCell3D/CC3D.h>

using namespace CompuCell3D;

using namespace std;

#include "SaveCOM.h"

SaveCOM::SaveCOM()
    : cell_field_(0), simulator_(0), potts_(0), xml_data_(0), cell_inventory_ptr_(0), frequency_(1),
      com_fname_("com.tsv"), is_first_output_(true) { }

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
void SaveCOM::start() { }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveCOM::step(const unsigned int current_step) {
  ios_base::openmode open_mode = ios::out;
  if (!is_first_output_) {
    // If not the first time we append
    open_mode |= ios::app;
  }

  ofstream output_com_file;
  output_com_file.open(com_fname_.c_str(), open_mode);
  ASSERT_OR_THROW("Can't open output com file\n", output_com_file.is_open())

  string sep = "\t";
  if (is_first_output_) {
    // write headers to the file
    output_com_file << "id" << sep << "step" << sep << "xCom" << sep << "yCom" << sep << "zCom"
        << sep << "xCCOM" << sep << "yCCOM" << sep << "zCCOM" << endl;
  }

  for (CellInventory::cellInventoryIterator cell_iterator = cell_inventory_ptr_->cellInventoryBegin();
       cell_iterator != cell_inventory_ptr_->cellInventoryEnd(); ++cell_iterator) {
    CellG *cell = cell_inventory_ptr_->getCell(cell_iterator);
    output_com_file << cell->id << sep << current_step;
    output_com_file << sep << cell->xCOM << sep << cell->yCOM << sep << cell->zCOM;
    output_com_file << sep << cell->xCCOM << sep << cell->yCCOM << sep << cell->zCCOM;
    output_com_file << endl;
  }

  output_com_file.close();
  is_first_output_ = false;
}

void SaveCOM::update(CC3DXMLElement *xml_data, bool full_init_flag) {
  if (xml_data->findElement("COMFileName")) {
    CC3DXMLElement *COMFileNameElement = xml_data->getFirstElement("COMFileName");
    com_fname_ = COMFileNameElement->getText();
  }

  // Make sure we're outputting in the simulation directory
  string basePath = simulator_->getBasePath();
  if (!basePath.empty()) {
    com_fname_ = basePath + "/" + com_fname_;
  }

}

std::string SaveCOM::toString() {
  return "SaveCOM";
}

std::string SaveCOM::steerableName() {
  return toString();
}
        
