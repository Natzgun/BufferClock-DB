#include <iostream>

#include "include/BufferManager.h"
#include "include/Page.h"

/* Erick Malcoaccha*/
int main() {
  BufferManager BfManger(3);
  while (true) {
    int instruction;
    cout << "================================================================"
         << endl;
    cout << "1. Load page " << endl;
    cout << "2. UpdatePage " << endl;
    cout << "3. Kill Process " << endl;
    cout << "4. Save page " << endl;
    cout << "5. Print Table Frame" << endl;
    cout << "6. Pin" << endl;
    cout << "7. Exit" << endl;
    cout << "8. Show Page Details" << endl;
    cout << "================================================================"
         << endl;
    cout << "Option: ";
    cin >> instruction;

    if (instruction == 7) {
      break;
    } else if (instruction == 1) {
      cout << "En que modo desea cargar" << endl;
      cout << "(L) Lectura" << endl;
      cout << "(W) Escritura" << endl;
      char mode;
      cout << "Mode: ";
      cin >> mode;
      int pageid;
      cout << "Page ID: ";
      cin >> pageid;
      string blockPath;
      cout << "Block Path: ";
      cin >> blockPath;
      BfManger.loadPageFromDiskClock(pageid, blockPath, mode);
    } else if (instruction == 2) {
      int pageID;
      cout << "Page ID: ";
      cin >> pageID;
      BfManger.updatePage(pageID);
    } else if (instruction == 3) {
      cout << "Indica el proceso que deseas terminar" << endl;
      int pageid;
      cout << "Page ID: ";
      cin >> pageid;
      BfManger.killProcess(pageid);
    } else if (instruction == 4) {
      cout << "Indica la pagina que deseas guardar" << endl;
      /* Aqui deberia retornarme un error si la pagina tiene procesos sin
       * terminar*/
      int pageid;
      cout << "Page ID: ";
      cin >> pageid;
    } else if (instruction == 5) {
      BfManger.printTableFrame();
    } else if (instruction == 6) {
      BfManger.updatePinnedPage();
    } else if (instruction == 8) {
      cout << "Indica la pagina que deseas ver" << endl;
      int pageid;
      cout << "Page ID: ";
      cin >> pageid;
      BfManger.showPageDetails(pageid);
    }
  }
  return 0;
}