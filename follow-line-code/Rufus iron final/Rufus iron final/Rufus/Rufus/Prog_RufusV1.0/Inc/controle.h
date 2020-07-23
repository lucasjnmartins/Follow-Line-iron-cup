/*
 * controle.h
 *
 *  Created on: 31 de mai de 2019
 *      Author: luis_
 */

#ifndef CONTROLE_H_
#define CONTROLE_H_

//velocidade 40, kp 16, kd 2,ki 0.2  ;;  vcurva= 45 kp=28 kd=1.948 ki=0.112 (curva)  ;; vreta=70 kp=18 kd=0.32 ki=0.112; vel=25 kp=28,kd=1.867; ki=0.001
#define Kp 32//Kp_Recebido //16,9~~17.5 valores do coeficiente proporcional (Kp) 16   28
#define Kd 2//Kd_Recebido//valores do coeficiente derivativo (Kd) 2  1.425
#define Ki 0//Ki_Recebido //valores do coeficiente integrativo (Ki) 0.1

volatile float P,D,I;
volatile float PID_valor;

volatile float valor_posicao;
volatile float valor_posicao_anterior;
void posicao(void);
void PID(void);


#endif /* CONTROLE_H_ */
