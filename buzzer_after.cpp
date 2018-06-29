//BEEP TYPE FOR API LIB
#define BEEP_NO			0x01
#define BEEP_OK			0x02
#define BEEP_ERROR		0x04
#define BEEP_KEY		0x08
#define BEEP_START		0x10
#define BEEP_NO			0x20

//BEEP COUNT VALUE FOR API LIB
#define BUZZ_OK_HIGH_CNT	80
#define BUZZ_OK_LOW_CNT		5
#define BUZZ_ERROR_HIGH_CNT	100
#define BUZZ_ERROR_LOW_CNT	10
#define BUZZ_KEY_HIGH_CNT	80
#define BUZZ_KEY_LOW_CNT	0
#define BUZZ_START_HIGH_CNT	100
#define BUZZ_START_LOW_CNT	0

//BUZZER TYPE FOR DRIVER API
#define BUZZ_HIGT		1
#define BUZZ_MIDDLE		4
#define BUZZ_LOW		7
#define BUZZ_ADD_SLEEP	10

#define MSEC			1
#define SEC				1000

#define USE_ONE_TIME	1
#define USE_TWO_TIME	2


/*******************************************************************************
* Function              : ApiBuzzer
* Argument              : 
                          unsigned int BuzzerType : type of buzzer by tone.
						  unsigned int BuzzerCnt  : count of playing buzzer.
						  unsigned int BuzzerOn   : high signal cnt in 1 perriod.(PWM)
						  unsigned int BuzzerOff  : low signal cnt in 1 perriod.(PWM)
* Return                : None
* Description           : Play buzzer by BuzzerType. And buzz for Buzzer times. BuzzerOn and BuzzerOff means msec in 1 perriod. 
* Example               : ApiBuzzer(BUZZ_HIGT, 2, 80, 5);
*******************************************************************************/

void ApiBuzzer(unsigned int BuzzerType, unsigned int BuzzerCnt, unsigned int BuzzerOn, unsigned int BuzzerOff)
{
    struct buzzer_param buzzer;

    buzzer.BuzzerType = BuzzerType;
    buzzer.count = BuzzerCnt;
    buzzer.mson = BuzzerOn;
    buzzer.msoff = BuzzerOff;

    if (ioctl(fd_buzzer, BUZZER_TONE, &buzzer) < 0)
    {
        return;
    }
    usleep((BuzzerOn+BUZZ_ADD_SLEEP)*SEC);   // Magic Number 를 디파인 해주세요.
}

/*******************************************************************************
* Function              : dev_BEEP_play_sound
* Argument              : 
                          BYTE nBeeptype : type of buzzer.
* Return                : None
* Description           : Play buzzer by nBeeptype. 
* Example               : dev_BEEP_play_sound(BEEP_OK);
*******************************************************************************/
// 함수명 을 Camel Case, UnderBar 통일
// -> 고객사에서 함수 네이밍 지정.
void dev_BEEP_play_sound (BYTE nBeeptype)
{
    if ( deviceSetting.use_beep == FALSE )
        return ;          // Return 문 말고 블럭으로 처리해주세요
                          // -> 가독성의 이유로 그대로 작성합니다.
    
    switch( nBeeptype)
    {
		case BEEP_NO:
			break;
		case BEEP_OK:
			ApiBuzzer(BUZZ_HIGT, USE_TWO_TIME, BUZZ_OK_HIGH_CNT, BUZZ_OK_LOW_CNT);
			break;
		case BEEP_ERROR:
			ApiBuzzer(BUZZ_LOW, USE_TWO_TIME, BUZZ_ERROR_HIGH_CNT, BUZZ_ERROR_LOW_CNT);
			break;
		case BEEP_KEY:
			ApiBuzzer(BUZZ_MIDDLE, USE_ONE_TIME, BUZZ_KEY_HIGH_CNT, BUZZ_KEY_LOW_CNT);
			break;
		case BEEP_START:
			ApiBuzzer(BUZZ_HIGT, USE_ONE_TIME, BUZZ_START_HIGH_CNT, BUZZ_START_LOW_CNT);
			ApiBuzzer(BUZZ_MIDDLE, USE_ONE_TIME, BUZZ_START_HIGH_CNT, BUZZ_START_LOW_CNT);
			ApiBuzzer(BUZZ_LOW, USE_ONE_TIME, BUZZ_START_HIGH_CNT, BUZZ_START_LOW_CNT);
			break;
		default:
			break;
    }
}
