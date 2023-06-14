/*	JAIME VILLAR	*/

#include "filemanager_stub.h"
#include "utils.h"

filemanager_stub::filemanager_stub(char *_dirPath)
{
    dirPath = _dirPath;
    conn = initClient("172.31.91.5", 60000);
}

vector<string *> *filemanager_stub::listFichero()
{
    int bufferSize = 0;
    vector<string *> *buffer = 0x00;

    int op = OP_LISTFICHERO;

    sendMSG(0, (void *)&op, sizeof(int));

    sendMSG(0, dirPath, strlen(dirPath));      // second message
    recvMSG(0, (void **)&buffer, &bufferSize); // vector<string*> typed buffer

    return buffer;
}

char *filemanager_stub::writeFichero(char *file, char *content)
{
    int bufferSize = 0;
    char *buffer = 0x00;

    int op = OP_READFICHERO;

    sendMSG(0, (void *)&op, sizeof(int));

    sendMSG(0, file, strlen(file));            // second message
    sendMSG(0, content, strlen(content));      // third message
    sendMSG(0, dirPath, strlen(dirPath));      // fourth message
    recvMSG(0, (void **)&buffer, &bufferSize); // char* conteniendo error o success

    return buffer;
}

char *filemanager_stub::leeFichero(char *nombre)
{
    int bufferSize = 0;
    char *buffer = 0x00;

    int op = OP_READFICHERO;

    std::string truePath = std::string(dirPath) + nombre;

    sendMSG(0, (void *)&op, sizeof(int));

    sendMSG(0, nombre, strlen(nombre));        // second message
    sendMSG(0, dirPath, strlen(dirPath));      // third message
    recvMSG(0, (void **)&buffer, &bufferSize); // char* conteniendo error o contenido del fichero

    return buffer;
}

char *filemanager_stub::freeListedFiles(vector<string *> *fileList)
{
    int bufferSize = 0;
    char *buffer = 0x00;

    int op = OP_FREELISTED;

    sendMSG(0, (void *)&op, sizeof(int));

    sendMSG(0, fileList, fileList->size());    // second message
    sendMSG(0, dirPath, strlen(dirPath));      // third message
    recvMSG(0, (void **)&buffer, &bufferSize); // char* conteniendo error o success

    return buffer;
}

filemanager_stub::~filemanager_stub()
{
    int op = OP_FIN;
    sendMSG(0, &op, sizeof(int));

    closeConnection(0);
}