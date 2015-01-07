#include <avr/io.h>
#include<avr/interrupt.h>
#include<avr/iom16.h>
#include<math.h>
#pragma data:code
#define uch unsigned char


const uch table[]="Tao Lin and Tong Zhou";


	
	

void delay(unsigned int x)
{	
   TCNT0 = 55;          
   TCCR0 |=(1<<CS01);   
   for(int i=0;i<x*10;i++)         
   {	  
		while(!(TIFR & (1 << TOV0)));
        TCNT0 = 55;
   }
}	

void write_com(uch com)
{
       PORTC&=~(1<<7);   
	   PORTC&=~(1<<6);      
	   PORTA=com;
	   PORTC|=(1<<1);             
	   delay(1);
	   PORTC&=~(1<<1);        
}

void write_dat(uch dat)
{     
       PORTC|=(1<<7);
	   PORTC&=~(1<<6);
	   PORTA=dat;
	   PORTC|=(1<<1);
	   delay(1);
	   PORTC&=~(1<<1);

}

void INI_POTR(void)
{
	DDRC|=0xff;
	DDRA=0XFF;    
	PORTC&=~(1<<7);
}


unsigned char isKeyPress(void)	
{
	DDRB=0xff;       
	PORTB=0xf0;      
	DDRB=0x0f;       

	if(PINB==0xf0)   
	{
		DDRB=0xff;
		return 0;    
	}
	else             
	{
		DDRB=0xff;
		return 1;    
	}	

}

	
//identify the button's function
unsigned char keyPressed(void)
{
 	unsigned char i=0x7f,key,k; 
	delay(10);            
	if(isKeyPress())     
	{
		while(1)
		{
			 PORTB=i;
	 		 DDRB=0xf0;
			 key=PINB;
			 k=key&0x0f;
			 if(k!=0x0f)
			 {
			 	break;
			  }
			 i=(i>>1|i<<7);
			 if(i==0b11110111)
			 {
			 	i=0x7f;
             }
	    }

		switch(key)
		{
			case 0b11101110:
			key=1;
			break;
            case 0b11011110:
			key=5;
			break;
			case 0b10111110:
			key=9;
			break;
			case 0b01111110:
			key=12;
			break;
			case 0b11101101:
			key=2;
			break;
			case 0b11011101:
			key=6;
			break;
			case 0b10111101:
			key=0;
			break;
			case 0b01111101:
			key=13;
			break;
			case 0b11101011:
			key=3;
			break;
			case 0b11011011:
			key=7;
			break;
			case 0b10111011:
			key=10;
			break;
			case 0b01111011:
			key=14;
			break;
			case 0b11100111:
			key=4;
			break;
			case 0b11010111:
			key=8;
			break;
			case 0b10110111:
			key=11;
			break;
			case 0b01110111:
			key=15;
			break;
		}		       
	}
	else
	{
		key=16;
	}
	return key;
}

unsigned int music_l[7]={131,147,165,175,196,220,247};
unsigned int music_h[7]={524,588,660,698,784,880,988};
unsigned int music_c[7]={262,294,330,349,392,440,494};

unsigned int music[7]={262,294,330,349,392,440,494};
unsigned int music_p[][2];

unsigned int shiyin[][2]=           //试音。从L的最低音到H的最高音。展现全部音域。
{
	{131,500},{147,500},{165,500},{175,500},{196,500},{220,500},{247,500},
	{262,400},{294,400},{330,400},{349,400},{392,400},{440,400},{494,400},
	{524,400},{588,400},{660,400},{698,400},{784,400},{880,400},{988,400}
};

unsigned int mamahao [][2]=          			//世上只有妈妈好
{
  {440,750},{392,250},{330,500},{392,500},{524,500},{440,250},{392,250},
  {440,1000},{330,500},{392,250},{440,250},{392,500},{330,250},{294,250},
  {262,250},{220,250},{392,250},{330,250},{294,1000},{294,750},{330,250},
  {392,500},{392,250},{440,250},{330,750},{294,250},{262,1000},{394,750},
  {330,250},{294,250},{262,250},{220,250},{262,250},{196,1000},{0,0}
} ; 

unsigned int super_mario[][2]=            //超级玛丽奥歌曲。
{
{659,200},{659,200},{0,200},{659,200},{0,200},{523,200},{659,200},{0,200},
{784,400},{0,400},{392,400},{0,400},{523,200},{0,400},{392,400},{0,400},
{330,200},{0,400},{440,200},{0,200},{494,200},{0,200},{466,200},{440,200},
{0,200},{392,266},{659,266},{784,266},{880,200},{0,200},{698,200},{784,200},
{0,200},{659,200},{0,200},{523,200},{587,200},{494,200},{0,400},{523,200},
{0,400},{392,400},{0,400},{330,200},{0,400},{440,200},{0,200},{494,200},
{0,200},{466,200},{440,200},{0,200},{392,266}

};

unsigned int two_tigers[][2]=					//两只老虎
{
  {262,500},{294,500},{330,500},{262,500},{262,500},{294,500},{330,500},{262,500},
  {330,500},{349,500},{392,1000},{330,500},{349,500},{392,1000},{392,375},{440,125},
  {392,375},{349,125},{330,500},{262,500},{392,375},{440,125},{392,375},{349,125},
  {330,500},{262,500},{294,500},{196,500},{262,1000},{294,500},{196,500},{262,1000},{0,0}

};

unsigned int TiankongZC[][2]=					//天空之城
{
 {440,500},{494,500},{524,1500},{494,500},{524,1000},{660,1000},{494,3000},
 {330,500},{330,500},{440,1500},{392,500},{440,1000},{524,1000},{392,2000},
 {0,1000},{330,500},{330,500},{349,1500},{330,500},{349,500},{524,1500},
 {330,2000},{0,500},{524,500},{524,500},{524,500},{494,1500},{349,500},
 {349,1000},{494,1000},{494,2000},{0,1000},{440,500},{494,500},{524,1500},
 {494,500},{524,1000},{660,1000},{494,2000},{0,1000},{330,500},{330,500},
 {440,1500},{392,500},{440,1000},{524,1000},{392,3000},{0,500},{330,500},
 {349,1000},{524,500},{494,500},{494,1000},{524,1000},{588,500},{588,500},
 {660,500},{524,1000},{0,1000},{524,1000},{494,500},{440,500},{440,500},
 {494,1000},{392,1000},{0,0}
 };

void main(void)
{
	INI_POTR();	           //必须启动！
	write_com(0X38);      
	write_com(0X01);        
	write_com(0X0f);         
	write_com(0X06);
	write_com(0X80+0X02); 
	for(char i=0;i<8;i++)
	  {
		write_dat(table[i]);		
	  }
	write_com(0X80+0X11);
	delay(5);

    int k=0;//获取键值
    int last=0;
	int next=0;
	int j=0;
	int m1=0;//录入音符数
    int m2=0;
    int m3=0;
	while(1)
	{
		if(j)
		{m3++;}
		if(isKeyPress())
		{
			k=keyPressed();//获取按下的键值

			if(k==8)  
            {
				
				for(int i=0;i<7;i++) 
				{
					music[i]=music_l[i];
				}
			}

            else if(k==9)  //按下9变为中音
            {
				
				for(int i=0;i<7;i++) 
				{
					music[i]=music_c[i];
				}
			}

			else if(k==0) //按下0变为高音
            {
				
				for(int i=0;i<7;i++) 
				{
					music[i]=music_h[i];
				}
			}
			else if(k==10) //按B播放示范音乐
			{  
			    while(1)
			   {
			  	k=keyPressed();//获取按下的键值
				if(k==1||last==1||next==1)
				{
				    for( int i=0;i<21;i++)
					{
						k=keyPressed();
						if(k==12)
						{break;}
                        else if(k==11)
						{break;last=k-1;}
						else if(k==13)
						{break;next=k+1;}
						else if(shiyin[i][0]!=0)
						{
							DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
							TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
						    TCCR1B=0x09;
							OCR1A=(500000/shiyin[i][0]-1); //设置使得输出频率

						}
						else{
							DDRD&=~0x30;   
						}
						delay(shiyin[i][1]);
					}
					DDRD &= ~0x30;	
					break;	
				}
				else if(k==2||last==2||next==2)//按1播放世上只有妈妈好
				 {
					for(int i=0;i<34;i++)
					{
						k=keyPressed();
						if(k==12)
						{break;}
                        else if(k==11)
						{break;last=k-1;}
						else if(k==13)
						{break;next=k+1;}

						else if(mamahao[i][0]!=0)
						{
						DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
						TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
					    TCCR1B=0x09;
						OCR1A=(500000/mamahao[i][0]-1); //设置使得输出频率
						}
						else{
							DDRD&=~0x30;   
						}
						delay(mamahao[i][1]);
					}
                    DDRD &= ~0x30;
					break;	
				 }
				else if(k==3||last==3||next==3)//按2播放超级玛丽奥
				{
					for(int i=0;i<53;i++)
					{
						k=keyPressed();
					    if(k==12)
						{break;}
                        else if(k==11)
						{break;last=k-1;}
						else if(k==13)
						{break;next=k+1;}

						else if(super_mario[i][0]!=0)
						{
						DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
						TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
					    TCCR1B=0x09;
						OCR1A=(500000/super_mario[i][0]-1); //设置使得输出频率

						}
						else{
							DDRD&=~0x30;   //设置PD4和PD5为输入
						}
						delay(super_mario[i][1]);
					}
					DDRD &= ~0x30;
					break;
				}
				else if(k==4||last==4||next==4)//按2播放里两只老虎
				{
					for(int i=0;i<32;i++)
					{
						k=keyPressed();//获取按下的键值
						if(k==12)
						{break;}
                        else if(k==11)
						{break;last=k-1;}
						else if(k==13)
						{break;next=k+1;}

						else if(two_tigers[i][0]!=0)
						{
						DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
						TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
					    TCCR1B=0x09;
						OCR1A=(500000/two_tigers[i][0]-1); //设置使得输出频率

						}
						else{
							DDRD&=~0x30;   //设置PD4和PD5为输入
						}
						delay(two_tigers[i][1]);//延时音长	
					}
					DDRD &= ~0x30;
					break;
				}
				else if(k==5||last==5||next==5)//按2播放里天空之城
				{
					for(int i=0;i<65;i++)
					{
						k=keyPressed();//获取按下的键值
						if(k==12)
						{break;}
                        else if(k==11)
						{break;last=k-1;}
						else if(k==13)
						{break;next=k+1;}

						else if(TiankongZC[i][0]!=0)
						{
						DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
						TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
					    TCCR1B=0x09;
						OCR1A=(500000/TiankongZC[i][0]-1); //设置使得输出频率

						}
						else{
							DDRD&=~0x30;   //设置PD4和PD5为输入
						}
						delay(TiankongZC[i][1]);//延时音长	
					}
					DDRD &= ~0x30;
					break;
				}
               } 
			}
		
			else if(k==12)
			{
				DDRD=0x00;
			}
			else if(k==14)
			{
				j=1;
				for(int i=0;i<m1;i++)
				{
					music_p[i][0]=0;
					music_p[i][1]=0;
				}
				m1=0;

			}
			else if(k==15) //播放录入的音乐
			{
			
				if(m1!=0)
				{
					for(int i=0;i<m1;i++)
					{
						k=keyPressed();//获取按下的键值
						if(k==13)
						{break;}

						else if(music_p[i][0]!=0)
						{
						DDRD|=0x30;   //设置PD4和PD5为输出（PD4对应OC1B,PD5对应OC1A）
						TCCR1A=0x50;  //一下两个设置使得：无分频，计数上限ICR1，OC1B/OC1A电平取反
					    TCCR1B=0x09;
						OCR1A=(500000/music_p[i][0]-1); //设置使得输出频率

						}
						else{
							DDRD&=~0x30;   //设置PD4和PD5为输入
						}
						delay(music_p[i][1]);//延时音长	
					}
					DDRD &= ~0x30;
					j=0;
				}
			
			}
			else//播放按下的音符
			{
				while(isKeyPress())
				{
					DDRD|=0x30;
				    TCCR1A=0x50;
				    TCCR1B=0x09;
					OCR1A=(500000/music[k-1]-1);
					if(j)		 //开启录入模式后，将音乐存入RAM
					{    
						music_p[m1][0]=0;
						music_p[m1][1]=m3/7;
						music_p[m1+1][0]=music[k-1];
						m2=m2+2;
					 }
				}
				if(j)
				{
					 m3=0;
					 music_p[m1+1][1]=m2;
					 m1+=2;
					 m2=0;
				}
				DDRD&=~0x30;
			}

		}	
	}
}
	

	
	
	
	
