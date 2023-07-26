/** This C++ program appears to be a simple graphics library for creating and manipulating
 * basic geometric shapes such as points, lines, circles, arcs, and triangles on a 2D grid.
 * It also provides functionality for saving the current state of the grid to a file. */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class ecran{
char **obl;
int x,y;
public:
ecran(int x1,int y1){
x=x1;y=y1;
if ((x1==0)||(y1==0))obl=0;
	else
	{
		obl=new char *[x];
	for (int i = 0; i < x; i++) {
		obl[i] = new char[y];
		
	}clrscr();}}

~ecran(){for (int i = 0; i < y; i++)	
	delete []obl[i];   
	delete []obl;
	}
void set_point(int x1,int y1,char c1){if ((x1<x)&&(y1<y)&&(x1>=0)&&(y1>=0))obl[x1][y1]=c1;}
void out(){for(int i=0;i<y;i++){for(int j=0;j<x;j++)cout<<obl[j][i];cout<<'|'<<endl;} }
void out_koord(){for(int i=0;i<x;i++) if(i%10==0) cout<<i/10;else cout<<" ";for(int j=1;j<y;j++) if(j%10==0) cout<<j/10<<endl;else cout<<endl;}
void save(){
cout<<"\nEnter the path and file name!\n";
char path[100];cin>>path;
ofstream fout(path);


if(!fout){cout<<"\nIt is impossible to create the file!";return;}
for(int i=0;i<y;i++){fout<<endl;for(int j=0;j<x;j++)fout<<obl[j][i];}
fout.close();}

void clrscr(){for(int k=0;k<x;k++)for(int j=0;j<y;j++){obl[k][j]=' ';}}

};


struct coord{
int x,y;
void in(string str="")
{cout<<"Enter the koords of the ";
cout<<str<<"point\n";
cin>>x;
cin>>y;}
void in(int x1,int y1)
{x=x1;y=y1;}
void out(string str=""){cout<<"\nThe coordinate of the "<<str<<"point:\n\t X="<<x<<"\n\t Y="<<y<<endl;}
};
class list;
class figure{
protected: char colour;
string name;
public:
virtual void change()=0;
virtual void print(ecran &P)=0;
virtual void infa()=0;
virtual void fill_all()=0;
virtual void unfill_all()=0;
virtual void inverse()=0;
virtual void turn(coord turn,double t)=0;
virtual void shift(int x,int y)=0;
virtual void colour_ch(char t){colour=t;};
virtual list* l_get(){return 0;}
};


class point:public figure
{protected:
coord c1;
public:
point(int x1, int y1,char t){c1.in(x1,y1);colour=t;name="point";}
point(string str="")
{cout<<"\nEnter the colour\n";
cin>>colour;cout<<endl;
c1.in(str);
name="point";}
virtual void change(){
infa();int dejstvie;while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- coordinates\n\t3- the turn\n\t4- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
    case 2:cout<<"Enter the new coordinates: ";cin>>c1.x>>c1.y;cout<<endl;break;
    case 3: coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;
		turn(turn1,f); break;
    case 4:cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl; c1.x+=x; c1.y+=y;break;
    case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    
    
    }             
}
}
virtual void print(ecran &P){P.set_point(c1.x,c1.y,colour);}

virtual void infa(){cout<<"\t"<<name<<endl;
	
	cout<<"\nThe colour is: "<<colour<<endl;
	c1.out();
}
void fill_all(){}
void unfill_all(){}
void inverse(){}
virtual void turn(coord turn,double f){int xn;xn=(c1.x-turn.x)*cos(f/57.295779)-(c1.y-turn.y)*sin(f/57.295779);int yn;yn=(c1.x-turn.x)*sin(f/57.295779)+(c1.y-turn.y)*cos(f/57.295779);c1.x=xn;c1.y=yn;}
virtual void shift(int x,int y){c1.x+=x; c1.y+=y;}
};


class line:public figure{
protected:
coord c2,c1;

public:
line ()
{cout<<"\nEnter the colour\n";
cin>>colour;cout<<endl;
c1.in("first ");
c2.in("second ");
name="line";}
line(coord c1_,coord c2_,char colour_){c1=c1_;c2=c2_;colour=colour_;name="line";}
virtual void change(){infa(); 
int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- coordinates\n\t3- the turn\n\t4- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
	case 2:cout<<"Enter the new coordinates: \nFirst point: ";cin>>c1.x>>c1.y;cout<<endl<<"Second point: ";cin>>c2.x>>c2.y;cout<<endl;break;
	case 3: coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;turn(turn1,f); break;
	case 4: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;c1.x+=x;c1.y+=y;c2.x+=x;c2.y+=y;break;
	case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}}

virtual void print(ecran &P)
{if(c2.x!=c1.x)
{double k=((double)(c2.y-c1.y)/(double)(c2.x-c1.x));double b=c1.y-k*c1.x;int x_max,x_min,y_max,y_min;if(c1.x>c2.x){x_max=c1.x;x_min=c2.x;}else{x_max=c2.x;x_min=c1.x;} if(c1.y>c2.y){y_max=c1.y;y_min=c2.y;}else{y_max=c2.y;y_min=c1.y;}for(float p=x_min;p<=x_max;p+=0.01)for(float q=y_min;q<=y_max;q+=0.01){//if((q>b+k*p-2)&&(q<b+k*p+2)) 
if((int)q==(int)(b+k*p))
P.set_point(p,q,colour);}}

else {int y_max,y_min;if(c1.y>c2.y){y_max=c1.y;y_min=c2.y;}else{y_max=c2.y;y_min=c1.y;}for(int z=y_min;z<=y_max;z++)P.set_point(c2.x,z,colour);}   }

virtual void infa(){cout<<"\t"<<name<<endl;cout<<"\nThe colour is: "<<colour<<endl;c1.out("first ");c2.out("second ");}

void fill_all(){}
void unfill_all(){}
void inverse(){}
virtual void turn(coord turn,double f){int xn,yn;xn=(c1.x-turn.x)*cos(f/57.295779)-(c1.y-turn.y)*sin(f/57.295779);yn=(c1.x-turn.x)*sin(f/57.295779)+(c1.y-turn.y)*cos(f/57.295779);c1.x=xn;c1.y=yn;xn=(c2.x-turn.x)*cos(f/57.295779)-(c2.y-turn.y)*sin(f/57.295779);yn=(c2.x-turn.x)*sin(f/57.295779)+(c2.y-turn.y)*cos(f/57.295779);c2.x=xn;c2.y=yn;};
void shift(int x,int y){c1.x+=x; c1.y+=y;c2.x+=x; c2.y+=y;}

};

class circle:public figure{
protected:
unsigned int rad;
coord centr;

bool inter_p;
void fill(){cout<<"\nFill the circle? 0- not to fill   1- to fill\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;inter_p=dejstvie;}
public: 
circle(){name="circle";centr.in("centr ");cout<<"\nEnter radius\n";cin>>rad;cout<<"\nEnter colour\n";cin>>colour;fill();}
void change(){infa();int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- center\n\t3- radious\n\t4- paint inside\n\t5- the turn\n\t6- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
  case 2:cout<<"Enter the new center: \n";cin>>centr.x>>centr.y;cout<<endl;break;
  case 3:cout<<"Enter the radious:\n";cin>>rad;break;
  case 4:fill();break;
  case 5: coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;turn(turn1,f); break;
  case 6: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;centr.x+=x;centr.y+=y;break;
   case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}}

void print(ecran &P){int x_max,x_min,y_max,y_min;x_max=centr.x+rad;x_min=centr.x-rad;y_max=centr.y+rad;y_min=centr.y-rad;
for(float i=x_min;i<=x_max;i+=0.05)for(float j=y_min;j<=y_max;j+=0.05){if(rad*rad==(int)((centr.x-i)*(centr.x-i)+(centr.y-j)*(centr.y-j)))P.set_point(i,j,colour);if(inter_p){if(rad*rad>((centr.x-i)*(centr.x-i)+(centr.y-j)*(centr.y-j)))P.set_point(i,j,colour);}
}}
virtual void infa(){cout<<"\t"<<name<<endl;cout<<"The colour is: "<<colour<<endl;centr.out();cout<<"The radius is: "<<rad<<endl<<"Painted inside: "<<inter_p<<endl;}

void fill_all(){inter_p=1;}
void unfill_all(){inter_p=0;}
virtual void turn(coord turn,double f){int xn;xn=(centr.x-turn.x)*cos(f/57.295779)-(centr.y-turn.y)*sin(f/57.295779);int yn;yn=(centr.x-turn.x)*sin(f/57.295779)+(centr.y-turn.y)*cos(f/57.295779);centr.x=xn;centr.y=yn;}
void inverse(){inter_p=!inter_p;}
void shift(int x,int y){centr.x+=x; centr.y+=y;}



};

class arc:public circle{
protected:
double f1,f2;
bool line_vis;
void border(){cout<<"\nMake the border lines visible? 0- not to make   1- make\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;line_vis=dejstvie;}
void angles_in(){
cout<<"Enter the first angle: \n";cin>>f1; while((f1<-360)||(f1>360)){cout<<"\nThe first angle should be betweeo -360 and 360 degrees!\n";cin>>f1;}  cout<<endl<<"Enter the second angle: \n";cin>>f2;while((f1>f2)||(f2>360)){cout<<"\nThe second angle should be no less than the first angle and not more than 360 degrees!\n";cin>>f2;}cout<<endl;
}
public: 
arc():circle(){name="arc";angles_in();cout<<"\nMake the border lines visible? 0- not to make   1- to make\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;line_vis=dejstvie;}
void change(){infa();int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- center\n\t3- radious\n\t4- paint inside\n\t5- angels\n\t6- borders\n\t7- the turn\n\t8- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
  case 2:cout<<"Enter the new center: \n";cin>>centr.x>>centr.y;cout<<endl;break;
  case 3:cout<<"Enter the radious:\n";cin>>rad;break;
  case 4:fill();break;
  case 5:angles_in();break;
  case 6:border();break;
  case 7: coord turn1;turn1.in("turn ");
	  double f;cout<<"Enter the angle\n";cin>>f;
	  cout<<endl;turn(turn1,f); break;
  case 8: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;centr.x+=x;centr.y+=y;break;
   case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}}

virtual void print(ecran &P){
coord cl1,cl2;
cl1.x=(rad*cos(f1/57.295779)+centr.x);
cl1.y=(rad*sin(f1/57.295779)+centr.y);//peresec 1 go ygla
cl2.x=(rad*cos(f2/57.295779)+centr.x);
cl2.y=(rad*sin(f2/57.295779)+centr.y);//peresec 2go ygla
line l1(centr,cl1,colour),l2(centr,cl2,colour);

if (line_vis)
{l1.print(P);
l2.print(P);}

double k1=tan(f1/57.295779),k2=tan(f2/57.295779);

int x_max,x_min,y_max,y_min;
//x_max=(cl1.x<cl2.x)?cl1.x:cl2.x;if(centr.x>x_max)x_max=centr.x;
//x_min=(cl1.x>cl2.x)?cl1.x:cl2.x;if(centr.x<x_min)x_min=centr.x;
//y_max=(cl1.y<cl2.y)?cl1.y:cl2.y;if(centr.y>y_max)y_max=centr.y;
//y_min=(cl1.y>cl2.y)?cl1.y:cl2.y;if(centr.y<y_min)y_min=centr.y;

x_max=centr.x+rad;x_min=centr.x-rad;y_max=centr.y+rad;y_min=centr.y-rad;

float b1=centr.y-k1*centr.x,b2=centr.y-k2*centr.x;
for(float i=x_min;i<=x_max;i+=0.05)for(float j=y_min;j<=y_max;j+=0.05){
if(rad*rad==(int)((centr.x-i)*(centr.x-i)+(centr.y-j)*(centr.y-j)))
P.set_point(i,j,colour);

if((cl1.x>=centr.x)&&(cl1.y>=centr.y)&&(cl2.x>=centr.x)&&cl2.y>=centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
if((cl1.x>=centr.x)&&(cl1.y>=centr.y)&&(cl2.x>=centr.x)&&cl2.y<=centr.y){if((j>(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if((cl1.x>=centr.x)&&(cl1.y>=centr.y)&&(cl2.x<centr.x)&&cl2.y>centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if((cl1.x>=centr.x)&&(cl1.y>=centr.y)&&(cl2.x<centr.x)&&cl2.y<centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}

//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y>=centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y<=centr.y){if((j>(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y>centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y<centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}

//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y>=centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y<=centr.y){if((j>(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y>centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y<centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}

//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y>=centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x>=centr.x&&cl2.y<=centr.y){if((j>(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y>centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}
//if(cl1.x>=centr.x&&cl1.y>=centr.y&&cl2.x<centr.x&&cl2.y<centr.y){if((j<(k2*i+b2))&&(j>(k1*i+b1)))P.set_point(i,j,colour);}

}

}

virtual void infa(){cout<<"\t"<<name<<endl;cout<<"The colour is: "<<colour<<endl;centr.out();cout<<"The radius is: "<<rad<<endl<<"Painted inside: "<<inter_p<<endl<<"The first angle: "<<f1<<endl<<"The second angle: "<<f2<<endl;}
};    

class triangle:public figure{
protected:

float Sq(){float p,a,b,c;
a=sqrt((c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y));
b=sqrt((c1.x-c3.x)*(c1.x-c3.x)+(c1.y-c3.y)*(c1.y-c3.y));
c=sqrt((c3.x-c2.x)*(c3.x-c2.x)+(c3.y-c2.y)*(c3.y-c2.y));
p=(a+b+c)/2;
return sqrt(p*(p-a)*(p-b)*(p-c));}


void fill(){cout<<"\nFill the triangle? 0- not to fill   1- to fill\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;inter_p=dejstvie;}
bool inter_p;

coord c3,c1,c2;
public:
triangle(){ 
	cout<<"\nEnter the colour\n";
cin>>colour;cout<<endl;
c1.in("first ");
c2.in("second ");
	name="triangle";
c3.in("third ");
fill();
} 
triangle(coord c1_,coord c2_,coord c3_,char colour1){colour=colour1;c1=c1_;c2=c2_;c3=c3_;inter_p=1;}
void change(){infa(); 
int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- coordinates\n\t3- paint inside \n\t4- the turn\n\t5- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
  case 2:cout<<"Enter the new coordinates: \nFirst point: ";cin>>c1.x>>c1.y;cout<<endl<<"Second point: ";cin>>c2.x>>c2.y;cout<<endl<<"Therd point: ";cin>>c3.x>>c3.y;cout<<endl;break;
  case 3:fill();break;
  case 4:  coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;turn(turn1,f); break;
  case 5: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;c1.x+=x;c1.y+=y;c2.x+=x;c2.y+=y;c3.x+=x;c3.y+=y;break;
   case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}}
    
void print(ecran &P){line a(c1,c2,colour),b(c1,c3,colour),c(c3,c2,colour);a.print(P);b.print(P);c.print(P);//(x1>x2)?x1:x2
if(inter_p){int x_max,x_min,y_max,y_min;
x_max=(c1.x>c2.x)?c1.x:c2.x;if(c3.x>x_max) x_max=c3.x;   
x_min=(c1.x<c2.x)?c1.x:c2.x;if(c3.x<x_min) x_min=c3.x;
y_max=(c1.y>c2.y)?c1.y:c2.y;if(c3.y>y_max) y_max=c3.y;   
y_min=(c1.y<c2.y)?c1.y:c2.y;if(c3.y<y_min) y_min=c3.y;
float S;

S=Sq();
for(int i=x_min;i<=x_max;i++)for(int j=y_min;j<=y_max;j++){
coord n;n.x=i;n.y=j;
triangle p1(c1,c2,n,colour),p2(c1,c3,n,colour),p3(c2,c3,n,colour);
if(S>=(p1.Sq()+p2.Sq()+p3.Sq()-0.7))P.set_point(i,j,colour);

}
}}
virtual void infa(){cout<<"\t"<<name<<endl;cout<<"The the colour is: "<<colour<<endl;c1.out("first ");c2.out("second ");c3.out("thierd ");cout<<"Painted inside: "<<inter_p<<endl;}
void fill_all(){inter_p=1;}
void unfill_all(){inter_p=0;}
void inverse(){inter_p=!inter_p;}
void turn(coord turn,double f){int xn,yn;
xn=(c1.x-turn.x)*cos(f/57.295779)-(c1.y-turn.y)*sin(f/57.295779);
yn=(c1.x-turn.x)*sin(f/57.295779)+(c1.y-turn.y)*cos(f/57.295779);c1.x=xn;c1.y=yn;
xn=(c2.x-turn.x)*cos(f/57.295779)-(c2.y-turn.y)*sin(f/57.295779);
yn=(c2.x-turn.x)*sin(f/57.295779)+(c2.y-turn.y)*cos(f/57.295779);c2.x=xn;c2.y=yn;
xn=(c3.x-turn.x)*cos(f/57.295779)-(c3.y-turn.y)*sin(f/57.295779);
yn=(c3.x-turn.x)*sin(f/57.295779)+(c3.y-turn.y)*cos(f/57.295779);c3.x=xn;c3.y=yn;}
void shift(int x,int y){c1.x+=x; c1.y+=y;c2.x+=x; c2.y+=y;c3.x+=x; c3.y+=y;}

};

class ellipse:public figure{
      protected:
                coord f1,f2;
                bool inter_p;
                
      float m;
      void fill(){cout<<"\nFill the elipse? 0- not to fill   1- to fill\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;inter_p=dejstvie;}
      public:
             ellipse(){name="ellpse";f1.in("first focus ");f2.in("second focus ");cout<<"\nEnter parameter\n";cin>>m;while(m*m<(f1.x-f2.x)*(f1.x-f2.x)+(f1.y-f2.y)*(f1.y-f2.y)){cout<<"\nEnter a grater number\n";cin>>m;cout<<endl;}cout<<"\nEnter colour\n";cin>>colour;fill();}
             void infa(){cout<<"\t"<<name<<endl;cout<<"The the colour is: "<<colour<<endl;f1.out("first focus ");f2.out("second focus ");cout<<"The parameter is: "<<m<<endl<<"Painted inside: "<<inter_p<<endl;}
             
virtual void change(){infa();
             int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- focus coordinates\n\t3- paint inside \n\t4- paramether\n\t5- the turn\n\t6- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
  case 2:cout<<"Enter the new coordinates: \nFirst focus: ";cin>>f1.x>>f1.y;cout<<endl<<"Second focus: ";cin>>f2.x>>f2.y;cout<<endl;if(m*m<(f1.x-f2.x)*(f1.x-f2.x)+(f1.y-f2.y)*(f1.y-f2.y))cout<<"The parameter doesn't sutes, enter a bigger one\n"; while(m*m<(f1.x-f2.x)*(f1.x-f2.x)+(f1.y-f2.y)*(f1.y-f2.y)){cout<<"\nEnter a grater number\n";cin>>m;cout<<endl;}break;
  case 3:fill();break;
  case 4:cout<<"Enter the paramether:\n";cin>>m;while(m*m<(f1.x-f2.x)*(f1.x-f2.x)+(f1.y-f2.y)*(f1.y-f2.y)){cout<<"\nEnter a grater number\n";cin>>m;cout<<endl;} break;
   case 5:coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;
	   turn(turn1,f); break;
   case 6: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;f1.x+=x;f1.y+=y;f2.x+=x;f2.y=+y;
   case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}}
             
             
             
             void print(ecran &P){
float f_max,f_min,x_max,y_max,x_min,y_min;
/// for x:

f_min=(f1.x<f2.x)?f1.x:f2.x;
f_max=(f1.x>f2.x)?f1.x:f2.x;
x_max= 1+f_max+m;
x_min= f_min-m-1;
f_min=(f1.y<f2.y)?f1.y:f2.y;
f_max=(f1.y>f2.y)?f1.y:f2.y;
y_max= 1+f_max+m;
y_min= f_min-m-1;

for(float i=x_min;i<=x_max;i+=0.1)for(float j=y_min;j<=y_max;j+=0.1){
float m1,m2,sm;
m1=sqrt((f1.x-i)*(f1.x-i)+(f1.y-j)*(f1.y-j));
if(m1>m)continue;
m2=sqrt((f2.x-i)*(f2.x-i)+(f2.y-j)*(f2.y-j));
if((sm=(m2+m1))>(m+0.3))continue;

if((int)m==(int)sm)
P.set_point(i,j,colour);
if(inter_p&&(((int)m)>((int)sm)))P.set_point(i,j,colour);
}

}
      
  void fill_all(){inter_p=1;}
void unfill_all(){inter_p=0;}
void inverse(){inter_p=!inter_p;}
void turn(coord turn,double f){int xn,yn;
xn=(f1.x-turn.x)*cos(f/57.295779)-(f1.y-turn.y)*sin(f/57.295779);
yn=(f1.x-turn.x)*sin(f/57.295779)+(f1.y-turn.y)*cos(f/57.295779);f1.x=xn;
f1.y=yn;xn=(f2.x-turn.x)*cos(f/57.295779)-(f2.y-turn.y)*sin(f/57.295779);
yn=(f2.x-turn.x)*sin(f/57.295779)+(f2.y-turn.y)*cos(f/57.295779);f2.x=xn;
f2.y=yn;}
void shift(int x,int y){f1.x+=x; f1.y+=y;f2.x+=x; f2.y+=y;}

      };
class rectangle:public figure{
      protected:

	coord c1,c2;
     float width;
	bool inter_p;
	
void fill(){cout<<"\nFill the rectangle? 0- not to fill   1- to fill\n";int dejstvie;cin>>dejstvie;while(dejstvie!=0&&dejstvie!=1){cout<<"\nChoose 0 or 1\n";cin>>dejstvie;}cout<<endl;inter_p=dejstvie;}
      public:
             rectangle(){name="rectangle";cout<<"\nEnter the middle line!\n";
c1.in("first ");
c2.in("second ");fill();cout<<"\nEnter width!\n";cin>>width;
cout<<"\nEnter colour!\n";cin>>colour;cout<<"\n";}
             void infa(){cout<<"\t"<<name<<endl;
cout<<"The the colour is: "<<colour<<endl<<"The middle line\n";c1.out("first ");c2.out("second ");cout<<"The width: \n"<<width<<endl<<"Painted inside: "<<inter_p<<endl;
}
             
             void change(){infa();
             int dejstvie;

while(1==1){cout<<"\nChoose the changes\n\t1- colour\n\t2- middle line coordinates\n\t3- paint inside \n\t4- width\n\t5- the turn\n\t6- shift for a vector\n\t0- return\n";
cin>>dejstvie;switch(dejstvie)    {
    case 1:cout<<"Enter the new colour:\n";cin>>colour;cout<<endl;break;
  case 2:cout<<"Enter the new coordinates of the middle line: \nFirst point: ";cin>>c1.x>>c1.y;cout<<endl<<"Second point: ";cin>>c2.x>>c2.y;cout<<endl;break;
  case 3:fill();break;
  case 4:cout<<"Enter the width:\n";cin>>width;break;
   case 5:coord turn1;turn1.in("turn ");double f;cout<<"Enter the angle\n";cin>>f;cout<<endl;turn(turn1,f); break;
   case 6: cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;c1.x+=x;c1.y+=y;c2.x+=x;c2.y=+y;
   case 0:return;
    default: cout<<"\nChoose the correct number\n";break;
    }}
}

             void print(ecran &P){
if(inter_p)
	{if(c1.y==c2.y)
		{int x_max=(c1.x>c2.x)?c1.x:c2.x;
		int x_min=(c1.x<c2.x)?c1.x:c2.x;
			for(int i=x_min;i<=x_max;i++)
			for(int j=c1.y-width;j<=c1.y+width;j++)
			{P.set_point(i,j,colour);}
			return;}
	if (c1.x==c2.x)
		{int y_max=(c1.y>c2.y)?c1.y:c2.y;
		int y_min=(c1.y<c2.x)?c1.y:c2.y;
			for(int i=y_min;i<=y_max;i++)
			for(int j=c1.x-width;j<=c1.x+width;j++)
			{P.set_point(j,i,colour);}
			return;}
	
		coord c1_,c2_,c3_,c4_;
		float k=(double)(c1.y-c2.y)/(double)(c1.x-c2.x);
		float p=width*sin(atan(k))/2,q=width*cos(atan(k))/2;
		c1_.x=c1.x+p;c1_.y=c1.y-q;
		c2_.x=c1.x-p;c2_.y=c1.y+q;
		c3_.x=c2.x+p;c3_.y=c2.y-q;
		c4_.x=c2.x-p;c4_.y=c2.y+q;

		triangle t1(c1_,c4_,c3_,colour),t2(c1_,c4_,c2_,colour);t1.print(P);t2.print(P);}
	else{
		if(c1.y==c2.y){
			coord c1_,c2_,c3_,c4_;c1_.x=c2_.x=c1.x;c3_.x=c4_.x=c2.x;
c1_.y=c4_.y=c1.y-width;c2_.y=c3_.y=c1.y+width;
line l1(c1_,c2_,colour),l2(c2_,c3_,colour),l3(c3_,c4_,colour),l4(c1_,c4_,colour);l1.print(P);l2.print(P);l3.print(P);l4.print(P);return;}
if (c1.x==c2.x){
coord c1_,c2_,c3_,c4_;c1_.y=c2_.y=c1.y;c3_.y=c4_.y=c2.y;
c1_.x=c4_.x=c1.x-width;c2_.x=c3_.x=c1.x+width;
line l1(c1_,c2_,colour),l2(c2_,c3_,colour),l3(c3_,c4_,colour),l4(c1_,c4_,colour);l1.print(P);l2.print(P);l3.print(P);l4.print(P);return;}
if((c1.x!=c2.x)&&(c1.y!=c2.y)){
coord c1_,c2_,c3_,c4_;
float k=(double)(c1.y-c2.y)/(double)(c1.x-c2.x);float p=width*sin(atan(k))/2,q=width*cos(atan(k))/2;
c1_.x=c1.x+p;c1_.y=c1.y-q;
c2_.x=c1.x-p;c2_.y=c1.y+q;
c3_.x=c2.x+p;c3_.y=c2.y-q;
c4_.x=c2.x-p;c4_.y=c2.y+q;
line l1(c1_,c2_,colour),l2(c2_,c4_,colour),l3(c3_,c4_,colour),l4(c1_,c3_,colour);l1.print(P);l2.print(P);l3.print(P);l4.print(P);}
}


}
    void fill_all(){inter_p=1;}
void unfill_all(){inter_p=0;}
void inverse(){inter_p=!inter_p;}
  void turn(coord turn,double f){int xn,yn;xn=(c1.x-turn.x)*cos(f/57.295779)-(c1.y-turn.y)*sin(f/57.295779);
yn=(c1.x-turn.x)*sin(f/57.295779)+(c1.y-turn.y)*cos(f/57.295779);
c1.x=xn;c1.y=yn;xn=(c2.x-turn.x)*cos(f/57.295779)-(c2.y-turn.y)*sin(f/57.295779);
yn=(c2.x-turn.x)*sin(f/57.295779)+(c2.y-turn.y)*cos(f/57.295779);
c2.x=xn;c2.y=yn;};
void shift(int x,int y){c1.x+=x; c1.y+=y;c2.x+=x; c2.y+=y;}
      
      };

class list{

protected:
list *next;
figure *fig;
int number;
public:

list();
list(figure *t);
list *find_num(int num);
list *find_end();
void add();
void add(figure *t);
	
	figure *delete_l(int j);
void change();

void out();
void out(ecran &P);
void fill_all();
void unfill_all();
void inv_all();
void turn_all(coord,float);
void ch_colour_all(char r);
void shift_all(int,int);
~list(){if(fig!=0)delete fig;if (next!=0)next->~list();}










};

class complex_fig:public figure{

list l;

public:
list *l_get(){return &l;}
void change(){{int dejstvie;
while(1==1){
cout<<"\nChoose the action:\n1- Add figures \n2- Figures included \n3- Delete a figure\n4- Change the colour \n5- Fill\n6- Unfill\n7- Inverse\n8- Shift\n9- Turn figures\n10- Change a conrete figure\n \n0- Return\n"; 
cin>>dejstvie;
switch(dejstvie){

case 1:add();break;
case 2:infa();;break;
case 3:int j;cout<<"\nEnter figure to delete!\n";
		cin>>j;l.delete_l(j);break;
case 4:char c;cout<<"\nEnter the colour\n";cin>>c; l.ch_colour_all(c);break;
case 5:l.fill_all();break;
case 6:l.unfill_all();break;
case 7:l.inv_all();break;
case 8:cout<<"Enter vector\n";int x,y;cin>>x>>y;cout<<endl;l.shift_all(x,y);break;
case 9:coord cc;cc.in("turn ");cout<<"\nEnter the angle\n";float f;cin>>f; l.turn_all(cc,f); break;
case 10:l.change(); break;

case 0:return;

default:cout<<"\nChoose the right number\n";break;}}}}

void add(){l.add();}
void add(figure *t){}
complex_fig();
void print(ecran &P){l.out(P);}
void infa(){cout<<"\ncomplex figure\n";l.out();}
void colour_ch(char c){l.ch_colour_all(c);}
void fill_all(){l.fill_all();}
void unfill_all(){l.unfill_all();}
void inverse(){l.inv_all();}

void turn(coord turn,double f){l.turn_all(turn,f);}
void shift(int x,int y){l.shift_all(x,y);}
};



list::list(){next=0;fig=0;number=0;}
list::list(figure *t){next=0;fig=t;}
list *list::find_num(int num){list *t;t=this;while(t!=0){if(t->number==num)return t;t=t->next;} return t;}
list *list::find_end(){list *t;t=this;while(t->next!=0) t=t->next;return t;}
void list::add()
	{list *t; t=find_end();
	int dejstvie;
	cout<<"\nInsert:\n\t1- point\n\t2- line\n\t3- triangle\n\t4- circle\n\t5- arc\n\t6- rectangle\n\t7- ellipse\n\t8- complex figure\n\t0- cancel\n";
while(1==1){
cin>>dejstvie;
switch(dejstvie){
case 1:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new point();return;
case 2:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new line();return;
case 3:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new triangle();return;
case 4:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new circle();return;
case 5:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new arc();return;
case 6:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new rectangle();return;
case 7:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new ellipse();return;
case 8:t->next=new list();t->next->number=(t->number)+1;t=t->next;t->fig=new complex_fig();return;

case 0:return;

default:cout<<"\nChoose the right number\n";break;}
}
	}
void list:: add(figure *t){list *tt;
tt=find_end();
tt->next=new list(t);
tt->next->number=tt->number+1;}
	
figure* list:: delete_l(int j){list *n,*temp;
		if((temp=find_num(j-1))==0)
		{cout<<"\nNo such a figure\n";return 0;}if(temp->next==0){cout<<"\nNo such a figure\n";return 0;}n=temp->next->next;
		temp->next->next=0;
		figure *t=temp->next->fig;delete temp->next;temp->next=n;while(temp!=0){temp=temp->next;if(temp!=0)temp->number--;}return t;}

////void del(){int j;cout<<"\nEnter figure to delete!\n";
////		cin>>j;list *n,*temp;
////		if((temp=find_num(j-1))==0)
////		{cout<<"\nNo such a figure\n";return;}
////		if(temp->next==0){cout<<"\nNo such a figure\n";return;}
////		n=temp->next->next;
////		temp->next->next=0;
//	//	figure *t=temp->next->fig;
//	//	delete temp->next;
//	//	delete t;temp->next=n;
//	//	while(temp!=0)
//	//	{temp=temp->next;if(temp!=0)temp->number--;}}
//
//
//
void list:: change(){cout<<endl;list *tempor;
tempor=this->next;
if (tempor==0){cout<<"\nThe list is empty\n";return;}
cout<<"Enter number of the figure you whant to change\n";
int i;cin>>i;if((tempor=find_num(i))==0)
{cout<<"\nNo such a figure\n";return;};tempor->fig->change();}

void list:: out(){cout<<endl;list *t;t=this->next;if (t==0){cout<<"\nThe list is empty\n";return;}while(t!=0){cout<<"\nNumber "<<t->number;t->fig->infa();cout<<endl;t=t->next;}}
void list::out(ecran &P){cout<<endl;list *t;t=this->next;if (t==0){return;}while(t!=0){t->fig->print(P);t=t->next;}}
void list::fill_all(){list *t;t=this->next;while(t!=0){t->fig->fill_all();t=t->next;}}
void list::unfill_all(){list *t;t=this->next;while(t!=0){t->fig->unfill_all();t=t->next;}}
void list::inv_all(){list *t;t=this->next;while(t!=0){t->fig->inverse();t=t->next;}}
void list::turn_all(coord c,float f){list *t;t=this->next;while(t!=0){t->fig->turn(c,f);t=t->next;}}
void list::ch_colour_all(char r){list *t;t=this->next;while(t!=0){t->fig->colour_ch(r);t=t->next;}}
void list::shift_all(int x,int y){list *t;t=this->next;while(t!=0){t->fig->shift(x,y);t=t->next;}}


complex_fig::complex_fig(){name="Complex figure";}

class Cinterface{
list l;
public:
void vibor (class ecran &ecr)
{int dejstvie;
while(1==1){
cout<<"\nChoose the action:\n1- Print the picture\n2- Add figures \n3- Save picture \n4- Change the figure\n5- Figures in the list\n6- Delete the figure\n7- Print coordinates\n0- Exit the program\n"; 
cin>>dejstvie;
switch(dejstvie){
case 1://interf_list *tt;tt=this->next;ecr.clrscr();if (tt==0){cout<<"\nThe list is empty\n";break;}while(tt!=0){tt->fig->print(ecr);tt=tt->next;}ecr.out();break;
ecr.clrscr();l.out(ecr);ecr.out();break;
case 2:l.add();break;
case 3:ecr.save();break;
case 4://change
//cout<<endl;interf_list *tempor;tempor=this->next;if (tempor==0){cout<<"\nThe list is empty\n";break;}cout<<"Enter number of the figure you whant to change\n";int i;cin>>i;if((tempor=find_num(i))==0){cout<<"\nNo such a figure\n";break;};tempor->fig->change();break;
l.change();break;
case 5://cout<<endl;interf_list *t;t=this->next;if (t==0){cout<<"\nThe list is empty\n";break;}while(t!=0){cout<<"\nNumber "<<t->number;t->fig->infa();cout<<endl;t=t->next;}break;
//out
l.out();break;
case 6:
int j;cout<<"\nEnter figure to delete!\n";cin>>j;figure *f;
f=l.delete_l(j);if(!f) delete f;break;
case 7:ecr.out_koord();break;
case 0:return;

default:cout<<"\nChoose the right number\n";break;}}}
};



int main(int argc, char *argv[])
{ecran P(60,30);

Cinterface l;
l.vibor(P);
    system("PAUSE"); 
    return EXIT_SUCCESS;
}

