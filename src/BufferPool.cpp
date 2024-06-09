#include "../include/Buffer.h"

#include <iostream>

#include "../include/Page.h"

using namespace std;


//Inicializamos el buffer con un número fijo de frames y capacidad.
Buffer::Buffer() {
  this->numFrames = 3;
  this->capacity = 360;

  Page frame;

  for (int i = 0; i < 3; i++) {     //Llena el vector de frames con instancias de la clase Page
    this->frames.push_back(frame);
    page_table[i] = -1;             // configura la tabla de páginas como vacía.
  }

  printPage_table();
}


//proporciona acceso al vector de frames, permitiendo la manipulación directa de las páginas en el buffer desde fuera de la clase.
vector<Page>& Buffer::getFrames() { return frames; }

/*
Carga una página en un frame específico dentro del buffer
actualizado la tabla de páginas
imprime el contenido sobre el estado actual del buffer y la página cargada.
*/
void Buffer::setPage(Page& page, int frameID) {
  if (frameID >= 0 && frameID < numFrames) {
    frames[frameID] = page;
    page_table[frameID] = 1;
  } else {
    cout << "SetP: Frame ID fuera de rango" << endl;
    return;
  }

  printPage(frameID);
  printPage_table();

  cout << "\nPagina [" << frameID << "] cargada Correctamente\n" << endl;
}



//Permite visualizar el contenido y estado de una página específica en el buffer, se considera solo los frames cargados.
void Buffer::printPage(int pageID) {
  cout << "= ===================================" << endl;
  if (pageID >= 0 && pageID < numFrames) {
    if (page_table[pageID] == 1) {
      Page& page = frames[pageID];

      cout << "Frame ID: " << pageID << endl;
      cout << "Capacity: " << page.pageCapacity << endl;
      cout << "Dirty Flag: " << (page.isDirty() ? "true" : "false") << endl;
      cout << "Pin Count: " << page.getPinCount() << endl;

      cout << "Contenido del frame " << pageID << ":\n" << endl;
      for (const string& content : page.getContent()) {
        cout << content << endl;
      }
    } else {
      cout << "El frame " << pageID << " está vacío" << endl;
    }
  } else {
    cout << "PP: Page ID fuera de rango" << endl;
  }

  cout << "= ===================================" << endl;
}

//Añade un registro a una página específica en el buffer, marcando la página como modificada y actualizando el contador de pines.
void Buffer::addRecord(int pageID) {
  string record = "Transformer    3454354  cybertron";
  if (pageID >= 0 && pageID < numFrames) {
    if (page_table[pageID] == 1) {
      Page& page = frames[pageID];
      page.setContent(record);
      page.setDirtyFlag(true);
      page.setPinCount(1);
      cout << "Registro agregado al frame " << pageID << endl;
    } else {
      cout << "AddRecord: El frame " << pageID << " está vacío" << endl;
    }
  } else {
    cout << "Frame ID fuera de rango" << endl;
  }
}

/*
Busca un frame libre en el buffer para cargar una nueva página.
permitiendo saber si hay espacio disponible para nuevas páginas.
*/
int Buffer::freeFrame() {
  for (auto it = page_table.begin(); it != page_table.end(); ++it) {
    if (it->second == -1) return it->first;
  }

  /*Si retorna -2 es porque todos los frames ya tienen cargado una pagina*/
  return -2;
}


//Imprime el estado actual de la tabla de páginas
void Buffer::printPage_table() {
  for (auto it = page_table.begin(); it != page_table.end(); ++it) {
    if (it->second == 1)
      std::cout << "PageId: " << it->first << ", (status) Used: " << it->second
                << std::endl;
    else
      std::cout << "FrameId: " << it->first << ", (status) Free: " << it->second
                << std::endl;
  }
}

//Comprueba si una página específica ha sido modificada (está sucia)
bool Buffer::pageIsDirty(int pageID) {
  Page& page = frames[pageID];
  return page.isDirty();
}