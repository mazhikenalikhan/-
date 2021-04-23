#include <bits/stdc++.h>
using namespace std;
char a[100][100];
char b[100][100];
int clear(int px,int py,int x,int y){//������� ��� ����, ����� ������� �� �������� ������ ������ ���������
	if(b[px][py]==a[px][py])return 0;//���� ��� �� ����� ���� ������� ������ �� ������� � ������� 0
	b[px][py]=a[px][py];
	int points=1;
	if(a[px][py]==' '){//���� ������ ������, �� ������ ������ ��� ��� � ����� ������� �������� ������ 
		if(px-1>=0){//���� �������� ������ �� ������� �� ����� ����, ������� �������� ������
			points+=clear(px-1,py,x,y);//���������� ��������� ������
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
	return points;//������� ����� ���������� �������� �����
}
int turn(int px,int py,int x,int y){//������� ���� �� ������ px, py �� ���� x �� y
	if(px>=0&&py>=0&&px<x&&py<y){//��� ������ �� �������� �� ����� ����(�������)
		if(a[px][py]=='X'){//���� �� ������ ����, ������� -1
			return -1;
		}else if(a[px][py]==b[px][py]){//���� �� ������� ��� ������ �� �����, �� ������ �� ����� � �� ������� 0, ������ ��� �� �� ��������� �� ����� ����� ������
			cout<<"Please, choose a position that doesn't taken:"<<endl;
			return 0;
		}else if(a[px][py]==' '){//���� ������ ������, �� ������ ������ ��� ��� � ����� ������� �������� ������ 
			int points=1;
			b[px][py]=a[px][py];//������� ������
			if(px-1>=0){//���� �������� ������ �� ������� �� ����� ����, ������� �������� ������
				points+=clear(px-1,py,x,y);//�������� � ����� ���������� �������� �����, ���������� �������� ����� �� ��� �� �������� ������
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
			return points;//������� ����� ��������� �������� ����� 
		}else {//���� �� ������ ������ �����, ������� ������ ��� � ������� 1  
			b[px][py]=a[px][py];
			return 1;
		}
	}else {
		cout<<"Please, choose correct position:"<<endl;
		return 0;
	}
}
void playgame(int x,int y,int number){//������� ��� ������� ����, � �������� ���� x � y, � ���������� ���
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			b[i][j]='?';//���������� ������ ���������� ������ �� �����, ���� ��� �� �������, �� �� �� ��������� ����� ���������� ?, ���� ������� ������ �� �� �������� �������� �� ������� �
			a[i][j]=' ';//���������� ������ ���������� ��� ���������� �� ������, � ��� ����, ������  ������ ��� ������ ��� ���, ����� ������� ���������� ��� ������ ������
		}
	}
	srand (time(NULL));//����� ��� ����������
	for(int i=0;i<number;i++){//���� ��� ����, ����� ��������� �������� ����
		int k=rand()%x;//������ ���������� k ��������� �������� �� 0 �� �-1
		int l=rand()%y;//������ ���������� l ��������� �������� �� 0 �� y-1
		while(a[k][l]=='X'){//���� �� �������� ��������� ������ ��� ���� ����, ����� �������� �������� ���� �� ����� ������� ������
			k=rand()%x;
			l=rand()%y;
		}
		a[k][l]='X';
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){//���� ����� ���������� ��� ������ �� ����
			if(a[i][j]!='X'){//���� �� ������ ��� ����, ���� ���������� ���������� ��� ������
				int q=0;//���������� ��� ������ 
				for(int k=i-1;k<i+2;k++){
					for(int h=j-1;h<j+2;h++){//���� ��� ���� ����� ���������� ��� ������ ������ ������ (i,j)
						if(k>=0&&h>=0&&k<x&&h<y&&a[k][h]=='X'){//���� ������ �� ������� �� ����� ����(�������) � �� ��� ���������� ���� ����������� q
							q++;
						}
					}
				}
				if(q>0){//���� ���� ����, ������ �������� a[i][j] ���������� ���
					char c='0'+q;
					a[i][j]=c;
				}
			}
		}
	}
	bool l=true;//���������� ������, ���� ����� ����� true, ������ ����� ������� 
	int r=x*y-number;//���������� ����������� �����
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
	while(r>0){//����,������ ���� ���� �� �������� �������� ������  
		cout<<"Write position:"<<endl;
		int px,py;
		cin>>px>>py;//�� ������
		int points=turn(px-1,py-1,x,y);//������� ����
		if(points==-1){//���� ������� ������ -1 ������ ��� ����
			l=false;//�������� ������ false, ������ ����� ��������
			break;
		}else {
			r-=points;//���� ������� ������ ������ ��������, ��� ���������� �������� ����� �� ���� ���
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
	if(!l){//���� ����� �������� �������� �� ���� 
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
