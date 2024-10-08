#include <iostream>
#include "IRClientTCP.h"
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;
unsigned int ChaineVersInt(char * chaineHexa, int nbCar)
{ int nombre=0;
  int j=0;


  char caractere;
  for(j=0;j<nbCar;j++)
  {
	  caractere=chaineHexa[j];
	  if(caractere>='0'&&caractere<='9')
	  {	nombre=nombre+((caractere-'0')<<(4*(nbCar-j-1)));
	  }
	  else
	  {	nombre=nombre+((caractere-'A'+10)<<(4*(nbCar-j-1)));
	  }
  }
  return nombre;
}



int main()
{
	cout <<"Bonjour" <<endl;
	cin.get();
	cout <<ChaineVersInt("15",2)<<endl;
	cin.get();
	IRClientTCP monClient;
	char trameCAN[50];
	char idCAN[10]="128";
	while (true)
	{
	   cout <<"Saisir un id" <<endl;
	   monClient.SeConnecterAUnServeur("172.20.21.24",4111);
	   monClient.Envoyer(idCAN,strlen(idCAN));
	   monClient.Recevoir(trameCAN,50);
	   cout <<trameCAN<<endl;
	   if(!strcmp(idCAN,"0B6"))
	   {
	   int vitesse=ChaineVersInt(trameCAN+23,2)*2.55;
	   cout<< vitesse <<" km/h"<<endl;
	   int moteur=ChaineVersInt(trameCAN+19,2)*100/3.1;
	   cout<< moteur <<"tr/min"<<endl;
	   }
	   else
	   { unsigned char octet = ChaineVersInt(trameCAN+27,2);
	   cout<<"Croisement : "<<(bool)(octet&(0x01<<6))<<endl;
	   cout<<"Route : "<<(bool)(octet&(0x01<<5))<<endl;
	   cout<<"Brouillard : "<<(bool)(octet&(0x01<<3))<<endl;
	   cout<<"Cligno D : "<<(bool)(octet&(0x01<<2))<<endl;
	   cout<<"Cligno G : "<<(bool)(octet&(0x01<<1))<<endl;
	   Sleep(100);

	   }
	   monClient.SeDeconnecter();
	   Sleep(1000);
	}


}


