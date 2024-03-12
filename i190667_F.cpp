/*Abdullah Khalid
19I-0667
PF-F
semester project.
*/
#include<iostream>
#include<fstream>
using namespace std;
void readfile(int &, int &, int[20][20], int[100][2]);
void neighbour(int &,int, int[20][20], int[100][2], int[300][2]);
void display(int[20][20]);
void secondary(int &, int[20][20], int[100][2]);
void liveNei(int &,int &,int[20][20],int [100][2],int [300][2]);
void clearNei(int &,int [300][2]);
void gridUpdate(int,int [20][20],int [100][2]);
bool Dub(int [300][2],int,int,int);
void fileWrite(int [100][2],int,int);
bool checkLive(int [20][20],int,int);
bool checkDead(int [20][20],int,int);
void start ();

int main()
{
start();
return 0;
}

void start()//function for starting the game as per requirements.
{
	int gen = 0;//variable for storing the iterations entered by the user
	int noCells = 0;//for storing the count of cells of secondary array
	int noNei=0;//for storing the count of cells of neighbourhood array
	int grid[20][20] = { 0 };
	int sec[100][2] = { 0 };
	int nei[300][2] = { 0 };

	readfile(gen, noCells, grid, sec);
	cout<<"\nGeneration count:"<<0<<endl;
	display(grid);
	cout<<"Secondary array after the current generation:\n";
	for(int i=0;i<noCells;i++)
	{
		cout<<sec[i][0]<<"__"<<sec[i][1]<<endl;
	}
	cout<<"_______________________________________________\n\n";
	for(int i=0;i<gen;i++)
	{
		cout<<"\nGeneration count:"<<i+1<<endl;
		neighbour(noNei,noCells, grid, sec, nei);
		secondary(noCells, grid, sec);
		liveNei(noCells,noNei,grid,sec,nei);
		gridUpdate(noCells,grid,sec);
		clearNei(noNei,nei);
		display(grid);
		cout<<"Secondary array after the current generation:\n";
		for(int i=0;i<noCells;i++)
		{
			cout<<sec[i][0]<<"__"<<sec[i][1]<<endl;
		}
		cout<<"_______________________________________________\n\n";
	}
	fileWrite(sec,gen,noCells);
}

void readfile(int &g, int &n, int a[20][20], int b[100][2]) //start of the game(coordinates entered by user are put to sec array)
{
int check=0;
int x=0,y=0;
string fileName;
	while(check!=1)//checks whether the name of file entered exists or not
	{
		cout<<"Please enter the name of file from which you have to read the data:\n";
		cout<<"For instance:\"input.txt(You have to give file name with its type)\"\n";
		getline(cin,fileName);

			ifstream takeInput;
			takeInput.open(fileName);
			
			if(takeInput)
			{
				cout << "Taking the no of generations from the file.-DONE\n";
				takeInput >> g;
				cout << "Taking the no of cells which user want to read.-DONE\n";
				takeInput >> n;
				cout<< "Now taking the coordiantes from the file which the user wants to become live:\n";

				for (int i = 0; i < n; i++)//the coordinates entered in file are put to the array initially
				{
					takeInput >> x;
					takeInput >> y;
					b[i][0] = x;
					b[i][1] = y;
					a[x][y] = 1;
				}
				takeInput.close();
				check=1;
			}
			else//give error if name of file is not correct
			{
				cout<<"error-no such file present!!!\n\a";
				cout<<"Please re-enter the filename!!!\n\n\n\a";
			}
	}

}

bool Dub(int arr[300][2], int x, int y,int c)//function for checking duplication in neighbour array
{
	for (int i=0 ;i < c; i++){
		if(arr[i][0] == x && arr[i][1] == y)
		{
			return true;
		}
	}
	return false;
}

void neighbour(int &m,int n, int a[20][20], int b[100][2], int c[300][2]) //function for determining the dead neighbours of live cells
{
	int x = 0;
	int y = 0;
	int z = 0;

	for (int i = 0; i < n; i++) {
		x = b[i][0];
		y = b[i][1];
		for (int i = x - 1; i <= x + 1; i++)//loops for count of neighbours
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (i >= 0 && i < 20 && j >= 0 && j < 20) //check for the boundary of grid while determining neighbours
				{
					if (checkDead(a,i,j)) //check for the dead neighbbour
					{
						if (i != x || j != y)
						{//neighbours are being added to array
							if(z==0)
							{
								c[z][0] = i;
								c[z][1] = j;
								z++;
							}
							else
							{
								if(!(Dub( c, i,j,z)))
								{
									c[z][0] = i;
									c[z][1] = j;
									z++;
								}
							}
						}
					}
				}
			}
		}
	}
	m=z;//m is the counter for the number of dead neighbours that are added in the neighbour array in current cycle
}

void display(int a[20][20]) //displaying the grid
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
}

bool checkLive(int a[20][20],int b,int c)//function for checking dead naighbour 
{
	if(a[b][c]==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void secondary(int &n, int a[20][20], int b[100][2])//function for checking secondary array
{
	int N = n;
	int x = 0;
	int y = 0;
	int count = 0;//this count counts the no of live neighbours of current coordinate 
	for (int i = 0; i < N; i++)
	{
		x = b[i][0];
		y = b[i][1];
		for (int j = x - 1; j <= x + 1; j++) 
		{
			for (int k = y - 1; k <= y + 1; k++)
			{
				if(j >= 0 && j < 20 && k >= 0 && k < 20)//check for the boundary of grid while determining neighbours
				{
					if(checkLive(a,j,k))//neighbours are being checked live or dead
					{
						if(j != x || k != y)
						{
							count++;
						}
					}
				}
			}
		}
		if (!(count == 2 || count == 3))//rules are being applied as per requirements
		{
			b[i][0] = -1;
			b[i][1] = -1;
			n--;
		}
		count = 0;
	}
	for (int i = 99; i >= 0; i--) //secondary array coordinates which become dead are removed and array is shifted right to left
	{
		if (b[i][0] == -1 && b[i][1] == -1)
		{
			for (int l = i; l < 100; l++) 
			{
				b[l][0] = b[l + 1][0];
				b[l][1] = b[l + 1][1];
			}
		}
	}
}

void liveNei(int &a,int &b,int c[20][20],int d[100][2],int e[300][2])
{
/*in this porion of code,
when neighbour array got filled,the function checks whther the neighbour 
become live or dead in the next generation.
if neighbour become live it is put to secondary array linearly. 
*/
int count=0;//this count counts the no of live neighbours of current coordinate.
int x=0;
int y=0;
	for(int i=0;i<b;i++)
	{
		x=e[i][0];
		y=e[i][1];
		for(int j=x-1;j<=x+1;j++)
		{
			for(int k=y-1;k<=y+1;k++)
			{
				if(j >= 0 && j < 20 && k >= 0 && k < 20)//check for the boundary of grid while determining neighbours
				{
					if(j!=x || k!=y)
					{
						if(checkLive(c,j,k))//neighbours are being checked live or dead
						{
							count++;
						}
					}
				}
			}
		}
		if(count==3)//rules applied(if exactly "3" live neighbours found then it will become live next generation)
		{
			d[a][0]=x;
			d[a][1]=y;
			a++;
		}
	count=0;
	}
}

void clearNei(int &b,int a[300][2])//this functions formats the neighbour array when its work is done
{
b=0;
	for(int i=0;i<300;i++)
	{
		a[i][0]=0;
		a[i][1]=0;
	}
}

void gridUpdate(int a,int b[20][20],int c[100][2])//function for grid upgradation
{
int x=0;
int y=0;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			b[i][j]=0;
		}
	}
	for(int j=0;j<a;j++)//the coordinates which will live next are made live by this function
	{
		x=c[j][0];
		y=c[j][1];
		b[x][y]=1;
	}
}

void fileWrite(int a[100][2],int b,int c)//function for writing the coordinates to the file
{
ofstream recieveOutput;
recieveOutput.open("output.txt");
			
	recieveOutput<<b<<endl;
	recieveOutput<<c<<endl;
		for(int i=0;i<c;i++)
		{
			recieveOutput<<a[i][0];
			recieveOutput<<" ";
			recieveOutput<<a[i][1]<<endl;
		}
	
recieveOutput.close();
cout<<"Done wrting to the file\n";
}

bool checkDead(int a[20][20],int b,int c)//this function check for the dead neighbourhood when called
{
	if(a[b][c]==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
