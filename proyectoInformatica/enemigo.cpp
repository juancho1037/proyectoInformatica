#include "enemigo.h"
#include "personaje.h"


enemigo::enemigo(qreal *lastPosition)
{
    sonido = new QMediaPlayer();
    this-> temporal=0;
    this->habilidad=false;
    this->cambio = 6+rand()%15;

    // constructor
    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();
    this->setRect(0,0,30,50);
    this->setTransformOriginPoint(this->boundingRect().center());
    // establecer dimensiones del personaje 30 x 50

#ifdef DEBUG_ENEMIGO
    qDebug() << "Generacion : Enemigo común ";
#endif

    srand(time(NULL));
    this->setScale(0.7);

    // inicialización de atributos
    this->last_position=lastPosition;

    // inicialización de reloj y slots
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moverEnemigo()));
    timer->start(60);

    // llamado a metodos para personalizar el objeto creado
    // se asignará a travez de argumentos variaciones para este objeto
    // pasados por valor
    asignarCaracteristicas();
    sonido->setVolume(30);

}










enemigo::~enemigo()
{
    // este destructor eliminará automaticamente el personaje de la escena dando así la oportunidad
    // elimar únicamente de la memoria (en caso de eliminar de la escena en otra clase)
    // se advertirá sobre la inexistencia del objeto en pantalla. NO deberia afectar.
    scene()->addItem(new Animaciones(pos().x(),pos().y(),1));
    short int op = 1+rand()%5;
    if(op == 3){
        scene()->addItem(new BonusLife(this->pos().x(),this->pos().y()));
    }
    else {
        scene()->addItem(new BonusRocket(pos().x(),pos().y()));
    }
    scene()->removeItem(this);

#ifdef DEBUG_ENEMIGO
    qDebug() << "Eliminación : Enemigo común";
#endif
    //eliminacion del timer
}









QRectF enemigo::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap_zombie,columnas,0,ancho,alto);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}











void enemigo::moverEnemigo()
{
    /*
        Este método está encargado del movimiento del personaje
        Actualmente el enemigo se mueve en dirección hacia un punto (ultimo conocido)
        del personaje. se pretende que el enemigo además describa otros movimientos
        de forma inesperada (poco predecible para el jugador )
        Estos movimientos deben estar aquí :

            0) cambiarAnimación() FIJA //
            1) movimiento horizontales (implementados)

    */

    if(*last_position  < pos().x()){
        setPos(x()-cambio,pos().y());
        setTransform(QTransform());
    }
    else if(*last_position > pos().x()){
        setPos(x()+cambio,pos().y());
        setTransform(QTransform(-1, 0, 0, 1, 0, 0));
    }

    else{
        setTransform(QTransform());
        // que hacer si ya estoy en el punto  //
        // cambio de pixmap  ... etc  //
    }

    cambiarAnimacion(); // FIJA
#ifdef DEBUG_ENEMIGO
    qDebug()<< *last_position << "pos at <--";
#endif
}











void enemigo::cambiarAnimacion()
{
    // Este método se encarga de refrescar el personaje mediante el llamado del TIMER
    // --> x --> x1 --> x2 --> x3 --> de forma horizontal (avanzando por columnas).
     /*
        para corregir la animación que se desplaza hacia la derecha e izquierda
        es necesario que algunas iteraciones se hagan al reveź. por estar razón
        el atributo direction : determinará en qué secuencia se motrará el pixmap.
    */
    columnas = columnas+ancho;
    if (columnas >= limite){
        columnas=0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}












void enemigo::asignarCaracteristicas()
{
    // Este método se encarga de asignar caracteristicas al Enemigo
    // algunas son de tipo aleatorios como la posición de spaw
    // NEXT :
    //        se buscará implementar la aparición de un zoombie en pantalla
    //        sin aparición lateral

    short int aleatorio = 1+rand() %7;

    if(aleatorio == 1){
        //  zombie candidato #1
        this->ancho=97.2;
        this->alto=100;
        this->columnas=0;
        this->direction=false; // el zombie irá hacia la izquierda
        this->limite = 1458;

        pixmap_zombie = new QPixmap(":/multimedia/zombies/zombie_hacha.png");
        sonido->setMedia(QUrl("qrc:/multimedia/Sonidos/zombie_gruendo.mp3"));
        sonido->play();
        this->setScale(1.3);
    }

    else if(aleatorio == 2){
        // zombie candidato #2
        this->ancho=97.2;
        this->alto=100;
        this->columnas=1458;
        this->limite = 1458;
        this->direction=true; // el zombie irá hacia la derecha

        pixmap_zombie = new QPixmap(":/multimedia/zombies/zombie_hacha.png");
        sonido->setMedia(QUrl("qrc:/multimedia/Sonidos/zombie-demon-spawn.mp3"));
        sonido->play();
        this->setScale(1.3);
    }

    else if(aleatorio == 3){
        //alien 0 corriendo (mounstro)
        this->ancho = 169;
        this->alto = 132;
        this->columnas = 8450;
        this->direction = false;
        this->limite = 1458;
        pixmap_zombie = new QPixmap(":/multimedia/aliens/Alien0run.png");
        this->setScale(1.1);
        habilidad = true;
    }

    else if(aleatorio == 4){
        //Alien 1 corriendo (extraterrestre)
        this->ancho = 232;
        this->alto = 172;
        this->columnas = 5809;
        this->direction = false;
        this->limite = 5800;

        pixmap_zombie = new QPixmap(":/multimedia/aliens/Alien1run.png");
        habilidad = true;
    }

    else if(aleatorio == 5){
        //Alien 2 saltando (insecto)
        this->ancho = 177.26;
        this->alto = 130;
        this->columnas = 3368;
        this->direction = false;
        this->limite = 3360;

        pixmap_zombie = new QPixmap(":/multimedia/aliens/Alien2Jump.png");
    }

    else if(aleatorio == 6){
        //Alien 3 corriendo (cucaracha)
        this->ancho = 252.33;
        this->alto = 131;
        this->columnas = 2271;
        this->direction = false;
        this->limite = 2260;

        pixmap_zombie = new QPixmap(":/multimedia/aliens/alien3run.png");
    }

    else if(aleatorio == 7){
        //Alien 4 saltando (tipo kong estraterrestre)
        this->ancho = 217;
        this->alto = 130;
        this->columnas = 3689;
        this->direction = false;
        this->limite = 3689;

        pixmap_zombie = new QPixmap(":/multimedia/aliens/Alien4Jump.png");
    }

    if(1+rand()%2 == 1){
        setPos(1320,580 - rect().height());
    }
    else{
        setPos(-300, 580 -rect().height());
        //setTransform(QTransform(-1, 0, 0, 1, 0, 0));
    }
}


