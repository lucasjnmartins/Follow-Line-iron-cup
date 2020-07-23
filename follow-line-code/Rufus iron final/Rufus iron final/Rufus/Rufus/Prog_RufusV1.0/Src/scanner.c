/*
 * scanner.c
 *
 *  Created on: 31 de mai de 2019
 *      Author: luis_
 */
#include "scanner.h"
#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "drive_TB66.h"
#include "stm32f0xx_it.h"
volatile int i = 0;
volatile int j = 0;
volatile int k = 0;

void leitura_adc() {
	for (i = 0; i < 8; i++) {
		sensor[i].valor = adc_valor[i];
	}
}

void inicia_scanner() {
	leitura_adc(); //ler o primeiro valor analogico
	for (j = 0; j < 8; j++) { //registrar os primeiros valores na estrutura
		sensor[j].valor_minimo = 400; //valor minimo é a primeira leitura do sensor
		sensor[j].valor_maximo = 2300; //valor maximo é a primeira leitura do sensor
		sensor[j].valor_linha_branca = 260; //valor da linha branca para cada sensor
	}
}
void scanner() {
	for (j = 0; j < 8; j++) {
		if (adc_valor[j] > sensor[j].valor_maximo) {
			sensor[j].valor_maximo = adc_valor[j];
		}
		if (adc_valor[j] < sensor[j].valor_minimo) {
			sensor[j].valor_minimo = adc_valor[j];
		}
	}
	for (i = 0; i < 8; i++) {
		sensor[i].media =
				((sensor[i].valor_maximo - sensor[i].valor_minimo) / 2);
	}
}

void get_sensor_calibrated(void) {
	int i;
	for (i = 0; i < 8; i++) {
		sensor[i].calibrado = adc_valor[i];
		if (sensor[i].calibrado >= sensor[i].media) {
			sensor[i].calibrado = 3000;
		} else {
			sensor[i].calibrado = adc_valor[i];
		}
	}
}
