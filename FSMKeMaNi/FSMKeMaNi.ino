//#include <Arduino.h>
//http://playground.arduino.cc/uploads/Code/FSM.zip
#include <FiniteStateMachine.h>

////////////////////////
////    FSM
////    En el loop esta la logica de transiciones
////    
////    Las primeras 5 funciones son la logica de las acciones del estado.
////
////    Las ultimas 3 funciones son para leer los sensores y bluetooth para tomar
////    acciones al respecto
////////////////////////

//Funcion para mover el robot hacia adelante.
void avanzar() {

}

//Funcion para mover el robot de acuerdo con los comandos del usuario
void controlManual() {

}

//Funcion para actuar cuando se encuentra con un obstaculo
void obstaculo() {

}

//Funcion para revisar a la derecha e izquierda para moverse
void revisar() {

}

//Funcion para dar la vuelta en alguna direccion
void darVuelta() {

}


const byte NUMBER_OF_STATES = 5; //Cantidad de ciclos

//Estados
State Avanzar = State(avanzar);
State ControlManual = State(controlManual);
State Obstaculo = State(obstaculo);
State Revisar = State(revisar);
State DarVuelta = State(darVuelta);

FSM aspiradora = FSM(Avanzar);     //Primer estado es Avanzar

void setup() {
  /*Nada aun*/
}

  //Transisicones
  void loop() {

  //Si esta en el estado de Avanzar revisa primero si el usuario quiere el control manual, de
  //ser asi cambia al estado de ControlManual, despues revisa si hay obstaculos o no para
  // ver si se mantiene en el estado de Avanzar o cambia a Obstaculo
  if ( aspiradora.isInState( Avanzar )) {

    if ( mensajeRecibido() == "m" ) {

      aspiradora.transitionTo(ControlManual);
      aspiradora.update();
    }
    else if (caminoLibre() && !hayVacio()) {

      aspiradora.transitionTo(Avanzar);
      aspiradora.update();
    }
    else {

      aspiradora.transitionTo(Obstaculo);
      aspiradora.update();
    }
  }
  
  //Si esta en el estado de ControlManual  revisa primero si el usuario quiere el control 
  //automatico, de ser asi cambia al estado de Avanzar, si no entonces se mantiene en 
  //ControlManual
  else if ( aspiradora.isInState(ControlManual) ) {

    if (mensajeRecibido() == "a") {

      aspiradora.transitionTo(Avanzar);
      aspiradora.update();
    }
    else {

      aspiradora.transitionTo(ControlManual);
      aspiradora.update();
    }
  }

  //Si esta en el estado de Obstaculo revisa primero si el usuario quiere el control manual, de
  //ser asi cambia al estado de ControlManual, si no entonces cambia al estado de Revisar 
  else if ( aspiradora.isInState(Obstaculo) ) {

    if ( mensajeRecibido() == "m") {

      aspiradora.transitionTo(ControlManual);
      aspiradora.update();
    }
    else {

      aspiradora.transitionTo(Revisar);
      aspiradora.update();
    }
  }

  //Si esta en el estado de Revisar revisa primero si el usuario quiere el control manual, de
  //ser asi cambia al estado de ControlManual, si no entonces cambia al estado de DarVuelta
  else if ( aspiradora.isInState (Revisar) ) {

    if ( mensajeRecibido() == "m") {

      aspiradora.transitionTo(ControlManual);
      aspiradora.update();
    }
    else {

      aspiradora.transitionTo(DarVuelta);
      aspiradora.update();
    }
  }

  //Si esta en el estado de DarVuelta revisa primero si el usuario quiere el control manual, de
  //ser asi cambia al estado de ControlManual, si no entonces cambia al estado de Avanzar
  else if (  aspiradora.isInState (DarVuelta) ) {

    if ( mensajeRecibido() == "m") {

      aspiradora.transitionTo(ControlManual);
      aspiradora.update();
    }
    else {

      aspiradora.transitionTo(Avanzar);
      aspiradora.update();
    }
  }
}


//Funcion que determina si no hay obstaculos adelante del camino del robot.
boolean caminoLibre() {

  return true;
}

//Funcion que determina si hay vacio por debajo del robot.
boolean hayVacio() {

  return false;
}

//Funcion que se comunica por Bluetooth con la app y lee datos (si hay)
//No estoy seguro del tipo de dato de retorno de la funcion
String mensajeRecibido() {

  return "";
}

