#ifndef FRAME_H
#define FRAME_H

#include "Page.h"

class Frame {
private:
  int frameID;
  bool dirty_flag;
  int pinCount;
  Page page;
  int refbit;
  bool pinned;

public:
  // Constructor
  Frame(int frameID);


  // Getters
  int getframeID();

  bool isDirty();

  int getPinCount();


  Page &getPage();

  int getRefBit();

  // Setters
  void setFrameID(int id);

  void setDirtyFlag(bool dirty);

  void setPinCount(int pin);

  void setRefBit(int refBit);

  void setPage(Page pg);

  void incrementPinCount();

  void decrementPinCount();

  void setPinned(bool value);

  bool getPinned();
};

#endif  // FRAME_H
