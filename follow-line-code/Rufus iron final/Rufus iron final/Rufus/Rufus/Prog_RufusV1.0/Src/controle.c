/*
 * controle.c
 *
 *  Created on: 31 de mai de 2019
 *      Author: luis_
 */
#include "controle.h"
#include "gpio.h"
#include "adc.h"
#include "scanner.h"
#include "drive_TB66.h"




void posicao(void){
	float m;
	float d;
	get_sensor_calibrated();
	m = ((4*(sensor[7].calibrado-sensor[0].calibrado))+(3*(sensor[6].calibrado-sensor[1].calibrado))+(2*(sensor[5].calibrado-sensor[2].calibrado))+(1*(sensor[4].calibrado-sensor[3].calibrado)));
	d = (sensor[0].calibrado+sensor[1].calibrado+sensor[2].calibrado+sensor[3].calibrado+sensor[4].calibrado+sensor[5].calibrado+sensor[6].calibrado+sensor[7].calibrado);
	valor_posicao = - m/d;
	valor_posicao_anterior = valor_posicao;
}


void PID(void){
	P = valor_posicao;
	D = (valor_posicao - valor_posicao_anterior);
	I += (valor_posicao);
	PID_valor= (Kp*P)+(Kd*D)+(Ki*I);
}

