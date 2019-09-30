/* ���: osccal.c
 * �����: Christian Starkjohann
 * �������: microsin.ru 
 * ���� ��������: 2008-04-10
 * ���������: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * ��������: GNU GPL v2 (��. License.txt) ��� ������������� (CommercialLicense.txt)
 * �������: $Id: osccal.c 553 2008-04-17 19:00:20Z cs $
 */

#include <avr/io.h>

/* ------------------------------------------------------------------------- */
/* -------------------- ���������� ��������� ���������� -------------------- */
/* ------------------------------------------------------------------------- */

/* ������� ��������� RC-���������. ��� ������� �������� ������� ������� - 
 *  ������ SOF, Start Of Frame (���� ��� SE0), ������������� ������ �����������
 *  ����� ����� ��������� USB RESET. �� ������� ������ �������� ����� ��������
 *  OSCCAL, � ����� ������������ ��� �������� ������� �������� ��������.
 *  ���� �������� ����� ����� �������������� ��� ���������� RC-���������� ��������
 *  �� 12 MHz (�� ����������� ����, ����� ������� ��� ������� ����� ������������ 
 *  ����� �� ���� AVR), �� ��� ������� ��� ������������ �������� OSCCAL � ����������� 
 *  �������� ��� ������ �� 12 ���! ����������� RC-���������, ������������� �� 12 ���
 *  ������ ��� �������������!
 */
void    calibrateOscillator(void)
{
uchar       step = 128;
uchar       trialValue = 0, optimumValue;
int         x, optimumDev, targetValue = (unsigned)(1499 * (double)F_CPU / 10.5e6 + 0.5);

    /* ������ �������� �����: */
    do{
        OSCCAL = trialValue + step;
        x = usbMeasureFrameLength();    /* ��������������� ������� �������� ������� */
        if(x < targetValue)             /* ������� ��� ������� ������ */
            trialValue += step;
        step >>= 1;
    }while(step > 0);
    /* ����� �� ����� �������� +/- 1 �� ������������ OSCCAL */
    /*  ������ ���� �������� �������� ��� ����������� �������� */
    optimumValue = trialValue;
    optimumDev = x; /* ��� ������� ����� ������ �� �������� */
    for(OSCCAL = trialValue - 1; OSCCAL <= trialValue + 1; OSCCAL++){
        x = usbMeasureFrameLength() - targetValue;
        if(x < 0)
            x = -x;
        if(x < optimumDev){
            optimumDev = x;
            optimumValue = OSCCAL;
        }
    }
    OSCCAL = optimumValue;
}
/*
���������: ���� �������� ���������� ���� �������� ���������� ����� ��������� 
�������� OSCCAL �� 192, ���� ���� ����������� �������� ������ ������ 192. 
����� �������, ����� ���� ��������� ���������� �������� ������� CPU � ����������� 
� ������������� ��������! �� ������ �������� ���� �������� ������ ����� ������
���������� �� ������ �������, ���� �� ������ �������������� ����������� ���,
��������, ������������ ������� CPU.
��� RC-����������� ������ 5.x (� ������� �������� ����������� ������ �� 2x128 
�����, �������� ATTiny25, ATTiny45, ATTiny85), ����� ���� ������� ������ ������� 
� ����� ��������.
*/