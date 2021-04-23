#include <bits/stdc++.h>
using namespace std;
class Player{//класс игрок
	public:
		int points;//количество очков игрока
		string name;//имя игрока
		Player(){//конструктор для создания игрока
			points=0;
		}
};
class Cell{//класс ячейка
	public:
		char thing;//состояние ячейки (бомба, пробел, число)
		bool opened;//состояние ячейки, открывали ли эту ячейку
	Cell(){//конструктор для создания ячейки
		thing=' ';
		opened=false;
	}
	int open(){//функция класса ячейка для того, чтобы открыть ячейку, возвращает число
		if(thing=='X')return -1;//если тут мина он вернёт -1
		if(opened)return 0;//если ячейка до этого уже была открыта то он вернёт 0
		opened=true;//если ячейку до этого не открывали он поставит opened=true и вернёт 1
		return 1;
	}
};
class Game{
	public:
		char b[100][100];//массив символов для вывода на экран открытые ячейки
		Cell c[100][100];//массив ячеек
		int rows;//количество строка 
		int columns;//количество столбцов
		int minenumber;//количество мин
		Game(int x,int y,int number){//конструктор, создает обьект классы Game поле x на y, number количество мин
			rows=x;
			columns=y;
			minenumber=number;
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){//перебирает каждую ячейку и ставит ? для вывода на экран
					b[i][j]='?';
				}
			}
			srand (time(NULL));//нужен для рандомайза
			for(int i=0;i<number;i++){//цикл для того, чтобы поставить рандомно мины
			int k=rand()%x;//задаст переменной k рандомное значение от 0 до х-1
			int l=rand()%y;//задаст переменной l рандомное значение от 0 до y-1
			while(c[k][l].thing=='X'){//если на рандомно выбренной ячейке уже есть мина, будет рандомно выберать пока не найдёт пустоую ячейку
				k=rand()%x;
				l=rand()%y;
			}
			c[k][l].thing='X';
		}
		for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){//иикл чтобы перебирать все ячейки на поле
			if(c[i][j].thing!='X'){//если на ячейки нет мины, надо подсичтать количество мин вокруг
				int q=0;//количество мин вокруг 
				for(int k=i-1;k<i+2;k++){
					for(int h=j-1;h<j+2;h++){//цикл для того чтобы переберать все ячейки вокруг ячейки (i,j)
						if(k>=0&&h>=0&&k<x&&h<y&&c[k][h].thing=='X'){//если ячейка не выходит за рамки поля(массива) и на ней находиться мина увеличеваем q
							q++;
						}
					}
				}
				if(q>0){//если мины есть, задать значение с[i][j].thing количество мин
					char qw='0'+q;
					c[i][j].thing=qw;
				}
			}
		}
	}
	}	
		int clear(int px,int py,int x,int y){//функция в классе Game для того, чтобы открыть все соседние клетки вокруг пустой клетки 
			if(c[px][py].opened)return 0;//если ячейку уже до этого открыли функция вернёт 0
			int points=0;
			points+=c[px][py].open();//откроет ячейку
			b[px][py]=c[px][py].thing;//обновит символ вывода на экран
			for(int i=px-1;i<px+2;i++){
				for(int j=py-1;j<py+2;j++){//перебирает все ячейки вокруг ныняшней
					if(i>=0&&j>=0&&i<x&&j<y){
						if(c[i][j].thing==' ')points+=clear(i,j,x,y);//если соседняя ячейка пуста, то через рекурсию открывает её и её соседей тоже
						else points+=c[i][j].open();//если только число, то открывает только одну ячейку
						b[i][j]=c[i][j].thing;//обновит символ вывода на экран
					}
				}
			}
			return points;//
		}
		int turn(int px,int py,int x,int y){//функция в классе Game для хода
			if(px>=0&&py>=0&&px<x&&py<y){//если координаты не выходят за рамки то он открывает их
				if(c[px][py].opened){//если ячейка уже до этого была открыта возвращяет 0 и выводит следующий текст
					cout<<"Please choose free cell!"<<endl;
					return 0;
				}
				if(c[px][py].thing==' '){//если ячейка пуста откроет все соседние клетки вокруг пустой клетки
					return clear(px,py,x,y);
				}else {//если просто число открывает его и обнавляет символ вывода на экран
					b[px][py]=c[px][py].thing;
					return c[px][py].open();
				}
			}else{//если координаты выходят за рамки, то он возвращяет 0 и выводит следующий текст 
				cout<<"Please choose correct position!"<<endl;
				return 0;
			}
		}
		void show(){//функция в классе Game для вывода поле на экран
			cout<<"  |";
			for(int i=1;i<=columns;i++)if(i>9)cout<<i<<' ';
			else cout<<i<<"  ";
			cout<<endl;
			for(int i=0;i<=columns;i++)cout<<"___";
			cout<<endl;
			for(int i=0;i<rows;i++){
				if(i+1<10) cout<<i+1<<" |";
				else cout<<i+1<<"|";
			for(int j=0;j<columns;j++){
				cout<<b[i][j]<<"  ";
			}
			cout<<endl;
		}
	}
};
void playgame(int x,int y,int number){//функция для запуска игры, с размером поля x и y, и количества мин
	Player a[2];//создает двух игроков
	cout<<"Please write players name:"<<endl<<"First player:";
	cin>>a[0].name;
	cout<<"Second player:";
	cin>>a[1].name;
	cout<<a[0].name<<": "<<a[0].points<<endl;
	cout<<a[1].name<<": "<<a[1].points<<endl;
	Game currentgame(x,y,number);//создает игру
	int turnsid=0;//id игрока у которого ход
	bool l=true;//переменная победы, если будет равен true, значит игроки победили 
	int r=x*y-number;//количество безопастных ячеек
	currentgame.show();//функция, которая выводит на экран поле
	while(r>0){//цикл,ходить пока есть не открытые сводоные ячейки 
		cout<<"It is "<<a[turnsid].name<<"'s turn."<<endl;
		cout<<"Write position:"<<endl;
		int px,py;
		cin>>px>>py;//ход игрока
		int points=currentgame.turn(px-1,py-1,x,y);//функция хода
		if(points==-1){//если функция вернет -1 значит там мина
			l=false;//значение победы false, значит игроки проиграли
			break;
		}else {
			r-=points;//если функция вернет другое значение, это количество открытых ячеек за один ход
			a[turnsid].points+=points;//добавляет текущему игроку очки
		}	
		cout<<a[0].name<<": "<<a[0].points<<endl;
		cout<<a[1].name<<": "<<a[1].points<<endl;
		currentgame.show();
		if(points!=0)turnsid=1-turnsid;//если points не равны 0, то есть игрок открыл хотябы одну ячейку
		}
	cout<<"Game over!"<<endl;
	cout<<a[0].name<<": "<<a[0].points<<endl;
	cout<<a[1].name<<": "<<a[1].points<<endl;
	if(a[0].points>a[1].points)cout<<a[0].name<<" is winner!"<<endl;//если у первого игрока больше очков, то он победил
	else{
		if(a[1].points>a[0].points)cout<<a[1].name<<" is winner!"<<endl;//если у второго игрока больше очков, то он победил
		else cout<<"Friendship is best thing"<<endl;//если равное количество очков, то ничья
	}
}
int main(){
	int n;
	cout<<"Enter 1 in order to play or another button to close the game:";
	cin>>n;
	while(n==1){//цикла для того чтобы игра продолжалась, пока мы не скажем остановться
		int x,y;
		cout<<"Please, choose the size of the table in the range(1,100):"<<endl<<"x=";
		cin>>x;
		cout<<"y=";
		cin>>y;
		while(x<1||x>100||y<1||y>100){//цикл чтобы игрок вводил данные о размере поля, пока не ввел правильные данные
			cout<<"Choose the correct values:"<<endl<<"x=";
			cin>>x;
			cout<<"y=";
			cin>>y;
		}
		cout<<"Please, choose the number of mines in the range(1,"<<x*y<<"):"<<endl;
		int number;
		cin>>number;
		while(number<1||number>x*y){// цикл чтоы игрок вводил данные о количества мин, пока не введет приемлемое количество мин 
			cout<<"Choose the correct value:";
			cin>>number;
		}
		playgame(x,y,number);//функция для запска игры
		cout<<"Enter 1 in order to play or another button to close the game:";
		cin>>n;
	}
}
