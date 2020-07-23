/*
 * scanner.h
 *
 *  Created on: 31 de mai de 2019
 *      Author: luis_
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include "main.h"

volatile uint16_t adc_valor[8];

typedef struct sensores{
	volatile uint16_t valor;
	volatile uint16_t valor_linha_branca;
	volatile uint16_t calibrado;
	volatile uint16_t valor_maximo;
	volatile uint16_t valor_minimo;
	volatile uint16_t media;

} sensores;
sensores sensor[8];
void get_sensor_calibrated (void);
void leitura_adc(void);
void inicia_scanner(void); //define maior e menor valor adc inicial
void scanner(); //define os maiores e menores valores em geral
void linha_branca(void);
#endif /* SCANNER_H_ */
