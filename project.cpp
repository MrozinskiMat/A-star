/*
Autor: Mateusz Mroziñski mrozinski.mat@gmail.com
III rok Informatyk, ISI, WMiI UWM
grupa: œroda 13:15-14:45
zadanie: Algorytm A*
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int xStart=0,yStart=0,xEnd=0,yEnd=0;
const int x=20;										
const int y=20;	
int xPunkt,yPunkt;

static int tab[y][x];
static float zamknieta[y][x]; 
static float otwarta[y][x];
static int rodzic[y][x];

static int RLy[4]={-1, 0, 1, 0};
static int RLx[4]={0, -1, 0, 1};

bool blad=false;
int droga=0;

void wczytajMape()
{
	std::fstream plik;
	plik.open("grid.txt",ios::in|ios::out);
	cout<<"Mapa wczytana pomyslnie!"<<endl<<endl;
	for(int i=0;i<x;i++)
	{			
		for(int j=0;j<y;j++)
        {
			plik>>tab[i][j];
		}
	
	}
	plik.close();
}
void wyswietlMape()
{
    cout<<"   ";
	for (int k=0;k<20;k++)
	{
		if (k<10)
		{
			cout<<k<<"  ";
		}
		else
		{
			cout<<k<<" ";
		}
	}
	cout<<endl;
	cout<<"   ";
	for (int p=0;p<20;p++)
	{
		cout<<"___";
	}
	cout<<endl;
	for (int i=0;i<20;i++)
	{
		if (i<10)
		{
		cout<<i<<" |";	
		}
		else
		{
		cout<<i<<"|";
		}
		for (int j=0;j<20;j++)
		{
			if (tab[i][j]==5)
			{
				cout<<"#"<<"  ";

			}
			else 
			{
				if (tab[i][j]==3)
				{
					cout<<"o"<<"  ";
				}
				else
				{
					if (tab[i][j]==4)
					{
						cout<<"o"<<"  ";
					}
					else
					{
						if (tab[i][j]==1||tab[i][j]==2)
						{
							cout<<"X"<<"  ";
						}
						else
						{
							cout<<"."<<"  ";
						}
					}
				}
			}

		}
		cout<<endl;
	}
	cout<<endl;
}
void wczytajStartEnd()
{
	do
	{
		cout<<"Podaj wspolzedne punktu startowego (0-19):"<<endl;
		cout<<"X:";
		while(!(cin>>xStart)|| xStart>=x) //dopóki strumieñ jest w stanie b³êdu -> dopóki podawane s¹ b³êdne dane
		{
			cout<<"Wprowadzona wartosc jest nieprawidlowa! Podaj poprawna wartosc:";
  			cin.clear(); //kasowanie flagi b³êdu strumienia
  			cin.sync(); //kasowanie zbêdnych znaków z bufora
		}
		cout<<"Y:";
		while(!(cin>>yStart)|| yStart>=y) 
		{
			cout<<"Wprowadzona wartosc jest nieprawidlowa! Podaj poprawna wartosc:";
 	 		cin.clear(); 
 	 		cin.sync(); 
		}
		if (tab[yStart][xStart]==5)
		{
			cout<<"Wybrany punkt to przeszkoda! Wybierz inny punkt."<<endl;
		}
	}while(tab[yStart][xStart]==5);
	
	do
	{
		cout<<"Podaj wspolzedne punktu koncowego (0-19):"<<endl;
		cout<<"X:";
		while(!(cin>>xEnd)|| xEnd>=x) 
		{
			cout<<"Wprowadzona wartosc jest nieprawidlowa! Podaj poprawna wartosc:";
  			cin.clear(); 
  			cin.sync();
		}
		cout<<"Y:";
		while(!(cin>>yEnd)|| yEnd>=y) 
		{
			cout<<"Wprowadzona wartosc jest nieprawidlowa! Podaj poprawna wartosc:";
  			cin.clear(); 
  			cin.sync(); 
		}
				if (tab[yEnd][xEnd]==5)
		{
			cout<<"Wybrany punkt to przeszkoda! Wybierz inny punkt."<<endl;
		}
	}while(tab[yEnd][xEnd]==5);
	
	tab[yStart][xStart]=1;
	tab[yEnd][xEnd]=2;
	
	cout<<endl<<"punkt Start ["<<xStart<<","<<yStart<<"]"<<endl;
	cout<<"punkt End ["<<xEnd<<","<<yEnd<<"]"<<endl<<endl;
	
	for(int i=0;i<x;i++)
	{			
		for(int j=0;j<y;j++)
        {
			otwarta[i][j]=0;
			rodzic[i][j]=0;
		}
	}
	
}
void obliczKomorki(int xP,int yP)
{
	for(int i=0;i<4;i++)
	{
		if((tab[yP+RLy[i]][xP+RLx[i]]==2 || tab[yP+RLy[i]][xP+RLx[i]]==0) && yP+RLy[i]>=0 && yP+RLy[i]<y && xP+RLx[i]>=0 && xP+RLx[i]<x)
		{ 		
 			otwarta[yP+RLy[i]][xP+RLx[i]]=sqrt((xP+RLx[i]-xEnd)*(xP+RLx[i]-xEnd)+(yP+RLy[i]-yEnd)*(yP+RLy[i]-yEnd));
			tab[yP+RLy[i]][xP+RLx[i]]=3;
			rodzic[yP+RLy[i]][xP+RLx[i]]=i+1;	
	 	}
	}
}
void sprwadzKomorki()
{
	int zamknietaX, zamknietaY;
	bool start=true;	
	for(int i=0;i<x;i++)
	{			
		for(int j=0;j<y;j++)
       	{	
		   	if (tab[i][j]==3 && start==true)
       	 	{	
				zamknietaY = i;
   				zamknietaX = j;
   				start = false;	
			}
			else
			{
				if (tab[i][j]==3 && otwarta[zamknietaY][zamknietaX]>otwarta[i][j])
  	     	 	{	
					zamknietaY = i;
   					zamknietaX = j;
				}
			}
		}
	}	
	xPunkt=zamknietaX;
	yPunkt=zamknietaY;	
	zamknieta[yPunkt][xPunkt]=otwarta[yPunkt][xPunkt];
	otwarta[yPunkt][xPunkt]=0;	
	tab[yPunkt][xPunkt]=4;
	
}
void sciezka(int Tx, int Ty)
{	
	bool flaga;
	while(Tx!=xStart||Ty!=yStart)
	{	
		flaga=true;
		tab[Ty][Tx]=1;
		for(int i=1;i<=4;i++)
		{
			if(rodzic[Ty][Tx]==i && flaga)
			{
				Ty-=RLy[i-1];
				Tx-=RLx[i-1];
				flaga=false;
			}
		}
		droga+=1;
	}
}
void czyIstnieje()
{
	bool flaga=false;
	for(int i=0;i<x;i++)
	{			
		for(int j=0;j<y;j++)
		{
			if (otwarta[i][j]!=0)
			{
				flaga=true;
			}
		}
	}
	blad=!flaga;
}

int main()
{
	do{
		
		blad=false;
		
		wczytajMape();
		wyswietlMape();
		wczytajStartEnd();
		wyswietlMape();
		
		xPunkt=xStart;
		yPunkt=yStart;
		
		while((yPunkt!=yEnd || xPunkt!=xEnd) && !blad)
		{
			obliczKomorki(xPunkt, yPunkt);
			czyIstnieje();
			sprwadzKomorki();				
		}
		
		if(blad)
		{
			cout<<"Nie znaleziono sciezki! Wcisnij dowolny klawisz aby wprowadzic dane jeszcze raz."<<endl;
			system("pause");
		}
		
	}while(blad);
		
	sciezka(xPunkt,yPunkt);
	wyswietlMape();
	cout<<"Dlugosc drogi: "<<droga<<endl;
	system("pause");
	return 0;
}
