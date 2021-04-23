#include <bits/stdc++.h>
using namespace std;
class Player{//����� �����
	public:
		int points;//���������� ����� ������
		string name;//��� ������
		Player(){//����������� ��� �������� ������
			points=0;
		}
};
class Cell{//����� ������
	public:
		char thing;//��������� ������ (�����, ������, �����)
		bool opened;//��������� ������, ��������� �� ��� ������
	Cell(){//����������� ��� �������� ������
		thing=' ';
		opened=false;
	}
	int open(){//������� ������ ������ ��� ����, ����� ������� ������, ���������� �����
		if(thing=='X')return -1;//���� ��� ���� �� ����� -1
		if(opened)return 0;//���� ������ �� ����� ��� ���� ������� �� �� ����� 0
		opened=true;//���� ������ �� ����� �� ��������� �� �������� opened=true � ����� 1
		return 1;
	}
};
class Game{
	public:
		char b[100][100];//������ �������� ��� ������ �� ����� �������� ������
		Cell c[100][100];//������ �����
		int rows;//���������� ������ 
		int columns;//���������� ��������
		int minenumber;//���������� ���
		Game(int x,int y,int number){//�����������, ������� ������ ������ Game ���� x �� y, number ���������� ���
			rows=x;
			columns=y;
			minenumber=number;
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){//���������� ������ ������ � ������ ? ��� ������ �� �����
					b[i][j]='?';
				}
			}
			srand (time(NULL));//����� ��� ����������
			for(int i=0;i<number;i++){//���� ��� ����, ����� ��������� �������� ����
			int k=rand()%x;//������ ���������� k ��������� �������� �� 0 �� �-1
			int l=rand()%y;//������ ���������� l ��������� �������� �� 0 �� y-1
			while(c[k][l].thing=='X'){//���� �� �������� ��������� ������ ��� ���� ����, ����� �������� �������� ���� �� ����� ������� ������
				k=rand()%x;
				l=rand()%y;
			}
			c[k][l].thing='X';
		}
		for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){//���� ����� ���������� ��� ������ �� ����
			if(c[i][j].thing!='X'){//���� �� ������ ��� ����, ���� ���������� ���������� ��� ������
				int q=0;//���������� ��� ������ 
				for(int k=i-1;k<i+2;k++){
					for(int h=j-1;h<j+2;h++){//���� ��� ���� ����� ���������� ��� ������ ������ ������ (i,j)
						if(k>=0&&h>=0&&k<x&&h<y&&c[k][h].thing=='X'){//���� ������ �� ������� �� ����� ����(�������) � �� ��� ���������� ���� ����������� q
							q++;
						}
					}
				}
				if(q>0){//���� ���� ����, ������ �������� �[i][j].thing ���������� ���
					char qw='0'+q;
					c[i][j].thing=qw;
				}
			}
		}
	}
	}	
		int clear(int px,int py,int x,int y){//������� � ������ Game ��� ����, ����� ������� ��� �������� ������ ������ ������ ������ 
			if(c[px][py].opened)return 0;//���� ������ ��� �� ����� ������� ������� ����� 0
			int points=0;
			points+=c[px][py].open();//������� ������
			b[px][py]=c[px][py].thing;//������� ������ ������ �� �����
			for(int i=px-1;i<px+2;i++){
				for(int j=py-1;j<py+2;j++){//���������� ��� ������ ������ ��������
					if(i>=0&&j>=0&&i<x&&j<y){
						if(c[i][j].thing==' ')points+=clear(i,j,x,y);//���� �������� ������ �����, �� ����� �������� ��������� � � � ������� ����
						else points+=c[i][j].open();//���� ������ �����, �� ��������� ������ ���� ������
						b[i][j]=c[i][j].thing;//������� ������ ������ �� �����
					}
				}
			}
			return points;//
		}
		int turn(int px,int py,int x,int y){//������� � ������ Game ��� ����
			if(px>=0&&py>=0&&px<x&&py<y){//���� ���������� �� ������� �� ����� �� �� ��������� ��
				if(c[px][py].opened){//���� ������ ��� �� ����� ���� ������� ���������� 0 � ������� ��������� �����
					cout<<"Please choose free cell!"<<endl;
					return 0;
				}
				if(c[px][py].thing==' '){//���� ������ ����� ������� ��� �������� ������ ������ ������ ������
					return clear(px,py,x,y);
				}else {//���� ������ ����� ��������� ��� � ��������� ������ ������ �� �����
					b[px][py]=c[px][py].thing;
					return c[px][py].open();
				}
			}else{//���� ���������� ������� �� �����, �� �� ���������� 0 � ������� ��������� ����� 
				cout<<"Please choose correct position!"<<endl;
				return 0;
			}
		}
		void show(){//������� � ������ Game ��� ������ ���� �� �����
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
void playgame(int x,int y,int number){//������� ��� ������� ����, � �������� ���� x � y, � ���������� ���
	Player a[2];//������� ���� �������
	cout<<"Please write players name:"<<endl<<"First player:";
	cin>>a[0].name;
	cout<<"Second player:";
	cin>>a[1].name;
	cout<<a[0].name<<": "<<a[0].points<<endl;
	cout<<a[1].name<<": "<<a[1].points<<endl;
	Game currentgame(x,y,number);//������� ����
	int turnsid=0;//id ������ � �������� ���
	bool l=true;//���������� ������, ���� ����� ����� true, ������ ������ �������� 
	int r=x*y-number;//���������� ����������� �����
	currentgame.show();//�������, ������� ������� �� ����� ����
	while(r>0){//����,������ ���� ���� �� �������� �������� ������ 
		cout<<"It is "<<a[turnsid].name<<"'s turn."<<endl;
		cout<<"Write position:"<<endl;
		int px,py;
		cin>>px>>py;//��� ������
		int points=currentgame.turn(px-1,py-1,x,y);//������� ����
		if(points==-1){//���� ������� ������ -1 ������ ��� ����
			l=false;//�������� ������ false, ������ ������ ���������
			break;
		}else {
			r-=points;//���� ������� ������ ������ ��������, ��� ���������� �������� ����� �� ���� ���
			a[turnsid].points+=points;//��������� �������� ������ ����
		}	
		cout<<a[0].name<<": "<<a[0].points<<endl;
		cout<<a[1].name<<": "<<a[1].points<<endl;
		currentgame.show();
		if(points!=0)turnsid=1-turnsid;//���� points �� ����� 0, �� ���� ����� ������ ������ ���� ������
		}
	cout<<"Game over!"<<endl;
	cout<<a[0].name<<": "<<a[0].points<<endl;
	cout<<a[1].name<<": "<<a[1].points<<endl;
	if(a[0].points>a[1].points)cout<<a[0].name<<" is winner!"<<endl;//���� � ������� ������ ������ �����, �� �� �������
	else{
		if(a[1].points>a[0].points)cout<<a[1].name<<" is winner!"<<endl;//���� � ������� ������ ������ �����, �� �� �������
		else cout<<"Friendship is best thing"<<endl;//���� ������ ���������� �����, �� �����
	}
}
int main(){
	int n;
	cout<<"Enter 1 in order to play or another button to close the game:";
	cin>>n;
	while(n==1){//����� ��� ���� ����� ���� ������������, ���� �� �� ������ �����������
		int x,y;
		cout<<"Please, choose the size of the table in the range(1,100):"<<endl<<"x=";
		cin>>x;
		cout<<"y=";
		cin>>y;
		while(x<1||x>100||y<1||y>100){//���� ����� ����� ������ ������ � ������� ����, ���� �� ���� ���������� ������
			cout<<"Choose the correct values:"<<endl<<"x=";
			cin>>x;
			cout<<"y=";
			cin>>y;
		}
		cout<<"Please, choose the number of mines in the range(1,"<<x*y<<"):"<<endl;
		int number;
		cin>>number;
		while(number<1||number>x*y){// ���� ���� ����� ������ ������ � ���������� ���, ���� �� ������ ���������� ���������� ��� 
			cout<<"Choose the correct value:";
			cin>>number;
		}
		playgame(x,y,number);//������� ��� ������ ����
		cout<<"Enter 1 in order to play or another button to close the game:";
		cin>>n;
	}
}
