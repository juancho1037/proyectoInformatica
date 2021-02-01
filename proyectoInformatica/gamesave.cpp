#include "gamesave.h"

GameSave::GameSave()
{

}

bool GameSave::confirmarArchivo(std::string nombreArchivo)
{
    file.open(nombreArchivo,std::ios::in);
     if(file.is_open()){
         return true;
     }
     else {
         return false;
     }
     file.close();

}



bool GameSave::leerInformacion(std::string nombreArchivo)
{
    qDebug()<<"buscando el usuario"<<endl;
    file.open(nombreArchivo,std::ios::in);

    if(load==true){
        short int limit=10;
        short int out=0;
        while (!file.eof()){
            out+=1;
            file >> puntaje >> shoots >> level >> life_level;
            if(out>limit){
                qDebug()<<"limit --"<< endl;
                break;
            }
        }
    }
    else{
        return false;
        file.close();
        qDebug() << "Usuario no encontrado : "<< endl;
    }
    file.close();
    return false;

}

void GameSave::escribirInformacion(std::string nombreArchivo)
{
    file.open(nombreArchivo,std::ios::out);
    file << puntaje <<" "<<shoots<<" "<<level <<" "<<life_level;
    file.close();
}


void GameSave::crearUsuario(std::string nombreArchivo)
{
    file.open(nombreArchivo,std::ios::out);
    file << 0 << " "<< 0<<" "<<0<<" "<<0;
    file.close();
}
