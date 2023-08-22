#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macrosAndGlobalVar.h"
#include "openSpi.h"
#include "mmc_SPIsoft.h"
#include "GLCD_driver.h"
#include "GLCD_graphics.h"
#include "funciones_RS232.h"


void mmc_init()
{
    char i = 0;
    char j = 0;
    char escribir[60];
    int time_out;
    char response = 0xFF;
    char versionMmc = 5;
   
    for(i=0; i<=10;i++)
        WriteChar_SPI(0xFF);            // dummy clock
    
    ChipSelect = 0;
    __delay_us(2);
    for(j=0;j<=10;j++){
        command_mmc(CMD0, 0x00, 0x00, 0x00, 0x00);           //comando 0
        time_out = 0x0F;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta
            time_out--;
//            sprintf(escribir, "Respuesta actual: %d\r\nTime out: %d", response, time_out);
//            glcd_text57(0, LINE_1, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, LINE_1, escribir, 1, OFF);
//            __delay_ms(100);
        }while(response != 0x01 && time_out > 0);
        if(time_out == 0){
//            sprintf(escribir, "   Enviando CMD0\r\n   respuesta: %d\r\n    intento: %d", response, j);
//            glcd_text57(0, 6, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, 6, escribir, 1, OFF);
            
        }
        if(response == 0x01){
//            sprintf(escribir, "Comando %d EXITO\r\nrespuesta final: %d",CMD0,  response);
//            glcd_text57(0, LINE_1, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, LINE_1, escribir, 1, OFF);
//            __delay_ms(600);            
            break;
        }
        __delay_ms(500);
    }
    
    for(i=0; i<=4;i++)
        WriteChar_SPI(0xFF);  // 4 clocks de espera   
    
//////// comando 08
    response = 0xFF;
    for(j=0;j<=3;j++){
        command_mmc(CMD_08, 0x00, 0x00, 0x01, 0xAA);    //comando CMD8
        time_out = 16;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta 0x01
            time_out--;
        }while(response != 0x01 && time_out > 0);
        if(response == 0x01){
            do{
                response = WriteChar_SPI(0xFF);     //espero respuesta
                time_out--;
            }while(response != 0xAA && time_out > 0);          
        }
        if(response == 0xAA){
            versionMmc = 2;
            break;  
        }
        if(time_out == 0){
//            sprintf(escribir, "Enviando CMD8\r\nRespuesta: %d\r\nIntento: %d", response, j);
//            glcd_text57(0, LINE_1, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, LINE_1, escribir, 1, OFF);
//            __delay_ms(500);
        }
    }
    if(versionMmc == 2){
        strcpy(escribir, "Envio CMD1");
        glcd_text57(0, LINE_1, escribir, 1, ON);
        glcd_update();
        ////// comando 1
        for(i=0; i<=4;i++)
            WriteChar_SPI(0xFF);  // 4 clocks de espera 
        response = 0xFF;
        for(j=0;j<=20;j++){
            command_mmc(CMD1, 0x40, 0x00, 0x00, 0x00);    //comando 1 para SDHC
            time_out = 5;
            do{
                response = WriteChar_SPI(0xFF);     //espero respuesta
                time_out--;
//                sprintf(escribir, "Respuesta actual: %d\r\nTime out: %d\r\nIntento: %d", response, time_out, j);
//                glcd_text57(0, LINE_3, escribir, 1, ON);
//                glcd_update();
//                glcd_text57(0, LINE_3, escribir, 1, OFF);
                __delay_ms(1);
            }while(response != 0x00 && time_out > 0);
            if(response == 0x00){
//                glcd_fillScreen(OFF);
//                strcpy(escribir, "  Memoria Iniciada\r\n Sastifactoriamente");
//                glcd_text57(0, LINE_1, escribir, 1, ON);
//                glcd_update();
//                __delay_ms(300);
                break;
            }
        }
    }
    else{// no es sd version 2.0
        for(j=0;j<=20;j++){
            command_mmc(CMD1, 0x00, 0x00, 0x00, 0x00);    //comando 1 para SD viejas
            time_out = 5;
            do{
                response = WriteChar_SPI(0xFF);     //espero respuesta
                time_out--;
//                sprintf(escribir, "Respuesta actual: %d\r\nTime out: %d\r\nIntento: %d", response, time_out, j);
//                glcd_text57(0, LINE_3, escribir, 1, ON);
//                glcd_update();
//                glcd_text57(0, LINE_3, escribir, 1, OFF);
//                __delay_ms(100);
            }while(response != 0x00 && time_out > 0);
            if(response == 0x00){
//                glcd_fillScreen(OFF);
//                strcpy(escribir, "  Memoria Iniciada\r\n Sastifactoriamente");
//                glcd_text57(0, LINE_1, escribir, 1, ON);
//                glcd_update();
//                __delay_ms(300);
                break;
            }
        }        
    }
    for(i=0; i<=4;i++)
        WriteChar_SPI(0xFF);  // 4 clocks de espera
    
//    glcd_fillScreen(OFF);
//    strcpy(escribir, "SET_BLOCK_LEN:");
//    glcd_text57(0, 0, escribir, 1, ON);
//    for(j=0;j<=20;j++){
//         command_mmc(SET_BLOCKLEN, 0x00, 0x00, 0x02, 0x00);
//         time_out = 16;
//         do{
//             response = WriteChar_SPI(0xFF);     //espero respuesta
//             time_out--;
//             sprintf(escribir, "Respuesta actual: %d\r\nTime out: %d\r\nIntento: %d", response, time_out, j);
//             glcd_text57(0, LINE_2, escribir, 1, ON);
//             glcd_update();
//             glcd_text57(0, LINE_2, escribir, 1, OFF);
//             __delay_ms(500);
//         }while(response != 0x00 && time_out > 0);
//         if(response == 0x00){
//             glcd_fillScreen(OFF);
//             strcpy(escribir, "  SET_BLOCK_LEN\r\n Sastifactoriamente");
//             glcd_text57(0, LINE_1, escribir, 1, ON);
//             glcd_update();
//             __delay_ms(500);
//             break;
//         }
//     }     

    ChipSelect = 1;
    __delay_us(1);
}

void Read_page(unsigned long dir)
{
    char k = 0;
//    char escribir[60];
    char time_out;
    char response;
    unsigned char dir1 = 0,dir2 = 0, dir3 = 0, dir4 = 0;

    dir4 = (unsigned char)(dir/0x01000000);
    dir3 = (unsigned char)(dir/0x010000);
    dir2 = (unsigned char)(dir/0x0100);
    dir1 = (unsigned char)(dir);
    
//    glcd_fillScreen(OFF);
//    sprintf(escribir, "dir: %02d %02d %02d %02d", dir4, dir3, dir2, dir1);
//    glcd_text57(0, LINE_1, escribir, 1, ON);
//    glcd_update();
//    __delay_ms(1500);
//    glcd_fillScreen(OFF);
    
    response = 0xFF;
    time_out = 0xFF;
    ChipSelect = 0;
    __delay_us(1000); 
 /////////////   

    for(k=0;k<5;k++){
        command_mmc(READ_MMC, dir4, dir3, dir2, dir1);
        time_out = 0x06;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta
            time_out--;
//            sprintf(escribir, "Respuesta: %d\r\nTime out: %d", response, time_out);
//            glcd_text57(0, LINE_1, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, LINE_1, escribir, 1, OFF);
            __delay_us(1);
        }while(response != 0x00 && time_out > 0);
        if(response == 0x00){
            break;
        }
    }   

    response = 0xFF;
///////////    
    for(k=0;k<10;k++){
        time_out = 0x06;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta
            time_out--;
//            sprintf(escribir, "Respuesta: %d\r\nTime out: %d", response, time_out);
//            glcd_text57(0, LINE_1, escribir, 1, ON);
//            glcd_update();
//            glcd_text57(0, LINE_1, escribir, 1, OFF);
            __delay_us(1);
        }while(response != 0xFE && time_out > 0);
        if(response == 0xFE){
            break;
        }
        if(k == 5){
            break;
        }
    } 
/// ********************* Bloque de lectura **********************/
    for(bufferSdCount = 0; bufferSdCount < 512; bufferSdCount++){
        bufferSd[bufferSdCount] = WriteChar_SPI(0xFF);     //recibe dato
    }
    ChipSelect = 1;
    __delay_us(1);
/// *************************************************************/
}
/******************************************************************************/
void Read_image_mmc(long int dir, char animation, char w1, char w2, char h1, char h2)
{

}


/******************************************************************************/
void Write_page(unsigned long dir, char clean)
{
//    char escribir[60];
    unsigned int time_out = 0x0F;
    char response = 0xFF;       //inicia el valor de respuesta
    unsigned char dir1 = 0,dir2 = 0 ,dir3 = 0, dir4 = 0;
    unsigned int k=0;
    
    dir4 = (unsigned char)(dir/0x01000000);
    dir3 = (unsigned char)(dir/0x010000);
    dir2 = (unsigned char)(dir/0x0100);
    dir1 = (unsigned char)(dir);
    
//    sprintf(escribir, "!", dir4, dir3, dir2, dir1);
//    glcd_text57(35, 2, "!", 1, ON);
//    glcd_update();
    __delay_ms(20);
    ChipSelect = 0;
    __delay_us(1);

    
    for(k=0;k<5;k++){
        command_mmc(WRITE_MMC, dir4, dir3, dir2, dir1);
        time_out = 0x08;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta
            time_out--;
            __delay_us(1);
        }while(response != 0x00 && time_out > 0);
        if(response == 0x00){
            break;
        }
    }
//    WriteChar_SPI(0xFF);
    WriteChar_SPI(0xFF);
    WriteChar_SPI(0xFE);    //notificacion enviaran los datos
/// ********************* Bloque de escritura **********************/
    if(!clean){
        for(k=0;k<512;k++){
            WriteChar_SPI(bufferSd[k]); 
        }
    }
    
/// ***************************************************************/   
    for(k=0;k<3;k++){
        time_out = 0x400;
        do{
            response = WriteChar_SPI(0xFF);     //espero respuesta
            time_out--;
        }while(response != 0xE5 && time_out > 0 && response != 0x05);
        if(response == 0xE5 || response != 0x05){
//            glcd_text57(35, 2, "!", 1, OFF);
//            glcd_update();
            break;
        }
    }
          //respuesta escritura OK
    ChipSelect = 1;
    __delay_us(1);
}
////////////////////////////////////////////////////////////////////////////////
void Write_image_mmc(long int dir)
{


}
///////////////////////////////////////////////////////////////////////////////
void command_mmc(char comd, char char1, char char2, char char3, char char4)
{
    switch(comd){
            case CMD0:
                WriteChar_SPI(0x40);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0x95);        // CRC
                break;
            case CMD1:
                WriteChar_SPI(0x41);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0xF9);
                break;
            case SET_BLOCKLEN:
                WriteChar_SPI(0x50);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0xFF);
                break;
            case READ_MMC:
                WriteChar_SPI(0x51);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0xFF);
                break;
            case WRITE_MMC:
                WriteChar_SPI(0x58);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0xFF);
                break;
            case CMD_08:
                WriteChar_SPI(0x48);
                WriteChar_SPI(char1);
                WriteChar_SPI(char2);
                WriteChar_SPI(char3);
                WriteChar_SPI(char4);
                WriteChar_SPI(0x87);
                break;
//            case CMD_77:
//                WriteChar_SPI(0x77);
//                WriteChar_SPI(char1);
//                WriteChar_SPI(char2);
//                WriteChar_SPI(char3);
//                WriteChar_SPI(char4);
//                WriteChar_SPI(0xFF);
//                break;
//            case CMD_69:
//                WriteChar_SPI(0x69);
//                WriteChar_SPI(char1);
//                WriteChar_SPI(char2);
//                WriteChar_SPI(char3);
//                WriteChar_SPI(char4);
//                WriteChar_SPI(0xFF);
//                break;
//            case 9:
//                WriteChar_SPI(0x49);
//                WriteChar_SPI(char1);
//                WriteChar_SPI(char2);
//                WriteChar_SPI(char3);
//                WriteChar_SPI(char4);
//                WriteChar_SPI(0xAF);
//                WriteChar_SPI(0xFF);
//                resp = WriteChar_SPI(0xFF);
//                break;
//            case 13:
//                WriteChar_SPI(0x4D);
//                WriteChar_SPI(char1);
//                WriteChar_SPI(char2);
//                WriteChar_SPI(char3);
//                WriteChar_SPI(char4);
//                WriteChar_SPI(0xFF);
//                WriteChar_SPI(0xFF);
//                resp = WriteChar_SPI(0xFF);
//                break;
    }
}

void Clean_block_mmc(unsigned long dir, unsigned long cant_char)
{

}


void wakeUpSD(){
    
 
}