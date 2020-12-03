#include <LiquidCrystal.h>

#define move_btn 8
#define confirm_btn 9
#define encode_btn 10

// inicializamos el objecto de tipo LiquidCrystal con sus pines correspondientes
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int puntero = 0; //puntero para movernos por el abecedario
bool move_btn_previo; //estado de boton anterior
bool confirm_btn_previo;//estado de boton anterior
bool encode_btn_previo;//estado de boton anterior

String texto = ""; //texto confirmado
int clave = 3; //clave del algoritmo de cifra
String texto_cifrado = ""; //texto cifrado
bool isEncoded = false; //flag que indica si el usuario quiere cifrar el texto


void setup() {
  
  Serial.begin(9600);
  
  lcd.begin(16, 2); //iniciamos las filas y columnas del lcd
  lcd.cursor();//muestra el cursor
  lcd.print("Codificando:");//imprimimos en la primera fila
  
  pinMode(move_btn,INPUT);
  pinMode(confirm_btn,INPUT);
  
  pinMode(encode_btn,INPUT);
  
  //estado de los botones
  move_btn_previo = digitalRead(move_btn); 
  confirm_btn_previo = digitalRead(confirm_btn);
  encode_btn_previo = digitalRead(encode_btn);
  
}

void cambiarLetra(int pin){ //si se pulsa el boton cambiar letra se mueve el puntero de abc
  if (!digitalRead(pin) && move_btn_previo){
    //recorre el string del abecedario en bucle
    if(puntero<25){
      	puntero++;
    }else{ puntero = 0; } //si nos salimos de la longitud del string volvemos a empezar
  }

  move_btn_previo = digitalRead(pin); //guardamos el estado
}

void confirmarLetra(){//si se pulsa el boton de confirmar confirma la letra mostrada
  if (!digitalRead(confirm_btn) && confirm_btn_previo){
    texto += abc.charAt(puntero); //añade la letra al texto a mostrar
    cifrarLetra(); //llamamos a la funcion cifrar letra
  }
  confirm_btn_previo = digitalRead(confirm_btn);
}
  
void cifrarLetra(){ // ciframos la letra y lo añadimos a un string del texto cifrado 
  texto_cifrado += abc.charAt((puntero+clave)%abc.length());//haciendo uso de la clave(3) y del algoritmo de cifrado del cesar
}

void cifrar(){ //si pulsamos el boton de crifrar, mostramos la cifra
   if (!digitalRead(encode_btn) && encode_btn_previo){
     	texto = texto_cifrado; //el texto que se muestra en el lcd pasa a ser el text cifrado
     	isEncoded = true; //flag para que no muestre mas letras, solo el text cifrado
     	lcd.noCursor(); //quitamos el cursor
     	lcd.clear(); //borramos el lc y se coloca el cursor en la posicion 0,0
  		lcd.print("Cifrado!"); //pintamos en la primera fila
     	pintarLcd(); //pintamos el texto cifrado en la segunda fila
  }

  encode_btn_previo = digitalRead(encode_btn); //guardamos el estado del boton cifrar
}

void pintarLcd(){ //pintamos los valores que el usuario ha confirmado
  lcd.setCursor(0,1);
  lcd.print(texto); 
  
   
}

void mostrarLetra(){ //mostramos la letra a elegir DESPUES del los datos ya elegidos
  if(!isEncoded){ //usamos el flag de antes, si el usuario ha dado a codificar, ya no tiene que ver la letra a elegir
  	lcd.setCursor(texto.length(),1); //colocamos el cursos justo despues del texto ya confirmado
  	lcd.print(abc.charAt(puntero)); //pintamos la letra siguiente
    
    
  }
}



void loop() {
  	
  	mostrarLetra(); //mostramos la letra segun va cambiando
  	cambiarLetra(move_btn); // boton cambiamos la letra
  	confirmarLetra();//boton confirmar letra
  	cifrar(); //boton cifrar texto confirmado
  
  
  
  
  
  
}
 