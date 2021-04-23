#include <bits/stdc++.h>
using namespace std;
char a[100][100];
char b[100][100];
int clear(int px,int py,int x,int y){//функция для того, чтобы открыть не открытые ячейки вокруг нынешнего
	if(b[px][py]==a[px][py])return 0;//если уже до этого была открыта ничего не сделать и вернуть 0
	b[px][py]=a[px][py];
	int points=1;
	if(a[px][py]==' '){//если ячейка пустая, то значит вокруг нет мин и можно открыть соседние ячейки 
		if(px-1>=0){//если соседняя ячейка не выходит за рамки поля, открыть соседнию ячейку
			points+=clear(px-1,py,x,y);//рекурсивно открывать ячейки
		}
		if(px+1<x){
			points+=clear(px+1,py,x,y);
		}
		if(py-1>=0){
			points+=clear(px,py-1,x,y);
		}
		if(py+1<x){
			points+=clear(px,py+1,x,y);
		}
	}
	return points;//вернуть общее количество открытых ячеек
}
int turn(int px,int py,int x,int y){//функция хода на ячейку px, py на поле x на y
	if(px>=0&&py>=0&&px<x&&py<y){//ход должен не выходить за рамки поля(массива)
		if(a[px][py]=='X'){//если на ячейке мина, вернуть -1
			return -1;
		}else if(a[px][py]==b[px][py]){//если мы открыли это ячейку до этого, то ничего не будет и он вернуть 0, потому что мы не открывали ни одной новой ячейки
			cout<<"Please, choose a position that doesn't taken:"<<endl;
			return 0;
		}else if(a[px][py]==' '){//если ячейка пустая, то значит вокруг нет мин и можно открыть соседние ячейки 
			int points=1;
			b[px][py]=a[px][py];//открыть ячейку
			if(px-1>=0){//если соседняя ячейка не выходит за рамки поля, открыть соседнию ячейку
				points+=clear(px-1,py,x,y);//добавить в общее количество открытых ячеек, количество открытых ячеек за ход на соседнюю ячейку
			}
			if(px+1<x){
				points+=clear(px+1,py,x,y);
			}
			if(py-1>=0){
				points+=clear(px,py-1,x,y);
			}
			if(py+1<x){
				points+=clear(px,py+1,x,y);
			}
			return points;//вернуть общее количетво открытых ячеек 
		}else {//если на ячейке только число, открыть только его и вернуть 1  
			b[px][py]=a[px][py];
			return 1;
		}
	}else {
		cout<<"Please, choose correct position:"<<endl;
		return 0;
	}
}
void playgame(int x,int y,int number){//функция для запуска игры, с размером поля x и y, и количества мин
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			b[i][j]='?';//двухмерный массив показывает ячейки на экран, если его не выбрать, то он по умолчанию будет показывать ?, если открыть ячейку то он возьметь значение из массива а
			a[i][j]=' ';//двухмерный массив показывает что находиться на ячейке, Х это мина, пробел  значит что вокруг нет мин, число покажет количество мин вокруг ячейки
		}
	}
	srand (time(NULL));//нужен для рандомайза
	for(int i=0;i<number;i++){//цикл для того, чтобы поставить рандомно мины
		int k=rand()%x;//задаст переменной k рандомное значение от 0 до х-1
		int l=rand()%y;//задаст переменной l рандомное значение от 0 до y-1
		while(a[k][l]=='X'){//если на рандомно выбренной ячейке уже есть мина, будет рандомно выберать пока не найдёт пустоую ячейку
			k=rand()%x;
			l=rand()%y;
		}
		a[k][l]='X';
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){//иикл чтобы перебирать все ячейки на поле
			if(a[i][j]!='X'){//если на ячейки нет мины, надо подсичтать количество мин вокруг
				int q=0;//количество мин вокруг 
				for(int k=i-1;k<i+2;k++){
					for(int h=j-1;h<j+2;h++){//цикл для того чтобы переберать все ячейки вокруг ячейки (i,j)
						if(k>=0&&h>=0&&k<x&&h<y&&a[k][h]=='X'){//если ячейка не выходит за рамки поля(массива) и на ней находиться мина увеличеваем q
							q++;
						}
					}
				}
				if(q>0){//если мины есть, задать значение a[i][j] количество мин
					char c='0'+q;
					a[i][j]=c;
				}
			}
		}
	}
	bool l=true;//переменная победы, если будет равен true, значит игрок победил 
	int r=x*y-number;//количество безопастных ячеек
	cout<<"  |";
		for(int i=1;i<=y;i++)if(i>9)cout<<i<<' ';
		else cout<<i<<"  ";
		cout<<endl;
		for(int i=0;i<=y;i++)
            cout<<"___";
		cout<<endl;
		for(int i=0;i<x;i++){
			if(i+1<10) cout<<i+1<<" |";
			else cout<<i+1<<"|";
		for(int j=0;j<y;j++){
			cout<<b[i][j]<<"  ";
		}
		cout<<endl;
	}
	while(r>0){//цикл,ходить пока есть не открытые сводоные ячейки  
		cout<<"Write position:"<<endl;
		int px,py;
		cin>>px>>py;//од игрока
		int points=turn(px-1,py-1,x,y);//функция хода
		if(points==-1){//если функция вернет -1 значит там мина
			l=false;//значение победы false, значит игрок проиграл
			break;
		}else {
			r-=points;//если функция вернет другое значение, это количество открытых ячеек за один ход
		}
		cout<<"  |";
		for(int i=1;i<=y;i++)if(i>9)cout<<i<<' ';
		else cout<<i<<"  ";
		cout<<endl;
		for(int i=0;i<=y;i++)
            cout<<"___";
		cout<<endl;
		for(int i=0;i<x;i++){
			if(i+1<10) cout<<i+1<<" |";
			else cout<<i+1<<"|";
		for(int j=0;j<y;j++){
			cout<<b[i][j]<<"  ";
		}
		cout<<endl;
	}
	}
	if(l)cout<<"You win!"<<endl;
	else cout<<"You lost!"<<endl;
	if(!l){//если игрок проиграл показать всё поле 
	cout<<"  |";
		for(int i=1;i<=y;i++)if(i>9)cout<<i<<' ';
		else cout<<i<<"  ";
		cout<<endl;
		for(int i=0;i<=y;i++)
            cout<<"___";
		cout<<endl;
		for(int i=0;i<x;i++){
			if(i+1<10) cout<<i+1<<" |";
			else cout<<i+1<<"|";
		for(int j=0;j<y;j++){
			cout<<a[i][j]<<"  ";
		}
		cout<<endl;
	}
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
