/*	JAIME VILLAR	*/

#include "filemanager_imp.h"
#include "filemanager_stub.h"
#include "utils.h"
#include <string.h>

filemanager_imp::filemanager_imp(int clientID)
{
    this->clientID = clientID; // waitForConnections(server_fd);
    // fm = new FileManager(); Esperamos a crear el filemanager una vez hayamos recibido el dirPath del cliente.
}

void filemanager_imp::recvOP()
{
    int op = -1;
    char *buff;
    int bufLen;
    recvMSG(clientID, (void **)&buff, &bufLen);
    op = ((int *)buff)[0];
    delete[] buff;

    switch (op)
    {
    case OP_LISTFICHERO:
    {
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe dirPath para crear FileManager
        char *path = buff;
        FileManager fm = FileManager(path); // creamos FileManager
        delete[] buff;

        vector<string *> *res = fm.listFiles(); // almacenamos el resultado de listFiles

        sendMSG(clientID, (void *)&res, sizeof(res)); // devolvemos dicho resultado

        break;
    }
    case OP_WRITEFICHERO:
    {
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe nombre del fichero
        char *file = buff;
        delete[] buff;
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe contenido que escribir en fichero
        char *content = buff;
        int len = bufLen;
        delete[] buff;
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe dirPath para crear FileManager
        char *path = buff;
        delete[] buff;

        FileManager fm = FileManager(path);

        char *res = fm.writeFile(file, content, len); // writeFile escribe el content en un file. Si no existe file, lo crea.
                                                      // devuelve un error o el success y lo guarda en data
        sendMSG(clientID, res, strlen(res));
        delete[] res;
        delete[] buff;
        break;
    }
    case OP_READFICHERO:
    {
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe nombre del fichero
        char *file = buff;
        delete[] buff;
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe dirPath para crear FileManager
        char *path = buff;
        FileManager fm = FileManager(path);

        unsigned long int fileLen = 0;

        char *data = fm.readFile(file, fileLen); // readFile devuelve el contenido del archivo
                                                 // devuelve un error o el contenido y lo guarda en data
        sendMSG(clientID, data, fileLen);

        delete[] data;
        delete[] buff;
        break;
    }
    case OP_FREELISTED:
    {
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe lista de ficheros
        vector<string *> *fileList = (vector<string *> *)buff;
        delete[] buff;
        recvMSG(clientID, (void **)&buff, &bufLen); // recibe dirPath para crear FileManager
        char *path = buff;
        FileManager fm = FileManager(path);

        char *res = fm.freeListedFiles(fileList);

        sendMSG(clientID, res, strlen(res));
        delete[] res;
        delete[] buff;
    }
    case OP_FIN:
    {
        salir = true;
        break;
    }
    default:
    {
        printf("ERROR OP NO DEFINIDA: %d\n", op);
        break;
    }
    }
}

filemanager_imp::~filemanager_imp()
{

    closeConnection(clientID);

    delete fm;
}
