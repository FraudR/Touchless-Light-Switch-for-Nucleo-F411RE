#include "mbed.h" 
#include "TextLCD.h" 
AnalogIn ain(PA_0);
TextLCD lcd(PB_8, PC_8, PB_13, PB_14, PB_15, PB_1);  //LCD interfac
DigitalOut led2(LED2);
Serial pc(USBTX, USBRX); // tx, rx


int main() 
{   
    float voltage;
    int light=1;
    int count=0;
    
    while(1) 
    {  
        voltage= (ain*3.3);
        //if hand over switch
        if (voltage>=3.00){

            //wait until hand off
            while(voltage>3.00){
                pc.printf(" %0.2f V %d,\n",voltage,light);
                voltage= (ain*3.3);
                lcd.locate(0,1);
                lcd.printf("%0.2f V",voltage);               
            }
            
            //switch on
            if(light==0){
                light=1;
            }
            
            //switch off
            else if(light==1){
                light=0;
            }           
        }

        if(light==1){
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("Light ON");
            led2=1;
            lcd.locate(0,1);
            lcd.printf("%0.2f V",voltage);
            
            if(count==0){
                pc.printf(" %0.2f V %d,\n",voltage,light);
            }
        }

        if(light==0){
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("Light OFF");
            led2=0;
            lcd.locate(0,1);
            lcd.printf("%0.2f V",voltage);
            if(count==0){
                pc.printf(" %0.2f V %d,\n",voltage,light);
            }
        }
        

        wait(0.01) ;
        count++;
        if(count>15)
        {
            count=0;
        } 
        } 
}
 