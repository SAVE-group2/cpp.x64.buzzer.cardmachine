/*******************************************************************************
* Function              : ApiBuzzer
* Argument              : None
* Return                : None
* Description           : 
* Example               : 
*******************************************************************************/

// 주석

// 함수명과 인수들이 어떤 역할을 하는지로 이름 변경
void ApiBuzzer(unsigned int type, unsigned int cnt, unsigned int on, unsigned int off)
{
    struct buzzer_param buzzer;

    buzzer.type = type;
    buzzer.count = cnt;
    buzzer.mson = on;
    buzzer.msoff = off;

    if (ioctl(fd_buzzer, BUZZER_TONE, &buzzer) < 0)
    {
        return;
    }
    usleep((on+10)*1000);   // Magic Number 를 디파인 해주세요.
}


// 함수명 을 Camel Case, UnderBar 통일
// BYTE 입력을 Enum 처리
// Legacy 코드로 될 확률이 높아요.  인터페이스를 명확하게 해주세요.

void dev_BEEP_play_sound (BYTE nBeeptype)
{
    unsigned int type=0;
    
    if ( use_beep == FALSE )
        return ;          // Return 문 말고 블럭으로 처리해주세요

    // 인덴트
    
    switch( nBeeptype)
    {
    case BEEP_NO:                   // break 처리  // indent
        return ;
    case BEEP_OK:
        ApiBuzzer( 1, 2, 80, 5);    // 각각의 항목의 의미
        break;
    case BEEP_ERROR:
        ApiBuzzer( 7, 2, 100, 10);
        break;
    case BEEP_KEY:
        ApiBuzzer( 4, 1, 80, 0);
        break;
    case BEEP_START:
        ApiBuzzer(1, 1, 100, 0);
        ApiBuzzer(4, 1, 100, 0);
        ApiBuzzer(7, 1, 100, 0);
        break;
    }
}
