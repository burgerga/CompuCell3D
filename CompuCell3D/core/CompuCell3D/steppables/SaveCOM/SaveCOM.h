#ifndef SAVECOMSTEPPABLE_H
#define SAVECOMSTEPPABLE_H

#include <CompuCell3D/CC3D.h>


#include "SaveCOMDLLSpecifier.h"


namespace CompuCell3D {

template<class T>
class Field3D;
template<class T>
class WatchableField3D;

class Potts3D;
class Automaton;
class BoundaryStrategy;
class CellInventory;
class CellG;

class SAVECOM_EXPORT SaveCOM: public Steppable {


  WatchableField3D<CellG *> *cell_field_;
  Simulator *simulator_;
  Potts3D *potts_;
  CC3DXMLElement *xml_data_;
  CellInventory *cell_inventory_ptr_;

  int frequency_;
  string com_fname_;


 public:
  SaveCOM();
  virtual ~SaveCOM();
  // SimObject interface
  virtual void init(Simulator *simulator, CC3DXMLElement *xml_data = 0);
  virtual void extraInit(Simulator *simulator);


  //steppable interface
  virtual void start();
  virtual void step(const unsigned int current_step);
  virtual void finish() { }


  //SteerableObject interface
  virtual void update(CC3DXMLElement *xml_data, bool full_init_flag = false);
  virtual std::string steerableName();
  virtual std::string toString();

};
};
#endif        
