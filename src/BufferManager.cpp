#include "../include/BufferManager.h"

#include "../include/Frame.h"
#include "../include/Page.h"

// configura LRU (Least Recently Used) con el número total de frames.

BufferManager::BufferManager(int numFrames) {
  this->numFrames = numFrames;
  this->bpool = BufferPool(numFrames);
}

/*

Carga una página desde el disco al buffer pool.
Si todos los frames están ocupados, selecciona un frame para reemplazar usando
el algoritmo LRU guarda la página reemplazada en el disco y luego carga la nueva
página en ese frame.
*/

/*void BufferManager::loadPageFromDisk(string blockPath, int pageID, char _mode) {
  bool mode = _mode == 'W' ? true : false;
  if (bpool.isPageLoaded(pageID)){
    cout << "La pagina ya esta cargada" << "\n";
    if (_mode == 'L') {
      bpool.getFrame(bpool.getFrameId(pageID)).setDirtyFlag(false);
    } else {
      bpool.getFrame(bpool.getFrameId(pageID)).setDirtyFlag(true);
    }
    bpool.modifyPinInExistingFrame(pageID, 'i');
    bpool.incrementHistory();
    bpool.printTableFrame();
    return;
  }

  bpool.LRU();

  Page tempPage;
  tempPage.setName(blockPath);
  tempPage.setPageId(pageID);

  int idFree = bpool.findFreeFrame();
  Frame tempFrame(idFree);
  tempFrame.setDirtyFlag(mode);
  tempFrame.setPage(tempPage);
  tempFrame.incrementPinCount();

  bpool.setPageInFrame(idFree, pageID, tempFrame);
  bpool.incrementHistory();
  bpool.printTableFrame();
}*/

// ESTO CARGA UN BLOQUE DEL DISCO AL BUFFER MANAGER
// SEGIO CASTILLO Y ERICK MALCOACCHA
void BufferManager ::useClockPolicy(int pageID, string path, char _mode) {
  bool mode = _mode == 'W' ? true : false;
  if (bpool.isPageLoaded(pageID)) {
    bpool.getFrame(bpool.getFrameId(pageID)).addRequest(mode);
    cout << "La pagina ya esta cargada\n";
    if (_mode == 'L' && !bpool.getFrame(bpool.getFrameId(pageID)).isDirty()) {
      bpool.getFrame(bpool.getFrameId(pageID)).setDirtyFlag(false);
    } else {
      bpool.getFrame(bpool.getFrameId(pageID)).setDirtyFlag(true);
    }
    bpool.modifyPinInExistingFrame(pageID, 'i');
    bpool.printTableFrame();
    return;
  }
  int valueF = bpool.findFreeFrame();
  if (valueF != -2) {
    Page tempPage;
    tempPage.setName(path);
    tempPage.setPageId(pageID);

    bpool.setPageInFrame2(valueF, pageID, mode, tempPage);
    bpool.printTableFrame();
    return;
  }
  cout << "\n****************************************************\n";
  bpool.clock_Replacement(pageID, path, mode);
  cout << "\n****************************************************\n";
  bpool.printTableFrame();
}

void BufferManager::killProcess(int pageID) {
  /*
  if (bpool.getFrames()[bpool.getFrameId(pageID)].getPinned() == true) {
    cout << "Hey, hey, hey... Esta pagina esta PINEADA no la puedes tocar \n";
    return;
  }
  */

  std::string killed;
  bpool.getFrames()[bpool.getFrameId(pageID)].showVector();
  int salida = bpool.getFrames()[bpool.getFrameId(pageID)].freeRequest();
  if (salida == 1) {
    if(bpool.getFrames()[bpool.getFrameId(pageID)].posLastWrite() == -1){
      bpool.getFrames()[bpool.getFrameId(pageID)].setDirtyFlag(0);
    }
    cout << "Desea guardarlo en el disco?" << std::endl;
    cout << "Si/No: ";
    cin >> killed;
    if (killed == "Si") {
      savePageToDisk(pageID);
    }
  }
  else if(salida == -1){
    cout << "No se puede liberar procesos que no existen\n";
  }
  bpool.modifyPinInExistingFrame(pageID, 'k');
  // bpool.incrementHistory();
  bpool.printTableFrame();
}

void BufferManager::printTableFrame() { bpool.printTableFrame(); }

void BufferManager::savePageToDisk(int pageID) {
  cout << "=============================================\n";
  cout << "Pagina guardado en disco :D" << endl;
  cout << "=============================================\n";
}

void BufferManager::updatePinnedPage() {
  cout << "(1) Pinear pagina" << endl;
  cout << "(2) Despinear pagina" << endl;
  char option;
  int idPinned;
  cin >> option;
  cout << "Id de la pagina a pinear: ";
  cin >> idPinned;

  if (option == '1') {
    pinnedPage(idPinned);
  } else {
    unpinnedPage(idPinned);
  }
}

void BufferManager::pinnedPage(int pageID) {
  bpool.getFrames()[bpool.getFrameId(pageID)].setPinned(true);
}

void BufferManager::unpinnedPage(int pageID) {
  bpool.getFrames()[bpool.getFrameId(pageID)].setPinned(false);
}
